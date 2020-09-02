/*
Frhed - Free hex editor
Copyright (C) 2000 Raihan Kibria
SPDX-License-Identifier: GPL-3.0-or-later
Last change: 2020-09-02 by Jochen Neubeck
*/
/**
 * @file Constants.h
 *
 * @brief Frhed constants, URLs, paths etc.
 *
 */

/** @brief Application name used in the GUI. */
const TCHAR ApplicationName[] = _T("Frhed");

/** @brief Frhed homepage URL. */
const TCHAR FrhedHomepageURL[] = _T("https://github.com/datadiode/frhed");

/** @brief Filename of the contributors list. */
const TCHAR ContributorsList[] = _T("Docs\\Contributors.txt");

/** @brief HtmlHelp file to open from Frhed program folder. */
const TCHAR HtmlHelpFile[] = _T("docs\\frhed.chm");

/** @brief Registry key for Frhed. */
const TCHAR OptionsRegistryPath[] = _T("Software\\Frhed");

/** @brief Registry key for Frhed settings. */
const TCHAR OptionsRegistrySettingsPath[] = _T("Software\\Frhed\\Settings");

/** @brief Subfolder where language files (PO files) are. */
const WCHAR LangFileSubFolder[] = L"Languages";
