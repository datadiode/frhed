/*
Frhed - Free hex editor
Copyright (C) 2000 Raihan Kibria

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.

Last change: 2013-02-24 by Jochen Neubeck
*/
#include "precomp.h"
#include "toolbar.h"
#include "resource.h"

#define IMAGEWIDTH 16
#define IMAGEHEIGHT 16
#define BUTTONWIDTH 0
#define BUTTONHEIGHT 0

static const TBBUTTON tbButtons[] = // Array defining the toolbar buttons
{
	{  0, IDM_NEW,                   TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
	{  1, IDM_OPEN,                  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
	{  2, IDM_SAVE,                  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
	{  0, 0,                         TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0 },
	{  3, IDM_EDIT_CUT,              TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
	{  4, IDM_EDIT_COPY,             TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
	{  5, IDM_EDIT_PASTE,            TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
	{  0, 0,                         TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0 },
	{  6, IDM_FIND,                  TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
	{  7, IDM_REPLACE,               TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
	{  0, 0,                         TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0 },
	{  8, IDM_HELP_TOPICS,           TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
	{  0, 0,                         TBSTATE_ENABLED, TBSTYLE_SEP,    0, 0 },
	{  9, ID_DISK_GOTOFIRSTTRACK,    0,               TBSTYLE_BUTTON, 0, 0 },
	{ 10, ID_DISK_GOTOPREVIOUSTRACK, 0,               TBSTYLE_BUTTON, 0, 0 },
	{ 11, ID_DISK_GOTONEXTTRACK,     0,               TBSTYLE_BUTTON, 0, 0 },
	{ 12, ID_DISK_GOTOLASTTRACK,     0,               TBSTYLE_BUTTON, 0, 0 }
};

HWND CreateTBar(HWND hWnd, HINSTANCE hInst)
{
	HWND hwndToolBar = CreateToolbarEx(hWnd,
		WS_CHILD | WS_VISIBLE | CCS_NORESIZE |
		TBSTYLE_TOOLTIPS | TBSTYLE_FLAT | TBSTYLE_WRAPABLE,
		0,
		RTL_NUMBER_OF(tbButtons) - 4,
		hInst,
		IDB_TOOLBAR,
		tbButtons,
		RTL_NUMBER_OF(tbButtons),
		BUTTONWIDTH,
		BUTTONHEIGHT,
		IMAGEWIDTH,
		IMAGEHEIGHT,
		sizeof(TBBUTTON));
	return hwndToolBar;
}
