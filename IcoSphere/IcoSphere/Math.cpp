/* *****************************************************************************
 *
 * Copyright (C) 2012 Jason William Staiert. All Rights Reserved.
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

#include <math.h>
#undef PI

#include "Math.h"

////////////////////////////////////////////////////////////////////////////////
// (See Math.h)
////////////////////////////////////////////////////////////////////////////////
F32 Math::ConvertDegreesToRadians(F32 degrees) throw ()
{
  return (2.0f * Math::PI *  degrees) / 360.0f;
}

////////////////////////////////////////////////////////////////////////////////
// (See Math.h)
////////////////////////////////////////////////////////////////////////////////
F32 Math::ConvertRadiansToDegrees(F32 radians) throw ()
{
  return (360.0f * radians) / (2.0f * Math::PI);
}

////////////////////////////////////////////////////////////////////////////////
// (See Math.h)
////////////////////////////////////////////////////////////////////////////////
F32 Math::Sine(F32 radians) throw ()
{
  return sinf(radians);
}

////////////////////////////////////////////////////////////////////////////////
// (See Math.h)
////////////////////////////////////////////////////////////////////////////////
F32 Math::ArcSine(F32 radians) throw ()
{
  return asinf(radians);
}

////////////////////////////////////////////////////////////////////////////////
// (See Math.h)
////////////////////////////////////////////////////////////////////////////////
F32 Math::Cosine(F32 radians) throw ()
{
  return cosf(radians);
}

////////////////////////////////////////////////////////////////////////////////
// (See Math.h)
////////////////////////////////////////////////////////////////////////////////
F32 Math::ArcCosine(F32 value) throw ()
{
  return acosf(value);
}

////////////////////////////////////////////////////////////////////////////////
// (See Math.h)
////////////////////////////////////////////////////////////////////////////////
F32 Math::SquareRoot(F32 value) throw ()
{
  return sqrtf(value);
}

////////////////////////////////////////////////////////////////////////////////
// (See Math.h)
////////////////////////////////////////////////////////////////////////////////
F32 Math::Round(F32 value, U8 decimalPlaces) throw ()
{
  F32 multiplier = powf(10.0f, (F32)decimalPlaces);

  return roundf(multiplier * value) / multiplier;
}

/* *****************************************************************************
 *
 * Copyright (C) 2012, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
