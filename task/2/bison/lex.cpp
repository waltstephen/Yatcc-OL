#include "lex.hpp"
#include <cstring>
#include <iostream>
#include <unordered_map>

namespace lex {

G g;

int
come_line(const char* yytext, int yyleng, int yylineno)
{
  char name[64];
  char value[64];
  sscanf(yytext, "%s '%[^']'", name, value);

  static const std::unordered_map<std::string, int> kTokenId = {
    { "identifier", IDENTIFIER },
    { "numeric_constant", CONSTANT },
    { "string_literal", STRING_LITERAL },
    { "int", INT },
    { "void", VOID },
    { "char", CHAR },
    { "long", LONG },
    { "const", CONST },
    { "return", RETURN },
    { "if", IF },
    { "else", ELSE },
    { "while", WHILE },
    { "do", DO },
    { "for", FOR },
    { "break", BREAK },
    { "continue", CONTINUE },
    { "l_paren", '(' },
    { "r_paren", ')' },
    { "l_brace", '{' },
    { "r_brace", '}' },
    { "semi", ';' },
    { "equal", '=' },
    { "l_square", '[' },
    { "r_square", ']' },
    { "comma", ',' },
    { "minus", '-' },
    { "plus", '+' },
    { "star", '*' },
    { "slash", '/' },
    { "percent", '%' },
    { "less", '<' },
    { "greater", '>' },
    { "lessequal", LE_OP },
    { "greaterequal", GE_OP },
    { "equalequal", EQ_OP },
    { "exclaimequal", NE_OP },
    { "ampamp", AND_OP },
    { "pipepipe", OR_OP },
    { "exclaim", '!' },
    { "amp", '&' },
    { "pipe", '|' },
    { "eof", YYEOF },
  };

  auto iter = kTokenId.find(name);
  assert(iter != kTokenId.end());

  yylval.RawStr = new std::string(value, strlen(value));
  return iter->second;
}

int
come(int tokenId, const char* yytext, int yyleng, int yylineno)
{
  g.mId = tokenId;
  g.mText = { yytext, std::size_t(yyleng) };
  g.mLine = yylineno;

  g.mStartOfLine = false;
  g.mLeadingSpace = false;

  return tokenId;
}

} // namespace lex
