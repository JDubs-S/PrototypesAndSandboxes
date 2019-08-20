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

struct ColorRGBA
{
  F32 R;
  F32 G;
  F32 B;
  F32 A;

  inline
  ColorRGBA(
      ) throw ()
      : R()
      , G()
      , B()
      , A()
  {
  }

  inline
  ColorRGBA(
      const ColorRGBA & other
      ) throw ()
      : R(other.R)
      , G(other.G)
      , B(other.B)
      , A(other.A)
  {
  }

  inline
  ColorRGBA(
      const F32 initializerArray[],
      const Size initializerCount
      ) throw ()
      : R(0.0f)
      , G(0.0f)
      , B(0.0f)
      , A(0.0f)
  {
    if (initializerArray != nullptr)
    {
      for (int i = 0; i < initializerCount; i++)
      {
        (*this)[i] = initializerArray[i];
      }
    }
  }

  inline
  ColorRGBA(
      F32 r,
      F32 g,
      F32 b
      ) throw ()
      : R(r)
      , G(g)
      , B(b)
      , A(0.0f)
  {
  }

  inline
  ColorRGBA(
      F32 r,
      F32 g,
      F32 b,
      F32 a
      ) throw ()
      : R(r)
      , G(g)
      , B(b)
      , A(a)
  {
  }

  inline
  ~ColorRGBA(
      ) throw ()
  {
  }

  inline
  ColorRGBA &
  operator=(
      const ColorRGBA & other
      ) throw ()
  {
    R = other.R;
    G = other.G;
    B = other.B;
    A = other.A;
    return *this;
  }

  inline
  const F32 &
  operator[](
      int index
      ) const throw ()
  {
    const F32 * retVal;

    if (index <= 0)
      retVal = &R;
    else if (index == 1)
      retVal = &G;
    else if (index == 2)
      retVal = &B;
    else
      retVal = &A;

    return *retVal;
  }

  inline
  F32 &
  operator[](
      int index
      ) throw ()
  {
    F32 * retVal;

    if (index <= 0)
      retVal = &R;
    else if (index == 1)
      retVal = &G;
    else if (index == 2)
      retVal = &B;
    else
      retVal = &A;

    return *retVal;
  }

  inline
  ColorRGBA operator*(
      F32 scalar
      ) const throw ()
  {
    return ColorRGBA(R * scalar, G * scalar, B * scalar, A);
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
    return &R;
  }
}__attribute__((aligned (4), packed));

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
 
