#include "lex.hpp"
#include <iostream>

void
print_token();

namespace lex {

static const char* kTokenNames[] = {
  "identifier",      "numeric_constant", "string_literal",
  // keywords
  "int",             "return",           "const",
  "void",            "if",               "else",
  "while",           "break",            "continue",
  // delimiters
  "l_brace",         "r_brace",          "l_square",
  "r_square",        "l_paren",          "r_paren",
  "semi",            "comma",
  // operators
  "equal",           "plus",             "minus",
  "star",            "slash",            "percent",
  "less",            "greater",          "lessequal",
  "greaterequal",    "equalequal",       "exclaimequal",
  "ampamp",          "pipepipe",         "exclaim"
};

const char*
id2str(Id id)
{
  static char sCharBuf[2] = { 0, 0 };
  if (id == Id::YYEOF) {
    return "eof";
  }
  else if (id < Id::IDENTIFIER) {
    sCharBuf[0] = char(id);
    return sCharBuf;
  }
  return kTokenNames[int(id) - int(Id::IDENTIFIER)];
}

G g;

int
come(int tokenId, const char* yytext, int yyleng, int startCol)
{
  g.mId = Id(tokenId);
  g.mText = { yytext, std::size_t(yyleng) };

  if (g.mId == Id::YYEOF) {
    // For EOF, report position right after last real token
    g.mColumn = g.mLastTokenEndCol;
    g.mLine = g.mLastTokenEndLine;
    g.mStartOfLine = false;
    g.mLeadingSpace = false;
    print_token();
  } else {
    int endCol = g.mColumn;
    g.mColumn = startCol;
    print_token();
    g.mColumn = endCol;

    // Track last token end position
    g.mLastTokenEndCol = endCol;
    g.mLastTokenEndLine = g.mLine;
  }

  g.mStartOfLine = false;
  g.mLeadingSpace = false;

  return tokenId;
}

} // namespace lex
