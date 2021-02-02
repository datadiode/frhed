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

Last change: 2013-04-10 by Jochen Neubeck
*/
/**
 * @file  precomp.h
 *
 * @brief Precompiled header files listing.
 *
 */
// Needed to include
// DISK_GEOMETRY_EX, PARTITION_INFORMATION_EX
// and couple of others from WinIoCtl.h
#define _WIN32_WINNT 0x0501
#define _WIN32_IE 0x0700
#define _CRT_NON_CONFORMING_SWPRINTFS

#include "H2O.h"

using H2O::HWindow;
using H2O::HButton;
using H2O::HComboBox;
using H2O::HEdit;
using H2O::HListBox;
using H2O::HListView;
using H2O::HToolBar;
using H2O::HStatusBar;
using H2O::HSurface;
using H2O::HGdiObj;
using H2O::HFont;
using H2O::HBrush;
using H2O::HPen;
using H2O::HMenu;

using MAUtil::Vector;
using MAUtil::String;

// Token pasting macros taken from
// https://github.com/alexforencich/templates/blob/master/xmega.cpp/usart.h
// Copyright (c) 2011 Alex Forencich
// SPDX-License-Identifier: MIT

#define TOKEN_PASTE2_INT(x, y) x ## y
#define TOKEN_PASTE2(x, y) TOKEN_PASTE2_INT(x, y)
#define TOKEN_PASTE3_INT(x, y, z) x ## y ## z
#define TOKEN_PASTE3(x, y, z) TOKEN_PASTE3_INT(x, y, z)

namespace NT4
{
	struct OPENFILENAME : public OPENFILENAME_NT4
	{
	};
	extern "C" BOOL APIENTRY GetOpenFileName(OPENFILENAME *);
	extern "C" BOOL APIENTRY GetSaveFileName(OPENFILENAME *);
}

using NT4::OPENFILENAME;
using NT4::GetOpenFileName;
using NT4::GetSaveFileName;

#include <windowsx.h>
#include <crtdbg.h>
#include <crtdefs.h>
#include <assert.h>
#include <tchar.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <direct.h>
#include <string.h>
#include <stdio.h>
#include <commctrl.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <limits.h>
#include "gtools.h"
