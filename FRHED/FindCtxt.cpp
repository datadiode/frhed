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
 * @file  FindCtxt.cpp
 *
 * @brief Implementation of the hex window.
 *
 */
#include "precomp.h"
#include "FindCtxt.h"

/**
 * @brief Constructor.
 */
FindCtxt::FindCtxt()
: m_pText(NULL)
, m_bMatchCase(false)
, m_iDirection(0)
, m_bUnicode(false)
{
}

/**
 * @brief Destructor.
 */
FindCtxt::~FindCtxt()
{
	free(m_pText);
}

/**
 * @brief Clear the search text.
 */
void FindCtxt::ClearText()
{
	free(m_pText);
	m_pText = NULL;
}

/**
 * @brief Set the search text.
 * @param [in] text New search text.
 */
void FindCtxt::SetText(LPCSTR text)
{
	ClearText();
	m_pText = _strdup(text);
}
