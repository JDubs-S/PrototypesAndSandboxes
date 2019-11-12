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

#include "Memory.h"

#include <string.h>

////////////////////////////////////////////////////////////////////////////////
// (See Memory.h)
////////////////////////////////////////////////////////////////////////////////
void
Memory::Zero(
    Size count,
    void * memory
    ) throw (Exception::Type)
{
  if (! (nullptr != memory))
  {
    throw (Exception::PARAMETER_ERROR);
  }

  memset(memory, 0, count);
}

////////////////////////////////////////////////////////////////////////////////
// (See Memory.h)
////////////////////////////////////////////////////////////////////////////////
void
Memory::Copy(
    Size sourceCount,
    const void * source,
    Size destinationCount,
    void * destination
    ) throw (Exception::Type)
{
  if (! (nullptr != source) && (nullptr != destination))
  {
    throw (Exception::PARAMETER_ERROR);
  }

  memcpy(destination, source, ((sourceCount < destinationCount) ? sourceCount : destinationCount));
}

////////////////////////////////////////////////////////////////////////////////
// (See Memory.h)
////////////////////////////////////////////////////////////////////////////////
void
Memory::Initialize(
    const U16 value,
    const Size count,
    U16 memory[]
    ) throw (Exception::Type)
{
  if (! (nullptr != memory))
  {
    throw (Exception::PARAMETER_ERROR);
  }

  for (Size i = 0; i < count; ++i)
  {
    memory[i] = value;
  }
}

////////////////////////////////////////////////////////////////////////////////
// (See Memory.h)
////////////////////////////////////////////////////////////////////////////////
void
Memory::Initialize(
    const S16 value,
    const Size count,
    S16 memory[]
    ) throw (Exception::Type)
{
  if (! (nullptr != memory))
  {
    throw (Exception::PARAMETER_ERROR);
  }

  for (Size i = 0; i < count; ++i)
  {
    memory[i] = value;
  }
}

/* *****************************************************************************
 *
 * Copyright (C) 2012, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
