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

#include "NativeTypes.h"
#include "RenderContext.h"
#include "VertexArray.h"

#include <OpenGL/gl3.h>

RenderContext::RenderContext(
    ) throw ()
{
}

RenderContext::~RenderContext(
    ) throw ()
{
}

void
RenderContext::Reset(
    ) throw ()
{
#ifndef TESTING
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  glDepthMask(GL_TRUE);
  glClearDepthf(1.0f);
  glClear(GL_DEPTH_BUFFER_BIT);
#endif
}

void
RenderContext::Draw(
    const VertexArray & array
    ) throw ()
{
#ifndef TESTING
  Size stride = array.GetStride();
  Size drawCount = array.GetDrawCount();
  U32 drawType = GetGLDrawType(array.DrawType);
  const F32 *vertexPointer = array.GetGLVertexPointer();
  Size vertexSize = array.GetGLVertexSize();
  const F32 *colorPointer = array.GetGLColorPointer();
  Size colorSize = array.GetGLColorSize();

  // Enable vertex arrays.
  glEnableVertexAttribArray(0); // position
  glVertexAttribPointer(0, vertexSize, GL_FLOAT, GL_FALSE, stride, vertexPointer);

  if (nullptr != colorPointer)
  {
    glEnableVertexAttribArray(1); // color
    glVertexAttribPointer(1, colorSize, GL_FLOAT, GL_FALSE, stride, colorPointer);
  }

  // Draw the vertex arrays.
  glDrawArrays(drawType, 0, drawCount);

  // Disable vertex arrays.
  if (nullptr != colorPointer)
  {
    glDisableVertexAttribArray(1);
  }

  glDisableVertexAttribArray(0);
#endif
}

////////////////////////////////////////////////////////////////////////////////
//! Returns the OpenGL ES 2.0 array type.
////////////////////////////////////////////////////////////////////////////////
U32
RenderContext::GetGLDrawType(
    VertexArray::Type type
    ) const throw ()
{
  U32 drawType = 0;

  if (VertexArray::TYPE_POINTS == type)
  {
    drawType = GL_POINTS;
  }
  else if (VertexArray::TYPE_TRIANGLE_FAN == type)
  {
    drawType = GL_TRIANGLE_FAN;
  }

  return drawType;
}

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
