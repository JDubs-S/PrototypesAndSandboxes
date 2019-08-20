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

#include "IcosCell.h"
#include "IcosMap.h"
#include "NativeTypes.h"
#include "VertexArrayT.h"

class RenderContext;

class IcosCellView
{
public:

  IcosCellView(
      ) throw ();

  ~IcosCellView(
      ) throw ();

  void
  SetMapCell(
      const IcosMap & map,
      const IcosCell & cell
      ) throw ();

  void
  Render(
      RenderContext & context
      ) const throw ();

private:

  const IcosMap * Map;

  const IcosCell * Cell;

  static const Size MAX_SURFACE_VERTEX_COUNT = 8;
  VertexArrayT<MAX_SURFACE_VERTEX_COUNT> SurfaceVertexArray;

};

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
