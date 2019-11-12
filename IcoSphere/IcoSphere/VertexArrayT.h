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

#include "Vector.h"
#include "Vertex.h"
#include "VertexArray.h"

template<Size MAX_VERTEX_COUNT>
class VertexArrayT : public VertexArray
{
public:

  VertexArrayT(
      Type drawType
      ) throw ()
      : VertexArray(drawType)
      , DrawCount(0u)
      , Array()
  {
  }

  ~VertexArrayT(
      ) throw ()
  {
  }

  inline
  const Vertex &
  operator[](
      Size i
      ) const throw ()
  {
    return Array[i];
  }

  //////////////////////////////////////////////////////////////////////////////
  //! Resets vertex count to zero.
  //////////////////////////////////////////////////////////////////////////////
  inline
  void
  Reset(
      ) throw ()
  {
    DrawCount = 0;
  }

  inline
  void AddVertex(
      const Vector & pos
      ) throw ()
  {
    if (DrawCount < MAX_VERTEX_COUNT)
    {
      Array[DrawCount].Position = pos;
      Array[DrawCount].Color = Color;
    }
    DrawCount++;
  }

  ColorRGBA Color;

protected:

  Size
  GetDrawCount(
      ) const throw ()
  {
    return DrawCount;
  }

  Size
  GetStride(
      ) const throw ()
  {
    return sizeof(Vertex);
  }

  Size
  GetGLVertexSize(
      ) const throw ()
  {
    return Array[0].GetGLVertexSize();
  }

  const F32 *
  GetGLVertexPointer(
      ) const throw ()
  {
    return Array[0].GetGLVertexPointer();
  }

  Size
  GetGLColorSize(
      ) const throw ()
  {
    return Array[0].GetGLColorSize();
  }

  const F32 *
  GetGLColorPointer(
      ) const throw ()
  {
    return Array[0].GetGLColorPointer();
  }

  Size
  GetGLNormalSize(
      ) const throw ()
  {
    return Array[0].GetGLNormalSize();
  }

  const F32 *
  GetGLNormalPointer(
      ) const throw ()
  {
    return Array[0].GetGLNormalPointer();
  }

  Size
  GetGLTextureCoordinateSize(
      ) const throw ()
  {
    return Array[0].GetGLTextureCoordinateSize();
  }

  const F32 *
  GetGLTextureCoordinatePointer(
      ) const throw ()
  {
    return Array[0].GetGLTextureCoordinatePointer();
  }

private:

  Size DrawCount;

  Vertex Array[MAX_VERTEX_COUNT];

private:

  VertexArrayT(
      const VertexArrayT<MAX_VERTEX_COUNT> &
      ) throw ();

  VertexArrayT<MAX_VERTEX_COUNT> &
  operator=(
      const VertexArrayT<MAX_VERTEX_COUNT> &
      ) throw ();

} __attribute__((packed));

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/

