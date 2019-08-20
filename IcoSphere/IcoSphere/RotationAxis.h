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

#include "NativeTypes.h"
#include "Matrix.h"
#include "Vector.h"

////////////////////////////////////////////////////////////////////////////////
//! Represents a right hand rotation about a given axis.
////////////////////////////////////////////////////////////////////////////////
class RotationAxis
{
public:

  inline
  RotationAxis(
      ) throw ()
      : X(1.0f)
      , Y(0.0f)
      , Z(0.0f)
  {
  }

  inline
  RotationAxis(
      const RotationAxis & other
      ) throw ()
      : X(other.X)
      , Y(other.Y)
      , Z(other.Z)
  {
  }

  inline
  RotationAxis(
      const Vector & vector
      ) throw ()
      : X(vector.X)
      , Y(vector.Y)
      , Z(vector.Z)
  {
    NormalizeAxis();
  }

  inline
  RotationAxis(
      F32 x,
      F32 y
      ) throw ()
      : X(x)
      , Y(y)
      , Z(0.0f)
  {
    NormalizeAxis();
  }

  inline
  RotationAxis(
      F32 x,
      F32 y,
      F32 z
      ) throw ()
      : X(x)
      , Y(y)
      , Z(z)
  {
    NormalizeAxis();
  }

  inline
  ~RotationAxis(
      ) throw ()
  {
  }

  inline
  RotationAxis &
  operator=(
      const RotationAxis & other
      ) throw ()
  {
    X = other.X;
    Y = other.Y;
    Z = other.Z;
    return *this;
  }

  inline
  RotationAxis &
  operator=(
      const Vector & vector
      ) throw ()
  {
    X = vector.X;
    Y = vector.Y;
    Z = vector.Z;
    NormalizeAxis();
    return *this;
  }

  void
  GetRotationMatrix(
      const F32 angle,
      CMatrix & matrix
      ) const throw ();

private:

  void
  NormalizeAxis(
      ) throw ();

  F32 X;
  F32 Y;
  F32 Z;

}__attribute__((packed));

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
