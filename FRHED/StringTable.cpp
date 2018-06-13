/*
Frhed - Free hex editor
Copyright (C) 2000 Raihan Kibria

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Last change: 2013-02-24 by Jochen Neubeck
*/
/** 
 * @file  StringTable.cpp
 *
 * @brief Implementation of the translation Stringtable.
 *
 */
#include "precomp.h"
#include "StringTable.h"
#include "resource.h"

StringTable<LPTSTR> S;

StringTable<WORD> IDS =
{
#	define DECLARE(X) X,
#	include "StringTable.inl"
#	undef DECLARE
};
