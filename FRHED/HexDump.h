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
 * @file  HexDump.h
 *
 * @brief Hex dump class declaration.
 *
 */
#ifndef _HEX_DUMP_H_
#define _HEX_DUMP_H_

#include "simparr.h"

class HexDump
{
public:
	HexDump();
	~HexDump();

	void Settings(int bytesPerLine, int charsPerLine,
			bool partialStats, INT64 partialOffset,
			int byteSpace, int charSpace, int charset);
	void SetOffsets(int minLen, int maxLen);
	void SetArray(const SimpleArray<BYTE> *dataArray);
	void CreateBuffer(unsigned size);
	char *GetBuffer() const;
	void Write(int startInd, int endInd);

private:
	SimpleArray<BYTE> *m_pData;
	char *m_pBuffer;
	int m_bytesPerLine;
	int m_charsPerLine;
	int m_offsetMaxLen;
	int m_offsetMinLen;
	bool m_partialStats;
	INT64 m_partialOffset;
	int m_byteSpace;
	int m_charSpace;
	int m_charset;
};


#endif // _HEX_DUMP_H_
