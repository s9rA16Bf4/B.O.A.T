#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>
#include <vector>

struct tokenType{
  std::string tokenName;
  std::string tokenValue;
};

std::vector<tokenType> legalTokens = {
  {"ILLEGAL", "ILLEGAL"},
  {"EOF", "\0"},
  {"NEWLINE", "\n"},
  {"TAB", "\t"},
  {"SPACE", " "},
  {"INT", "int"},
  {"COMMENT", "%"},
  {"ASSIGN", "="},
  {"ADD","+"},
  {"SUB","-"},
  {"COMMA", ","},
  {"SEMICOMMA", ";"},
  {"LPAREN", "("},
  {"RPAREN", ")"},
  {"LWING", "{"},
  {"RWING", "}"},
  {"PRINT", "print"},
  {"FUNCTION", "def"},
  {"LET", "let"}
};

#endif
