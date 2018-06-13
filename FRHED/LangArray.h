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
 * @file  LangArray.h
 *
 * @brief Declaration of translated text array class.
 *
 */
class LangArray : protected Vector<char *>
{
public:
	static const LANGID DefLangId;
	struct StringData
	{
		int refcount;
		char data[1];
		static StringData *Create(const char *, size_t);
		char *Share();
		static void Unshare(char *);
	};
	HMODULE m_hLangDll;
	unsigned m_codepage;
	LANGID m_langid;
	LangArray();
	~LangArray();
	void ExpandToSize();
	void ClearAll();
	BOOL Load(HINSTANCE hMainInstance, LANGID langid, LPCTSTR langdir);
	PTSTR TranslateString(int line);
	void TranslateDialog(HWND);
	void TranslateMenu(HMENU);
	HMENU LoadMenu(HINSTANCE, LPTSTR);
	static int LangCodeMajor(LANGID, LPTSTR);
	static int LangCodeMinor(LANGID, LPTSTR);
};
