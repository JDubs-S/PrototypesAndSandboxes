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

#include "Math.h"
#include "NativeTypes.h"

///////////////////////////////////////////////////////////////////////////////
// Forward declarations.
///////////////////////////////////////////////////////////////////////////////
namespace Coordinates
{
  struct UnitSphereDegrees;
}

struct Vector
{
  F32 X;
  F32 Y;
  F32 Z;
  F32 W;

  inline
  Vector() throw ()
      : X()
      , Y()
      , Z()
      , W()
  {
  }

  inline
  Vector(
      const Vector & other
      ) throw ()
      : X(other.X)
      , Y(other.Y)
      , Z(other.Z)
      , W(other.W)
  {
  }

  Vector(
      const Coordinates::UnitSphereDegrees & coord
      ) throw ();

  inline
  Vector(
      const F32 initializerArray[],
      const Size initializerCount
      ) throw ()
      : X(0.0f)
      , Y(0.0f)
      , Z(0.0f)
      , W(1.0f)
  {
    if (initializerArray != nullptr)
    {
      for (Size i = 0; i < initializerCount; i++)
      {
        (*this)[i] = initializerArray[i];
      }
    }
  }

  inline
  Vector(
      F32 x,
      F32 y
      ) throw ()
      : X(x)
      , Y(y)
      , Z(0.0f)
      , W(1.0f)
  {
  }

  inline
  Vector(
      F32 x,
      F32 y,
      F32 z
      ) throw ()
      : X(x)
      , Y(y)
      , Z(z)
      , W(1.0f)
  {
  }

  inline
  Vector(
      F32 x,
      F32 y,
      F32 z,
      F32 w
      ) throw ()
      : X(x)
      , Y(y)
      , Z(z)
      , W(w)
  {
  }

  inline
  ~Vector(
      ) throw ()
  {
  }

  inline
  Vector &
  operator=(
      const Vector & other
      ) throw ()
  {
    X = other.X;
    Y = other.Y;
    Z = other.Z;
    W = other.W;
    return *this;
  }

  Vector &
  operator=(
      const Coordinates::UnitSphereDegrees & other
      ) throw ();

  operator Coordinates::UnitSphereDegrees (
      ) throw ();

  inline
  const F32 &
  operator[](
      int index
      ) const throw ()
  {
    const F32 * result;

    if (index <= 0)
      result = &X;
    else if (index == 1)
      result = &Y;
    else if (index == 2)
      result = &Z;
    else
      result = &W;

    return *result;
  }

  inline
  F32 &
  operator[](
      int index
      ) throw ()
  {
    F32 * result;

    if (index <= 0)
      result = &X;
    else if (index == 1)
      result = &Y;
    else if (index == 2)
      result = &Z;
    else
      result = &W;

    return *result;
  }

  inline
  Size
  GetGLSize(
      ) const throw ()
  {
    return 4;
  }

  inline
  const F32 *
  GetGLPointer(
      ) const throw ()
  {
    return &X;
  }

  /////////////////////////////////////////////////////////////////////////////
  //! Returns the length of this vector.
  /////////////////////////////////////////////////////////////////////////////
  F32
  Length(
      ) const throw ();

  /////////////////////////////////////////////////////////////////////////////
  //! Normalize the X, Y, Z components of this vector. Sets W = 1 if the normal
  //! length is not zero, otherwise W = 0.
  /////////////////////////////////////////////////////////////////////////////
  void
  Normalize(
      ) throw ();

  /////////////////////////////////////////////////////////////////////////////
  //! Rounds each component to the nearest decimal fraction with the given
  //! number of decimal places.
  /////////////////////////////////////////////////////////////////////////////
  void
  Round(
      U8 decimalPlaces  //!< Maximum number of non-zero decimal places in result.
      ) throw ();

  ///////////////////////////////////////////////////////////////////////////////
  //! Calculates the cross product of two vector as if they only had three
  //! components X, Y, Z and returns the result with W = 1.
  ///////////////////////////////////////////////////////////////////////////////
  static
  Vector
  CrossProduct(
      const Vector & vA,    //!< Vector A.
      const Vector & vB     //!< Vector B.
      ) throw ();

  /////////////////////////////////////////////////////////////////////////////
  //! Calculates the least angle in Radians between two vectors.
  /////////////////////////////////////////////////////////////////////////////
  static
  F32
  LeastAngleRadians(
      Vector & a,   //!< Angle is measured from this vector.
      Vector & b    //!< Angle is measured to this vector.
      ) throw ();

}__attribute__((aligned (4), packed));

inline
Vector
operator+(
    const Vector & a,
    const Vector & b
    )
{
  return Vector(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

inline
Vector
operator-(
          const Vector & a,
          const Vector & b
          )
{
  return Vector(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}

inline
F32
operator*(
          const Vector & a,
          const Vector & b
          )
{
  return (a.X * b.X + a.Y * b.Y + a.Z * b.Z);
}

inline
Vector
operator*(
          const Vector & a,
          const F32 scalar
          )
{
  return Vector(a.X * scalar, a.Y * scalar, a.Z * scalar);
}

inline
Vector
operator/(
    const Vector & a,
    const F32 divisor
    )
{
  return Vector(a.X / divisor, a.Y / divisor, a.Z / divisor);
}

inline
bool
operator==(
    const Vector & a,
    const Vector & b
    )
{
  F32 diffX = a.X - b.X;
  F32 diffY = a.Y - b.Y;
  F32 diffZ = a.Z - b.Z;
  F32 diffW = a.W - b.W;
  return (
      (Math::N_EPSILON < diffX) && (diffX < Math::P_EPSILON) &&
      (Math::N_EPSILON < diffY) && (diffY < Math::P_EPSILON) &&
      (Math::N_EPSILON < diffZ) && (diffZ < Math::P_EPSILON) &&
      (Math::N_EPSILON < diffW) && (diffW < Math::P_EPSILON)
      );
}

inline
bool
operator!=(
    const Vector & a,
    const Vector & b
    )
{
  F32 diffX = a.X - b.X;
  F32 diffY = a.Y - b.Y;
  F32 diffZ = a.Z - b.Z;
  F32 diffW = a.W - b.W;
  return (
      (diffX < Math::N_EPSILON) || (Math::P_EPSILON < diffX) ||
      (diffY < Math::N_EPSILON) || (Math::P_EPSILON < diffY) ||
      (diffZ < Math::N_EPSILON) || (Math::P_EPSILON < diffZ) ||
      (diffW < Math::N_EPSILON) || (Math::P_EPSILON < diffW)
      );
}

/* *****************************************************************************
 *
 * Copyright (C) 2012, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
