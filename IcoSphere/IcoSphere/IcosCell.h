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

#include "Coordinates.h"
#include "NativeTypes.h"
#include "Vector.h"

struct IcosCell
{
public:

  static const U16 MAX_ADJACENT_CELLS = 6;

  static const U16 TYPE_NONE;
  static const U16 TYPE_VERTEX;
  static const U16 TYPE_EDGE;
  static const U16 TYPE_FACE;

  IcosCell(
      ) throw ();

  ~IcosCell(
      ) throw ();

  void
  Initialize(
      ) throw ();

  //////////////////////////////////////////////////////////////////////////////
  //! Return the ID of this cell.
  //////////////////////////////////////////////////////////////////////////////
  inline
  U16
  GetID(
      ) const throw ()
  {
    return ID;
  }

  //////////////////////////////////////////////////////////////////////////////
  //! Return type of this cell.
  //////////////////////////////////////////////////////////////////////////////
  inline
  U16
  GetType(
      ) const throw ()
  {
    return Type;
  }

  //////////////////////////////////////////////////////////////////////////////
  //! Return the type ID of this cell.
  //////////////////////////////////////////////////////////////////////////////
  inline
  U16
  GetTypeID(
      ) const throw ()
  {
    return TypeID;
  }

  //////////////////////////////////////////////////////////////////////////////
  //! Return the longitude and latitude of this cell.
  //////////////////////////////////////////////////////////////////////////////
  inline
  Coordinates::UnitSphereDegrees
  GetCoordinates(
      ) const throw ()
  {
    return Coordinates;
  }

  //////////////////////////////////////////////////////////////////////////////
  //! Return the number of cells adjacent to this cell.
  //////////////////////////////////////////////////////////////////////////////
  inline
  U16
  GetAdjacentCount(
      ) const throw ()
  {
    return AdjacentCount;
  }

  //////////////////////////////////////////////////////////////////////////////
  //! Return the ID of the give adjacent cell. Index wraps.
  //////////////////////////////////////////////////////////////////////////////
  inline
  U16
  GetAdjacentID(
      U16 index  //! Index of the adjacent cell.
      ) const throw ()
  {
    return AdjacentID[index % AdjacentCount];
  }

  void AddAdjacentCellID(U16 cellID) throw ();

  //! Unique ID of cell.
  U16 ID;
  //! X map coordinate of cell.
  U16 X;
  //! Y map coordinate of cell.
  U16 Y;
  //! Cell type, 0 = vertex, 1 = edge, 2 = face
  U16 Type;
  //! Which vertex, edge, or face this cell belongs to.
  U16 TypeID;
  //! Number of adjacent cells.
  U16 AdjacentCount;
  //! IDs of adjacent cells.
  U16 AdjacentID[MAX_ADJACENT_CELLS];
  Coordinates::UnitSphereDegrees Coordinates;
  Vector Normal;
  F32 Elevation;
};

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/

