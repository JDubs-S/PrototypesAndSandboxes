#pragma once
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

#include "NativeTypes.h"
#include "Vector.h"

////////////////////////////////////////////////////////////////////////////////
//
// This matrix is stored in column-major order:
//   (This is the matrix type used by OpenGL.)
//
//   m1   m5   m9   m13    M[0][0] M[1][0] M[2][0] M[3][0]
//   m2   m6   m10  m14 -- M[0][1] M[1][1] M[2][1] M[3][1]
//   m3   m7   m11  m15 -- M[0][2] M[1][2] M[2][2] M[3][2]
//   m4   m8   m12  m16    M[0][3] M[1][3] M[2][3] M[3][3]
//
// and is the transpose of a row-major matrix:
//
//   m1   m2   m3   m4     M[0][0] M[0][1] M[0][2] M[0][3]
//   m5   m6   m7   m8  -- M[1][0] M[1][1] M[1][2] M[1][3]
//   m9   m10  m11  m12 -- M[2][0] M[2][1] M[2][2] M[2][3]
//   m13  m14  m15  m16    M[3][0] M[3][1] M[3][2] M[3][3]
//
// Layout in memory is as:
//
// Address   C Array   Matrix    Transpose
// Offset    Index     Element   Element
// --------- --------- --------- ---------
// 0         M[0][0]   m1        m1
// 1         M[0][1]   m2        m5
// 2         M[0][2]   m3        m9
// 3         M[0][3]   m4        m13
// 4         M[1][0]   m5        m2
// 5         M[1][1]   m6        m6
// 6         M[1][2]   m7        m10
// 7         M[1][3]   m8        m14
// 8         M[2][0]   m9        m3
// 9         M[2][1]   m10       m7
// 10        M[2][2]   m11       m11
// 11        M[2][3]   m12       m15
// 12        M[3][0]   m13       m4
// 13        M[3][1]   m14       m8
// 14        M[3][2]   m15       m12
// 15        M[3][3]   m16       m16
//
////////////////////////////////////////////////////////////////////////////////
struct CMatrix
{
  F32 M[4][4];

  inline
  CMatrix(
      ) throw ()
  {
  }

  inline
  CMatrix(
      const CMatrix & other
      ) throw ()
  {
    M[0][0] = other.M[0][0];
    M[0][1] = other.M[0][1];
    M[0][2] = other.M[0][2];
    M[0][3] = other.M[0][3];

    M[1][0] = other.M[1][0];
    M[1][1] = other.M[1][1];
    M[1][2] = other.M[1][2];
    M[1][3] = other.M[1][3];

    M[2][0] = other.M[2][0];
    M[2][1] = other.M[2][1];
    M[2][2] = other.M[2][2];
    M[2][3] = other.M[2][3];

    M[3][0] = other.M[3][0];
    M[3][1] = other.M[3][1];
    M[3][2] = other.M[3][2];
    M[3][3] = other.M[3][3];
  }

  inline
  CMatrix(
      const F32 m[4][4] //!< Array matrix in row major order.
      ) throw ()
  {
    M[0][0] = m[0][0];
    M[1][0] = m[0][1];
    M[2][0] = m[0][2];
    M[3][0] = m[0][3];
    M[0][1] = m[1][0];
    M[1][1] = m[1][1];
    M[2][1] = m[1][2];
    M[3][1] = m[1][3];
    M[0][2] = m[2][0];
    M[1][2] = m[2][1];
    M[2][2] = m[2][2];
    M[3][2] = m[2][3];
    M[0][3] = m[3][0];
    M[1][3] = m[3][1];
    M[2][3] = m[3][2];
    M[3][3] = m[3][3];
  }

  inline
  CMatrix(
      const F32 m00, const F32 m10, const F32 m20, const F32 m30,
      const F32 m01, const F32 m11, const F32 m21, const F32 m31,
      const F32 m02, const F32 m12, const F32 m22, const F32 m32,
      const F32 m03, const F32 m13, const F32 m23, const F32 m33
      ) throw ()
  {
    M[0][0] = m00;
    M[0][1] = m01;
    M[0][2] = m02;
    M[0][3] = m03;

    M[1][0] = m10;
    M[1][1] = m11;
    M[1][2] = m12;
    M[1][3] = m13;

    M[2][0] = m20;
    M[2][1] = m21;
    M[2][2] = m22;
    M[2][3] = m23;

    M[3][0] = m30;
    M[3][1] = m31;
    M[3][2] = m32;
    M[3][3] = m33;
  }

  inline
  CMatrix &
  operator=(
      const CMatrix & other
      ) throw ()
  {
    M[0][0] = other.M[0][0];
    M[0][1] = other.M[0][1];
    M[0][2] = other.M[0][2];
    M[0][3] = other.M[0][3];

    M[1][0] = other.M[1][0];
    M[1][1] = other.M[1][1];
    M[1][2] = other.M[1][2];
    M[1][3] = other.M[1][3];

    M[2][0] = other.M[2][0];
    M[2][1] = other.M[2][1];
    M[2][2] = other.M[2][2];
    M[2][3] = other.M[2][3];

    M[3][0] = other.M[3][0];
    M[3][1] = other.M[3][1];
    M[3][2] = other.M[3][2];
    M[3][3] = other.M[3][3];

    return *this;
  }

  /////////////////////////////////////////////////////////////////////////////
  //! Multiply a vector by matrix and return the result.
  /////////////////////////////////////////////////////////////////////////////
  void
  Multiply(
      const Vector & vector,    //!< Vector to multiply by this matrix.
      Vector & result           //!< Result of multiplication.
      ) const throw();

}__attribute__((packed));

///////////////////////////////////////////////////////////////////////////////
//
// This is a typical C-style matrix.
//
// This matrix is stored in row-major order:
//
//   m1   m2   m3   m4     M[0][0] M[0][1] M[0][2] M[0][3]
//   m5   m6   m7   m8  -- M[1][0] M[1][1] M[1][2] M[1][3]
//   m9   m10  m11  m12 -- M[2][0] M[2][1] M[2][2] M[2][3]
//   m13  m14  m15  m16    M[3][0] M[3][1] M[3][2] M[3][3]
//
// and is the transpose of a column-major matrix:
//
//   m1   m5   m9   m13    M[0][0] M[1][0] M[2][0] M[3][0]
//   m2   m6   m10  m14 -- M[0][1] M[1][1] M[2][1] M[3][1]
//   m3   m7   m11  m15 -- M[0][2] M[1][2] M[2][2] M[3][2]
//   m4   m8   m12  m16    M[0][3] M[1][3] M[2][3] M[3][3]
//
// Layout in memory is as:
//
// Address   C Array   Matrix    Transpose
// Offset    Index     Element   Element
// --------- --------- --------- ---------
// 0         M[0][0]   m1        m1
// 1         M[0][1]   m2        m5
// 2         M[0][2]   m3        m9
// 3         M[0][3]   m4        m13
// 4         M[1][0]   m5        m2
// 5         M[1][1]   m6        m6
// 6         M[1][2]   m7        m10
// 7         M[1][3]   m8        m14
// 8         M[2][0]   m9        m3
// 9         M[2][1]   m10       m7
// 10        M[2][2]   m11       m11
// 11        M[2][3]   m12       m15
// 12        M[3][0]   m13       m4
// 13        M[3][1]   m14       m8
// 14        M[3][2]   m15       m12
// 15        M[3][3]   m16       m16
//
///////////////////////////////////////////////////////////////////////////////
struct RMatrix
{
  F32 M[4][4];
}__attribute__((packed));

///////////////////////////////////////////////////////////////////////////////
//!Identity Matrix
///////////////////////////////////////////////////////////////////////////////
const CMatrix IdentityMatrix(
    1.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 1.0f
    );

///////////////////////////////////////////////////////////////////////////////
//
//! Operators
//
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//! Multiply matrix A and B and return the result.
///////////////////////////////////////////////////////////////////////////////
CMatrix
operator*(
    const CMatrix & A,
    const CMatrix & B
    ) throw ();

///////////////////////////////////////////////////////////////////////////////
//! Multiply matrix M and vector V and return the result.
///////////////////////////////////////////////////////////////////////////////
Vector
operator*(
    const CMatrix & M,
    const Vector & V
    ) throw ();

///////////////////////////////////////////////////////////////////////////////
//! Compare matrix A and B.
///////////////////////////////////////////////////////////////////////////////
bool
operator==(
    const CMatrix & A,
    const CMatrix & B
    ) throw ();

///////////////////////////////////////////////////////////////////////////////
//! Compare matrix A and B.
///////////////////////////////////////////////////////////////////////////////
bool
operator!=(
    const CMatrix & A,
    const CMatrix & B
    ) throw ();

/* *****************************************************************************
 *
 * Copyright (C) 2012, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
