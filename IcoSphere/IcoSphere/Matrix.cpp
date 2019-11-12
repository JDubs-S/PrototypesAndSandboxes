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

#include "Matrix.h"

////////////////////////////////////////////////////////////////////////////////
// (See Matrix.h)
////////////////////////////////////////////////////////////////////////////////
void
CMatrix::Multiply(
   const Vector & vector,
   Vector & result
   ) const throw ()
{
  result.X = vector.X * M[0][0] + vector.Y * M[1][0] + vector.Z * M[2][0] + vector.W * M[3][0];
  result.Y = vector.X * M[0][1] + vector.Y * M[1][1] + vector.Z * M[2][1] + vector.W * M[3][1];
  result.Z = vector.X * M[0][2] + vector.Y * M[1][2] + vector.Z * M[2][2] + vector.W * M[3][2];
  result.W = vector.X * M[0][3] + vector.Y * M[1][3] + vector.Z * M[2][3] + vector.W * M[3][3];
}

////////////////////////////////////////////////////////////////////////////////
// (See Matrix.h)
////////////////////////////////////////////////////////////////////////////////
CMatrix
operator*(
    const CMatrix & A,
    const CMatrix & B
    ) throw ()
{
  CMatrix m;
  m.M[0][0] = A.M[0][0] * B.M[0][0];
  m.M[0][1] = A.M[0][1] * B.M[0][1];
  m.M[0][2] = A.M[0][2] * B.M[0][2];
  m.M[0][3] = A.M[0][3] * B.M[0][3];
  m.M[1][0] = A.M[1][0] * B.M[1][0];
  m.M[1][1] = A.M[1][1] * B.M[1][1];
  m.M[1][2] = A.M[1][2] * B.M[1][2];
  m.M[1][3] = A.M[1][3] * B.M[1][3];
  m.M[2][0] = A.M[2][0] * B.M[2][0];
  m.M[2][1] = A.M[2][1] * B.M[2][1];
  m.M[2][2] = A.M[2][2] * B.M[2][2];
  m.M[2][3] = A.M[2][3] * B.M[2][3];
  m.M[3][0] = A.M[3][0] * B.M[3][0];
  m.M[3][1] = A.M[3][1] * B.M[3][1];
  m.M[3][2] = A.M[3][2] * B.M[3][2];
  m.M[3][3] = A.M[3][3] * B.M[3][3];
  return m;
}

////////////////////////////////////////////////////////////////////////////////
// (See Matrix.h)
////////////////////////////////////////////////////////////////////////////////
Vector
operator*(
    const CMatrix & M,
    const Vector & V
    ) throw ()
{
  Vector result;
  result.X = V.X * M.M[0][0] + V.Y * M.M[1][0] + V.Z * M.M[2][0] + V.W * M.M[3][0];
  result.Y = V.X * M.M[0][1] + V.Y * M.M[1][1] + V.Z * M.M[2][1] + V.W * M.M[3][1];
  result.Z = V.X * M.M[0][2] + V.Y * M.M[1][2] + V.Z * M.M[2][2] + V.W * M.M[3][2];
  result.W = V.X * M.M[0][3] + V.Y * M.M[1][3] + V.Z * M.M[2][3] + V.W * M.M[3][3];
  return result;
}

////////////////////////////////////////////////////////////////////////////////
// (See Matrix.h)
////////////////////////////////////////////////////////////////////////////////
bool
operator==(
    const CMatrix & A,
    const CMatrix & B
    ) throw ()
{
  bool equal = true;

  for (int i = 0; (equal && (i < 4)); ++i)
  {
    for (int j = 0; (equal && (j < 4)); ++j)
    {
      F32 diff = A.M[i][j] - B.M[i][j];

      equal = ((Math::N_EPSILON < diff) && (diff < Math::P_EPSILON));
    }
  }

  return equal;
}

////////////////////////////////////////////////////////////////////////////////
// (See Matrix.h)
////////////////////////////////////////////////////////////////////////////////
bool
operator!=(
    const CMatrix & A,
    const CMatrix & B
    ) throw ()
{
  bool notEqual = true;

  for (int i = 0; (notEqual && (i < 4)); ++i)
  {
    for (int j = 0; (notEqual && (j < 4)); ++j)
    {
      F32 diff = A.M[i][j] - B.M[i][j];

      notEqual = ((diff < Math::N_EPSILON) || (Math::P_EPSILON < diff));
    }
  }

  return notEqual;
}

/* *****************************************************************************
 *
 * Copyright (C) 2012, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
