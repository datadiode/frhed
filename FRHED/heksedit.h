/*
Frhed - Free hex editor
Copyright (C) 2000 Raihan Kibria
SPDX-License-Identifier: GPL-3.0-or-later
Last change: 2019-05-25 by Jochen Neubeck
*/
/**
 * @file  heksedit.h
 *
 * @brief Interface definition for the hekseditor window.
 *
 */
#ifndef _HEKSEDIT_H_
#define _HEKSEDIT_H_

#ifndef HEKSEDIT_INTERFACE_VERSION
#define HEKSEDIT_INTERFACE_VERSION 3
#define const(x) x
#endif

/**
 * @brief Interface for the Hexeditor window.
 * @note This file is published to hosting applications. Do not add global declarations.
 */
class IHexEditorWindow
{
public:
	/**
	 * @brief Byte endians.
	 */
	enum BYTE_ENDIAN
	{
		ENDIAN_LITTLE, /**< Little endian used e.g. in Intel processors. */
		ENDIAN_BIG /**< Big endian used e.g. in Motorola processors. */
	};

	struct Colors
	{
		COLORREF iTextColorValue, iBkColorValue, iSepColorValue;
		COLORREF iSelBkColorValue, iSelTextColorValue;
		COLORREF iBmkColor;
		COLORREF iDiffBkColorValue, iDiffTextColorValue, iSelDiffBkColorValue, iSelDiffTextColorValue;
	};

	/** @brief Frhed settings. */
	struct Settings
	{
		int iBytesPerLine; /**< How many bytes in one line in hex view. */
		int iAutomaticBPL; /**< Add max amount of bytes that fit to view. */
		BYTE_ENDIAN iBinaryMode; /**< Binary mode, little/big endian. */
		int bReadOnly; /**< Is editor in read-only mode? */
		int bSaveIni; /**< Save INI file when required. */
		int iFontSize;
		int iCharacterSet; /**< Use OEM or ANSI character set? */
		int iMinOffsetLen; /**< Minimum numbers used in offset. */
		int iMaxOffsetLen; /**< Maximum numbers used in offset. */
		int bAutoOffsetLen; /**< Determine offset length automatically. */
		int bCenterCaret;
		int iFontZoom;
#if HEKSEDIT_INTERFACE_VERSION < 3
	private:
#endif
		//General OLEDD options
		int enable_drop;
		int enable_drag;
		int enable_scroll_delay_dd;
		int enable_scroll_delay_sel;
		int always_pick_move_copy;
		//Input OLEDD options
		int prefer_CF_HDROP;
		int prefer_CF_BINARYDATA;
		int prefer_CF_TEXT;
		//Output OLEDD options
		int output_CF_BINARYDATA;
		int output_CF_TEXT;
		int output_text_special;
		int output_text_hexdump_display;
		int output_CF_RTF;
	};

	struct Status
	{
		int iFileChanged;
		int const(iEnteringMode);
		int const(iCurByte);
		int const(iCurNibble);
		int const(iVscrollMax);
		int const(iVscrollPos);
		int const(iHscrollMax);
		int const(iHscrollPos);
		int const(bSelected);
		int const(iStartOfSelection);
		int const(iEndOfSelection);
	};

	struct SharedUndoRecords;

	virtual unsigned STDMETHODCALLTYPE get_interface_version() = 0;
	virtual unsigned char *STDMETHODCALLTYPE get_buffer(int) = 0;
	virtual int STDMETHODCALLTYPE get_length() = 0;
	virtual void STDMETHODCALLTYPE set_sibling(IHexEditorWindow *) = 0;
	virtual Colors *STDMETHODCALLTYPE get_colors() = 0;
	virtual Settings *STDMETHODCALLTYPE get_settings() = 0;
	virtual Status *STDMETHODCALLTYPE get_status() = 0;
	virtual void STDMETHODCALLTYPE resize_window() = 0;
	virtual void STDMETHODCALLTYPE repaint(int from, int to) = 0;
	virtual void STDMETHODCALLTYPE adjust_hscrollbar() = 0;
	virtual void STDMETHODCALLTYPE adjust_vscrollbar() = 0;
	virtual int STDMETHODCALLTYPE translate_accelerator(MSG *) = 0;
	virtual void STDMETHODCALLTYPE CMD_find() = 0;
	virtual void STDMETHODCALLTYPE CMD_findprev() = 0;
	virtual void STDMETHODCALLTYPE CMD_findnext() = 0;
	virtual void STDMETHODCALLTYPE CMD_replace() = 0;
	virtual void STDMETHODCALLTYPE CMD_edit_cut() = 0;
	virtual void STDMETHODCALLTYPE CMD_edit_copy() = 0;
	virtual void STDMETHODCALLTYPE CMD_edit_paste() = 0;
	virtual void STDMETHODCALLTYPE CMD_edit_clear() = 0;
	virtual BOOL STDMETHODCALLTYPE select_next_diff(BOOL bFromStart) = 0;
	virtual BOOL STDMETHODCALLTYPE select_prev_diff(BOOL bFromEnd) = 0;
	virtual BOOL STDMETHODCALLTYPE load_lang(LANGID langid, LPCWSTR langdir = NULL) = 0;
	virtual void STDMETHODCALLTYPE CMD_zoom(int) = 0;
	virtual void STDMETHODCALLTYPE CMD_select_all() = 0;
#if HEKSEDIT_INTERFACE_VERSION < 2
private:
#endif
	virtual void STDMETHODCALLTYPE copy_sel_from(IHexEditorWindow *) = 0;
	virtual void STDMETHODCALLTYPE copy_all_from(IHexEditorWindow *) = 0;
	virtual void STDMETHODCALLTYPE CMD_edit_undo() = 0;
	virtual void STDMETHODCALLTYPE CMD_edit_redo() = 0;
	virtual BOOL STDMETHODCALLTYPE can_undo() const = 0;
	virtual BOOL STDMETHODCALLTYPE can_redo() const = 0;
	virtual void STDMETHODCALLTYPE set_savepoint() = 0;
	virtual void STDMETHODCALLTYPE clear_undorecords() = 0;
	virtual SharedUndoRecords *STDMETHODCALLTYPE share_undorecords(SharedUndoRecords *) = 0;
};

#undef const

#endif // _HEKSEDIT_H_
