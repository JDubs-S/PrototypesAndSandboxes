#pragma once
/* *****************************************************************************
 *
 * Copyright (C) 2012, 2019 by owner of https://github.com/JDubs-S.
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

#include "NativeTypes.h"

/* *****************************************************************************
 *
 * This namespace defines constants used in the various IcoSphere algorithms and
 * wrappers for system math functions. These wrappers facilitate unit testing
 * without preprocessor magic.
 *
 * ****************************************************************************/

namespace Math
{
  //////////////////////////////////////////////////////////////////////////////
  //! Constants.
  //////////////////////////////////////////////////////////////////////////////
  static const F32 PI = 3.14159265359f;
  static const F32 P_EPSILON = +0.00001f;
  static const F32 N_EPSILON = -0.00001f;

  //////////////////////////////////////////////////////////////////////////////
  //! Radian values for common degree angles.
  //////////////////////////////////////////////////////////////////////////////
  static const F32 RADIANS_0    = 0.0f;
  static const F32 RADIANS_45   = Math::PI / 4.0f;
  static const F32 RADIANS_90   = Math::PI / 2.0f;
  static const F32 RADIANS_135  = 3.0f * Math::PI / 4.0f;
  static const F32 RADIANS_180  = Math::PI;
  static const F32 RADIANS_225  = 5.0f * Math::PI / 4.0f;
  static const F32 RADIANS_270  = 3.0f * Math::PI / 2.0f;
  static const F32 RADIANS_315  = 7.0f * Math::PI / 4.0f;
  static const F32 RADIANS_360  = 2.0f * Math::PI;

  //////////////////////////////////////////////////////////////////////////////
  //! Sine values for common degree angles.
  //////////////////////////////////////////////////////////////////////////////
  static const F32 SINE_0       = 0.0f;
  static const F32 SINE_45      = 0.707106781f;
  static const F32 SINE_90      = 1.0f;
  static const F32 SINE_135     = 0.707106781f;
  static const F32 SINE_180     = 0.0f;
  static const F32 SINE_225     = -0.707106781f;
  static const F32 SINE_270     = -1.0f;
  static const F32 SINE_315     = -0.707106781f;
  static const F32 SINE_360     = 0.0f;

  //////////////////////////////////////////////////////////////////////////////
  //! Cosine values for common degree angles.
  //////////////////////////////////////////////////////////////////////////////
  static const F32 COSINE_0     = 1.0f;
  static const F32 COSINE_45    = 0.707106781f;
  static const F32 COSINE_90    = 0.0f;
  static const F32 COSINE_135   = -0.707106781f;
  static const F32 COSINE_180   = -1.0f;
  static const F32 COSINE_225   = -0.707106781f;
  static const F32 COSINE_270   = 0.0f;
  static const F32 COSINE_315   = 0.707106781f;
  static const F32 COSINE_360   = 1.0f;

  //////////////////////////////////////////////////////////////////////////////
  //! Convert degrees to radians.
  //////////////////////////////////////////////////////////////////////////////
  F32 ConvertDegreesToRadians(F32 degrees) throw ();

  //////////////////////////////////////////////////////////////////////////////
  //! Convert radians to degrees.
  //////////////////////////////////////////////////////////////////////////////
  F32 ConvertRadiansToDegrees(F32 radians) throw ();

  //////////////////////////////////////////////////////////////////////////////
  //! Trigonometric Functions.
  //////////////////////////////////////////////////////////////////////////////
  F32 Sine(F32 radians) throw ();
  F32 ArcSine(F32 radians) throw ();
  F32 Cosine(F32 radians) throw ();
  F32 ArcCosine(F32 value) throw ();

  //////////////////////////////////////////////////////////////////////////////
  //! Operators.
  //////////////////////////////////////////////////////////////////////////////
  F32 SquareRoot(F32 value) throw ();

  //////////////////////////////////////////////////////////////////////////////
  //! Returns value rounded to the nearest decimal fraction with the given
  //! number of decimal places.
  //////////////////////////////////////////////////////////////////////////////
  F32 Round(
      F32 value,        //!< Value to round.
      U8 decimalPlaces  //!< Maximum number of non-zero decimal places in result.
      ) throw ();

};

/* *****************************************************************************
 *
 * Copyright (C) 2012, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
