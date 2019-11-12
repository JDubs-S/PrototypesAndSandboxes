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

/* *****************************************************************************
 *
 * A C++ implementation of the Mersenne Twister PRNG, derived from the the
 * original C implementation by Makoto Matsumoto and Takuji Nishimura.
 *
 * ****************************************************************************/

#define UUT_RANDOM_NUMBER_GENERATOR 1

#include "NumberGenerator.hpp"

#define M                 397
#define MATRIX_A          0x9908b0dfUL
#define UPPER_MASK        0x80000000UL
#define LOWER_MASK        0x7fffffffUL

static const U64 sMag01[2] = {0x0UL, MATRIX_A};

/* *****************************************************************************
 * (See NumberGenerator.hpp)
 * ****************************************************************************/
NumberGenerator::NumberGenerator(
    ) throw ()
  : mMT()
  , mIndex(STATE_SIZE+1)
{
}

/* *****************************************************************************
 * (See NumberGenerator.hpp)
 * ****************************************************************************/
NumberGenerator::NumberGenerator(
    const NumberGenerator & other
    ) throw ()
  : mMT(other.mMT)
  , mIndex(other.mIndex)
{
}

/* *****************************************************************************
 * (See NumberGenerator.hpp)
 * ****************************************************************************/
NumberGenerator::~NumberGenerator(
    ) throw ()
{
}

/* *****************************************************************************
 * (See NumberGenerator.hpp)
 * ****************************************************************************/
NumberGenerator &
NumberGenerator::operator=(
    const NumberGenerator & other
    ) throw ()
{
  mMT = other.mMT;
  mIndex = other.mIndex;
  return *this;
}

/* *****************************************************************************
 * (See NumberGenerator.hpp)
 * ****************************************************************************/
void
NumberGenerator::Seed(
    U64 seed
    ) throw ()
{
  mMT[0]= seed & 0xFFFFFFFFUL;

  for (mIndex = 1; mIndex < STATE_SIZE; ++mIndex)
  {
    mMT[mIndex] = (1812433253UL * (mMT[mIndex-1] ^ (mMT[mIndex-1] >> 30)) + mIndex);

    mMT[mIndex] &= 0xFFFFFFFFUL;
  }
}

/* *****************************************************************************
 * (See NumberGenerator.hpp)
 * ****************************************************************************/
void
NumberGenerator::Seed(
    const U64 seed[],
    U32 count
    ) throw ()
{
  Seed(19650218UL);

  U32 i=1;
  U32 j=0;

  U32 k = ( STATE_SIZE > count ? STATE_SIZE : count);

  for (; k; k--)
  {
    mMT[i] = (mMT[i] ^ ((mMT[i-1] ^ (mMT[i-1] >> 30)) * 1664525UL)) + seed[j] + j;

    mMT[i] &= 0xffffffffUL;

    i++; j++;

    if (i>=STATE_SIZE) { mMT[0] = mMT[STATE_SIZE-1]; i=1; }

    if (j>=count) j=0;
  }

  for (k=STATE_SIZE-1; k; k--)
  {
    mMT[i] = (mMT[i] ^ ((mMT[i-1] ^ (mMT[i-1] >> 30)) * 1566083941UL)) - i;

    mMT[i] &= 0xffffffffUL;

    i++;

    if (i>=STATE_SIZE) { mMT[0] = mMT[STATE_SIZE-1]; i=1; }
  }

  mMT[0] = 0x80000000UL;
}

/* *****************************************************************************
 * (See NumberGenerator.hpp)
 * ****************************************************************************/
U32
NumberGenerator::GenerateU32(
    ) throw ()
{
  return (U32)Generate();
}

/* *****************************************************************************
 * (See NumberGenerator.hpp)
 * ****************************************************************************/
F64
NumberGenerator::GenerateF64(
    ) throw ()
{
  return ((F64)Generate() * (1.0/4294967295.0));
}

/* *****************************************************************************
 * (See NumberGenerator.hpp)
 * ****************************************************************************/
inline
U32
NumberGenerator::Generate(
    ) throw ()
{
  U64 temp;

  if (mIndex >= STATE_SIZE)
  {
    if (mIndex == (STATE_SIZE+1))
    {
      Seed(5489UL);
    }

    U32 i = 0;

    for (; i < (STATE_SIZE-M); ++i)
    {
      temp = (mMT[i] & UPPER_MASK) | (mMT[i+1] & LOWER_MASK);

      mMT[i] = mMT[i+M] ^ (temp >> 1) ^ sMag01[temp & 0x1UL];
    }

    for ( ; i < STATE_SIZE-1; ++i)
    {
      temp = (mMT[i] & UPPER_MASK) | (mMT[i+1] & LOWER_MASK);

      mMT[i] = mMT[i+(M-STATE_SIZE)] ^ (temp >> 1) ^ sMag01[temp & 0x1UL];
    }

    temp = (mMT[STATE_SIZE-1] & UPPER_MASK) | (mMT[0] & LOWER_MASK);

    mMT[STATE_SIZE-1] = mMT[M-1] ^ (temp >> 1) ^ sMag01[temp & 0x1UL];

    mIndex = 0;
  }

  temp = mMT[mIndex++];

  temp ^= (temp >> 11);
  temp ^= (temp << 7) & 0x9d2c5680UL;
  temp ^= (temp << 15) & 0xefc60000UL;
  temp ^= (temp >> 18);

  return (U32)(temp & 0x00000000FFFFFFFFUL);
}

/* *****************************************************************************
 *
 * Copyright (C) 2014, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
