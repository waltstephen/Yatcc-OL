#pragma once

#include <string>
#include <string_view>
#include <cstring>

namespace lex {

enum Id
{
  YYEMPTY = -2,
  YYEOF = 0,     /* "end of file"  */
  YYerror = 256, /* error  */
  YYUNDEF = 257, /* "invalid token"  */
  IDENTIFIER,
  CONSTANT,
  STRING_LITERAL,
  // keywords
  INT,
  RETURN,
  CONST,
  VOID,
  IF,
  ELSE,
  WHILE,
  BREAK,
  CONTINUE,
  // delimiters
  L_BRACE,
  R_BRACE,
  L_SQUARE,
  R_SQUARE,
  L_PAREN,
  R_PAREN,
  SEMI,
  COMMA,
  // operators
  EQUAL,
  PLUS,
  MINUS,
  STAR,
  SLASH,
  PERCENT,
  LESS,
  GREATER,
  LESSEQUAL,
  GREATEREQUAL,
  EQUALEQUAL,
  EXCLAIMEQUAL,
  AMPAMP,
  PIPEPIPE,
  EXCLAIM
};

const char*
id2str(Id id);

struct G
{
  Id mId{ YYEOF };              // 词号
  std::string_view mText;       // 对应文本
  std::string mFile;            // 文件路径
  int mLine{ 1 }, mColumn{ 1 }; // 行号、列号
  bool mStartOfLine{ true };    // 是否是行首
  bool mLeadingSpace{ false };  // 是否有前导空格
  int mLastTokenEndCol{ 1 };    // 上一个token结束列
  int mLastTokenEndLine{ 1 };   // 上一个token结束行
};

extern G g;

int
come(int tokenId, const char* yytext, int yyleng, int startCol);

} // namespace lex
