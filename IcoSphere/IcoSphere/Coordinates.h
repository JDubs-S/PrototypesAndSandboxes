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

#include "Math.h"
#include "NativeTypes.h"

namespace Coordinates
{
  //////////////////////////////////////////////////////////////////////////////
  //! Unit sphere coordinates with units in Degrees. Assumes 90 degrees
  //! latitude is +Y, and 0 degrees longitude is +X, with positive latitude in
  //! the direction of +Z.
  //////////////////////////////////////////////////////////////////////////////
  struct UnitSphereDegrees
  {
    F32 Latitude;   //! Latitude in degrees on a unit sphere.
    F32 Longitude;  //! Longitude in degrees on a unit sphere.
  }__attribute__((packed));
}

inline
bool
operator==(
    const Coordinates::UnitSphereDegrees & a,
    const Coordinates::UnitSphereDegrees & b
    )
{
  F32 diffLatitude  = a.Latitude - b.Latitude;
  F32 diffLongitude = a.Longitude - b.Longitude;
  return (
      (Math::N_EPSILON < diffLatitude) && (diffLatitude < Math::P_EPSILON) &&
      (Math::N_EPSILON < diffLongitude) && (diffLongitude < Math::P_EPSILON)
      );
}

inline
bool
operator!=(
    const Coordinates::UnitSphereDegrees & a,
    const Coordinates::UnitSphereDegrees & b
    )
{
  F32 diffLatitude  = a.Latitude - b.Latitude;
  F32 diffLongitude = a.Longitude - b.Longitude;
  return (
      (diffLatitude < Math::N_EPSILON) || (Math::P_EPSILON < diffLatitude) ||
      (diffLongitude < Math::N_EPSILON) || (Math::P_EPSILON < diffLongitude)
      );
}

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
