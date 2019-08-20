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

#include "Coordinates.h"
#include "IcosCellView.h"
#include "RenderContext.h"
#include "RotationAxis.h"

#include <iostream>

IcosCellView::IcosCellView(
    ) throw ()
    : Map(nullptr)
    , Cell(nullptr)
    , SurfaceVertexArray(VertexArray::TYPE_TRIANGLE_FAN)
{
}

IcosCellView::~IcosCellView(
    ) throw ()
{
}

extern U16 CellID;
void
IcosCellView::SetMapCell(
    const IcosMap & map,
    const IcosCell & cell
    ) throw ()
{
  Map = & map;
  Cell = & cell;

  SurfaceVertexArray.Reset();

#if 0
  U16 cellID = cell.GetID();

//  if (Cell->GetType()!=IcosCell::TYPE_VERTEX) return;
//  if ((cellID > CellID && Cell->GetType()!=IcosCell::TYPE_VERTEX && Cell->GetType()!=IcosCell::TYPE_EDGE)) return;
  if (Cell->GetType()==IcosCell::TYPE_VERTEX || Cell->GetType()==IcosCell::TYPE_EDGE) return;

  if (CellID == cellID)
  {
    std::cout << "CellID=" << cellID << " Lat=" << Cell->Coordinates.Latitude << " Lon=" << Cell->Coordinates.Longitude << "\n";
    std::cout << "X=" << (U16)Cell->X << " Y=" << (U16)Cell->Y << "\n";
    std::cout << "AdjCount=" << (U16)Cell->AdjacentCount << "\n";
    std::cout << "Adj0=" << Cell->AdjacentID[0] << "\n";
    std::cout << "Adj1=" << Cell->AdjacentID[1] << "\n";
    std::cout << "Adj2=" << Cell->AdjacentID[2] << "\n";
    std::cout << "Adj3=" << Cell->AdjacentID[3] << "\n";
    std::cout << "Adj4=" << Cell->AdjacentID[4] << "\n";
    std::cout << "Adj5=" << Cell->AdjacentID[5] << "\n";
  }
#endif

#if 0
  if (cellID % 7 == 0) SurfaceVertexArray.Color = ColorRGBA(1.0f, 0.0f, 0.0f);
  else if (cellID % 7 == 1) SurfaceVertexArray.Color = ColorRGBA(0.0f, 1.0f, 0.0f);
  else if (cellID % 7 == 2) SurfaceVertexArray.Color = ColorRGBA(0.0f, 0.0f, 1.0f);
  else if (cellID % 7 == 3) SurfaceVertexArray.Color = ColorRGBA(1.0f, 0.5f, 0.0f);
  else if (cellID % 7 == 4) SurfaceVertexArray.Color = ColorRGBA(0.5f, 1.0f, 0.0f);
  else if (cellID % 7 == 5) SurfaceVertexArray.Color = ColorRGBA(1.0f, 0.0f, 0.5f);
  else if (cellID % 7 == 6) SurfaceVertexArray.Color = ColorRGBA(0.0f, 1.0f, 0.5f);
#endif

  SurfaceVertexArray.Color = ColorRGBA(Cell->Elevation, Cell->Elevation, Cell->Elevation);

  F32 cellElevation = Cell->Elevation;

  Vector cellVertex = Cell->GetCoordinates();
  cellVertex = cellVertex * (0.8F + cellElevation / 5.0F);

  SurfaceVertexArray.AddVertex(cellVertex);

  // To create complete triangle fan the first vertex processed must also be the last.
  for (U8 i = 0; i <= Cell->GetAdjacentCount(); ++i)
  {
    Vector firstAdjacentVertex = (Map->GetCell(Cell->GetAdjacentID(i))).GetCoordinates();
    F32 firstAdjacentElevation = (Map->GetCell(Cell->GetAdjacentID(i))).Elevation;
    Vector secondAdjacentVertex = (Map->GetCell(Cell->GetAdjacentID(i+1))).GetCoordinates();
    F32 secondAdjacentElevation = (Map->GetCell(Cell->GetAdjacentID(i+1))).Elevation;

    Vector sum = (cellVertex + firstAdjacentVertex + secondAdjacentVertex);
    sum.Normalize();
    sum = sum * (0.8f + ((cellElevation + firstAdjacentElevation + secondAdjacentElevation) / 15.0f) );

    SurfaceVertexArray.AddVertex(sum);
  }
}

////////////////////////////////////////////////////////////////////////////////
// (See IcosCellView.h)
////////////////////////////////////////////////////////////////////////////////
void
IcosCellView::Render(
    RenderContext & context
    ) const throw ()
{
  context.Draw(SurfaceVertexArray);
}

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
