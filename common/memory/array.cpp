/*
* Copyright (c) 2011 Sveriges Television AB <info@casparcg.com>
*
* This file is part of CasparCG (www.casparcg.com).
*
* CasparCG is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* CasparCG is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with CasparCG. If not, see <http://www.gnu.org/licenses/>.
*
* Author: Robert Nagy, ronag89@gmail.com
*/

#include "../stdafx.h"

#include "array.h"

#include "../assert.h"

namespace caspar { namespace core {
		
mutable_array::mutable_array(mutable_array&& other)
	: ptr_(other.ptr_)
	, size_(other.size_)
	, cacheable_(other.cacheable_)
	, storage_(std::move(other.storage_))
{
	CASPAR_ASSERT(storage_);
}
	
mutable_array& mutable_array::operator=(mutable_array&& other)
{
	ptr_		= other.ptr_;
	size_		= other.size_;
	cacheable_  = other.cacheable_;
	storage_	= std::move(other.storage_);

	CASPAR_ASSERT(storage_);

	return *this;
}
		
std::uint8_t* mutable_array::begin()				{return ptr_;}		
std::uint8_t* mutable_array::data()					{return ptr_;}
std::uint8_t* mutable_array::end()					{return ptr_ + size_;}	
const std::uint8_t* mutable_array::begin() const	{return ptr_;}		
const std::uint8_t* mutable_array::data() const		{return ptr_;}
const std::uint8_t* mutable_array::end() const		{return ptr_ + size_;}
std::size_t mutable_array::size() const				{return size_;}
bool mutable_array::empty() const					{return size() == 0;}
bool mutable_array::cacheable() const				{return cacheable_;}

const_array::const_array(const const_array& other)
	: ptr_(other.ptr_)
	, size_(other.size_)
	, cacheable_(other.cacheable_)
	, storage_(other.storage_)
{
	CASPAR_ASSERT(storage_);
}

const_array::const_array(mutable_array&& other)
	: ptr_(other.ptr_)
	, size_(other.size_)
	, cacheable_(other.cacheable_)
	, storage_(std::move(other.storage_))
{
	CASPAR_ASSERT(storage_);
}

const_array& const_array::operator=(const const_array& other)
{
	const_array(other).swap(*this);
	return *this;
}

void const_array::swap(const_array& other)
{
	ptr_		= other.ptr_;
	size_		= other.size_;
	storage_	= other.storage_;
	cacheable_	= other.cacheable_;
}
			
const std::uint8_t* const_array::begin() const	{return ptr_;}		
const std::uint8_t* const_array::data() const	{return ptr_;}
const std::uint8_t* const_array::end() const	{return ptr_ + size_;}
std::size_t const_array::size() const			{return size_;}
bool const_array::empty() const					{return size() == 0;}
bool const_array::cacheable() const				{return cacheable_;}

}}