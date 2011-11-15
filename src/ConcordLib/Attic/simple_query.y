%{

#include "QueryNode.h"
#include "QueryParser.h"

#define YYDEBUG 1
#define YYPARSE_PARAM _parser
#define YYLEX_PARAM _parser
#define _prs ((CQueryParser*) _parser)

#ifdef DETECT_MEMORY_LEAK
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif



void yyerror (const char *error);
int yylex (void*,  void*);


//-----------------------------------------------------------------------------------------------------------------
//			Simple  Parser && , ||  without negation and words as atoms 
//-----------------------------------------------------------------------------------------------------------------
%} 
%pure-parser
%union 
{
const string*	m_LabelPtr;  /* For returning src.            */
CQueryNode*		m_pnode;  /* For returning tree-nodes      */
}

%token	<m_LabelPtr>SIM_NAME
%token	<m_LabelPtr>CHUNK_NAME
%token	<m_LabelPtr>INDEX_NAME
%token	<m_LabelPtr>REG_EXPR_NAME
%token	<m_LabelPtr>SIM_NEAR_OPER_DELIM
%type	<m_pnode>exp
%type	<m_pnode>exp_neg
%type	<m_pnode>word_descr
%type	<m_pnode>seq_descr
%type	<m_pnode>seq_descr_tail
%type	<m_pnode>seq_descr_tail_with_distance
%type	<m_pnode>seq_descr_with_distance
%type	<m_pnode>seq_or_word




%left	SIM_AND SIM_OR 
%left	NEAR_OPERATOR 
%left	SIM_NEAR_OPER_DELIM
%left	WITH_OPERATOR 
%left	SIM_PRECISE




%%
//-----------------------------------------------------------------------------------------------------------------
//				RULES PART
//-----------------------------------------------------------------------------------------------------------------

exp		:		exp_neg
				{		
					$$ = $1;	
				}
			|	exp SIM_AND exp
				{
					CQueryAndOperation* pObj = new CQueryAndOperation;
					pObj->Create(_prs->m_pHolder, $1, $3, string("&&"));
					_prs->m_pQueryTree = pObj;
					$$ = pObj;
				}
			|	exp SIM_OR exp
				{
					if ($1->GetNegation() != $3->GetNegation())
					{
						//  we restrict negation only to conjunctions
						// !a || b   is not possible, since we doesn't  generate 
						// full negated list 
						YYABORT;
					};
					CQueryOrOperation* pObj = new CQueryOrOperation;
					pObj->Create(_prs->m_pHolder, $1, $3, string("||"));
					_prs->m_pQueryTree = pObj;
					$$ = pObj;
				}
			|	'(' exp ')'
				{
					$$ = $2;	
				};


exp_neg		:		seq_or_word
				{		
					$$ = $1;	
				}
			|	NEAR_OPERATOR '(' seq_or_word	SIM_NEAR_OPER_DELIM seq_or_word SIM_NEAR_OPER_DELIM SIM_NAME ')'
				{
					CQueryNearNode* pObj = new CQueryNearNode;
					if (!pObj->Create(_prs->m_pHolder, $7->c_str(), $3, $5))
					{
						delete pObj;
						YYABORT;
					}	

					_prs->m_pQueryTree = pObj;
					$$ = pObj;
				}
			|	NEAR_OPERATOR '(' seq_or_word	SIM_NEAR_OPER_DELIM seq_or_word SIM_NEAR_OPER_DELIM seq_or_word SIM_NEAR_OPER_DELIM SIM_NAME ')'
				{
					CQueryNearNode* pObj = new CQueryNearNode;
					if (!pObj->Create(_prs->m_pHolder, $9->c_str(), $3, $5, $7))
					{
						delete pObj;
						YYABORT;
					}	

					_prs->m_pQueryTree = pObj;
					$$ = pObj;
				}
				
			|	'!' exp_neg
				{
					$2->SetNegation (true);
					$$ = $2;	
				};


seq_or_word		:	word_descr
					{		
						$$ = $1;	
					}
					|  seq_descr
						{
						$$ = $1;	
					}
					|		seq_descr_with_distance
						{		
							$$ = $1;	
						};

seq_descr	:	 '"' seq_descr_tail '"'
				{
					const CQueryNode* it  = $2;

					CQuerySequenceNode* pObj = new CQuerySequenceNode;


					if (!pObj->Create(_prs->m_pHolder, _prs->m_CurrSequenceObj, _prs->m_CurrDistances))
					{
						delete pObj;
						YYABORT;
					}
					_prs->m_pQueryTree = pObj;
						
					_prs->m_CurrSequenceObj.clear();
					_prs->m_CurrDistances.clear();

					$$ = pObj;	
				};

seq_descr_tail : seq_descr_tail word_descr 
					{
						_prs->m_CurrSequenceObj.push_back($2);
						_prs->m_CurrDistances.push_back("0");
						$$ = $1;	
					}
				|	word_descr word_descr
					{
						_prs->m_CurrSequenceObj.push_back($1);
						_prs->m_CurrSequenceObj.push_back($2);
						_prs->m_CurrDistances.push_back("0");
						$$ = $1;	
						
					}


seq_descr_with_distance	:	 '"' seq_descr_tail_with_distance '"'
				{
					const CQueryNode* it  = $2;

					CQuerySequenceNode* pObj = new CQuerySequenceNode;
					
					assert (_prs->m_CurrSequenceObj.size() == _prs->m_CurrDistances.size() + 1);

					if (!pObj->Create(_prs->m_pHolder, _prs->m_CurrSequenceObj, _prs->m_CurrDistances))
					{
						delete pObj;
						YYABORT;
					}
					_prs->m_pQueryTree = pObj;
						
					_prs->m_CurrSequenceObj.clear();
					_prs->m_CurrDistances.clear();

					$$ = pObj;	
				}

seq_descr_tail_with_distance : seq_descr_tail_with_distance '#' SIM_NAME word_descr 
					{
						_prs->m_CurrSequenceObj.push_back($4);
						_prs->m_CurrDistances.push_back(*($3));
						$$ = $1;	
					}
				|	word_descr '#' SIM_NAME word_descr
					{

						_prs->m_CurrSequenceObj.push_back($1);
						_prs->m_CurrSequenceObj.push_back($4);
						_prs->m_CurrDistances.push_back(*($3));
			
						$$ = $1;	
					}
			
word_descr	:	SIM_NAME
				{
					CQueryTokenNode* pObj = new CQueryTokenNode(_prs->GetNewNodeIndex());
					if (!pObj->CreateTokenPattern(_prs->m_pHolder, $1->c_str(), false))
					{
						delete pObj;
						YYABORT;
					}
					_prs->m_pQueryTree = pObj;
					$$ = pObj;
				}
			|	INDEX_NAME '=' SIM_NAME
				{
					CQueryTokenNode* pObj = new CQueryTokenNode(_prs->GetNewNodeIndex());
					if ( !pObj->CreateNodeByIndexName(_prs->m_pHolder, $1->c_str(), $3->c_str(), false)  )
					{
						delete pObj;
						YYABORT;
					}
					_prs->m_pQueryTree = pObj;
					$$ = pObj;
				
				}
			|	INDEX_NAME '=' REG_EXPR_NAME
				{
					CQueryTokenNode* pObj = new CQueryTokenNode(_prs->GetNewNodeIndex());
					if ( !pObj->CreateNodeByIndexName(_prs->m_pHolder, $1->c_str(), $3->c_str(), true)  )
					{
						delete pObj;
						YYABORT;
					}
					_prs->m_pQueryTree = pObj;
					$$ = pObj;
				
				}
			| REG_EXPR_NAME
				{
					CQueryTokenNode* pObj = new CQueryTokenNode(_prs->GetNewNodeIndex());
					if (!pObj->CreateTokenPattern(_prs->m_pHolder, $1->c_str(), true))
					{
						delete pObj;
						YYABORT;
					}
					_prs->m_pQueryTree = pObj;
					$$ = pObj;
				}
			| '[' SIM_NAME ']'
				{

					try
					{
						CQueryTokenNode* pObj = new CQueryTokenNode(_prs->GetNewNodeIndex());
						if (!pObj->CreateMorphAnnotationPattern(_prs->m_pHolder, $2->c_str(), "MorphPattern"))
						{
							delete pObj;
							YYABORT;
						}
						_prs->m_pQueryTree = pObj;
						$$ = pObj;				
					}
					catch(...)
					{
							YYABORT;
					}						
					
				}
			| '{' SIM_NAME '}'
				{

					try
					{
						CQueryTokenNode* pObj = new CQueryTokenNode(_prs->GetNewNodeIndex());
						if (!pObj->CreateThesPattern(_prs->m_pHolder, $2->c_str()))
						{
							delete pObj;
							YYABORT;
						}
						_prs->m_pQueryTree = pObj;
						$$ = pObj;				
					}
					catch(...)
					{
							YYABORT;
					}						
					
				}

			| CHUNK_NAME 
				{
					if ($1->empty() || ((*$1)[0] != '^')) YYABORT;
					
					try
					{
						CQueryTokenNode* pObj = new CQueryTokenNode(_prs->GetNewNodeIndex());
						
						if (!pObj->CreateChunkPattern(_prs->m_pHolder, $1->substr(1).c_str()))
						{
							delete pObj;
							YYABORT;
						}
						_prs->m_pQueryTree = pObj;
						$$ = pObj;				
					}
					catch(...)
					{
							YYABORT;
					}						
					
				}
			|	word_descr WITH_OPERATOR word_descr 
				{
					CQueryWithNode* pObj = new CQueryWithNode;
					if ( !pObj->Create(_prs->m_pHolder, $1, $3) )
					{
						delete pObj;
						YYABORT;
					}					
					_prs->m_pQueryTree = pObj;
					$$ = pObj;
				}
			|	'%'  SIM_NAME
				{
					CQueryTokenNode* pObj = new CQueryTokenNode(_prs->GetNewNodeIndex());
					if ( !pObj->CreateMorphAnnotationPattern(_prs->m_pHolder,  $2->c_str(), "Lemma")  )
					{
						delete pObj;
						YYABORT;
					}					
					_prs->m_pQueryTree = pObj;
					$$ = pObj;
				}
			|	'='  SIM_NAME
				{
					try
					{
						CQueryTokenNode* pObj = new CQueryTokenNode(_prs->GetNewNodeIndex());
						if (!pObj->CreateFileList(_prs->m_pHolder, $2->c_str()))
						{
							delete pObj;
							YYABORT;
						}
						_prs->m_pQueryTree = pObj;
						$$ = pObj;				
					}
					catch(...)
					{
							YYABORT;
					}						
				}	
				;



%%
//-----------------------------------------------------------------------------------------------------------------
//				CODE PART
//-----------------------------------------------------------------------------------------------------------------
