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
 * @file  LangTools.cpp
 *
 * @brief A few functions related to UI translation.
 *
 */
#include "precomp.h"
#include "hexwnd.h"
#include "AnsiConvert.h"
#include "LangArray.h"

LangArray langArray;

void NTAPI TranslateDialog(HWND hwnd)
{
	langArray.TranslateDialog(hwnd);
}

int NTAPI ShowModalDialog(UINT idd, HWindow *pwnd, DLGPROC dlgproc, LPVOID param)
{
	HINSTANCE hinst = langArray.m_hLangDll ? langArray.m_hLangDll : hMainInstance;
	return static_cast<int>(DialogBoxParam(
		hinst, MAKEINTRESOURCE(idd), pwnd->m_hWnd, dlgproc, (LPARAM)param));
}
