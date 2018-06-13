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

Last change: 2017-06-21 by Jochen Neubeck
*/
/** 
 * @file  BinTrans.h
 *
 * @brief Text to binary converter class declaration.
 *
 */
#ifndef BinTrans_h
#define BinTrans_h

int create_bc_translation(BYTE** ppd, const char* src, int srclen, int charset, int binarymode);

/**
 * @brief A class translating between text export and binary data.
 */
class Text2BinTranslator : public String
{
public:
	int bCompareBin(Text2BinTranslator& tr2, int charmode, int binmode);
	Text2BinTranslator(const char* ps);
	static int iIsBytecode(const char* src, int len);
	static int iBytes2BytecodeDestLen(const BYTE* src, int srclen);
	static int iLengthOfTransToBin(const char* src, int srclen);
	static int iCreateBcTranslation(BYTE* dest, const char* src, int srclen, int charmode, int binmode);
	static int iTranslateOneBytecode(BYTE* dest, const char* src, int srclen, int binmode);
	static int iFindBytePos(const char* src, char c);
	static int iTranslateBytesToBC(char* pd, const BYTE* src, int srclen);

private:
	int GetTrans2Bin(Vector<BYTE>& sa, int charmode, int binmode);
};

#endif // BinTrans_h
