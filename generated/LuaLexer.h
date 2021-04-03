
// Generated from Lua.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"




class  LuaLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, T__17 = 18, T__18 = 19, T__19 = 20, 
    T__20 = 21, IVANMETHOD = 22, FUNCTION = 23, RETURN = 24, LOCAL = 25, 
    TRUE = 26, FALSE = 27, NIL = 28, BREAK = 29, DO = 30, END = 31, GOTO = 32, 
    WHILE = 33, REPEAT = 34, UNTIL = 35, FOR = 36, IF = 37, THEN = 38, ELSE = 39, 
    ELSEIF = 40, IN = 41, SEMI = 42, COMMA = 43, DOT = 44, EQL = 45, COLON = 46, 
    DCOLON = 47, ELLIPSIS = 48, LT = 49, GT = 50, LP = 51, RP = 52, LB = 53, 
    RB = 54, LSB = 55, RSB = 56, NAME = 57, NORMALSTRING = 58, CHARSTRING = 59, 
    LONGSTRING = 60, INT = 61, HEX = 62, FLOAT = 63, HEX_FLOAT = 64, COMMENT = 65, 
    LINE_COMMENT = 66, WS = 67, SHEBANG = 68
  };

  LuaLexer(antlr4::CharStream *input);
  ~LuaLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

