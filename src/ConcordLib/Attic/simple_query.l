%{

#define simple_query_l
#include "QueryParser.h"
// we need export  constants from yacc, like "SIM_NAME"

#ifdef WIN32
    #include "simple_qparse.h"
#else
    #include "unix_simple_qparse.h"
#endif

#ifdef DETECT_MEMORY_LEAK
	#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
	#endif
#endif



%}
%option c++
%option noyywrap
%option yyclass="CQueryParser"
 
underscore "_"
string		\"[^\n\"]+\"
ws			[ \t\n]+
eng_alpha   [\-\.A-Za-z\']
rus_alpha	[\-\.ÉÖÓÊÅÍÃØÙÇÕ¨ÚÔÛÂÀÏĞÎËÄÆİß×ÑÌÈÒÜÁŞéöóêåíãøùçõ¸úôûâàïğîëäæıÿ÷ñìèòüáş]
gen_alpha   [A-Za-z\200-\377]


dig			[0-9]
all_punct	[\^\!\"\§\$\%\&\/\(\)\=\?\\*\'\_\:\;\+\#\-\.\,\\\[\]\{\}]
parentness  [{}<>\[\]\(\)]
regular_operators [\$\^\*\+\?\\\.\[\:\]]
slashes		[\\/]
op_and		"&&" 
op_or		"||" 
char		({rus_alpha}|{eng_alpha}|{dig}|{gen_alpha})
name		[\@]?(({char})|({char}({char}|[/])*{char}))
reg_expr	({rus_alpha}|{eng_alpha}|{dig}|{gen_alpha}|{parentness}|{regular_operators})+
file_name	({dig}|{eng_alpha}|[.-]|{underscore}|{slashes})+
near_oper_delim	[,;]



grammems_text    ({gen_alpha}|{rus_alpha}|{eng_alpha}|{dig}|[,\-_]|{ws})+
dwds_thes_text    ({gen_alpha}|{rus_alpha}|{eng_alpha}|{dig}|[.,:-]|{ws})+
chunk_text          ({gen_alpha}|{rus_alpha}|{eng_alpha}|{dig}|{underscore})+

open_bracket "["
close_bracket "]"
open_curles "{"
close_curles "}"
slash		"\/"




%x GRAMMEMS
%x THES_ITEM

%%

{open_bracket} {
			BEGIN(GRAMMEMS);
			return ((int)YYText()[0]);
		}

<GRAMMEMS>{grammems_text} return SIM_NAME;
		

<GRAMMEMS>{close_bracket}	{
			BEGIN(INITIAL);
			return ((int)YYText()[0]);
		}



{open_curles} {
			BEGIN(THES_ITEM);
			return ((int)YYText()[0]);
		}

<THES_ITEM>{dwds_thes_text} return SIM_NAME;
		

<THES_ITEM>{close_curles}	{
			BEGIN(INITIAL);
			return ((int)YYText()[0]);
		}






\/{reg_expr}\/ return REG_EXPR_NAME;

NEAR		return NEAR_OPERATOR;
near		return NEAR_OPERATOR;
WITH		return WITH_OPERATOR;
with		return WITH_OPERATOR;

{op_and}		return SIM_AND;

{op_or}		return SIM_OR;

\\{all_punct}+			return SIM_NAME;

\^{name}		return CHUNK_NAME;
	
{name}		return SIM_NAME;



  /* left truncation */
\*{name}		return SIM_NAME;

 /* right truncation*/
{name}\*		return SIM_NAME;

\${eng_alpha}+	return INDEX_NAME;

{file_name} return SIM_NAME;

{near_oper_delim} return SIM_NEAR_OPER_DELIM;

{ws}    /* skip blanks and tabs */
.			return ((int)YYText()[0]);
%%
