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
#ifndef idt_h
#define idt_h

class HexEditorWindow;

class CDropTarget : public IDropTarget
{
private:
	ULONG m_cRefCount;

	DWORD LastKeyState;

	bool hdrop_present;
	IDataObject* pDataObj;
	HexEditorWindow &hexwnd;

	int PopupDropMenu(POINTL pt);

public:
	//Members
	CDropTarget(HexEditorWindow &);
	~CDropTarget();

	//IUnknown members
	STDMETHODIMP QueryInterface(REFIID iid, void** ppvObject);
	STDMETHODIMP_(ULONG) AddRef();
	STDMETHODIMP_(ULONG) Release();

	//IDropTarget methods
	STDMETHODIMP DragEnter(IDataObject* pDataObject, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);
	STDMETHODIMP DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect);
	STDMETHODIMP DragLeave();
	STDMETHODIMP Drop(IDataObject* pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
};

#endif // idt_h
