
    #include <vector>
    #include <string>


// Generated from Hello.g4 by ANTLR 4.13.1

#pragma once


#include "antlr4-runtime.h"




class  HelloLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, Whitespace = 2, Newline = 3, LineComment = 4, BlockComment = 5, 
    Bool = 6, Break = 7, Const = 8, Continue = 9, Double = 10, Else = 11, 
    False = 12, Float = 13, If = 14, Int = 15, Return = 16, True = 17, Void = 18, 
    While = 19, LeftParen = 20, RightParen = 21, LeftBracket = 22, RightBracket = 23, 
    LeftBrace = 24, RightBrace = 25, LessEqual = 26, GreaterEqual = 27, 
    Less = 28, Greater = 29, Plus = 30, Minus = 31, Star = 32, Div = 33, 
    Mod = 34, AndAnd = 35, OrOr = 36, Not = 37, Semi = 38, Comma = 39, Assign = 40, 
    Equal = 41, NotEqual = 42, Dot = 43, Ident = 44, IntConst = 45, CharConst = 46, 
    FloatConst = 47, Digit = 48
  };

  explicit HelloLexer(antlr4::CharStream *input);

  ~HelloLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

