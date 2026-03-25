%{
#include "lex.hpp"
#include <cstring>
#include <cstdlib>
#include <string>
/* 所有代码全部抽离出来，放到 lex.hpp 和 lex.cpp 里 */

using namespace lex;

#define COME(id) do { \
  int _startCol = g.mColumn; \
  g.mLine = yylineno; \
  g.mColumn += yyleng; \
  return come(id, yytext, yyleng, _startCol); \
} while(0)

%}

%option 8bit warn noyywrap yylineno

D     [0-9]
L     [a-zA-Z_]
H     [a-fA-F0-9]
IS    ((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))

%%

"const"     { COME(CONST); }
"void"      { COME(VOID); }
"int"       { COME(INT); }
"if"        { COME(IF); }
"else"      { COME(ELSE); }
"while"     { COME(WHILE); }
"break"     { COME(BREAK); }
"continue"  { COME(CONTINUE); }
"return"    { COME(RETURN); }

"("         { COME(L_PAREN); }
")"         { COME(R_PAREN); }
"["         { COME(L_SQUARE); }
"]"         { COME(R_SQUARE); }
"{"         { COME(L_BRACE); }
"}"         { COME(R_BRACE); }

"<="        { COME(LESSEQUAL); }
">="        { COME(GREATEREQUAL); }
"=="        { COME(EQUALEQUAL); }
"!="        { COME(EXCLAIMEQUAL); }
"&&"        { COME(AMPAMP); }
"||"        { COME(PIPEPIPE); }

"+"         { COME(PLUS); }
"-"         { COME(MINUS); }
"*"         { COME(STAR); }
"/"         { COME(SLASH); }
"%"         { COME(PERCENT); }
"<"         { COME(LESS); }
">"         { COME(GREATER); }
"="         { COME(EQUAL); }
"!"         { COME(EXCLAIM); }

";"         { COME(SEMI); }
","         { COME(COMMA); }

{L}({L}|{D})*         { COME(IDENTIFIER); }

L?\"(\\.|[^\\"\n])*\" { COME(STRING_LITERAL); }

0[xX]{H}+{IS}?        { COME(CONSTANT); }
0[0-7]*{IS}?          { COME(CONSTANT); }
[1-9]{D}*{IS}?        { COME(CONSTANT); }

^#[^\n]*              {
  /* 预处理信息处理：从预处理信息中获得文件名以及行号 */
  const char* p = yytext + 1;
  while (*p == ' ') p++;
  int line = 0;
  while (*p >= '0' && *p <= '9') {
    line = line * 10 + (*p - '0');
    p++;
  }
  while (*p == ' ') p++;
  if (*p == '"') {
    p++;
    const char* start = p;
    while (*p && *p != '"') p++;
    g.mFile = std::string(start, p - start);
  }
  yylineno = line - 1;
  g.mColumn = 1;
  g.mStartOfLine = true;
  g.mLeadingSpace = false;
  return ~YYEOF;
}

[ \t\v\f]            {
  g.mColumn += yyleng;
  g.mLeadingSpace = true;
  return ~YYEOF;
}

\n                    {
  g.mColumn = 1;
  g.mStartOfLine = true;
  g.mLeadingSpace = false;
  return ~YYEOF;
}

<<EOF>>     { COME(YYEOF); }

.           { g.mColumn += yyleng; return ~YYEOF; }

%%

/* about symbols avaliable (yytext, yyleng etc.) in the context of Flex:
 * https://ftp.gnu.org/old-gnu/Manuals/flex-2.5.4/html_node/flex_14.html
 * https://ftp.gnu.org/old-gnu/Manuals/flex-2.5.4/html_node/flex_15.html
*/
