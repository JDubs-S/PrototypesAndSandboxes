/* *****************************************************************************
 *
 * Copyright (C) 2014 Jason William Staiert. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, see <https://www.gnu.org/licenses>.
 *
 * Chagne Date        Description
 * -----------------------------------------------------------------------------
 * Aug 19, 2019 |---| added license notice
 *
 * ****************************************************************************/

#include <string.h>

#include "RotationAxis.h"
#include "Coordinates.h"
#include "IcosMap.h"
#include "Matrix.h"
#include "Memory.h"
#include "Vector.h"
#include "NumberGenerator.hpp"

////////////////////////////////////////////////////////////////////////////////
static const U8 ICOS_VERTEX_COUNT = 12u;

////////////////////////////////////////////////////////////////////////////////
//! The 20 faces of sphere are organized like:
//! /\/\/\/\/\
//! \/\/\/\/\/\
//!  \/\/\/\/\/
//! Rows run from from North (row 0) to South (row N). The first cell of each
//! row is the left most edge or vertex cell.
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//! The order of these vertices is important to the setup algorithm. Cells are
//! traversed from most northerly vertex traversing all cells at a given
//! latitude before traversing the cells in the next more southerly latitude.
////////////////////////////////////////////////////////////////////////////////
static const Coordinates::UnitSphereDegrees ICOS_VERTEX[ICOS_VERTEX_COUNT] = {
    { +90.0f,           0.0f }, //  0
    { +26.477362752,    0.0f }, //  1
    { +26.477362752,   72.0f }, //  2
    { +26.477362752,  144.0f }, //  3
    { +26.477362752,  216.0f }, //  4
    { +26.477362752,  288.0f }, //  5
    { -26.477362752,   36.0f }, //  6
    { -26.477362752,  108.0f }, //  7
    { -26.477362752,  180.0f }, //  8
    { -26.477362752,  252.0f }, //  9
    { -26.477362752,  324.0f }, // 10
    { -90.0f,           0.0f }, // 11
};

////////////////////////////////////////////////////////////////////////////////
struct IcosEdge
{
  U8 V1;
  U8 V2;
};

static const U8 ICOS_EDGE_COUNT = 30u;

////////////////////////////////////////////////////////////////////////////////
//! The order of these edges is important to the setup algorithm. Edges must be
//! in cell traversal order.
////////////////////////////////////////////////////////////////////////////////
static const IcosEdge ICOS_EDGE[ICOS_EDGE_COUNT] = {
    {  0u,  1u  }, //  0
    {  0u,  2u  }, //  1
    {  0u,  3u  }, //  2
    {  0u,  4u  }, //  3
    {  0u,  5u  }, //  4
    {  1u,  2u  }, //  5
    {  2u,  3u  }, //  6
    {  3u,  4u  }, //  7
    {  4u,  5u  }, //  8
    {  5u,  1u  }, //  9
    {  1u,  6u  }, //  10
    {  2u,  6u  }, //  11
    {  2u,  7u  }, //  12
    {  3u,  7u  }, //  13
    {  3u,  8u  }, //  14
    {  4u,  8u  }, //  15
    {  4u,  9u  }, //  16
    {  5u,  9u  }, //  17
    {  5u, 10u  }, //  18
    {  1u, 10u  }, //  19
    {  6u,  7u  }, //  20
    {  7u,  8u  }, //  21
    {  8u,  9u  }, //  22
    {  9u, 10u  }, //  23
    { 10u,  6u  }, //  24
    {  6u, 11u  }, //  25
    {  7u, 11u  }, //  26
    {  8u, 11u  }, //  27
    {  9u, 11u  }, //  28
    { 10u, 11u  }, //  29
};

////////////////////////////////////////////////////////////////////////////////
struct IcosFace
{
  U8 E1; // Edge ID of west edge.
  U8 E2; // Edge ID of east edge.
  bool Inverted; // True if face is /\, false if \/
};

static const U8 ICOS_FACE_COUNT = 20u;

////////////////////////////////////////////////////////////////////////////////
//! The order of these faces is important to the setup algorithm. Faces must be
//! in cell traversal order.
////////////////////////////////////////////////////////////////////////////////
static const IcosFace ICOS_FACE[ICOS_FACE_COUNT] = {
    {  0u,  1u, false  }, //  0
    {  1u,  2u, false  }, //  1
    {  2u,  3u, false  }, //  2
    {  3u,  4u, false  }, //  3
    {  4u,  0u, false  }, //  4
    { 10u, 11u, true   }, //  5
    { 11u, 12u, false  }, //  6
    { 12u, 13u, true   }, //  7
    { 13u, 14u, false  }, //  8
    { 14u, 15u, true   }, //  9
    { 15u, 16u, false  }, // 10
    { 16u, 17u, true   }, // 11
    { 17u, 18u, false  }, // 12
    { 18u, 19u, true   }, // 13
    { 19u, 10u, false  }, // 14
    { 25u, 26u, true   }, // 15
    { 26u, 27u, true   }, // 16
    { 27u, 28u, true   }, // 17
    { 28u, 29u, true   }, // 18
    { 29u, 25u, true   }, // 19
};

////////////////////////////////////////////////////////////////////////////////
IcosMap::IcosMap()
: Size(0u)
, CellCount(0u)
, ExpectedEdgeCellCount(0u)
, ExpectedFaceCellCount(0u)
, RowCount(0u)
{
  memset(VertexCell, 0, sizeof(VertexCell));
  memset(EdgeCellCount, 0, sizeof(EdgeCellCount));
  memset(EdgeCell, 0, sizeof(EdgeCell));
  memset(FaceCellCount, 0, sizeof(FaceCellCount));
  memset(FaceCell, 0, sizeof(FaceCell));
  memset(RowCellCount, 0, sizeof(RowCellCount));
  memset(RowCell, 0, sizeof(RowCell));
}

////////////////////////////////////////////////////////////////////////////////
IcosMap::~IcosMap()
{
}

////////////////////////////////////////////////////////////////////////////////
// (See IcosMap.h)
////////////////////////////////////////////////////////////////////////////////
void IcosMap::Initialize(U8 size) throw (Exception::Type)
{
  // Check parameters.
  if (size < MIN_SIZE || MAX_SIZE < size)
  {
    throw (Exception::PARAMETER_ERROR);
  }

  // Initialize member variables.
  Size = size;
  CellCount = 10u * Size * Size + 2u;
  ExpectedEdgeCellCount = Size - 1u;
  ExpectedFaceCellCount = ((Size - 2u) * (Size - 1u)) / 2;
  memset(VertexCell, 0, sizeof(VertexCell));
  memset(EdgeCellCount, 0, sizeof(EdgeCellCount));
  memset(EdgeCell, 0, sizeof(EdgeCell));
  memset(FaceCellCount, 0, sizeof(FaceCellCount));
  memset(FaceCell, 0, sizeof(FaceCell));

  RowCount = 3u * size + 1;
  memset(RowCellCount, 0, sizeof(RowCellCount));
  memset(RowCell, 0, sizeof(RowCell));

  for (U16 i = 0; i < MAX_CELL_COUNT; ++i)
  {
    Cell[i].Initialize();
  }

  // Initialize row cell count. Row cell counts follow this progression:
  // Size 1 :  1  5  5  1
  // Size 2 :  1  5 10 10 10  5  1
  // Size 3 :  1  5 10 15 15 15 15 10 5  1
  // Size 4 :  1  5 10 15 20 20 20 20 20 15 10  5  1
  for (U16 y = 0; y < RowCount; ++y)
  {
    U16 count;

    if (y == 0)
    {
      count = 1;
    }
    else if (y <= Size)
    {
      count = 5 * y;
    }
    else if (y <= (2 * Size))
    {
      count = 5 * Size;
    }
    else if (y < (RowCount - 1))
    {
      count = 5 * (RowCount - y - 1);
    }
    else
    {
      count = 1;
    }

    RowCellCount[y] = count;
  }

  // Initialize cell attributes and row cell arrays.
  U16 nextCellID = 0u;
  for (U16 y = 0; y < RowCount; ++y)
  {
    RowCell[y] = &Cell[nextCellID];

    for (U16 x = 0; x < RowCellCount[y]; ++x)
    {
      Cell[nextCellID].ID = nextCellID;
      Cell[nextCellID].X = x;
      Cell[nextCellID].Y = y;
      CalculateCellTypeAndTypeID(nextCellID); // Must not be called before X and Y are set.
      ++nextCellID;
    }
  }

  // Run initialization checks.
  CheckEdgeCellCounts();
  CheckFaceCellCounts();

  // Calculate longitude and latitude.
  CalculateLatitudeLongitudeForVertexCells();

  CalculateLatitudeLongitudeForEdgeCells(); // Must not be called before vertex cell latitude
                                            // and longitude have been calculated.
  CalculateLatitudeLongitudeForFaceCells(); // Must not be called before edge cell latitude
                                            // and longitude have been calculated.

  // Calculate adjacent cells.
  CalculateAdjacentCellsForVertexCells();
  CalculateAdjacentCellsForEdgeCells(); // Must not be called before adjacent cells for
                                        // vertex cells have been calculated.
  CalculateAdjacentCellsForFaceCells(); // Must not be called before adjacent cells for
                                        // vertex cells have been calculated.
}

////////////////////////////////////////////////////////////////////////////////
// (See IcosCell.h)
////////////////////////////////////////////////////////////////////////////////
U16 IcosMap::GetCellCount() const throw ()
{
  return CellCount;
}

////////////////////////////////////////////////////////////////////////////////
// (See IcosCell.h)
////////////////////////////////////////////////////////////////////////////////
U16 IcosMap::GetCellID(S16 x, U16 y) throw (Exception::Type)
{
  if (! (y < RowCount))
  {
    throw (Exception::PARAMETER_ERROR);
  }

  x = x % RowCellCount[y];

  if (x < 0) x = x + RowCellCount[y];

  return RowCell[y][x].ID;
}

////////////////////////////////////////////////////////////////////////////////
// (See IcosCell.h)
////////////////////////////////////////////////////////////////////////////////
U16 IcosMap::GetCellType(U16 x, U16 y) throw (Exception::Type)
{
  if (! ((y < RowCount) && (x < RowCellCount[y])) )
  {
    throw (Exception::PARAMETER_ERROR);
  }

  return RowCell[y][x].Type;
}

////////////////////////////////////////////////////////////////////////////////
// (See IcosCell.h)
////////////////////////////////////////////////////////////////////////////////
U16 IcosMap::GetCellTypeID(U16 x, U16 y) throw (Exception::Type)
{
  if (! ((y < RowCount) && (x < RowCellCount[y])) )
  {
    throw (Exception::PARAMETER_ERROR);
  }

  return RowCell[y][x].TypeID;
}

////////////////////////////////////////////////////////////////////////////////
// (See IcosCell.h)
////////////////////////////////////////////////////////////////////////////////
Coordinates::UnitSphereDegrees
IcosMap::GetCoordinates(
    U16 x,
    U16 y
    ) throw (Exception::Type)
{
  if (! ((y < RowCount) && (x < RowCellCount[y])) )
  {
    throw (Exception::PARAMETER_ERROR);
  }

  return RowCell[y][x].Coordinates;
}

void
IcosMap::GetAdjacentCellIDs(
    const U16 x,
    const U16 y,
    AdjacentCellIterator & iterator
    ) const throw (Exception::Type)
{
  if (! ((y < RowCount) && (x < RowCellCount[y])) )
  {
    throw (Exception::PARAMETER_ERROR);
  }

  iterator.CellID = RowCell[y][x].ID;
  iterator.CurrentIndex = 0u;
  iterator.AdjacentCellCount = RowCell[y][x].AdjacentCount;
  Memory_Copy(RowCell[y][x].AdjacentID, iterator.AdjacentCellID);
}

////////////////////////////////////////////////////////////////////////////////
//! Add cell cellID to vertex vertexID.
////////////////////////////////////////////////////////////////////////////////
void IcosMap::AddVertexCellID(U16 vertexID, U16 cellID) throw ()
{
  VertexCell[vertexID] = cellID;
}

////////////////////////////////////////////////////////////////////////////////
//! Add cell cellID to edge edgeID.
////////////////////////////////////////////////////////////////////////////////
void IcosMap::AddEdgeCellID(U16 edgeID, U16 cellID) throw ()
{
  EdgeCell[edgeID][EdgeCellCount[edgeID]] = cellID;
  EdgeCellCount[edgeID]++;
}

////////////////////////////////////////////////////////////////////////////////
//! Add cell cellID to face faceID.
////////////////////////////////////////////////////////////////////////////////
void IcosMap::AddFaceCellID(U16 faceID, U16 cellID) throw ()
{
  FaceCell[faceID][FaceCellCount[faceID]] = cellID;
  FaceCellCount[faceID]++;
}

////////////////////////////////////////////////////////////////////////////////
//! Calculates the cell type and vertex, edge, or face it belongs to. Must not
//! be called before cell X and Y attributes are initialized.
////////////////////////////////////////////////////////////////////////////////
void IcosMap::CalculateCellTypeAndTypeID(U16 cellID) throw ()
{
  U16 x = Cell[cellID].X;
  U16 y = Cell[cellID].Y;

  U16 cellType = IcosCell::TYPE_NONE;
  U16 cellTypeID = 0u;

  if (y == 0)
  {
    cellType = IcosCell::TYPE_VERTEX;
    cellTypeID = 0;
  }
  else if (y < Size)
  {
    if ((x % y) == 0)
    {
      cellType = IcosCell::TYPE_EDGE;
    }
    else
    {
      cellType = IcosCell::TYPE_FACE;
    }
    cellTypeID = (x / y);
  }
  else if (y == Size)
  {
    if ((x % Size) == 0)
    {
      cellType = IcosCell::TYPE_VERTEX;
      cellTypeID = 1;
    }
    else
    {
      cellType = IcosCell::TYPE_EDGE;
      cellTypeID = 5;
    }
    cellTypeID += (x / Size);
  }
  else if (y < (2 * Size))
  {
    U8 even = (2 * Size) - y;
    U8 odd = y - Size;
    U8 nextEdge = 0;
    if (x == nextEdge)
    {
      cellType = IcosCell::TYPE_EDGE;
      cellTypeID = 10;
    }
    else if (x < (nextEdge += even))
    {
      cellType = IcosCell::TYPE_FACE;
      cellTypeID = 5;
    }
    else if (x == nextEdge)
    {
      cellType = IcosCell::TYPE_EDGE;
      cellTypeID = 11;
    }
    else if (x < (nextEdge += odd))
    {
      cellType = IcosCell::TYPE_FACE;
      cellTypeID = 6;
    }
    else if (x == nextEdge)
    {
      cellType = IcosCell::TYPE_EDGE;
      cellTypeID = 12;
    }
    else if (x < (nextEdge += even))
    {
      cellType = IcosCell::TYPE_FACE;
      cellTypeID = 7;
    }
    else if (x == nextEdge)
    {
      cellType = IcosCell::TYPE_EDGE;
      cellTypeID = 13;
    }
    else if (x < (nextEdge += odd))
    {
      cellType = IcosCell::TYPE_FACE;
      cellTypeID = 8;
    }
    else if (x == nextEdge)
    {
      cellType = IcosCell::TYPE_EDGE;
      cellTypeID = 14;
    }
    else if (x < (nextEdge += even))
    {
      cellType = IcosCell::TYPE_FACE;
      cellTypeID = 9;
    }
    else if (x == nextEdge)
    {
      cellType = IcosCell::TYPE_EDGE;
      cellTypeID = 15;
    }
    else if (x < (nextEdge += odd))
    {
      cellType = IcosCell::TYPE_FACE;
      cellTypeID = 10;
    }
    else if (x == nextEdge)
    {
      cellType = IcosCell::TYPE_EDGE;
      cellTypeID = 16;
    }
    else if (x < (nextEdge += even))
    {
      cellType = IcosCell::TYPE_FACE;
      cellTypeID = 11;
    }
    else if (x == nextEdge)
    {
      cellType = IcosCell::TYPE_EDGE;
      cellTypeID = 17;
    }
    else if (x < (nextEdge += odd))
    {
      cellType = IcosCell::TYPE_FACE;
      cellTypeID = 12;
    }
    else if (x == nextEdge)
    {
      cellType = IcosCell::TYPE_EDGE;
      cellTypeID = 18;
    }
    else if (x < (nextEdge += even))
    {
      cellType = IcosCell::TYPE_FACE;
      cellTypeID = 13;
    }
    else if (x == nextEdge)
    {
      cellType = IcosCell::TYPE_EDGE;
      cellTypeID = 19;
    }
    else
    {
      cellType = IcosCell::TYPE_FACE;
      cellTypeID = 14;
    }
  }
  else if (y == (2 * Size))
  {
    if ((x % Size) == 0)
    {
      cellType = IcosCell::TYPE_VERTEX;
      cellTypeID = 6;
    }
    else
    {
      cellType = IcosCell::TYPE_EDGE;
      cellTypeID = 20;
    }
    cellTypeID += (x / Size);
  }
  else if (y < (RowCount - 1))
  {
    if ((x % (RowCount - y - 1)) == 0)
    {
      cellType = IcosCell::TYPE_EDGE;
      cellTypeID = 25;
    }
    else
    {
      cellType = IcosCell::TYPE_FACE;
      cellTypeID = 15;
    }
    cellTypeID += (x / (RowCount - y - 1));
  }
  else
  {
    cellType = IcosCell::TYPE_VERTEX;
    cellTypeID = 11;
  }

  if (IcosCell::TYPE_VERTEX == cellType)
  {
    AddVertexCellID(cellTypeID, cellID);
  }
  else if (IcosCell::TYPE_EDGE == cellType)
  {
    AddEdgeCellID(cellTypeID, cellID);
  }
  else if (IcosCell::TYPE_FACE == cellType)
  {
    AddFaceCellID(cellTypeID, cellID);
  }

  Cell[cellID].Type = cellType;
  Cell[cellID].TypeID = cellTypeID;
}

////////////////////////////////////////////////////////////////////////////////
//! Calculates the cell latitude and longitude for vertex cells.
////////////////////////////////////////////////////////////////////////////////
void IcosMap::CalculateLatitudeLongitudeForVertexCells() throw ()
{
  for (U16 i = 0; i < VERTEX_COUNT; ++i)
  {
    U16 cellID = VertexCell[i];

    Cell[cellID].Coordinates = ICOS_VERTEX[i];
    // Assign normal vector.
    Cell[cellID].Normal = Vector(Cell[cellID].Coordinates);
    Cell[cellID].Elevation = 0.0f;
  }
}

////////////////////////////////////////////////////////////////////////////////
//! Calculates the cell latitude and longitude for edge cells.
////////////////////////////////////////////////////////////////////////////////
void IcosMap::CalculateLatitudeLongitudeForEdgeCells() throw ()
{
  if (0u < ExpectedEdgeCellCount)
  {
    for (U16 i = 0; i < EDGE_COUNT; ++i)
    {
      // Get vertex IDs.
      U16 vertexID1 = ICOS_EDGE[i].V1;
      U16 vertexID2 = ICOS_EDGE[i].V2;
      // Convert vertex latitude longitude to Cartesian vector.
      Vector vectorID1(ICOS_VERTEX[vertexID1]);
      Vector vectorID2(ICOS_VERTEX[vertexID2]);
      // Calculate angle between vertices.
      F32 angleID1toID2 = Vector::LeastAngleRadians(vectorID1, vectorID2);
      // Calculate angle between edge cells.
      F32 angleBetweenCells = angleID1toID2 / (ExpectedEdgeCellCount + 1);
      // Calculate axis of rotation.
      RotationAxis axisOfRotation = Vector::CrossProduct(vectorID1, vectorID2);

      // Calculate latitude and longitude of each edge cell.
      for (U16 j = 0; j < ExpectedEdgeCellCount; ++j)
      {
        U16 cellID = EdgeCell[i][j];

        // Calculate angle of rotation that will rotate vertex ID1 to the edge cell.
        F32 angleOfRotation = (j + 1) * angleBetweenCells;

        // Get the rotation matrix that will rotate vertex ID1 to the edge cell.
        CMatrix rotationMatrix;
        axisOfRotation.GetRotationMatrix(angleOfRotation, rotationMatrix);

        // Rotate vertex ID1.
        Vector rotatedVertexID1;
        rotationMatrix.Multiply(vectorID1, rotatedVertexID1);

        // Assign latitude and longitude to edge cell.
        Cell[cellID].Coordinates = rotatedVertexID1;
        // Assign normal vector.
        Cell[cellID].Normal = Vector(Cell[cellID].Coordinates);
        Cell[cellID].Elevation = 0.0f;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
//! Calculates the cell latitude and longitude for face cells.
////////////////////////////////////////////////////////////////////////////////
void IcosMap::CalculateLatitudeLongitudeForFaceCells() throw ()
{
  if ((0u < ExpectedEdgeCellCount) && (0u < ExpectedFaceCellCount))
  {
    for (U16 i = 0; i < FACE_COUNT; ++i)
    {
      U16 edgeID1 = ICOS_FACE[i].E1; // west most edge
      U16 edgeID2 = ICOS_FACE[i].E2; // east most edge
      U16 faceCellIndex = 0;

      if (!ICOS_FACE[i].Inverted)
      {
        // iterate over each row, the first row has no face cells and vertex rows
        // are not counted so start with second row.
        for (U16 row = 1; row < ExpectedEdgeCellCount; ++row)
        {
          // Get coordinates of edge cells
          U16 westCellID = EdgeCell[edgeID1][row];
          U16 eastCellID = EdgeCell[edgeID2][row];
          Coordinates::UnitSphereDegrees westCoordinates = Cell[westCellID].Coordinates;
          Coordinates::UnitSphereDegrees eastCoordinates = Cell[eastCellID].Coordinates;
          // number of cells in each row is equal to the row: 1, 2, 3, 4. Think
          // of a pyramid to visualize this, with row 1 at the top, and row N at
          // the bottom.
          Vector westVector(westCoordinates);
          Vector eastVector(eastCoordinates);
          // Calculate angle between vertices.
          F32 angleWesttoEast = Vector::LeastAngleRadians(westVector, eastVector);
          // Calculate angle between face cells.
          F32 angleBetweenCells = angleWesttoEast / (row + 1);
          // Calculate axis of rotation.
          RotationAxis axisOfRotation = Vector::CrossProduct(westVector, eastVector);

          // Calculate latitude and longitude of each face cell in this row.
          for (U16 j = 0; j < row; ++j)
          {
            U16 cellID = FaceCell[i][faceCellIndex];

            // Calculate angle of rotation that will rotate West vector to the face cell.
            F32 angleOfRotation = (j + 1) * angleBetweenCells;

            // Get the rotation matrix that will rotate West to the face cell.
            CMatrix rotationMatrix;
            axisOfRotation.GetRotationMatrix(angleOfRotation, rotationMatrix);

            // Rotate West vector.
            Vector rotatedWestVector;
            rotationMatrix.Multiply(westVector, rotatedWestVector);

            // Assign latitude and longitude to edge cell.
            Cell[cellID].Coordinates = rotatedWestVector;
            // Assign normal vector.
            Cell[cellID].Normal = Vector(Cell[cellID].Coordinates);
            Cell[cellID].Elevation = 0.0f;

            faceCellIndex++;
          }
        }
      }
      else
      {
        // iterate over each row, the last row has no face cells and vertex rows
        // are not counted.
        for (U16 row = 0; row < (ExpectedEdgeCellCount-1u); ++row)
        {
          // Get coordinates of edge cells
          U16 westCellID = EdgeCell[edgeID1][row];
          U16 eastCellID = EdgeCell[edgeID2][row];
          Coordinates::UnitSphereDegrees westCoordinates = Cell[westCellID].Coordinates;
          Coordinates::UnitSphereDegrees eastCoordinates = Cell[eastCellID].Coordinates;
          // the number of cells in each row is equal to the number of edge cells
          // minus the row: 4, 3, 2, 1. Think of an inverted pyramid to visualize
          // this, with row 1 at the top, and row N at the bottom.
          Vector westVector(westCoordinates);
          Vector eastVector(eastCoordinates);
          // Calculate angle between vertices.
          F32 angleWesttoEast = Vector::LeastAngleRadians(westVector, eastVector);
          // Calculate angle between face cells.
          F32 angleBetweenCells = angleWesttoEast / (ExpectedEdgeCellCount - row);
          // Calculate axis of rotation.
          RotationAxis axisOfRotation = Vector::CrossProduct(westVector, eastVector);

          // Calculate latitude and longitude of each face cell in this row.
          for (U16 j = 0; j < (ExpectedEdgeCellCount-1u - row); ++j)
          {
            U16 cellID = FaceCell[i][faceCellIndex];

            // Calculate angle of rotation that will rotate West vector to the face cell.
            F32 angleOfRotation = (j + 1) * angleBetweenCells;

            // Get the rotation matrix that will rotate West to the face cell.
            CMatrix rotationMatrix;
            axisOfRotation.GetRotationMatrix(angleOfRotation, rotationMatrix);

            // Rotate West vector.
            Vector rotatedWestVector;
            rotationMatrix.Multiply(westVector, rotatedWestVector);

            // assign latitude and longitude to edge cell
            Cell[cellID].Coordinates = rotatedWestVector;
            // assign normal vector
            Cell[cellID].Normal = Vector(Cell[cellID].Coordinates);
            Cell[cellID].Elevation = 0.0f;

            faceCellIndex++;
          }
        }
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
//! Calculates the adjacent cells for each vertex cell.
////////////////////////////////////////////////////////////////////////////////
void
IcosMap::CalculateAdjacentCellsForVertexCells(
    ) throw ()
{
  // All of these cells only have 5 neighbors.

  // North Pole Cell
  U16 cellID = VertexCell[0];
  // Order adjacent IDs so the form a triangle fan with right hand rotation.
  Cell[cellID].AddAdjacentCellID(1);
  Cell[cellID].AddAdjacentCellID(2);
  Cell[cellID].AddAdjacentCellID(3);
  Cell[cellID].AddAdjacentCellID(4);
  Cell[cellID].AddAdjacentCellID(5);

  // Northern Equatorial Cells
  for (U16 i = 1; i <= 5; ++i)
  {
    cellID = VertexCell[i];
    U16 x = Cell[cellID].X;
    U16 y = Cell[cellID].Y;
    // Order adjacent IDs so the form a triangle fan with right hand rotation.
    Cell[cellID].AddAdjacentCellID(GetCellID((x/y)*(y-1u)   ,y-1u));
    Cell[cellID].AddAdjacentCellID(GetCellID(x-1u           ,y  ));
    Cell[cellID].AddAdjacentCellID(GetCellID(x-1u           ,y+1u));
    Cell[cellID].AddAdjacentCellID(GetCellID(x              ,y+1u));
    Cell[cellID].AddAdjacentCellID(GetCellID(x+1u           ,y  ));
  }

  // Southern Equatorial Cells
  for (U16 i = 6; i <= 10; ++i)
  {
    cellID = VertexCell[i];
    U16 x = Cell[cellID].X;
    U16 y = Cell[cellID].Y;
    // Order adjacent IDs so the form a triangle fan with right hand rotation.
    Cell[cellID].AddAdjacentCellID(GetCellID(x                                                   ,y-1u));
    Cell[cellID].AddAdjacentCellID(GetCellID(x-1u                                                ,y  ));
    Cell[cellID].AddAdjacentCellID(GetCellID((x/((RowCount-1u)-(y   )))*((RowCount-1u)-(y+1u))   ,y+1u));
    Cell[cellID].AddAdjacentCellID(GetCellID(x+1u                                                ,y  ));
    Cell[cellID].AddAdjacentCellID(GetCellID(x+1u                                                ,y-1u));
  }

  // Vertex 11 always has neighbors (CellCount-6) to (CellCount-2)
  cellID = VertexCell[11];
  // Order adjacent IDs so the form a triangle fan with right hand rotation.
  Cell[cellID].AddAdjacentCellID(CellCount-6);
  Cell[cellID].AddAdjacentCellID(CellCount-5);
  Cell[cellID].AddAdjacentCellID(CellCount-4);
  Cell[cellID].AddAdjacentCellID(CellCount-3);
  Cell[cellID].AddAdjacentCellID(CellCount-2);
}

////////////////////////////////////////////////////////////////////////////////
//! Calculates the adjacent cells for each edge cell.
////////////////////////////////////////////////////////////////////////////////
void
IcosMap::CalculateAdjacentCellsForEdgeCells(
    ) throw ()
{
  // Northern Pole Edges
  for (U16 i = 0; i <= 4; ++i)
  {
    for (U16 j = 0; j < ExpectedEdgeCellCount; ++j)
    {
      U16 cellID = EdgeCell[i][j];
      U16 x = Cell[cellID].X;
      U16 y = Cell[cellID].Y;
      // Order adjacent IDs so the form a triangle fan with right hand rotation.
      Cell[cellID].AddAdjacentCellID(GetCellID((x/y)*(y-1u)   ,y-1u));
      Cell[cellID].AddAdjacentCellID(GetCellID(x-1u           ,y  ));
      Cell[cellID].AddAdjacentCellID(GetCellID((x/y)*(y+1u)-1u,y+1u));
      Cell[cellID].AddAdjacentCellID(GetCellID((x/y)*(y+1u)   ,y+1u));
      Cell[cellID].AddAdjacentCellID(GetCellID((x/y)*(y+1u)+1u,y+1u));
      Cell[cellID].AddAdjacentCellID(GetCellID(x+1u           ,y  ));
    }
  }

  // Northern Belt Edges
  for (U16 i = 5; i <= 9; ++i)
  {
    for (U16 j = 0; j < ExpectedEdgeCellCount; ++j)
    {
      U16 cellID = EdgeCell[i][j];
      U16 x = Cell[cellID].X;
      U16 y = Cell[cellID].Y;
      // Order adjacent IDs so the form a triangle fan with right hand rotation.
      Cell[cellID].AddAdjacentCellID(GetCellID((x%y)+(x/y)*(y-1u)-1u,y-1u));
      Cell[cellID].AddAdjacentCellID(GetCellID(x-1u                 ,y  ));
      Cell[cellID].AddAdjacentCellID(GetCellID(x-1u                 ,y+1u));
      Cell[cellID].AddAdjacentCellID(GetCellID(x                    ,y+1u));
      Cell[cellID].AddAdjacentCellID(GetCellID(x+1u                 ,y  ));
      Cell[cellID].AddAdjacentCellID(GetCellID((x%y)+(x/y)*(y-1u)   ,y-1u));
    }
  }

  // Equatorial Edges
  for (U16 i = 10; i <= 19; ++i)
  {
    for (U16 j = 0; j < ExpectedEdgeCellCount; ++j)
    {
      U16 cellID = EdgeCell[i][j];
      U16 x = Cell[cellID].X;
      U16 y = Cell[cellID].Y;
      // order adjacent IDs so the form a triangle fan
      Cell[cellID].AddAdjacentCellID(GetCellID(x  ,y-1));
      Cell[cellID].AddAdjacentCellID(GetCellID(x-1,y  ));
      Cell[cellID].AddAdjacentCellID(GetCellID(x-1,y+1));
      Cell[cellID].AddAdjacentCellID(GetCellID(x  ,y+1));
      Cell[cellID].AddAdjacentCellID(GetCellID(x+1,y  ));
      Cell[cellID].AddAdjacentCellID(GetCellID(x+1,y-1));
    }
  }

  // Southern Belt Edges
  for (U16 i = 20; i <= 24; ++i)
  {
    for (U16 j = 0; j < ExpectedEdgeCellCount; ++j)
    {
      U16 cellID = EdgeCell[i][j];
      U16 x = Cell[cellID].X;
      U16 y = Cell[cellID].Y;
      // Order adjacent IDs so the form a triangle fan with right hand rotation.
      Cell[cellID].AddAdjacentCellID(GetCellID(x                                                                         ,y-1u));
      Cell[cellID].AddAdjacentCellID(GetCellID(x-1u                                                                      ,y   ));
      Cell[cellID].AddAdjacentCellID(GetCellID((x%((RowCount-1u)-y))+(x/((RowCount-1u)-(y   )))*((RowCount-1u)-(y+1u))-1u,y+1u));
      Cell[cellID].AddAdjacentCellID(GetCellID((x%((RowCount-1u)-y))+(x/((RowCount-1u)-(y   )))*((RowCount-1u)-(y+1u))   ,y+1u));
      Cell[cellID].AddAdjacentCellID(GetCellID(x+1u                                                                      ,y   ));
      Cell[cellID].AddAdjacentCellID(GetCellID(x+1u                                                                      ,y-1u));
    }
  }

  // Southern Pole Edges
  for (U16 i = 25; i <= 29; ++i)
  {
    for (U16 j = 0; j < ExpectedEdgeCellCount; ++j)
    {
      U16 cellID = EdgeCell[i][j];
      U16 x = Cell[cellID].X;
      U16 y = Cell[cellID].Y;
      // Order adjacent IDs so the form a triangle fan with right hand rotation.
      Cell[cellID].AddAdjacentCellID(GetCellID((x/((RowCount-1u)-(y   )))*((RowCount-1u)-(y-1u))   ,y-1u));
      Cell[cellID].AddAdjacentCellID(GetCellID((x/((RowCount-1u)-(y   )))*((RowCount-1u)-(y-1u))-1u,y-1u));
      Cell[cellID].AddAdjacentCellID(GetCellID(x-1u                                                ,y  ));
      Cell[cellID].AddAdjacentCellID(GetCellID((x/((RowCount-1u)-(y   )))*((RowCount-1u)-(y+1u))   ,y+1u));
      Cell[cellID].AddAdjacentCellID(GetCellID(x+1u                                                ,y  ));
      Cell[cellID].AddAdjacentCellID(GetCellID((x/((RowCount-1u)-(y   )))*((RowCount-1u)-(y-1u))+1u,y-1u));
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
//! Calculates the adjacent cells for each face cell.
////////////////////////////////////////////////////////////////////////////////
void
IcosMap::CalculateAdjacentCellsForFaceCells(
    ) throw ()
{
  // Northern Pole Faces
  for (U16 i = 0; i <= 4; ++i)
  {
    for (U16 j = 0; j < ExpectedFaceCellCount; ++j)
    {
      U16 cellID = FaceCell[i][j];
      U16 x = Cell[cellID].X;
      U16 y = Cell[cellID].Y;
      // Order adjacent IDs so the form a triangle fan with right hand rotation.
      Cell[cellID].AddAdjacentCellID(GetCellID((x%y)+(x/y)*(y-1u)-1u,y-1u));
      Cell[cellID].AddAdjacentCellID(GetCellID(x-1u                 ,y  ));
      Cell[cellID].AddAdjacentCellID(GetCellID((x%y)+(x/y)*(y+1u)   ,y+1u));
      Cell[cellID].AddAdjacentCellID(GetCellID((x%y)+(x/y)*(y+1u)+1u,y+1u));
      Cell[cellID].AddAdjacentCellID(GetCellID(x+1u                 ,y  ));
      Cell[cellID].AddAdjacentCellID(GetCellID((x%y)+(x/y)*(y-1u)   ,y-1u));
    }
  }

  // Equatorial Faces
  for (U16 i = 5; i <= 14; ++i)
  {
    for (U16 j = 0; j < ExpectedFaceCellCount; ++j)
    {
      U16 cellID = FaceCell[i][j];
      U16 x = Cell[cellID].X;
      U16 y = Cell[cellID].Y;
      // Order adjacent IDs so the form a triangle fan with right hand rotation.
      Cell[cellID].AddAdjacentCellID(GetCellID(x  ,y-1));
      Cell[cellID].AddAdjacentCellID(GetCellID(x+1,y-1));
      Cell[cellID].AddAdjacentCellID(GetCellID(x+1,y  ));
      Cell[cellID].AddAdjacentCellID(GetCellID(x  ,y+1));
      Cell[cellID].AddAdjacentCellID(GetCellID(x-1,y+1));
      Cell[cellID].AddAdjacentCellID(GetCellID(x-1,y  ));
    }
  }

  // Southern Pole Faces
  // Rows in these faces slope to the east from top to bottom.
  for (U16 i = 15; i <= 19; ++i)
  {
    for (U16 j = 0; j < ExpectedFaceCellCount; ++j)
    {
      U16 cellID = FaceCell[i][j];
      U16 x = Cell[cellID].X;
      U16 y = Cell[cellID].Y;
      // Order adjacent IDs so the form a triangle fan with right hand rotation.
      Cell[cellID].AddAdjacentCellID(GetCellID((x%((RowCount-1u)-(y   )))+(x/((RowCount-1u)-(y   )))*((RowCount-1u)-(y-1u))   ,y-1u));
      Cell[cellID].AddAdjacentCellID(GetCellID(x-1u                                                                 ,y  ));
      Cell[cellID].AddAdjacentCellID(GetCellID((x%((RowCount-1u)-(y   )))+(x/((RowCount-1u)-(y   )))*((RowCount-1u)-(y+1u))-1u,y+1u));
      Cell[cellID].AddAdjacentCellID(GetCellID((x%((RowCount-1u)-(y   )))+(x/((RowCount-1u)-(y   )))*((RowCount-1u)-(y+1u))   ,y+1u));
      Cell[cellID].AddAdjacentCellID(GetCellID(x+1u                                                                 ,y  ));
      Cell[cellID].AddAdjacentCellID(GetCellID((x%((RowCount-1u)-(y   )))+(x/((RowCount-1u)-(y   )))*((RowCount-1u)-(y-1u))+1u,y-1u));
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
//! Checks all edge cell counts for equality.
////////////////////////////////////////////////////////////////////////////////
void IcosMap::CheckEdgeCellCounts() throw (Exception::Type)
{
  for (U16 i = 0; i < EDGE_COUNT; ++i)
  {
    if (EdgeCellCount[i] != ExpectedEdgeCellCount)
    {
      throw (Exception::INITIALIZATION_ERROR);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
//! Check all face cell counts for equality.
////////////////////////////////////////////////////////////////////////////////
void IcosMap::CheckFaceCellCounts() throw (Exception::Type)
{
  for (U16 i = 0; i < FACE_COUNT; ++i)
  {
    if (FaceCellCount[i] != ExpectedFaceCellCount)
    {
      throw (Exception::INITIALIZATION_ERROR);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
//! Generates elevations using a displacement algorithm.
////////////////////////////////////////////////////////////////////////////////
void IcosMap::GenerateElevations_Displacement() throw ()
{
  NumberGenerator rand;

  rand.Seed(45234523U);

  static const U16 ITERATIONS = 5000;
//  static const U16 ITERATIONS = 10;

  for (U16 i = 0; i < ITERATIONS; ++i)
  {
    Vector origin = Vector((rand.GenerateF64()-0.5f), (rand.GenerateF64()-0.5f), (rand.GenerateF64()-0.5f));
    origin.Normalize();

    Vector direction = Vector((rand.GenerateF64()-0.5f), (rand.GenerateF64()-0.5f), (rand.GenerateF64()-0.5f));
    direction.Normalize();

    for (U16 j = 0; j < CellCount; ++j)
    {
      // Calculate vector from origin to cell center
      Vector originDifference = Cell[j].Normal - origin;
      // calculate dot product of direction and that vector
      F32 dotProduct = direction * originDifference;
      // if result greater than zero raise elevation of cell by X
      if (dotProduct > 0.0)
      {
        Cell[j].Elevation += 1.0;
      }
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
//! Generates elevations using a displacement algorithm.
////////////////////////////////////////////////////////////////////////////////
void IcosMap::GenerateElevations() throw ()
{
  GenerateElevations_Displacement();

  // Normalize elevations.
  F32 minElev = (F32)100000000;
  F32 maxElev = 0.0f;

  for (U16 j = 0; j < CellCount; ++j)
  {
    if (Cell[j].Elevation < minElev) minElev = Cell[j].Elevation;
    if (Cell[j].Elevation > maxElev) maxElev = Cell[j].Elevation;
  }

  F32 scaleElev = maxElev - minElev;

  for (U16 j = 0; j < CellCount; ++j)
  {
    Cell[j].Elevation -= minElev;
    Cell[j].Elevation /= scaleElev;
  }
}

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
