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

#include "NativeTypes.h"

#include "Array.h"

/* *****************************************************************************
 *
 * A C++ implementation of the Mersenne Twister PRNG, derived from the the
 * original C implementation by Makoto Matsumoto and Takuji Nishimura.
 *
 * ****************************************************************************/
class NumberGenerator
{
public:

  /* ***************************************************************************
   *
   * **************************************************************************/
  NumberGenerator(
      ) throw ();

  /* ***************************************************************************
   *
   * **************************************************************************/
  NumberGenerator(
      const NumberGenerator & other
      ) throw ();

  /* ***************************************************************************
   *
   * **************************************************************************/
  ~NumberGenerator(
      ) throw ();

  /* ***************************************************************************
   *
   * **************************************************************************/
  NumberGenerator &
  operator=(
      const NumberGenerator & other
      ) throw ();

  /* ***************************************************************************
   *
   * **************************************************************************/
  void Seed(
      U64 seed
      ) throw ();

  /* ***************************************************************************
   *
   * **************************************************************************/
  void Seed(
      const U64 seed[],
      U32 count
      ) throw ();

  /* ***************************************************************************
   *
   * **************************************************************************/
  U32
  GenerateU32(
      ) throw ();

  /* ***************************************************************************
   *
   * **************************************************************************/
  F64
  GenerateF64(
      ) throw ();

private:

  inline
  U32
  Generate(
      ) throw ();

private:

  static const U32 STATE_SIZE = 624;

  Containers::Array<U64, STATE_SIZE> mMT;

  U32 mIndex;

};

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
