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

#include "ColorRGBA.h"
#include "Vector.h"

struct Vertex
{
  Vector    Position;   //! Position of vertex in model space.
  ColorRGBA Color;      //! Color of vertex.

  inline
  Vertex(
      ) throw ()
      : Position()
      , Color()
  {
  }

  inline
  Vertex(
      Vector position,
      Vector normal,
      Vector textureCoordinate,
      ColorRGBA color
      ) throw ()
      : Position(position)
      , Color(color)
  {
  }

  inline
  Vertex(
      const Vector & position,
      const ColorRGBA & color
      ) throw ()
      : Position(position)
      , Color(color)
  {
  }

  inline
  Vertex(
      const Vertex & other
      ) throw ()
      : Position(other.Position)
      , Color(other.Color)
  {
  }

  inline
  ~Vertex(
      ) throw ()
  {
  }

  inline
  Vertex &
  operator=(
      const Vertex & other
      ) throw ()
  {
    Position = other.Position;
    Color = other.Color;
    return *this;
  }

  inline
  Size
  GetGLVertexSize(
      ) const throw ()
  {
    return Position.GetGLSize();
  }

  inline
  const F32 *
  GetGLVertexPointer(
      ) const throw ()
  {
    return Position.GetGLPointer();
  }

  inline
  Size
  GetGLColorSize(
      ) const throw ()
  {
    return Color.GetGLSize();
  }

  inline
  const F32 *
  GetGLColorPointer(
      ) const throw ()
  {
    return Color.GetGLPointer();
  }

  inline
  Size
  GetGLNormalSize(
      ) const throw ()
  {
    return 0;
  }

  inline
  const F32 *
  GetGLNormalPointer(
      ) const throw ()
  {
    return nullptr;
  }

  inline
  Size
  GetGLTextureCoordinateSize(
      ) const throw ()
  {
    return 0;
  }

  inline
  const F32 *
  GetGLTextureCoordinatePointer(
      ) const throw ()
  {
    return nullptr;
  }
} __attribute__((packed));

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
