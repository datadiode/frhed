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
 * @file  AboutDlg.cpp
 *
 * @brief Implementation of the About dialog.
 *
 */
#include "precomp.h"
#include "resource.h"
#include "Constants.h"
#include "hexwnd.h"
#include "hexwdlg.h"
#include "StringTable.h"

struct DrawItemStruct_WebLinkButton : DRAWITEMSTRUCT
{
	void DrawItem() const
	{
		TCHAR cText[2048];
		int cchText = ::GetWindowText(hwndItem, cText, _countof(cText));
		COLORREF clrText = ::GetSysColor(COLOR_HOTLIGHT);
		if (::GetWindowLong(hwndItem, GWL_STYLE) & BS_LEFTTEXT)
		{
			clrText = ::GetSysColor(COLOR_GRAYTEXT);
			if (GetRValue(clrText) == GetGValue(clrText) && GetRValue(clrText) == GetBValue(clrText))
				clrText &= RGB(255,0,255);
		}
		RECT rcText = rcItem;
		::DrawText(hDC, cText, cchText, &rcText, DT_LEFT | DT_CALCRECT);
		::SetWindowPos(hwndItem, NULL, 0, 0, rcText.right, rcItem.bottom,
			SWP_NOMOVE | SWP_NOZORDER | SWP_NOREDRAW);
		switch (itemAction)
		{
		case ODA_DRAWENTIRE:
			::ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rcItem, 0, 0, 0);
			::SetBkMode(hDC, TRANSPARENT);
			::SetTextColor(hDC, clrText);
			::DrawText(hDC, cText, cchText, &rcText, DT_LEFT);
			rcText.top = rcText.bottom - 1;
			::SetBkColor(hDC, clrText);
			::ExtTextOut(hDC, 0, 0, ETO_OPAQUE, &rcText, 0, 0, 0);
			if (itemState & ODS_FOCUS)
			{
			case ODA_FOCUS:
				if (!(itemState & ODS_NOFOCUSRECT))
				{
					::SetTextColor(hDC, RGB(0,0,0));
					::SetBkColor(hDC, RGB(255,255,255));
					::SetBkMode(hDC, OPAQUE);
					rcText.top = rcText.bottom - 1;
					++rcText.bottom;
					::DrawFocusRect(hDC, &rcText);
				}
			}
			break;
		}
	}
};

AboutDlg::AboutDlg()
{
	TCHAR path[MAX_PATH];
	GetModuleFileName(hMainInstance, path, _countof(path));
	PathRemoveFileSpec(path);
	PathAppend(path, _T("Frhed.exe"));
	m_hIcon = ExtractIcon(NULL, path, 0);
}

AboutDlg::~AboutDlg()
{
	DestroyIcon(m_hIcon);
}

/**
 * @brief Initialize the dialog.
 * @param [in] hDlg Handle to the dialog.
 */
BOOL AboutDlg::OnInitDialog(HWindow *pDlg)
{
	// Set the version information.
	TCHAR buf[4096];
	buf[RTL_NUMBER_OF(buf) - 1] = _T('\0');
	_sntprintf(buf, RTL_NUMBER_OF(buf) - 1, GetLangString(IDS_ABOUTFRHEDVER),
		FRHED_MAJOR_VERSION, FRHED_MINOR_VERSION, FRHED_SUB_RELEASE_NO);
	pDlg->SetDlgItemText(IDC_ABOUT_VER, buf);
	// Set the homepage URL.
	pDlg->SetDlgItemText(IDC_ABOUT_URL, FrhedHomepageURL);
	// Set the icon.
	pDlg->SendDlgItemMessage(IDC_APPICON, STM_SETICON, reinterpret_cast<WPARAM>(m_hIcon));
	return TRUE;
}

/**
 * @brief Handle dialog commands.
 * @param [in] hDlg Hanle to the dialog.
 * @param [in] wParam The command to handle.
 * @param [in] lParam Optional parameter for the command.
 * @return TRUE if the command was handled, FALSE otherwise.
 */
BOOL AboutDlg::OnCommand(HWindow *pDlg, WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	case IDOK:
	case IDCANCEL:
		pDlg->EndDialog(wParam);
		return TRUE;

	case IDC_ABOUT_URL:
		{
			HINSTANCE hi = ShellExecute(pDlg->m_hWnd,
				_T("open"), FrhedHomepageURL, 0, NULL, SW_SHOWNORMAL);
			if (reinterpret_cast<UINT>(hi) <= HINSTANCE_ERROR)
			{
				MessageBox(pDlg, GetLangString(IDS_ABOUT_BROWSER_ERR), MB_ICONERROR);
			}
		}
		return TRUE;

	case IDC_ABOUTCONTRIBS:
		{
			TCHAR contrList[MAX_PATH];
			GetModuleFileName(hMainInstance, contrList, MAX_PATH);
			PathRemoveFileSpec(contrList);
			PathAppend(contrList, ContributorsList);
			if (PathFileExists(contrList))
			{
				ShellExecute(pDlg->m_hWnd, _T("open"), _T("notepad.exe"), contrList, NULL, SW_SHOWNORMAL);
			}
			else
			{
				TCHAR buf[4096];
				_sntprintf(buf, RTL_NUMBER_OF(buf), GetLangString(IDS_ABOUT_FILENOTFOUND), ContributorsList);
				MessageBox(pDlg, buf, MB_ICONERROR);
			}
		}
		return TRUE;
	}
	return FALSE;
}

/**
 * @brief Handle dialog messages.
 * @param [in] hDlg Handle to the dialog.
 * @param [in] iMsg The message.
 * @param [in] wParam The command in the message.
 * @param [in] lParam The optional parameter for the command.
 * @return TRUE if the message was handled, FALSE otherwise.
 */
INT_PTR AboutDlg::DlgProc(HWindow *pDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		return OnInitDialog(pDlg);

	case WM_COMMAND:
		return OnCommand(pDlg, wParam, lParam);

	case WM_DRAWITEM:
		switch (wParam)
		{
		case IDC_ABOUT_URL:
			reinterpret_cast<DrawItemStruct_WebLinkButton *>(lParam)->DrawItem();
			return TRUE;
		}
		break;

	case WM_SETCURSOR:
		switch (reinterpret_cast<HWindow *>(wParam)->GetDlgCtrlID())
		{
		case IDC_ABOUT_URL:
			::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND)));
			pDlg->SetWindowLongPtr(DWLP_MSGRESULT, TRUE);
			return TRUE;
		}
		break;

	case WM_HELP:
		HexEditorWindow::OnHelp(pDlg);
		return TRUE;
	}
	return FALSE;
}

int CALLBACK About(HWND hWnd)
{
	return dialog<AboutDlg>().DoModal(reinterpret_cast<HWindow *>(hWnd));
}
