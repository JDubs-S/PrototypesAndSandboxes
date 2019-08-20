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

#include "Coordinates.h"
#include "Math.h"
#include "Matrix.h"
#include "Vector.h"

////////////////////////////////////////////////////////////////////////////////
//! Helper function for converting spherical coordinates to a vector.
////////////////////////////////////////////////////////////////////////////////
inline
static
void
ConvertToVector(
    const Coordinates::UnitSphereDegrees & coord,
    Vector & vector
    ) throw ()
{
  F32 latitudeRadians = Math::ConvertDegreesToRadians(coord.Latitude);
  F32 longitudeRadians = Math::ConvertDegreesToRadians(coord.Longitude);
  vector.X = Math::Cosine(latitudeRadians) * Math::Cosine(longitudeRadians);
  vector.Y = Math::Sine(latitudeRadians);
  vector.Z = Math::Cosine(latitudeRadians) * Math::Sine(longitudeRadians);
  vector.W = 1.0f;
  vector.Round(6u);
}

////////////////////////////////////////////////////////////////////////////////
//! Helper function for converting a vector to spherical coordinates.
////////////////////////////////////////////////////////////////////////////////
inline
static
void
ConvertFromVector(
    const Vector & vector,
    Coordinates::UnitSphereDegrees & coord
    ) throw ()
{
  // Vector must be normalized before latitude and longitude can be calculated.
  Vector normalizedXYZ(vector);
  normalizedXYZ.Normalize();

  // Calculate latitude, which is the arc sine of the Y axis coordinate.
  coord.Latitude = Math::ConvertRadiansToDegrees(
      Math::ArcSine(
          normalizedXYZ.Y
          )
      );

  // Convert the X,Z coordinates into a unit vector.
  Vector normalizedXZ(normalizedXYZ.X, 0.0f, normalizedXYZ.Z);
  normalizedXZ.Normalize();

  if (normalizedXZ.W > 0.0f)
  {
    // Calculate longitude, which is the arc cosine of the X axis coordinate of
    // the normalized X,Z vector.
    coord.Longitude = Math::ConvertRadiansToDegrees(
        Math::ArcCosine(
            normalizedXZ.X
            )
        );

    if (normalizedXZ.Z < 0.0f)
    {
      coord.Longitude = 360.0f - coord.Longitude;
    }
  }
  else
  {
    coord.Longitude = 0.0f;
  }
}

////////////////////////////////////////////////////////////////////////////////
// (See Vector.h)
////////////////////////////////////////////////////////////////////////////////
Vector::Vector(
    const Coordinates::UnitSphereDegrees & coord
    ) throw ()
{
  ConvertToVector(coord, *this);
}

////////////////////////////////////////////////////////////////////////////////
// (See Vector.h)
////////////////////////////////////////////////////////////////////////////////
Vector &
Vector::operator=(
    const Coordinates::UnitSphereDegrees & coord
    ) throw ()
{
  ConvertToVector(coord, *this);

  return *this;
}

////////////////////////////////////////////////////////////////////////////////
// (See Vector.h)
////////////////////////////////////////////////////////////////////////////////
Vector::operator Coordinates::UnitSphereDegrees (
    ) throw ()
{
  Coordinates::UnitSphereDegrees coordinates;

  ConvertFromVector(*this, coordinates);

  return coordinates;
}

////////////////////////////////////////////////////////////////////////////////
// (See Vector.h)
////////////////////////////////////////////////////////////////////////////////
F32
Vector::Length(
    ) const throw ()
{
  return Math::SquareRoot(X * X + Y * Y + Z * Z);
}

////////////////////////////////////////////////////////////////////////////////
// (See Vector.h)
////////////////////////////////////////////////////////////////////////////////
void
Vector::Normalize(
    ) throw ()
{
  F32 axisMagnitude = Math::SquareRoot(X * X + Y * Y + Z * Z);

  if (axisMagnitude > 0.0f)
  {
    X /= axisMagnitude;
    Y /= axisMagnitude;
    Z /= axisMagnitude;
    W = 1.0f;
  }
  else
  {
    X = 0.0f;
    Y = 0.0f;
    Z = 0.0f;
    W = 0.0f;
  }
}

////////////////////////////////////////////////////////////////////////////////
// (See Vector.h)
////////////////////////////////////////////////////////////////////////////////
void
Vector::Round(
    U8 decimalPlaces
    ) throw ()
{
  X = Math::Round(X, decimalPlaces);
  Y = Math::Round(Y, decimalPlaces);
  Z = Math::Round(Z, decimalPlaces);
  W = Math::Round(W, decimalPlaces);
}

////////////////////////////////////////////////////////////////////////////////
// (See Vector.h)
////////////////////////////////////////////////////////////////////////////////
Vector
Vector::CrossProduct(
    const Vector & vA,
    const Vector & vB
    ) throw ()
{
  F32 x = vA.Y * vB.Z - vA.Z * vB.Y;
  F32 y = vA.Z * vB.X - vA.X * vB.Z;
  F32 z = vA.X * vB.Y - vA.Y * vB.X;
  return Vector(x,y,z,1.0f);
}

///////////////////////////////////////////////////////////////////////////////
// (See Vector.h)
///////////////////////////////////////////////////////////////////////////////
F32
Vector::LeastAngleRadians(
    Vector & a,
    Vector & b
    ) throw ()
{
  F32 aLength = a.Length();
  F32 bLength = b.Length();
  F32 result = 0.0f;

  if ((aLength != 0.0f) && (bLength != 0))
  {
    result = Math::ArcCosine(
        ((a.X * b.X + a.Y * b.Y + a.Z * b.Z) / (aLength * bLength))
        );
  }

  return result;
}

/* *****************************************************************************
 *
 * Copyright (C) 2012, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/

