#pragma once
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

#include "Exception.h"
#include "NativeTypes.h"
#include "Vector.h"

////////////////////////////////////////////////////////////////////////////////
//! Forward declarations.
////////////////////////////////////////////////////////////////////////////////
class IcosMap;

class IcosMapGL
{
public:

  IcosMapGL(IcosMap & map);

  ~IcosMapGL();

  void Intialize() throw (Exception::Type);

  void Update();

private:

  struct Cell
  {
    U32 VertexCount;
    Vector Color[8];
    Vector Vertex[8];
  };

  U16 CellCount;

  Cell Face[10000];

  IcosMap & Map;

};

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
