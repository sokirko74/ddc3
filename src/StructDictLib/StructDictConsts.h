//
//  This file is part of DDC.
// 
//  DDC is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
// 
//  DDC is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
// 
//  You should have received a copy of the GNU Lesser General Public License
//  along with DDC.  If not, see <http://www.gnu.org/licenses/>.
//
// ==========  Dialing Structural Dictionary (www.aot.ru)
// ==========  Copyright by Alexey Sokirko (1998-2002), Bryan Jurish (2011)

#ifndef StructDictsConsts
#define StructDictsConsts

	const	DWORD	MaxDomensUnionSize = 20;
	const	DWORD	AuthorNameSize = 10;

	// максимальное число актантов 
	const	BYTE	MaxNumAct = 7;

	// ошибочный номер словарного входа 
	const	WORD	ErrUnitNo  = 65000;
	const	DWORD	EntryStrSize = 40;

	   // »сходный материал доменов
        const	BYTE	dsUnion = 'O';
	const	BYTE	dsExpres = 'C';
	const	BYTE	dsSystem = 'S';
	const	BYTE	dsText = 'T';
	const	BYTE	dsMetaText = 'M';

	const	BYTE	frOne = 'O';
	const	BYTE	frMany = 'M';
	const	BYTE	frFormula = 'F';


#endif
