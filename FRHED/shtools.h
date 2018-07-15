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
 * @file  shtools.h
 *
 * @brief Declaration of Shell api tool functions.
 *
 */
#ifndef _SHTOOLS_H_
#define _SHTOOLS_H_

STDAPI CreateLink(LPCTSTR lpszPathObj, LPCTSTR lpszPathLink);
STDAPI CreateLinkToMe(LPCTSTR lpszPathLink);
STDAPI ResolveIt(HWND hwnd, LPCTSTR lpszLinkFile, LPTSTR lpszPath);
STDAPI PathsEqual(LPCTSTR, LPCTSTR);
STDAPI PathPointsToMe(LPCTSTR);
STDAPI CreateShellCommand(LPCTSTR);
STDAPI GetLongPathNameWin32(LPCTSTR lpszShortPath, LPTSTR lpszLongPath);

#endif // _SHTOOLS_H_
