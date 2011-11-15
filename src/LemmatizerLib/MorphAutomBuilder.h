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
// ==========  Dialing Lemmatizer (www.aot.ru), 
// ==========  Copyright by Alexey Sokirko (2004), Bryan Jurish (2011)


//   The main function of this header is CMorphAutomatBuilder::AddStringDaciuk 
//  This function is an implementation of algorithm for constructing minimal,
// deterministic, acyclic FSM from unordered set of strings, which was described 
// in  "Jan Daciuk, Stoyan Mihov, Bruce Watson, and Richard Watson, 
//      Incremental Construction of Minimal Acyclic Finite State Automata, 
//		Computational Linguistics, 26(1), March 2000."

#ifndef MorphAutomBuilder_h
#define MorphAutomBuilder_h

#include "MorphAutomat.h"



struct CTrieNodeBuild;
struct IsLessRegister: public less<CTrieNodeBuild*>
{
	bool operator ()(const CTrieNodeBuild* pNodeNo1, const CTrieNodeBuild* pNodeNo2) const;
};

typedef set<CTrieNodeBuild*, IsLessRegister> CTrieRegister;




struct CTrieNodeBuild
{
	bool						m_bFinal;
	int							m_IncomingRelationsCount;
	CTrieNodeBuild*				m_Children[MaxAlphabetSize];
	CTrieRegister::iterator		m_pRegister;
	bool						m_bRegistered;
	int							m_NodeId;
	BYTE						m_FirstChildNo;
	BYTE						m_SecondChildNo;
	

	void				Initialize();
	void				AddChild(CTrieNodeBuild* Child, BYTE ChildNo);
	void				ModifyChild(CTrieNodeBuild* Child, BYTE ChildNo, bool bUpdateIncoming);
	CTrieNodeBuild*		GetNextNode(BYTE RelationChar)  const;
	void				SetNodeIdNullRecursive ();
	void				UnregisterRecursive();
	

	//  debug function
	bool				CheckIncomingRelationsCountRecursive(map<const CTrieNodeBuild*, size_t>& Node2Incoming) const;
	void				GetIncomingRelationsCountRecursive(map<const CTrieNodeBuild*, size_t>& Node2Incoming) const;
	bool				CheckRegisterRecursive() const;
	void				SetFinal(bool bFinal);
};




class CMorphAutomatBuilder : public CMorphAutomat
{

	CTrieNodeBuild*			m_pRoot;

	// a hash by the letter of the first  child and the number of children
	CTrieRegister			m_RegisterHash[MaxAlphabetSize+1][MaxAlphabetSize+1];

	vector<CTrieNodeBuild*>				m_Prefix;

	vector<CTrieNodeBuild*>		m_DeletedNodes;
	
	void				ClearBuildNodes();

	CTrieNodeBuild*		CreateNode();
	void				DeleteNode(CTrieNodeBuild* pNode);
	CTrieNodeBuild*		CloneNode(const CTrieNodeBuild* pPrototype);

	void				UpdateCommonPrefix(const string& WordForm);
	CTrieNodeBuild*		AddSuffix(CTrieNodeBuild* pParentNodeNo, const char* WordForm);
	CTrieNodeBuild*		ReplaceOrRegister(CTrieNodeBuild* pNode);
	void				DeleteFromRegister(CTrieNodeBuild* pNode);
	int					GetFirstConfluenceState() const;
	void				UnregisterNode(CTrieNodeBuild* pNode);
	
	CTrieRegister&		GetRegister(const CTrieNodeBuild* pNode);

	//  debug functions 
	bool				CheckRegister() const;
	bool				IsValid() const;
	
	
public:
	CMorphAutomatBuilder(MorphLanguageEnum Language, BYTE AnnotChar);
	~CMorphAutomatBuilder();

	void	InitTrie();
	bool	AddStringDaciuk(const string& WordForm);
	void	ClearRegister();
	void	ConvertBuildRelationsToRelations();
};



#endif
