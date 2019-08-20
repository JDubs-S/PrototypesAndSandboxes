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

#include "IcosMap.h"
#include "IcosMapGL.h"
#include "Coordinates.h"

#include <OpenGL/gl3.h>

////////////////////////////////////////////////////////////////////////////////
// (See IcosMapGL.h)
////////////////////////////////////////////////////////////////////////////////
IcosMapGL::IcosMapGL(
    IcosMap & map
    )
    : Map(map)
{
}

////////////////////////////////////////////////////////////////////////////////
// (See IcosMapGL.h)
////////////////////////////////////////////////////////////////////////////////
IcosMapGL::~IcosMapGL(
    )
{
}

////////////////////////////////////////////////////////////////////////////////
// (See IcosMapGL.h)
////////////////////////////////////////////////////////////////////////////////
void
IcosMapGL::Intialize(
    ) throw (Exception::Type)
{
  CellCount = Map.GetCellCount();

  for (U16 i = 0; i < CellCount; ++i)
  {
	Coordinates::UnitSphereDegrees coord = Map.GetCoordinates(i);
    Vector vec = coord;

    Face[i].VertexCount = 0;

    Face[i].Vertex[Face[i].VertexCount] = vec;
    Face[i].Color[Face[i].VertexCount] = Vector(1.0f, 1.0f, 1.0f);
    Face[i].VertexCount++;

    for (U16 j = 0; j < Map.GetAdjacentCellCount(i); ++j)
    {
      coord = Map.GetCoordinates(Map.GetAdjacentCellID(i,j));
      vec = coord;

      Face[i].Vertex[Face[i].VertexCount] = vec;
      Face[i].Color[Face[i].VertexCount] = Vector(1.0f, 1.0f, 1.0f);
      Face[i].VertexCount++;
    }

    coord = Map.GetCoordinates(Map.GetAdjacentCellID(i,0));
    vec = coord;

    Face[i].Vertex[Face[i].VertexCount] = vec;
    Face[i].Color[Face[i].VertexCount] = Vector(1.0f, 1.0f, 1.0f);
    Face[i].VertexCount++;
  }
}

////////////////////////////////////////////////////////////////////////////////
// (See IcosMapGL.h)
////////////////////////////////////////////////////////////////////////////////
void
IcosMapGL::Update()
{
  glClearColor(0.0,0.0,0.0,0.0);

  U16 i = 2;
//  for (U16 i = 0; i < CellCount; ++i)
//  {
    glEnableVertexAttribArray(0); // position
    glEnableVertexAttribArray(1); // color

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, &Face[i].Vertex[0]);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, &Face[i].Color[0]);
    glDrawArrays(GL_TRIANGLE_FAN, 0, Face[i].VertexCount);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
//  }
}

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
