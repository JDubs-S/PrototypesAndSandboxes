#pragma once
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

#include "Exception.h"
#include "NativeTypes.h"

#define Memory_Zero(memory) \
  Memory::Zero(sizeof(memory), memory)

#define Memory_Copy(source, destination) \
  Memory::Copy(sizeof(source), source, sizeof(destination), destination)

#define Memory_Initialize(value, memory) \
  Memory::Initialize(value, sizeof(memory), memory)

namespace Memory
{
  void
  Zero(
      Size count,
      void * memory
      ) throw (Exception::Type);

  void
  Copy(
      Size sourceCount,
      const void * source,
      Size destinationCount,
      void * destination
      ) throw (Exception::Type);

  void
  Initialize(
      const U16 value,
      const Size count,
      U16 memory[]
      ) throw (Exception::Type);

  void
  Initialize(
      const S16 value,
      const Size count,
      S16 memory[]
      ) throw (Exception::Type);

}

/* *****************************************************************************
 *
 * Copyright (C) 2012, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
