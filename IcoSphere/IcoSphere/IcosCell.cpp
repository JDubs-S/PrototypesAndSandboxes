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

#include "IcosCell.h"
#include "Memory.h"

const U16 IcosCell::TYPE_NONE = 0;
const U16 IcosCell::TYPE_VERTEX = 1;
const U16 IcosCell::TYPE_EDGE = 2;
const U16 IcosCell::TYPE_FACE = 3;

IcosCell::IcosCell(
    ) throw ()
: ID(0u)
, X(0u)
, Y(0u)
, AdjacentCount(0u)
{
  Coordinates.Latitude = 0.0f;
  Coordinates.Longitude = 0.0f;
  Memory::Initialize(-1, MAX_ADJACENT_CELLS, AdjacentID);
}

IcosCell::~IcosCell(
    ) throw ()
{
}

void
IcosCell::Initialize(
    ) throw ()
{
  ID = 0u;
  X = 0u;
  Y = 0u;
  AdjacentCount = 0u;
  Coordinates.Latitude = 0.0f;
  Coordinates.Longitude = 0.0f;
  Memory::Initialize(-1, MAX_ADJACENT_CELLS, AdjacentID);
}

void
IcosCell::AddAdjacentCellID(
    U16 cellID
    ) throw ()
{
  AdjacentID[AdjacentCount] = cellID;
  AdjacentCount++;
}

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/

