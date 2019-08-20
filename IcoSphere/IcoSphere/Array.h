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

#include "NativeTypes.h"

namespace Containers
{
template <class TYPE, U32 LENGTH>
class Array
{
public:

  inline Array() throw();

  inline Array(TYPE value) throw();

  inline Array(const Array & other) throw();

  inline ~Array() throw();

  inline Array<TYPE, LENGTH> & operator=(const Array<TYPE, LENGTH> & other) throw();

  inline U32 Length() const throw()  __attribute__((always_inline));

  inline TYPE & operator[](U32 index) throw() __attribute__((always_inline));
  inline TYPE & operator[](S32 index) throw() __attribute__((always_inline));

  inline TYPE operator[](U32 index) const throw() __attribute__((always_inline));
  inline TYPE operator[](S32 index) const throw() __attribute__((always_inline));

  inline operator TYPE *() throw() __attribute__((always_inline));

private:

  TYPE mData[LENGTH];

} __attribute__ ((packed));

}

template <class TYPE, U32 LENGTH>
inline Containers::Array<TYPE, LENGTH>::Array() throw()
{
}

template <class TYPE, U32 LENGTH>
inline Containers::Array<TYPE, LENGTH>::Array(TYPE value) throw()
{
  for (U32 i = 0; i < LENGTH; ++i) mData[i] = value;
}

template <class TYPE, U32 LENGTH>
inline Containers::Array<TYPE, LENGTH>::Array(const Array<TYPE, LENGTH> & other) throw()
{
  for (U32 i = 0; i < LENGTH; ++i) mData[i] = other.mData[i];
}

template <class TYPE, U32 LENGTH>
inline Containers::Array<TYPE, LENGTH>::~Array() throw()
{
}

template <class TYPE, U32 LENGTH>
inline U32 Containers::Array<TYPE, LENGTH>::Length() const throw()
{
  return LENGTH;
}

template <class TYPE, U32 LENGTH>
inline Containers::Array<TYPE, LENGTH> & Containers::Array<TYPE, LENGTH>::operator=(const Array<TYPE, LENGTH> & other) throw()
{
  for (U32 i = 0; i < LENGTH; ++i) mData[i] = other.mData[i];
  return *this;
}

template <class TYPE, U32 LENGTH>
inline TYPE & Containers::Array<TYPE, LENGTH>::operator[](U32 index) throw()
{
  return mData[index];
}

template <class TYPE, U32 LENGTH>
inline TYPE & Containers::Array<TYPE, LENGTH>::operator[](S32 index) throw()
{
  return mData[index];
}

template <class TYPE, U32 LENGTH>
inline TYPE Containers::Array<TYPE, LENGTH>::operator[](U32 index) const throw()
{
  return mData[index];
}

template <class TYPE, U32 LENGTH>
inline TYPE Containers::Array<TYPE, LENGTH>::operator[](S32 index) const throw()
{
  return mData[index];
}

template <class TYPE, U32 LENGTH>
inline
Containers::Array<TYPE, LENGTH>::operator TYPE *() throw()
{
  return &mData[0];
}

/* *****************************************************************************
 *
 * Copyright (C) 2012, 2019 by owner of https://github.com/JDubs-S.
 * All Rights Reserved
 *
 * ****************************************************************************/
