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

#include "IcosMapView.h"
#include "RenderContext.h"

IcosMapView::IcosMapView(
    ) throw ()
    : Map(nullptr)
    , CellViewCount(0u)
{
}

IcosMapView::~IcosMapView(
    ) throw ()
{
}

void
IcosMapView::SetMap(
    const IcosMap & map
    ) throw ()
{
  Map = & map;

  CellViewCount = Map->GetCellCount();

  for (U16 i = 0; i < CellViewCount; ++i)
  {
    CellView[i].SetMapCell(*Map, Map->GetCell(i));
  }
}

void
IcosMapView::Render(
    RenderContext & context
    ) const throw ()
{
  if (nullptr != Map)
  {
    for (U16 i = 0; i < CellViewCount; ++i)
    {
      CellView[i].Render(context);
    }
  }
}

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
