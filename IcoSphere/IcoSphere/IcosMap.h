#pragma once
/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
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

#include "Exception.h"
#include "IcosCell.h"
#include "NativeTypes.h"

class IcosMap
{
public:

  IcosMap();

  ~IcosMap();

  //////////////////////////////////////////////////////////////////////////////
  //! Initializes the map.
  //////////////////////////////////////////////////////////////////////////////
  static const U8 MIN_SIZE = 1;
  static const U8 MAX_SIZE = 50;
  void Initialize(U8 size) throw (Exception::Type);

  static const U16 MAX_CELL_COUNT = 10u * MAX_SIZE * MAX_SIZE + 2u;

  //////////////////////////////////////////////////////////////////////////////
  //! Returns the total number of cells in the map.
  //////////////////////////////////////////////////////////////////////////////
  U16 GetCellCount() const throw ();

  //////////////////////////////////////////////////////////////////////////////
  //! Returns the cell ID of the cell with coordinates X and Y. The X
  //! coordinate is wrapped.
  //////////////////////////////////////////////////////////////////////////////
  U16 GetCellID(S16 x, U16 y) throw (Exception::Type);

  //////////////////////////////////////////////////////////////////////////////
  //! Returns the cell type of cell (x,y): vertex, edge, or face.
  //////////////////////////////////////////////////////////////////////////////
  U16 GetCellType(U16 x, U16 y) throw (Exception::Type);

  //////////////////////////////////////////////////////////////////////////////
  //! Returns the vertex, edge, or face to which cell (x,y) belongs.
  //////////////////////////////////////////////////////////////////////////////
  U16 GetCellTypeID(U16 x, U16 y) throw (Exception::Type);

  //////////////////////////////////////////////////////////////////////////////
  //! Returns the coordinates of cell (x,y).
  //////////////////////////////////////////////////////////////////////////////
  Coordinates::UnitSphereDegrees GetCoordinates(U16 x, U16 y) throw (Exception::Type);

  static const U16 MAX_ADJACENT_CELLS = 6u;

  class AdjacentCellIterator
  {
  public:

    S16
    GetNextID(
        )
    {
      return AdjacentCellID[CurrentIndex++];
    }

  private:
    friend class IcosMap;
    S16 CellID;
    U16 CurrentIndex;
    U16 AdjacentCellCount;
    S16 AdjacentCellID[MAX_ADJACENT_CELLS];
  };

  //////////////////////////////////////////////////////////////////////////////
  //! Returns the IDs of cells adjacent to cell (x,y).
  //////////////////////////////////////////////////////////////////////////////
  void GetAdjacentCellIDs(
      const U16 x,
      const U16 y,
      AdjacentCellIterator & record
      ) const throw (Exception::Type);

  inline
  Coordinates::UnitSphereDegrees
  GetCoordinates(
      U16 cellId
      ) throw ()
  {
    return Cell[cellId].Coordinates;
  }

  inline
  U16
  GetAdjacentCellCount(
      U16 cellId
      ) throw ()
  {
    return Cell[cellId].AdjacentCount;
  }

  inline
  S16
  GetAdjacentCellID(
      U16 cellId,
      U8 i
      ) throw ()
  {
    return Cell[cellId].AdjacentID[i];
  }

  inline
  S16
  GetAdjacentCellID(
      U16 x,
      U16 y,
      U16 i
      )
  {
    return RowCell[y % RowCount][x % RowCellCount[y % RowCount]].AdjacentID[i % MAX_ADJACENT_CELLS];
  }

  inline
  const IcosCell &
  GetCell(
      U16 cellID
      ) const throw ()
  {
    return Cell[cellID];
  }

  void GenerateElevations() throw ();

private:

  void AddVertexCellID(U16 vertexID, U16 cellID) throw ();
  void AddEdgeCellID(U16 edgeID, U16 cellID) throw ();
  void AddFaceCellID(U16 faceID, U16 cellID) throw ();
  void CalculateCellTypeAndTypeID(U16 cellID) throw ();
  void CalculateLatitudeLongitudeForVertexCells() throw ();
  void CalculateLatitudeLongitudeForEdgeCells() throw ();
  void CalculateLatitudeLongitudeForFaceCells() throw ();
  void CalculateAdjacentCellsForVertexCells() throw ();
  void CalculateAdjacentCellsForEdgeCells() throw ();
  void CalculateAdjacentCellsForFaceCells() throw ();
  void CheckEdgeCellCounts() throw (Exception::Type);
  void CheckFaceCellCounts() throw (Exception::Type);

  void GenerateElevations_Displacement() throw ();
  void GenerateElevations_Cratering() throw ();
  void GenerateElevations_VolcanicEruptions() throw ();
  void GenerateElevations_PlateTectonics() throw ();

  static const U16 VERTEX_COUNT = 12u;
  static const U16 EDGE_COUNT = 30u;
  static const U16 FACE_COUNT = 20u;

  static const U16 MAX_ROW_COUNT = 3u * MAX_SIZE + 1u;
  static const U16 MAX_EDGE_CELL_COUNT = MAX_SIZE - 1u;
  static const U16 MAX_FACE_CELL_COUNT = ((MAX_SIZE - 2u) * (MAX_SIZE - 1u)) / 2;

  //! Size of map.
  U16 Size;
  //! Total number of cells in map.
  U16 CellCount;
  //! Coordinates of each vertex cell.
  U16 VertexCell[VERTEX_COUNT];
  //! Expected number of cells in each edge.
  U16 ExpectedEdgeCellCount;
  //! Total number of cells in each edge.
  U16 EdgeCellCount[EDGE_COUNT];
  //! Coordinates of each edge cell.
  U16 EdgeCell[EDGE_COUNT][MAX_EDGE_CELL_COUNT];
  //! Expected number of cells in each face.
  U16 ExpectedFaceCellCount;
  //! Total number of cells in each face.
  U16 FaceCellCount[FACE_COUNT];
  //! Coordinate of each face cell.
  U16 FaceCell[FACE_COUNT][MAX_FACE_CELL_COUNT];
  //! Total number of rows.
  U16 RowCount;
  //! Total number of cells in a row.
  U16 RowCellCount[MAX_ROW_COUNT];
  //! The cells in this map.
  IcosCell Cell[MAX_CELL_COUNT];
  //! Pointers to the first cell of each row.
  IcosCell* RowCell[MAX_ROW_COUNT];
};

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
