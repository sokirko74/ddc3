//--------------------------------------------------------------
bool	CQueryTokenNode::CreateTokenPattern(const CConcHolder* pHolder, const string& IndexName, const string& Value, bool bRegex, bool bExact)
{
	/*-- moo:
	 * + original code checked for '\\', '@' prefixes (exact match) here,
	 *   but this kind of thing properly belongs in the lexer+parser pair
	 * + same applies to the backslash checks, regex slashes, index-name '$' etc.
	 */
	string str(Value);
	SetHolder(pHolder);
	m_Source = str;
	m_IndexName = IndexName;
	m_IndexItems.clear();

	if (bRegex) {
		if (str.empty())
			throw CDDCExpc(errParseError, "Empty regular expression not allowed in token sub-query //");
		return BuildRegExp(str, m_IndexItems);
	}

	//--  exact or re-inflected query
	const CStringIndexSet* IndexSet = m_pHolder->m_pIndexator->GetIndexByName(m_IndexName);
	if (!IndexSet)
		throw CDDCExpc(errParseError, "Unknown index `%s' in token sub-query `%s'", m_IndexName.c_str(), Value.c_str());

	//-- moo: original code tokenized string here on "/": looks like a token-internal disjunction operator to me
	const string &word = Value;
	if (word.empty())
		throw CDDCExpc(errParseError, "Empty value not allowed `%s' in token sub-query", word.c_str());

	if (word[word.length() - 1] == '*') {
		//-- WORD* : right truncation (prefix condition)
		set<string> Prefixes;

		Prefixes.insert(word.substr(0,word.length() - 1));

		if (!pHolder->m_pIndexator->m_bCaseSensitive)
			AddFormsWithDifferentRegisters(m_pHolder->m_pIndexator->m_Language,Prefixes);

		for (set<string>::const_iterator it = Prefixes.begin(); it != Prefixes.end(); it++)
			IndexSet->QueryTokenListWithRightTruncation(*it, m_IndexItems);
	}
	else if (word[0] == '*') {
		//-- WORD* : left truncation (suffix condition)
		if (!BuildRegExp(word.substr(1)+"$", m_IndexItems))
			throw CDDCExpc(errParseError, "Could not construct regex for left-truncated query `%s'", word.c_str());
	}
	else {
		//-- WORD or @WORD : re-inflected or literal match
		set<string> WordForms;
		if (bExact || m_pHolder->m_pIndexator->m_bDisableDefaultQueryLexicalExpansion)
			WordForms.insert(word);
		else
			GetWordForms (m_pHolder->m_pIndexator->m_Language, word, WordForms);

		if (!pHolder->m_pIndexator->m_bCaseSensitive)
			AddFormsWithDifferentRegisters(m_pHolder->m_pIndexator->m_Language,WordForms);
		
		for (set<string>::const_iterator it = WordForms.begin(); it != WordForms.end(); it++) {
			IndexSet->QueryTokenList(*it, m_IndexItems);
		}
	}
			
	sort(m_IndexItems.begin(),  m_IndexItems.end());
	vector<DWORD>::iterator endit = unique(m_IndexItems.begin(),  m_IndexItems.end());
	m_IndexItems.erase(endit,m_IndexItems.end());
	
	return true;	
}

//--------------------------------------------------------------
bool	CQueryTokenNode::CreateItemSetPattern(const CConcHolder* pHolder, const string& IndexName, const set<string>& Values, bool bExact)
{
	SetHolder(pHolder);
	m_Source = "{...}";
	m_IndexItems.clear();

	//--  exact or re-inflected query
	const CStringIndexSet* IndexSet = m_pHolder->m_pIndexator->GetIndexByNameOrShortName(IndexName);
	if (!IndexSet)
		throw CDDCExpc(errParseError, "Unknown index `%s' in item-set sub-query", IndexName.c_str());
	m_IndexName = IndexSet->m_Name;

	set<string> WordForms(Values);
	if (m_IndexName=="Token") {
		if (!bExact && !m_pHolder->m_pIndexator->m_bDisableDefaultQueryLexicalExpansion) {
			//-- expand each item in the set
			for (set<string>::const_iterator vi=Values.begin(); vi!=Values.end(); vi++) {
				GetWordForms (m_pHolder->m_pIndexator->m_Language, *vi, WordForms);
			}
		}
		if (!pHolder->m_pIndexator->m_bCaseSensitive)
			AddFormsWithDifferentRegisters(m_pHolder->m_pIndexator->m_Language,WordForms);
	}

	//-- query each item in the (expanded) set individually
	for (set<string>::const_iterator it = WordForms.begin(); it != WordForms.end(); it++) {
		IndexSet->QueryTokenList(*it, m_IndexItems);
	}

	//-- (?) sort results in m_IndexItems (snagged from CreateTokenPattern())
	sort(m_IndexItems.begin(),  m_IndexItems.end());
	vector<DWORD>::iterator endit = unique(m_IndexItems.begin(),  m_IndexItems.end());
	m_IndexItems.erase(endit,m_IndexItems.end());
	
	return true;	
}


void GetWordForms (const MorphLanguageEnum Langua, const string& src, set<string>& WordForms)
{
	if ( src.empty() ) return;
	WordForms.insert(src);
	if (Langua == morphUnknown)  return;

	vector<CFormInfo> Paradigms;
	const CLemmatizer* pLemmatizer = GetLemmatizerByLanguage(Langua);
	if (!pLemmatizer) return;
	string tmp = pLemmatizer->recode_ext2int(src);
	const bool bCapital = is_upper_alpha((BYTE)tmp[0],Langua);

	try
	{
		pLemmatizer->CreateParadigmCollection(false, tmp, bCapital, true, Paradigms);
	}
	catch(...)
	{
		throw CDDCExpc (errProcessMorphology, Format("Morphology has crushed on %s ", src.c_str()));
	}

	//	print out all paradigms
	for (int i = 0; i < Paradigms.size(); i++)
	{
		const CFormInfo& F = Paradigms[i];
		//  print all forms of one paradigm
		for (int j = 0; j < F.GetCount(); j++)
		{
			string form  = F.GetWordForm(j);
			RmlMakeLower(form, Langua);
			// set register of the first char of "form" equal to the  register of "src"
			if (bCapital)
			{
				//  making the first word upper
				form[0] = ReverseChar((BYTE)form[0], Langua);
			};
			WordForms.insert(pLemmatizer->recode_int2ext(form));
		}
	}
};	

// for each string "aab" adds also "Aab" and "AAB"
// for each string "Aab" adds also "aab" and "AAB"
void AddFormsWithDifferentRegisters (const MorphLanguageEnum Langua, set<string>& WordForms)
{
	set<string> NewWordForms;
	for (set<string>::const_iterator it = WordForms.begin(); it != WordForms.end(); it++)
	{
		const string& q = *it;
		if (q.empty())  continue;
		NewWordForms.insert(q);

		if (is_lower_alpha((BYTE)q[0],  Langua))
		{
			string upp = q;
			upp[0] = ReverseChar((BYTE)upp[0], Langua);
			NewWordForms.insert(upp);
		}
		else
		{
			string lwr = q;
			RmlMakeLower(lwr, Langua);
			NewWordForms.insert(lwr);

		};
		string upr = q;
		RmlMakeUpper(upr, Langua);
		NewWordForms.insert(upr);
	};

	NewWordForms.swap(WordForms);
};
