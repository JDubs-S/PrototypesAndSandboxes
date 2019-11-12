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
#include "Matrix.h"
#include "RotationAxis.h"

////////////////////////////////////////////////////////////////////////////////
// (See RotationAxis.h)
////////////////////////////////////////////////////////////////////////////////
void
RotationAxis::GetRotationMatrix(
    const F32 angle,
    CMatrix & matrix
    ) const throw ()
{
  F32 cosTheta = Math::Cosine(angle);
  F32 sinTheta = Math::Sine(angle);
  F32 oneMinusCosTheta = 1 - cosTheta;
#if 0
  // first row
  matrix.M[0][0] = cosTheta + X * X * oneMinusCosTheta;
  matrix.M[1][0] = X * Y * oneMinusCosTheta - Z * sinTheta;
  matrix.M[2][0] = X * Z * oneMinusCosTheta + Y * sinTheta;
  // second row
  matrix.M[0][1] = Y * X * oneMinusCosTheta + Z * sinTheta;
  matrix.M[1][1] = cosTheta + Y * Y * oneMinusCosTheta;
  matrix.M[2][1] = Y * Z * oneMinusCosTheta - X * sinTheta;
  // third row
  matrix.M[0][2] = Z * X * oneMinusCosTheta - Y * sinTheta;
  matrix.M[1][2] = Z * Y * oneMinusCosTheta + X * sinTheta;
  matrix.M[2][2] = cosTheta + Z * Z * oneMinusCosTheta;
#else
  F32 XY = X * Y;
  F32 YZ = Y * Z;
  F32 ZX = Z * X;
  F32 XsinTheta = X * sinTheta;
  F32 YsinTheta = Y * sinTheta;
  F32 ZsinTheta = Z * sinTheta;
  // first row
  matrix.M[0][0] = cosTheta + X * X * oneMinusCosTheta;
  matrix.M[1][0] = XY * oneMinusCosTheta - ZsinTheta;
  matrix.M[2][0] = ZX * oneMinusCosTheta + YsinTheta;
  matrix.M[3][0] = 0.0f;
  // second row
  matrix.M[0][1] = XY * oneMinusCosTheta + ZsinTheta;
  matrix.M[1][1] = cosTheta + Y * Y * oneMinusCosTheta;
  matrix.M[2][1] = YZ * oneMinusCosTheta - XsinTheta;
  matrix.M[3][1] = 0.0f;
  // third row
  matrix.M[0][2] = ZX * oneMinusCosTheta - YsinTheta;
  matrix.M[1][2] = YZ * oneMinusCosTheta + XsinTheta;
  matrix.M[2][2] = cosTheta + Z * Z * oneMinusCosTheta;
  matrix.M[3][2] = 0.0f;
  // fourth row
  matrix.M[0][3] = 0.0f;
  matrix.M[1][3] = 0.0f;
  matrix.M[2][3] = 0.0f;
  matrix.M[3][3] = 1.0f;
#endif
}

///////////////////////////////////////////////////////////////////////////////
// (See RotationAxis.h)
///////////////////////////////////////////////////////////////////////////////
void
RotationAxis::NormalizeAxis(
    ) throw ()
{
  F32 axisMagnitude = Math::SquareRoot(X * X + Y * Y + Z * Z);

  if (axisMagnitude > 0.0f)
  {
    X /= axisMagnitude;
    Y /= axisMagnitude;
    Z /= axisMagnitude;
  }
  else
  {
    X = 1.0f;
    Y = 0.0f;
    Z = 0.0f;
  }
}

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
