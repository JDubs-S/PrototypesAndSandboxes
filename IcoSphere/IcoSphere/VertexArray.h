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

#include "Exception.h"
#include "NativeTypes.h"
#include "Vertex.h"

class RenderContext;

class VertexArray
{
public:

  enum Type
  {
    TYPE_POINTS,
    TYPE_TRIANGLE_FAN
  };

  VertexArray(
      Type drawType
      ) throw ();

  virtual
  ~VertexArray(
      ) throw ();

protected:

  friend class RenderContext;

  virtual
  Size
  GetDrawCount(
      ) const throw () = 0;

  virtual
  Size
  GetStride(
      ) const throw () = 0;

  virtual
  Size
  GetGLVertexSize(
      ) const throw () = 0;

  virtual
  const F32 *
  GetGLVertexPointer(
      ) const throw () = 0;

  virtual
  Size
  GetGLColorSize(
      ) const throw () = 0;

  virtual
  const F32 *
  GetGLColorPointer(
      ) const throw () = 0;

  virtual
  Size
  GetGLNormalSize(
      ) const throw () = 0;

  virtual
  const F32 *
  GetGLNormalPointer(
      ) const throw () = 0;

  virtual
  Size
  GetGLTextureCoordinateSize(
      ) const throw () = 0;

  virtual
  const F32 *
  GetGLTextureCoordinatePointer(
      ) const throw () = 0;

private:

  Type DrawType;

private:

  VertexArray(
      const VertexArray &
      ) throw ();

  VertexArray &
  operator=(
      const VertexArray &
      ) throw ();

};

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/

