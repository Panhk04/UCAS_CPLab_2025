
    #include <vector>
    #include <string>


// Generated from Hello.g4 by ANTLR 4.13.1


#include "HelloVisitor.h"

#include "HelloParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct HelloParserStaticData final {
  HelloParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  HelloParserStaticData(const HelloParserStaticData&) = delete;
  HelloParserStaticData(HelloParserStaticData&&) = delete;
  HelloParserStaticData& operator=(const HelloParserStaticData&) = delete;
  HelloParserStaticData& operator=(HelloParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag helloParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
HelloParserStaticData *helloParserStaticData = nullptr;

void helloParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (helloParserStaticData != nullptr) {
    return;
  }
#else
  assert(helloParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<HelloParserStaticData>(
    std::vector<std::string>{
      "compUnit", "decl", "btype", "constDecl", "varDecl", "constDef", "constInitVal", 
      "varDef", "funcDef", "funcType", "funcFParams", "funcFParam", "block", 
      "blockItem", "stmt", "lVal", "exp", "constExp", "addExpConst", "mulExpConst", 
      "unaryExpConst", "primaryExpConst", "cond", "number", "funcRParams", 
      "primaryExp", "unaryExp", "mulExp", "addExp", "relExp", "eqExp", "lAndExp", 
      "lOrExp", "character"
    },
    std::vector<std::string>{
      "", "'char'", "", "", "", "", "'bool'", "'break'", "'const'", "'continue'", 
      "'double'", "'else'", "'false'", "'float'", "'if'", "'int'", "'return'", 
      "'true'", "'void'", "'while'", "'('", "')'", "'['", "']'", "'{'", 
      "'}'", "'<='", "'>='", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'", 
      "'&&'", "'||'", "'!'", "';'", "','", "'='", "'=='", "'!='", "'.'", 
      "", "", "'\"character\"'"
    },
    std::vector<std::string>{
      "", "", "Whitespace", "Newline", "LineComment", "BlockComment", "Bool", 
      "Break", "Const", "Continue", "Double", "Else", "False", "Float", 
      "If", "Int", "Return", "True", "Void", "While", "LeftParen", "RightParen", 
      "LeftBracket", "RightBracket", "LeftBrace", "RightBrace", "LessEqual", 
      "GreaterEqual", "Less", "Greater", "Plus", "Minus", "Star", "Div", 
      "Mod", "AndAnd", "OrOr", "Not", "Semi", "Comma", "Assign", "Equal", 
      "NotEqual", "Dot", "Ident", "IntConst", "CharConst", "FloatConst", 
      "Digit"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,48,355,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,7,
  	21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,7,
  	28,2,29,7,29,2,30,7,30,2,31,7,31,2,32,7,32,2,33,7,33,1,0,1,0,4,0,71,8,
  	0,11,0,12,0,72,1,0,1,0,1,1,1,1,3,1,79,8,1,1,2,1,2,1,3,1,3,1,3,1,3,1,3,
  	5,3,88,8,3,10,3,12,3,91,9,3,1,3,1,3,1,4,1,4,1,4,1,4,5,4,99,8,4,10,4,12,
  	4,102,9,4,1,4,1,4,1,5,1,5,1,5,1,5,5,5,110,8,5,10,5,12,5,113,9,5,1,5,1,
  	5,1,5,1,6,1,6,1,6,1,6,1,6,5,6,123,8,6,10,6,12,6,126,9,6,3,6,128,8,6,1,
  	6,3,6,131,8,6,1,7,1,7,1,7,1,7,5,7,137,8,7,10,7,12,7,140,9,7,1,7,1,7,3,
  	7,144,8,7,1,8,1,8,1,8,1,8,3,8,150,8,8,1,8,1,8,1,8,1,9,1,9,3,9,157,8,9,
  	1,10,1,10,1,10,5,10,162,8,10,10,10,12,10,165,9,10,1,11,1,11,1,11,1,11,
  	3,11,171,8,11,1,11,1,11,1,11,1,11,5,11,177,8,11,10,11,12,11,180,9,11,
  	3,11,182,8,11,1,12,1,12,5,12,186,8,12,10,12,12,12,189,9,12,1,12,1,12,
  	1,13,1,13,3,13,195,8,13,1,14,1,14,1,14,1,14,1,14,1,14,3,14,203,8,14,1,
  	14,1,14,1,14,1,14,3,14,209,8,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,
  	14,3,14,219,8,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,3,
  	14,231,8,14,1,15,1,15,1,15,1,15,1,15,5,15,238,8,15,10,15,12,15,241,9,
  	15,1,16,1,16,1,17,1,17,1,17,1,17,1,17,3,17,250,8,17,1,18,1,18,1,18,5,
  	18,255,8,18,10,18,12,18,258,9,18,1,19,1,19,1,19,5,19,263,8,19,10,19,12,
  	19,266,9,19,1,20,1,20,1,20,3,20,271,8,20,1,21,1,21,1,21,1,21,1,21,3,21,
  	278,8,21,1,22,1,22,1,23,1,23,1,24,1,24,1,24,5,24,287,8,24,10,24,12,24,
  	290,9,24,1,25,1,25,1,25,1,25,1,25,1,25,3,25,298,8,25,1,26,1,26,1,26,1,
  	26,1,26,1,26,3,26,306,8,26,1,26,3,26,309,8,26,1,27,1,27,1,27,5,27,314,
  	8,27,10,27,12,27,317,9,27,1,28,1,28,1,28,5,28,322,8,28,10,28,12,28,325,
  	9,28,1,29,1,29,1,29,3,29,330,8,29,1,30,1,30,1,30,3,30,335,8,30,1,31,1,
  	31,1,31,5,31,340,8,31,10,31,12,31,343,9,31,1,32,1,32,1,32,5,32,348,8,
  	32,10,32,12,32,351,9,32,1,33,1,33,1,33,0,0,34,0,2,4,6,8,10,12,14,16,18,
  	20,22,24,26,28,30,32,34,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,
  	66,0,7,3,0,1,1,13,13,15,15,1,0,30,31,1,0,32,34,2,0,30,31,37,37,1,0,45,
  	47,1,0,26,29,1,0,41,42,367,0,70,1,0,0,0,2,78,1,0,0,0,4,80,1,0,0,0,6,82,
  	1,0,0,0,8,94,1,0,0,0,10,105,1,0,0,0,12,130,1,0,0,0,14,132,1,0,0,0,16,
  	145,1,0,0,0,18,156,1,0,0,0,20,158,1,0,0,0,22,166,1,0,0,0,24,183,1,0,0,
  	0,26,194,1,0,0,0,28,230,1,0,0,0,30,232,1,0,0,0,32,242,1,0,0,0,34,249,
  	1,0,0,0,36,251,1,0,0,0,38,259,1,0,0,0,40,270,1,0,0,0,42,277,1,0,0,0,44,
  	279,1,0,0,0,46,281,1,0,0,0,48,283,1,0,0,0,50,297,1,0,0,0,52,308,1,0,0,
  	0,54,310,1,0,0,0,56,318,1,0,0,0,58,326,1,0,0,0,60,331,1,0,0,0,62,336,
  	1,0,0,0,64,344,1,0,0,0,66,352,1,0,0,0,68,71,3,2,1,0,69,71,3,16,8,0,70,
  	68,1,0,0,0,70,69,1,0,0,0,71,72,1,0,0,0,72,70,1,0,0,0,72,73,1,0,0,0,73,
  	74,1,0,0,0,74,75,5,0,0,1,75,1,1,0,0,0,76,79,3,6,3,0,77,79,3,8,4,0,78,
  	76,1,0,0,0,78,77,1,0,0,0,79,3,1,0,0,0,80,81,7,0,0,0,81,5,1,0,0,0,82,83,
  	5,8,0,0,83,84,3,4,2,0,84,89,3,10,5,0,85,86,5,39,0,0,86,88,3,10,5,0,87,
  	85,1,0,0,0,88,91,1,0,0,0,89,87,1,0,0,0,89,90,1,0,0,0,90,92,1,0,0,0,91,
  	89,1,0,0,0,92,93,5,38,0,0,93,7,1,0,0,0,94,95,3,4,2,0,95,100,3,14,7,0,
  	96,97,5,39,0,0,97,99,3,14,7,0,98,96,1,0,0,0,99,102,1,0,0,0,100,98,1,0,
  	0,0,100,101,1,0,0,0,101,103,1,0,0,0,102,100,1,0,0,0,103,104,5,38,0,0,
  	104,9,1,0,0,0,105,111,5,44,0,0,106,107,5,22,0,0,107,108,5,45,0,0,108,
  	110,5,23,0,0,109,106,1,0,0,0,110,113,1,0,0,0,111,109,1,0,0,0,111,112,
  	1,0,0,0,112,114,1,0,0,0,113,111,1,0,0,0,114,115,5,40,0,0,115,116,3,12,
  	6,0,116,11,1,0,0,0,117,131,3,34,17,0,118,127,5,24,0,0,119,124,3,12,6,
  	0,120,121,5,39,0,0,121,123,3,12,6,0,122,120,1,0,0,0,123,126,1,0,0,0,124,
  	122,1,0,0,0,124,125,1,0,0,0,125,128,1,0,0,0,126,124,1,0,0,0,127,119,1,
  	0,0,0,127,128,1,0,0,0,128,129,1,0,0,0,129,131,5,25,0,0,130,117,1,0,0,
  	0,130,118,1,0,0,0,131,13,1,0,0,0,132,138,5,44,0,0,133,134,5,22,0,0,134,
  	135,5,45,0,0,135,137,5,23,0,0,136,133,1,0,0,0,137,140,1,0,0,0,138,136,
  	1,0,0,0,138,139,1,0,0,0,139,143,1,0,0,0,140,138,1,0,0,0,141,142,5,40,
  	0,0,142,144,3,12,6,0,143,141,1,0,0,0,143,144,1,0,0,0,144,15,1,0,0,0,145,
  	146,3,18,9,0,146,147,5,44,0,0,147,149,5,20,0,0,148,150,3,20,10,0,149,
  	148,1,0,0,0,149,150,1,0,0,0,150,151,1,0,0,0,151,152,5,21,0,0,152,153,
  	3,24,12,0,153,17,1,0,0,0,154,157,5,18,0,0,155,157,3,4,2,0,156,154,1,0,
  	0,0,156,155,1,0,0,0,157,19,1,0,0,0,158,163,3,22,11,0,159,160,5,39,0,0,
  	160,162,3,22,11,0,161,159,1,0,0,0,162,165,1,0,0,0,163,161,1,0,0,0,163,
  	164,1,0,0,0,164,21,1,0,0,0,165,163,1,0,0,0,166,167,3,4,2,0,167,181,5,
  	44,0,0,168,170,5,22,0,0,169,171,5,45,0,0,170,169,1,0,0,0,170,171,1,0,
  	0,0,171,172,1,0,0,0,172,178,5,23,0,0,173,174,5,22,0,0,174,175,5,45,0,
  	0,175,177,5,23,0,0,176,173,1,0,0,0,177,180,1,0,0,0,178,176,1,0,0,0,178,
  	179,1,0,0,0,179,182,1,0,0,0,180,178,1,0,0,0,181,168,1,0,0,0,181,182,1,
  	0,0,0,182,23,1,0,0,0,183,187,5,24,0,0,184,186,3,26,13,0,185,184,1,0,0,
  	0,186,189,1,0,0,0,187,185,1,0,0,0,187,188,1,0,0,0,188,190,1,0,0,0,189,
  	187,1,0,0,0,190,191,5,25,0,0,191,25,1,0,0,0,192,195,3,2,1,0,193,195,3,
  	28,14,0,194,192,1,0,0,0,194,193,1,0,0,0,195,27,1,0,0,0,196,197,3,30,15,
  	0,197,198,5,40,0,0,198,199,3,32,16,0,199,200,5,38,0,0,200,231,1,0,0,0,
  	201,203,3,32,16,0,202,201,1,0,0,0,202,203,1,0,0,0,203,204,1,0,0,0,204,
  	231,5,38,0,0,205,231,3,24,12,0,206,208,5,16,0,0,207,209,3,32,16,0,208,
  	207,1,0,0,0,208,209,1,0,0,0,209,210,1,0,0,0,210,231,5,38,0,0,211,212,
  	5,14,0,0,212,213,5,20,0,0,213,214,3,44,22,0,214,215,5,21,0,0,215,218,
  	3,28,14,0,216,217,5,11,0,0,217,219,3,28,14,0,218,216,1,0,0,0,218,219,
  	1,0,0,0,219,231,1,0,0,0,220,221,5,19,0,0,221,222,5,20,0,0,222,223,3,44,
  	22,0,223,224,5,21,0,0,224,225,3,28,14,0,225,231,1,0,0,0,226,227,5,7,0,
  	0,227,231,5,38,0,0,228,229,5,9,0,0,229,231,5,38,0,0,230,196,1,0,0,0,230,
  	202,1,0,0,0,230,205,1,0,0,0,230,206,1,0,0,0,230,211,1,0,0,0,230,220,1,
  	0,0,0,230,226,1,0,0,0,230,228,1,0,0,0,231,29,1,0,0,0,232,239,5,44,0,0,
  	233,234,5,22,0,0,234,235,3,32,16,0,235,236,5,23,0,0,236,238,1,0,0,0,237,
  	233,1,0,0,0,238,241,1,0,0,0,239,237,1,0,0,0,239,240,1,0,0,0,240,31,1,
  	0,0,0,241,239,1,0,0,0,242,243,3,56,28,0,243,33,1,0,0,0,244,250,3,46,23,
  	0,245,246,5,20,0,0,246,247,3,34,17,0,247,248,5,21,0,0,248,250,1,0,0,0,
  	249,244,1,0,0,0,249,245,1,0,0,0,250,35,1,0,0,0,251,256,3,38,19,0,252,
  	253,7,1,0,0,253,255,3,38,19,0,254,252,1,0,0,0,255,258,1,0,0,0,256,254,
  	1,0,0,0,256,257,1,0,0,0,257,37,1,0,0,0,258,256,1,0,0,0,259,264,3,40,20,
  	0,260,261,7,2,0,0,261,263,3,40,20,0,262,260,1,0,0,0,263,266,1,0,0,0,264,
  	262,1,0,0,0,264,265,1,0,0,0,265,39,1,0,0,0,266,264,1,0,0,0,267,268,7,
  	3,0,0,268,271,3,40,20,0,269,271,3,42,21,0,270,267,1,0,0,0,270,269,1,0,
  	0,0,271,41,1,0,0,0,272,273,5,20,0,0,273,274,3,34,17,0,274,275,5,21,0,
  	0,275,278,1,0,0,0,276,278,3,46,23,0,277,272,1,0,0,0,277,276,1,0,0,0,278,
  	43,1,0,0,0,279,280,3,64,32,0,280,45,1,0,0,0,281,282,7,4,0,0,282,47,1,
  	0,0,0,283,288,3,32,16,0,284,285,5,39,0,0,285,287,3,32,16,0,286,284,1,
  	0,0,0,287,290,1,0,0,0,288,286,1,0,0,0,288,289,1,0,0,0,289,49,1,0,0,0,
  	290,288,1,0,0,0,291,292,5,20,0,0,292,293,3,32,16,0,293,294,5,21,0,0,294,
  	298,1,0,0,0,295,298,3,30,15,0,296,298,3,46,23,0,297,291,1,0,0,0,297,295,
  	1,0,0,0,297,296,1,0,0,0,298,51,1,0,0,0,299,309,3,50,25,0,300,301,7,3,
  	0,0,301,309,3,52,26,0,302,303,5,44,0,0,303,305,5,20,0,0,304,306,3,48,
  	24,0,305,304,1,0,0,0,305,306,1,0,0,0,306,307,1,0,0,0,307,309,5,21,0,0,
  	308,299,1,0,0,0,308,300,1,0,0,0,308,302,1,0,0,0,309,53,1,0,0,0,310,315,
  	3,52,26,0,311,312,7,2,0,0,312,314,3,52,26,0,313,311,1,0,0,0,314,317,1,
  	0,0,0,315,313,1,0,0,0,315,316,1,0,0,0,316,55,1,0,0,0,317,315,1,0,0,0,
  	318,323,3,54,27,0,319,320,7,1,0,0,320,322,3,54,27,0,321,319,1,0,0,0,322,
  	325,1,0,0,0,323,321,1,0,0,0,323,324,1,0,0,0,324,57,1,0,0,0,325,323,1,
  	0,0,0,326,329,3,56,28,0,327,328,7,5,0,0,328,330,3,56,28,0,329,327,1,0,
  	0,0,329,330,1,0,0,0,330,59,1,0,0,0,331,334,3,58,29,0,332,333,7,6,0,0,
  	333,335,3,58,29,0,334,332,1,0,0,0,334,335,1,0,0,0,335,61,1,0,0,0,336,
  	341,3,60,30,0,337,338,5,35,0,0,338,340,3,60,30,0,339,337,1,0,0,0,340,
  	343,1,0,0,0,341,339,1,0,0,0,341,342,1,0,0,0,342,63,1,0,0,0,343,341,1,
  	0,0,0,344,349,3,62,31,0,345,346,5,36,0,0,346,348,3,62,31,0,347,345,1,
  	0,0,0,348,351,1,0,0,0,349,347,1,0,0,0,349,350,1,0,0,0,350,65,1,0,0,0,
  	351,349,1,0,0,0,352,353,1,0,0,0,353,67,1,0,0,0,39,70,72,78,89,100,111,
  	124,127,130,138,143,149,156,163,170,178,181,187,194,202,208,218,230,239,
  	249,256,264,270,277,288,297,305,308,315,323,329,334,341,349
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  helloParserStaticData = staticData.release();
}

}

HelloParser::HelloParser(TokenStream *input) : HelloParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

HelloParser::HelloParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  HelloParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *helloParserStaticData->atn, helloParserStaticData->decisionToDFA, helloParserStaticData->sharedContextCache, options);
}

HelloParser::~HelloParser() {
  delete _interpreter;
}

const atn::ATN& HelloParser::getATN() const {
  return *helloParserStaticData->atn;
}

std::string HelloParser::getGrammarFileName() const {
  return "Hello.g4";
}

const std::vector<std::string>& HelloParser::getRuleNames() const {
  return helloParserStaticData->ruleNames;
}

const dfa::Vocabulary& HelloParser::getVocabulary() const {
  return helloParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView HelloParser::getSerializedATN() const {
  return helloParserStaticData->serializedATN;
}


//----------------- CompUnitContext ------------------------------------------------------------------

HelloParser::CompUnitContext::CompUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::CompUnitContext::EOF() {
  return getToken(HelloParser::EOF, 0);
}

std::vector<HelloParser::DeclContext *> HelloParser::CompUnitContext::decl() {
  return getRuleContexts<HelloParser::DeclContext>();
}

HelloParser::DeclContext* HelloParser::CompUnitContext::decl(size_t i) {
  return getRuleContext<HelloParser::DeclContext>(i);
}

std::vector<HelloParser::FuncDefContext *> HelloParser::CompUnitContext::funcDef() {
  return getRuleContexts<HelloParser::FuncDefContext>();
}

HelloParser::FuncDefContext* HelloParser::CompUnitContext::funcDef(size_t i) {
  return getRuleContext<HelloParser::FuncDefContext>(i);
}


size_t HelloParser::CompUnitContext::getRuleIndex() const {
  return HelloParser::RuleCompUnit;
}


std::any HelloParser::CompUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitCompUnit(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::CompUnitContext* HelloParser::compUnit() {
  CompUnitContext *_localctx = _tracker.createInstance<CompUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, HelloParser::RuleCompUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(70); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(70);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(68);
        decl();
        break;
      }

      case 2: {
        setState(69);
        funcDef();
        break;
      }

      default:
        break;
      }
      setState(72); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 303362) != 0));
    setState(74);
    match(HelloParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclContext ------------------------------------------------------------------

HelloParser::DeclContext::DeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::ConstDeclContext* HelloParser::DeclContext::constDecl() {
  return getRuleContext<HelloParser::ConstDeclContext>(0);
}

HelloParser::VarDeclContext* HelloParser::DeclContext::varDecl() {
  return getRuleContext<HelloParser::VarDeclContext>(0);
}


size_t HelloParser::DeclContext::getRuleIndex() const {
  return HelloParser::RuleDecl;
}


std::any HelloParser::DeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitDecl(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::DeclContext* HelloParser::decl() {
  DeclContext *_localctx = _tracker.createInstance<DeclContext>(_ctx, getState());
  enterRule(_localctx, 2, HelloParser::RuleDecl);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(78);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HelloParser::Const: {
        enterOuterAlt(_localctx, 1);
        setState(76);
        constDecl();
        break;
      }

      case HelloParser::T__0:
      case HelloParser::Float:
      case HelloParser::Int: {
        enterOuterAlt(_localctx, 2);
        setState(77);
        varDecl();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BtypeContext ------------------------------------------------------------------

HelloParser::BtypeContext::BtypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::BtypeContext::Int() {
  return getToken(HelloParser::Int, 0);
}

tree::TerminalNode* HelloParser::BtypeContext::Float() {
  return getToken(HelloParser::Float, 0);
}


size_t HelloParser::BtypeContext::getRuleIndex() const {
  return HelloParser::RuleBtype;
}


std::any HelloParser::BtypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitBtype(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::BtypeContext* HelloParser::btype() {
  BtypeContext *_localctx = _tracker.createInstance<BtypeContext>(_ctx, getState());
  enterRule(_localctx, 4, HelloParser::RuleBtype);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(80);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 40962) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDeclContext ------------------------------------------------------------------

HelloParser::ConstDeclContext::ConstDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::ConstDeclContext::Const() {
  return getToken(HelloParser::Const, 0);
}

HelloParser::BtypeContext* HelloParser::ConstDeclContext::btype() {
  return getRuleContext<HelloParser::BtypeContext>(0);
}

std::vector<HelloParser::ConstDefContext *> HelloParser::ConstDeclContext::constDef() {
  return getRuleContexts<HelloParser::ConstDefContext>();
}

HelloParser::ConstDefContext* HelloParser::ConstDeclContext::constDef(size_t i) {
  return getRuleContext<HelloParser::ConstDefContext>(i);
}

tree::TerminalNode* HelloParser::ConstDeclContext::Semi() {
  return getToken(HelloParser::Semi, 0);
}

std::vector<tree::TerminalNode *> HelloParser::ConstDeclContext::Comma() {
  return getTokens(HelloParser::Comma);
}

tree::TerminalNode* HelloParser::ConstDeclContext::Comma(size_t i) {
  return getToken(HelloParser::Comma, i);
}


size_t HelloParser::ConstDeclContext::getRuleIndex() const {
  return HelloParser::RuleConstDecl;
}


std::any HelloParser::ConstDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitConstDecl(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::ConstDeclContext* HelloParser::constDecl() {
  ConstDeclContext *_localctx = _tracker.createInstance<ConstDeclContext>(_ctx, getState());
  enterRule(_localctx, 6, HelloParser::RuleConstDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(82);
    match(HelloParser::Const);
    setState(83);
    btype();
    setState(84);
    constDef();
    setState(89);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::Comma) {
      setState(85);
      match(HelloParser::Comma);
      setState(86);
      constDef();
      setState(91);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(92);
    match(HelloParser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDeclContext ------------------------------------------------------------------

HelloParser::VarDeclContext::VarDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::BtypeContext* HelloParser::VarDeclContext::btype() {
  return getRuleContext<HelloParser::BtypeContext>(0);
}

std::vector<HelloParser::VarDefContext *> HelloParser::VarDeclContext::varDef() {
  return getRuleContexts<HelloParser::VarDefContext>();
}

HelloParser::VarDefContext* HelloParser::VarDeclContext::varDef(size_t i) {
  return getRuleContext<HelloParser::VarDefContext>(i);
}

tree::TerminalNode* HelloParser::VarDeclContext::Semi() {
  return getToken(HelloParser::Semi, 0);
}

std::vector<tree::TerminalNode *> HelloParser::VarDeclContext::Comma() {
  return getTokens(HelloParser::Comma);
}

tree::TerminalNode* HelloParser::VarDeclContext::Comma(size_t i) {
  return getToken(HelloParser::Comma, i);
}


size_t HelloParser::VarDeclContext::getRuleIndex() const {
  return HelloParser::RuleVarDecl;
}


std::any HelloParser::VarDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitVarDecl(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::VarDeclContext* HelloParser::varDecl() {
  VarDeclContext *_localctx = _tracker.createInstance<VarDeclContext>(_ctx, getState());
  enterRule(_localctx, 8, HelloParser::RuleVarDecl);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(94);
    btype();
    setState(95);
    varDef();
    setState(100);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::Comma) {
      setState(96);
      match(HelloParser::Comma);
      setState(97);
      varDef();
      setState(102);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(103);
    match(HelloParser::Semi);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstDefContext ------------------------------------------------------------------

HelloParser::ConstDefContext::ConstDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::ConstDefContext::Ident() {
  return getToken(HelloParser::Ident, 0);
}

tree::TerminalNode* HelloParser::ConstDefContext::Assign() {
  return getToken(HelloParser::Assign, 0);
}

HelloParser::ConstInitValContext* HelloParser::ConstDefContext::constInitVal() {
  return getRuleContext<HelloParser::ConstInitValContext>(0);
}

std::vector<tree::TerminalNode *> HelloParser::ConstDefContext::LeftBracket() {
  return getTokens(HelloParser::LeftBracket);
}

tree::TerminalNode* HelloParser::ConstDefContext::LeftBracket(size_t i) {
  return getToken(HelloParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> HelloParser::ConstDefContext::IntConst() {
  return getTokens(HelloParser::IntConst);
}

tree::TerminalNode* HelloParser::ConstDefContext::IntConst(size_t i) {
  return getToken(HelloParser::IntConst, i);
}

std::vector<tree::TerminalNode *> HelloParser::ConstDefContext::RightBracket() {
  return getTokens(HelloParser::RightBracket);
}

tree::TerminalNode* HelloParser::ConstDefContext::RightBracket(size_t i) {
  return getToken(HelloParser::RightBracket, i);
}


size_t HelloParser::ConstDefContext::getRuleIndex() const {
  return HelloParser::RuleConstDef;
}


std::any HelloParser::ConstDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitConstDef(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::ConstDefContext* HelloParser::constDef() {
  ConstDefContext *_localctx = _tracker.createInstance<ConstDefContext>(_ctx, getState());
  enterRule(_localctx, 10, HelloParser::RuleConstDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(105);
    match(HelloParser::Ident);
    setState(111);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::LeftBracket) {
      setState(106);
      match(HelloParser::LeftBracket);
      setState(107);
      match(HelloParser::IntConst);
      setState(108);
      match(HelloParser::RightBracket);
      setState(113);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(114);
    match(HelloParser::Assign);
    setState(115);
    constInitVal();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstInitValContext ------------------------------------------------------------------

HelloParser::ConstInitValContext::ConstInitValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::ConstExpContext* HelloParser::ConstInitValContext::constExp() {
  return getRuleContext<HelloParser::ConstExpContext>(0);
}

tree::TerminalNode* HelloParser::ConstInitValContext::LeftBrace() {
  return getToken(HelloParser::LeftBrace, 0);
}

tree::TerminalNode* HelloParser::ConstInitValContext::RightBrace() {
  return getToken(HelloParser::RightBrace, 0);
}

std::vector<HelloParser::ConstInitValContext *> HelloParser::ConstInitValContext::constInitVal() {
  return getRuleContexts<HelloParser::ConstInitValContext>();
}

HelloParser::ConstInitValContext* HelloParser::ConstInitValContext::constInitVal(size_t i) {
  return getRuleContext<HelloParser::ConstInitValContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::ConstInitValContext::Comma() {
  return getTokens(HelloParser::Comma);
}

tree::TerminalNode* HelloParser::ConstInitValContext::Comma(size_t i) {
  return getToken(HelloParser::Comma, i);
}


size_t HelloParser::ConstInitValContext::getRuleIndex() const {
  return HelloParser::RuleConstInitVal;
}


std::any HelloParser::ConstInitValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitConstInitVal(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::ConstInitValContext* HelloParser::constInitVal() {
  ConstInitValContext *_localctx = _tracker.createInstance<ConstInitValContext>(_ctx, getState());
  enterRule(_localctx, 12, HelloParser::RuleConstInitVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(130);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HelloParser::LeftParen:
      case HelloParser::IntConst:
      case HelloParser::CharConst:
      case HelloParser::FloatConst: {
        enterOuterAlt(_localctx, 1);
        setState(117);
        constExp();
        break;
      }

      case HelloParser::LeftBrace: {
        enterOuterAlt(_localctx, 2);
        setState(118);
        match(HelloParser::LeftBrace);
        setState(127);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 246290622447616) != 0)) {
          setState(119);
          constInitVal();
          setState(124);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == HelloParser::Comma) {
            setState(120);
            match(HelloParser::Comma);
            setState(121);
            constInitVal();
            setState(126);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(129);
        match(HelloParser::RightBrace);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarDefContext ------------------------------------------------------------------

HelloParser::VarDefContext::VarDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::VarDefContext::Ident() {
  return getToken(HelloParser::Ident, 0);
}

std::vector<tree::TerminalNode *> HelloParser::VarDefContext::LeftBracket() {
  return getTokens(HelloParser::LeftBracket);
}

tree::TerminalNode* HelloParser::VarDefContext::LeftBracket(size_t i) {
  return getToken(HelloParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> HelloParser::VarDefContext::IntConst() {
  return getTokens(HelloParser::IntConst);
}

tree::TerminalNode* HelloParser::VarDefContext::IntConst(size_t i) {
  return getToken(HelloParser::IntConst, i);
}

std::vector<tree::TerminalNode *> HelloParser::VarDefContext::RightBracket() {
  return getTokens(HelloParser::RightBracket);
}

tree::TerminalNode* HelloParser::VarDefContext::RightBracket(size_t i) {
  return getToken(HelloParser::RightBracket, i);
}

tree::TerminalNode* HelloParser::VarDefContext::Assign() {
  return getToken(HelloParser::Assign, 0);
}

HelloParser::ConstInitValContext* HelloParser::VarDefContext::constInitVal() {
  return getRuleContext<HelloParser::ConstInitValContext>(0);
}


size_t HelloParser::VarDefContext::getRuleIndex() const {
  return HelloParser::RuleVarDef;
}


std::any HelloParser::VarDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitVarDef(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::VarDefContext* HelloParser::varDef() {
  VarDefContext *_localctx = _tracker.createInstance<VarDefContext>(_ctx, getState());
  enterRule(_localctx, 14, HelloParser::RuleVarDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(132);
    match(HelloParser::Ident);
    setState(138);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::LeftBracket) {
      setState(133);
      match(HelloParser::LeftBracket);
      setState(134);
      match(HelloParser::IntConst);
      setState(135);
      match(HelloParser::RightBracket);
      setState(140);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(143);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HelloParser::Assign) {
      setState(141);
      match(HelloParser::Assign);
      setState(142);
      constInitVal();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncDefContext ------------------------------------------------------------------

HelloParser::FuncDefContext::FuncDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::FuncTypeContext* HelloParser::FuncDefContext::funcType() {
  return getRuleContext<HelloParser::FuncTypeContext>(0);
}

tree::TerminalNode* HelloParser::FuncDefContext::Ident() {
  return getToken(HelloParser::Ident, 0);
}

tree::TerminalNode* HelloParser::FuncDefContext::LeftParen() {
  return getToken(HelloParser::LeftParen, 0);
}

tree::TerminalNode* HelloParser::FuncDefContext::RightParen() {
  return getToken(HelloParser::RightParen, 0);
}

HelloParser::BlockContext* HelloParser::FuncDefContext::block() {
  return getRuleContext<HelloParser::BlockContext>(0);
}

HelloParser::FuncFParamsContext* HelloParser::FuncDefContext::funcFParams() {
  return getRuleContext<HelloParser::FuncFParamsContext>(0);
}


size_t HelloParser::FuncDefContext::getRuleIndex() const {
  return HelloParser::RuleFuncDef;
}


std::any HelloParser::FuncDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitFuncDef(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::FuncDefContext* HelloParser::funcDef() {
  FuncDefContext *_localctx = _tracker.createInstance<FuncDefContext>(_ctx, getState());
  enterRule(_localctx, 16, HelloParser::RuleFuncDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(145);
    funcType();
    setState(146);
    match(HelloParser::Ident);
    setState(147);
    match(HelloParser::LeftParen);
    setState(149);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 40962) != 0)) {
      setState(148);
      funcFParams();
    }
    setState(151);
    match(HelloParser::RightParen);
    setState(152);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncTypeContext ------------------------------------------------------------------

HelloParser::FuncTypeContext::FuncTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::FuncTypeContext::Void() {
  return getToken(HelloParser::Void, 0);
}

HelloParser::BtypeContext* HelloParser::FuncTypeContext::btype() {
  return getRuleContext<HelloParser::BtypeContext>(0);
}


size_t HelloParser::FuncTypeContext::getRuleIndex() const {
  return HelloParser::RuleFuncType;
}


std::any HelloParser::FuncTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitFuncType(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::FuncTypeContext* HelloParser::funcType() {
  FuncTypeContext *_localctx = _tracker.createInstance<FuncTypeContext>(_ctx, getState());
  enterRule(_localctx, 18, HelloParser::RuleFuncType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(156);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HelloParser::Void: {
        enterOuterAlt(_localctx, 1);
        setState(154);
        match(HelloParser::Void);
        break;
      }

      case HelloParser::T__0:
      case HelloParser::Float:
      case HelloParser::Int: {
        enterOuterAlt(_localctx, 2);
        setState(155);
        btype();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamsContext ------------------------------------------------------------------

HelloParser::FuncFParamsContext::FuncFParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::FuncFParamContext *> HelloParser::FuncFParamsContext::funcFParam() {
  return getRuleContexts<HelloParser::FuncFParamContext>();
}

HelloParser::FuncFParamContext* HelloParser::FuncFParamsContext::funcFParam(size_t i) {
  return getRuleContext<HelloParser::FuncFParamContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::FuncFParamsContext::Comma() {
  return getTokens(HelloParser::Comma);
}

tree::TerminalNode* HelloParser::FuncFParamsContext::Comma(size_t i) {
  return getToken(HelloParser::Comma, i);
}


size_t HelloParser::FuncFParamsContext::getRuleIndex() const {
  return HelloParser::RuleFuncFParams;
}


std::any HelloParser::FuncFParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitFuncFParams(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::FuncFParamsContext* HelloParser::funcFParams() {
  FuncFParamsContext *_localctx = _tracker.createInstance<FuncFParamsContext>(_ctx, getState());
  enterRule(_localctx, 20, HelloParser::RuleFuncFParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(158);
    funcFParam();
    setState(163);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::Comma) {
      setState(159);
      match(HelloParser::Comma);
      setState(160);
      funcFParam();
      setState(165);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncFParamContext ------------------------------------------------------------------

HelloParser::FuncFParamContext::FuncFParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::BtypeContext* HelloParser::FuncFParamContext::btype() {
  return getRuleContext<HelloParser::BtypeContext>(0);
}

tree::TerminalNode* HelloParser::FuncFParamContext::Ident() {
  return getToken(HelloParser::Ident, 0);
}

std::vector<tree::TerminalNode *> HelloParser::FuncFParamContext::LeftBracket() {
  return getTokens(HelloParser::LeftBracket);
}

tree::TerminalNode* HelloParser::FuncFParamContext::LeftBracket(size_t i) {
  return getToken(HelloParser::LeftBracket, i);
}

std::vector<tree::TerminalNode *> HelloParser::FuncFParamContext::RightBracket() {
  return getTokens(HelloParser::RightBracket);
}

tree::TerminalNode* HelloParser::FuncFParamContext::RightBracket(size_t i) {
  return getToken(HelloParser::RightBracket, i);
}

std::vector<tree::TerminalNode *> HelloParser::FuncFParamContext::IntConst() {
  return getTokens(HelloParser::IntConst);
}

tree::TerminalNode* HelloParser::FuncFParamContext::IntConst(size_t i) {
  return getToken(HelloParser::IntConst, i);
}


size_t HelloParser::FuncFParamContext::getRuleIndex() const {
  return HelloParser::RuleFuncFParam;
}


std::any HelloParser::FuncFParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitFuncFParam(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::FuncFParamContext* HelloParser::funcFParam() {
  FuncFParamContext *_localctx = _tracker.createInstance<FuncFParamContext>(_ctx, getState());
  enterRule(_localctx, 22, HelloParser::RuleFuncFParam);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(166);
    btype();
    setState(167);
    match(HelloParser::Ident);
    setState(181);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HelloParser::LeftBracket) {
      setState(168);
      match(HelloParser::LeftBracket);
      setState(170);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == HelloParser::IntConst) {
        setState(169);
        match(HelloParser::IntConst);
      }
      setState(172);
      match(HelloParser::RightBracket);
      setState(178);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == HelloParser::LeftBracket) {
        setState(173);
        match(HelloParser::LeftBracket);
        setState(174);
        match(HelloParser::IntConst);
        setState(175);
        match(HelloParser::RightBracket);
        setState(180);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

HelloParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::BlockContext::LeftBrace() {
  return getToken(HelloParser::LeftBrace, 0);
}

tree::TerminalNode* HelloParser::BlockContext::RightBrace() {
  return getToken(HelloParser::RightBrace, 0);
}

std::vector<HelloParser::BlockItemContext *> HelloParser::BlockContext::blockItem() {
  return getRuleContexts<HelloParser::BlockItemContext>();
}

HelloParser::BlockItemContext* HelloParser::BlockContext::blockItem(size_t i) {
  return getRuleContext<HelloParser::BlockItemContext>(i);
}


size_t HelloParser::BlockContext::getRuleIndex() const {
  return HelloParser::RuleBlock;
}


std::any HelloParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::BlockContext* HelloParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 24, HelloParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(183);
    match(HelloParser::LeftBrace);
    setState(187);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 264298347225986) != 0)) {
      setState(184);
      blockItem();
      setState(189);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(190);
    match(HelloParser::RightBrace);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockItemContext ------------------------------------------------------------------

HelloParser::BlockItemContext::BlockItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::DeclContext* HelloParser::BlockItemContext::decl() {
  return getRuleContext<HelloParser::DeclContext>(0);
}

HelloParser::StmtContext* HelloParser::BlockItemContext::stmt() {
  return getRuleContext<HelloParser::StmtContext>(0);
}


size_t HelloParser::BlockItemContext::getRuleIndex() const {
  return HelloParser::RuleBlockItem;
}


std::any HelloParser::BlockItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitBlockItem(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::BlockItemContext* HelloParser::blockItem() {
  BlockItemContext *_localctx = _tracker.createInstance<BlockItemContext>(_ctx, getState());
  enterRule(_localctx, 26, HelloParser::RuleBlockItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(194);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HelloParser::T__0:
      case HelloParser::Const:
      case HelloParser::Float:
      case HelloParser::Int: {
        enterOuterAlt(_localctx, 1);
        setState(192);
        decl();
        break;
      }

      case HelloParser::Break:
      case HelloParser::Continue:
      case HelloParser::If:
      case HelloParser::Return:
      case HelloParser::While:
      case HelloParser::LeftParen:
      case HelloParser::LeftBrace:
      case HelloParser::Plus:
      case HelloParser::Minus:
      case HelloParser::Not:
      case HelloParser::Semi:
      case HelloParser::Ident:
      case HelloParser::IntConst:
      case HelloParser::CharConst:
      case HelloParser::FloatConst: {
        enterOuterAlt(_localctx, 2);
        setState(193);
        stmt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

HelloParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::LValContext* HelloParser::StmtContext::lVal() {
  return getRuleContext<HelloParser::LValContext>(0);
}

tree::TerminalNode* HelloParser::StmtContext::Assign() {
  return getToken(HelloParser::Assign, 0);
}

HelloParser::ExpContext* HelloParser::StmtContext::exp() {
  return getRuleContext<HelloParser::ExpContext>(0);
}

tree::TerminalNode* HelloParser::StmtContext::Semi() {
  return getToken(HelloParser::Semi, 0);
}

HelloParser::BlockContext* HelloParser::StmtContext::block() {
  return getRuleContext<HelloParser::BlockContext>(0);
}

tree::TerminalNode* HelloParser::StmtContext::Return() {
  return getToken(HelloParser::Return, 0);
}

tree::TerminalNode* HelloParser::StmtContext::If() {
  return getToken(HelloParser::If, 0);
}

tree::TerminalNode* HelloParser::StmtContext::LeftParen() {
  return getToken(HelloParser::LeftParen, 0);
}

HelloParser::CondContext* HelloParser::StmtContext::cond() {
  return getRuleContext<HelloParser::CondContext>(0);
}

tree::TerminalNode* HelloParser::StmtContext::RightParen() {
  return getToken(HelloParser::RightParen, 0);
}

std::vector<HelloParser::StmtContext *> HelloParser::StmtContext::stmt() {
  return getRuleContexts<HelloParser::StmtContext>();
}

HelloParser::StmtContext* HelloParser::StmtContext::stmt(size_t i) {
  return getRuleContext<HelloParser::StmtContext>(i);
}

tree::TerminalNode* HelloParser::StmtContext::Else() {
  return getToken(HelloParser::Else, 0);
}

tree::TerminalNode* HelloParser::StmtContext::While() {
  return getToken(HelloParser::While, 0);
}

tree::TerminalNode* HelloParser::StmtContext::Break() {
  return getToken(HelloParser::Break, 0);
}

tree::TerminalNode* HelloParser::StmtContext::Continue() {
  return getToken(HelloParser::Continue, 0);
}


size_t HelloParser::StmtContext::getRuleIndex() const {
  return HelloParser::RuleStmt;
}


std::any HelloParser::StmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitStmt(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::StmtContext* HelloParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 28, HelloParser::RuleStmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(230);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(196);
      lVal();
      setState(197);
      match(HelloParser::Assign);
      setState(198);
      exp();
      setState(199);
      match(HelloParser::Semi);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(202);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 264023451893760) != 0)) {
        setState(201);
        exp();
      }
      setState(204);
      match(HelloParser::Semi);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(205);
      block();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(206);
      match(HelloParser::Return);
      setState(208);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 264023451893760) != 0)) {
        setState(207);
        exp();
      }
      setState(210);
      match(HelloParser::Semi);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(211);
      match(HelloParser::If);
      setState(212);
      match(HelloParser::LeftParen);
      setState(213);
      cond();
      setState(214);
      match(HelloParser::RightParen);
      setState(215);
      stmt();
      setState(218);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx)) {
      case 1: {
        setState(216);
        match(HelloParser::Else);
        setState(217);
        stmt();
        break;
      }

      default:
        break;
      }
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(220);
      match(HelloParser::While);
      setState(221);
      match(HelloParser::LeftParen);
      setState(222);
      cond();
      setState(223);
      match(HelloParser::RightParen);
      setState(224);
      stmt();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(226);
      match(HelloParser::Break);
      setState(227);
      match(HelloParser::Semi);
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(228);
      match(HelloParser::Continue);
      setState(229);
      match(HelloParser::Semi);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LValContext ------------------------------------------------------------------

HelloParser::LValContext::LValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::LValContext::Ident() {
  return getToken(HelloParser::Ident, 0);
}

std::vector<tree::TerminalNode *> HelloParser::LValContext::LeftBracket() {
  return getTokens(HelloParser::LeftBracket);
}

tree::TerminalNode* HelloParser::LValContext::LeftBracket(size_t i) {
  return getToken(HelloParser::LeftBracket, i);
}

std::vector<HelloParser::ExpContext *> HelloParser::LValContext::exp() {
  return getRuleContexts<HelloParser::ExpContext>();
}

HelloParser::ExpContext* HelloParser::LValContext::exp(size_t i) {
  return getRuleContext<HelloParser::ExpContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::LValContext::RightBracket() {
  return getTokens(HelloParser::RightBracket);
}

tree::TerminalNode* HelloParser::LValContext::RightBracket(size_t i) {
  return getToken(HelloParser::RightBracket, i);
}


size_t HelloParser::LValContext::getRuleIndex() const {
  return HelloParser::RuleLVal;
}


std::any HelloParser::LValContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitLVal(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::LValContext* HelloParser::lVal() {
  LValContext *_localctx = _tracker.createInstance<LValContext>(_ctx, getState());
  enterRule(_localctx, 30, HelloParser::RuleLVal);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(232);
    match(HelloParser::Ident);
    setState(239);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::LeftBracket) {
      setState(233);
      match(HelloParser::LeftBracket);
      setState(234);
      exp();
      setState(235);
      match(HelloParser::RightBracket);
      setState(241);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpContext ------------------------------------------------------------------

HelloParser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::AddExpContext* HelloParser::ExpContext::addExp() {
  return getRuleContext<HelloParser::AddExpContext>(0);
}


size_t HelloParser::ExpContext::getRuleIndex() const {
  return HelloParser::RuleExp;
}


std::any HelloParser::ExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::ExpContext* HelloParser::exp() {
  ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, getState());
  enterRule(_localctx, 32, HelloParser::RuleExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(242);
    addExp();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstExpContext ------------------------------------------------------------------

HelloParser::ConstExpContext::ConstExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::NumberContext* HelloParser::ConstExpContext::number() {
  return getRuleContext<HelloParser::NumberContext>(0);
}

tree::TerminalNode* HelloParser::ConstExpContext::LeftParen() {
  return getToken(HelloParser::LeftParen, 0);
}

HelloParser::ConstExpContext* HelloParser::ConstExpContext::constExp() {
  return getRuleContext<HelloParser::ConstExpContext>(0);
}

tree::TerminalNode* HelloParser::ConstExpContext::RightParen() {
  return getToken(HelloParser::RightParen, 0);
}


size_t HelloParser::ConstExpContext::getRuleIndex() const {
  return HelloParser::RuleConstExp;
}


std::any HelloParser::ConstExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitConstExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::ConstExpContext* HelloParser::constExp() {
  ConstExpContext *_localctx = _tracker.createInstance<ConstExpContext>(_ctx, getState());
  enterRule(_localctx, 34, HelloParser::RuleConstExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(249);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HelloParser::IntConst:
      case HelloParser::CharConst:
      case HelloParser::FloatConst: {
        enterOuterAlt(_localctx, 1);
        setState(244);
        number();
        break;
      }

      case HelloParser::LeftParen: {
        enterOuterAlt(_localctx, 2);
        setState(245);
        match(HelloParser::LeftParen);
        setState(246);
        constExp();
        setState(247);
        match(HelloParser::RightParen);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddExpConstContext ------------------------------------------------------------------

HelloParser::AddExpConstContext::AddExpConstContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::MulExpConstContext *> HelloParser::AddExpConstContext::mulExpConst() {
  return getRuleContexts<HelloParser::MulExpConstContext>();
}

HelloParser::MulExpConstContext* HelloParser::AddExpConstContext::mulExpConst(size_t i) {
  return getRuleContext<HelloParser::MulExpConstContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::AddExpConstContext::Plus() {
  return getTokens(HelloParser::Plus);
}

tree::TerminalNode* HelloParser::AddExpConstContext::Plus(size_t i) {
  return getToken(HelloParser::Plus, i);
}

std::vector<tree::TerminalNode *> HelloParser::AddExpConstContext::Minus() {
  return getTokens(HelloParser::Minus);
}

tree::TerminalNode* HelloParser::AddExpConstContext::Minus(size_t i) {
  return getToken(HelloParser::Minus, i);
}


size_t HelloParser::AddExpConstContext::getRuleIndex() const {
  return HelloParser::RuleAddExpConst;
}


std::any HelloParser::AddExpConstContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitAddExpConst(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::AddExpConstContext* HelloParser::addExpConst() {
  AddExpConstContext *_localctx = _tracker.createInstance<AddExpConstContext>(_ctx, getState());
  enterRule(_localctx, 36, HelloParser::RuleAddExpConst);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(251);
    mulExpConst();
    setState(256);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::Plus

    || _la == HelloParser::Minus) {
      setState(252);
      _la = _input->LA(1);
      if (!(_la == HelloParser::Plus

      || _la == HelloParser::Minus)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(253);
      mulExpConst();
      setState(258);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulExpConstContext ------------------------------------------------------------------

HelloParser::MulExpConstContext::MulExpConstContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::UnaryExpConstContext *> HelloParser::MulExpConstContext::unaryExpConst() {
  return getRuleContexts<HelloParser::UnaryExpConstContext>();
}

HelloParser::UnaryExpConstContext* HelloParser::MulExpConstContext::unaryExpConst(size_t i) {
  return getRuleContext<HelloParser::UnaryExpConstContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::MulExpConstContext::Star() {
  return getTokens(HelloParser::Star);
}

tree::TerminalNode* HelloParser::MulExpConstContext::Star(size_t i) {
  return getToken(HelloParser::Star, i);
}

std::vector<tree::TerminalNode *> HelloParser::MulExpConstContext::Div() {
  return getTokens(HelloParser::Div);
}

tree::TerminalNode* HelloParser::MulExpConstContext::Div(size_t i) {
  return getToken(HelloParser::Div, i);
}

std::vector<tree::TerminalNode *> HelloParser::MulExpConstContext::Mod() {
  return getTokens(HelloParser::Mod);
}

tree::TerminalNode* HelloParser::MulExpConstContext::Mod(size_t i) {
  return getToken(HelloParser::Mod, i);
}


size_t HelloParser::MulExpConstContext::getRuleIndex() const {
  return HelloParser::RuleMulExpConst;
}


std::any HelloParser::MulExpConstContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitMulExpConst(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::MulExpConstContext* HelloParser::mulExpConst() {
  MulExpConstContext *_localctx = _tracker.createInstance<MulExpConstContext>(_ctx, getState());
  enterRule(_localctx, 38, HelloParser::RuleMulExpConst);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(259);
    unaryExpConst();
    setState(264);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 30064771072) != 0)) {
      setState(260);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 30064771072) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(261);
      unaryExpConst();
      setState(266);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpConstContext ------------------------------------------------------------------

HelloParser::UnaryExpConstContext::UnaryExpConstContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::UnaryExpConstContext* HelloParser::UnaryExpConstContext::unaryExpConst() {
  return getRuleContext<HelloParser::UnaryExpConstContext>(0);
}

tree::TerminalNode* HelloParser::UnaryExpConstContext::Plus() {
  return getToken(HelloParser::Plus, 0);
}

tree::TerminalNode* HelloParser::UnaryExpConstContext::Minus() {
  return getToken(HelloParser::Minus, 0);
}

tree::TerminalNode* HelloParser::UnaryExpConstContext::Not() {
  return getToken(HelloParser::Not, 0);
}

HelloParser::PrimaryExpConstContext* HelloParser::UnaryExpConstContext::primaryExpConst() {
  return getRuleContext<HelloParser::PrimaryExpConstContext>(0);
}


size_t HelloParser::UnaryExpConstContext::getRuleIndex() const {
  return HelloParser::RuleUnaryExpConst;
}


std::any HelloParser::UnaryExpConstContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitUnaryExpConst(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::UnaryExpConstContext* HelloParser::unaryExpConst() {
  UnaryExpConstContext *_localctx = _tracker.createInstance<UnaryExpConstContext>(_ctx, getState());
  enterRule(_localctx, 40, HelloParser::RuleUnaryExpConst);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(270);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HelloParser::Plus:
      case HelloParser::Minus:
      case HelloParser::Not: {
        enterOuterAlt(_localctx, 1);
        setState(267);
        _la = _input->LA(1);
        if (!((((_la & ~ 0x3fULL) == 0) &&
          ((1ULL << _la) & 140660178944) != 0))) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(268);
        unaryExpConst();
        break;
      }

      case HelloParser::LeftParen:
      case HelloParser::IntConst:
      case HelloParser::CharConst:
      case HelloParser::FloatConst: {
        enterOuterAlt(_localctx, 2);
        setState(269);
        primaryExpConst();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpConstContext ------------------------------------------------------------------

HelloParser::PrimaryExpConstContext::PrimaryExpConstContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::PrimaryExpConstContext::LeftParen() {
  return getToken(HelloParser::LeftParen, 0);
}

HelloParser::ConstExpContext* HelloParser::PrimaryExpConstContext::constExp() {
  return getRuleContext<HelloParser::ConstExpContext>(0);
}

tree::TerminalNode* HelloParser::PrimaryExpConstContext::RightParen() {
  return getToken(HelloParser::RightParen, 0);
}

HelloParser::NumberContext* HelloParser::PrimaryExpConstContext::number() {
  return getRuleContext<HelloParser::NumberContext>(0);
}


size_t HelloParser::PrimaryExpConstContext::getRuleIndex() const {
  return HelloParser::RulePrimaryExpConst;
}


std::any HelloParser::PrimaryExpConstContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitPrimaryExpConst(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::PrimaryExpConstContext* HelloParser::primaryExpConst() {
  PrimaryExpConstContext *_localctx = _tracker.createInstance<PrimaryExpConstContext>(_ctx, getState());
  enterRule(_localctx, 42, HelloParser::RulePrimaryExpConst);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(277);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HelloParser::LeftParen: {
        enterOuterAlt(_localctx, 1);
        setState(272);
        match(HelloParser::LeftParen);
        setState(273);
        constExp();
        setState(274);
        match(HelloParser::RightParen);
        break;
      }

      case HelloParser::IntConst:
      case HelloParser::CharConst:
      case HelloParser::FloatConst: {
        enterOuterAlt(_localctx, 2);
        setState(276);
        number();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CondContext ------------------------------------------------------------------

HelloParser::CondContext::CondContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::LOrExpContext* HelloParser::CondContext::lOrExp() {
  return getRuleContext<HelloParser::LOrExpContext>(0);
}


size_t HelloParser::CondContext::getRuleIndex() const {
  return HelloParser::RuleCond;
}


std::any HelloParser::CondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitCond(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::CondContext* HelloParser::cond() {
  CondContext *_localctx = _tracker.createInstance<CondContext>(_ctx, getState());
  enterRule(_localctx, 44, HelloParser::RuleCond);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(279);
    lOrExp();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext ------------------------------------------------------------------

HelloParser::NumberContext::NumberContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::NumberContext::IntConst() {
  return getToken(HelloParser::IntConst, 0);
}

tree::TerminalNode* HelloParser::NumberContext::CharConst() {
  return getToken(HelloParser::CharConst, 0);
}

tree::TerminalNode* HelloParser::NumberContext::FloatConst() {
  return getToken(HelloParser::FloatConst, 0);
}


size_t HelloParser::NumberContext::getRuleIndex() const {
  return HelloParser::RuleNumber;
}


std::any HelloParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::NumberContext* HelloParser::number() {
  NumberContext *_localctx = _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 46, HelloParser::RuleNumber);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(281);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 246290604621824) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncRParamsContext ------------------------------------------------------------------

HelloParser::FuncRParamsContext::FuncRParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::ExpContext *> HelloParser::FuncRParamsContext::exp() {
  return getRuleContexts<HelloParser::ExpContext>();
}

HelloParser::ExpContext* HelloParser::FuncRParamsContext::exp(size_t i) {
  return getRuleContext<HelloParser::ExpContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::FuncRParamsContext::Comma() {
  return getTokens(HelloParser::Comma);
}

tree::TerminalNode* HelloParser::FuncRParamsContext::Comma(size_t i) {
  return getToken(HelloParser::Comma, i);
}


size_t HelloParser::FuncRParamsContext::getRuleIndex() const {
  return HelloParser::RuleFuncRParams;
}


std::any HelloParser::FuncRParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitFuncRParams(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::FuncRParamsContext* HelloParser::funcRParams() {
  FuncRParamsContext *_localctx = _tracker.createInstance<FuncRParamsContext>(_ctx, getState());
  enterRule(_localctx, 48, HelloParser::RuleFuncRParams);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(283);
    exp();
    setState(288);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::Comma) {
      setState(284);
      match(HelloParser::Comma);
      setState(285);
      exp();
      setState(290);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpContext ------------------------------------------------------------------

HelloParser::PrimaryExpContext::PrimaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HelloParser::PrimaryExpContext::LeftParen() {
  return getToken(HelloParser::LeftParen, 0);
}

HelloParser::ExpContext* HelloParser::PrimaryExpContext::exp() {
  return getRuleContext<HelloParser::ExpContext>(0);
}

tree::TerminalNode* HelloParser::PrimaryExpContext::RightParen() {
  return getToken(HelloParser::RightParen, 0);
}

HelloParser::LValContext* HelloParser::PrimaryExpContext::lVal() {
  return getRuleContext<HelloParser::LValContext>(0);
}

HelloParser::NumberContext* HelloParser::PrimaryExpContext::number() {
  return getRuleContext<HelloParser::NumberContext>(0);
}


size_t HelloParser::PrimaryExpContext::getRuleIndex() const {
  return HelloParser::RulePrimaryExp;
}


std::any HelloParser::PrimaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitPrimaryExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::PrimaryExpContext* HelloParser::primaryExp() {
  PrimaryExpContext *_localctx = _tracker.createInstance<PrimaryExpContext>(_ctx, getState());
  enterRule(_localctx, 50, HelloParser::RulePrimaryExp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(297);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HelloParser::LeftParen: {
        enterOuterAlt(_localctx, 1);
        setState(291);
        match(HelloParser::LeftParen);
        setState(292);
        exp();
        setState(293);
        match(HelloParser::RightParen);
        break;
      }

      case HelloParser::Ident: {
        enterOuterAlt(_localctx, 2);
        setState(295);
        lVal();
        break;
      }

      case HelloParser::IntConst:
      case HelloParser::CharConst:
      case HelloParser::FloatConst: {
        enterOuterAlt(_localctx, 3);
        setState(296);
        number();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpContext ------------------------------------------------------------------

HelloParser::UnaryExpContext::UnaryExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HelloParser::PrimaryExpContext* HelloParser::UnaryExpContext::primaryExp() {
  return getRuleContext<HelloParser::PrimaryExpContext>(0);
}

HelloParser::UnaryExpContext* HelloParser::UnaryExpContext::unaryExp() {
  return getRuleContext<HelloParser::UnaryExpContext>(0);
}

tree::TerminalNode* HelloParser::UnaryExpContext::Plus() {
  return getToken(HelloParser::Plus, 0);
}

tree::TerminalNode* HelloParser::UnaryExpContext::Minus() {
  return getToken(HelloParser::Minus, 0);
}

tree::TerminalNode* HelloParser::UnaryExpContext::Not() {
  return getToken(HelloParser::Not, 0);
}

tree::TerminalNode* HelloParser::UnaryExpContext::Ident() {
  return getToken(HelloParser::Ident, 0);
}

tree::TerminalNode* HelloParser::UnaryExpContext::LeftParen() {
  return getToken(HelloParser::LeftParen, 0);
}

tree::TerminalNode* HelloParser::UnaryExpContext::RightParen() {
  return getToken(HelloParser::RightParen, 0);
}

HelloParser::FuncRParamsContext* HelloParser::UnaryExpContext::funcRParams() {
  return getRuleContext<HelloParser::FuncRParamsContext>(0);
}


size_t HelloParser::UnaryExpContext::getRuleIndex() const {
  return HelloParser::RuleUnaryExp;
}


std::any HelloParser::UnaryExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitUnaryExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::UnaryExpContext* HelloParser::unaryExp() {
  UnaryExpContext *_localctx = _tracker.createInstance<UnaryExpContext>(_ctx, getState());
  enterRule(_localctx, 52, HelloParser::RuleUnaryExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(308);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 32, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(299);
      primaryExp();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(300);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 140660178944) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(301);
      unaryExp();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(302);
      match(HelloParser::Ident);
      setState(303);
      match(HelloParser::LeftParen);
      setState(305);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 264023451893760) != 0)) {
        setState(304);
        funcRParams();
      }
      setState(307);
      match(HelloParser::RightParen);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MulExpContext ------------------------------------------------------------------

HelloParser::MulExpContext::MulExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::UnaryExpContext *> HelloParser::MulExpContext::unaryExp() {
  return getRuleContexts<HelloParser::UnaryExpContext>();
}

HelloParser::UnaryExpContext* HelloParser::MulExpContext::unaryExp(size_t i) {
  return getRuleContext<HelloParser::UnaryExpContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::MulExpContext::Star() {
  return getTokens(HelloParser::Star);
}

tree::TerminalNode* HelloParser::MulExpContext::Star(size_t i) {
  return getToken(HelloParser::Star, i);
}

std::vector<tree::TerminalNode *> HelloParser::MulExpContext::Div() {
  return getTokens(HelloParser::Div);
}

tree::TerminalNode* HelloParser::MulExpContext::Div(size_t i) {
  return getToken(HelloParser::Div, i);
}

std::vector<tree::TerminalNode *> HelloParser::MulExpContext::Mod() {
  return getTokens(HelloParser::Mod);
}

tree::TerminalNode* HelloParser::MulExpContext::Mod(size_t i) {
  return getToken(HelloParser::Mod, i);
}


size_t HelloParser::MulExpContext::getRuleIndex() const {
  return HelloParser::RuleMulExp;
}


std::any HelloParser::MulExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitMulExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::MulExpContext* HelloParser::mulExp() {
  MulExpContext *_localctx = _tracker.createInstance<MulExpContext>(_ctx, getState());
  enterRule(_localctx, 54, HelloParser::RuleMulExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(310);
    unaryExp();
    setState(315);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 30064771072) != 0)) {
      setState(311);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 30064771072) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(312);
      unaryExp();
      setState(317);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AddExpContext ------------------------------------------------------------------

HelloParser::AddExpContext::AddExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::MulExpContext *> HelloParser::AddExpContext::mulExp() {
  return getRuleContexts<HelloParser::MulExpContext>();
}

HelloParser::MulExpContext* HelloParser::AddExpContext::mulExp(size_t i) {
  return getRuleContext<HelloParser::MulExpContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::AddExpContext::Plus() {
  return getTokens(HelloParser::Plus);
}

tree::TerminalNode* HelloParser::AddExpContext::Plus(size_t i) {
  return getToken(HelloParser::Plus, i);
}

std::vector<tree::TerminalNode *> HelloParser::AddExpContext::Minus() {
  return getTokens(HelloParser::Minus);
}

tree::TerminalNode* HelloParser::AddExpContext::Minus(size_t i) {
  return getToken(HelloParser::Minus, i);
}


size_t HelloParser::AddExpContext::getRuleIndex() const {
  return HelloParser::RuleAddExp;
}


std::any HelloParser::AddExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitAddExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::AddExpContext* HelloParser::addExp() {
  AddExpContext *_localctx = _tracker.createInstance<AddExpContext>(_ctx, getState());
  enterRule(_localctx, 56, HelloParser::RuleAddExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(318);
    mulExp();
    setState(323);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::Plus

    || _la == HelloParser::Minus) {
      setState(319);
      _la = _input->LA(1);
      if (!(_la == HelloParser::Plus

      || _la == HelloParser::Minus)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(320);
      mulExp();
      setState(325);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelExpContext ------------------------------------------------------------------

HelloParser::RelExpContext::RelExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::AddExpContext *> HelloParser::RelExpContext::addExp() {
  return getRuleContexts<HelloParser::AddExpContext>();
}

HelloParser::AddExpContext* HelloParser::RelExpContext::addExp(size_t i) {
  return getRuleContext<HelloParser::AddExpContext>(i);
}

tree::TerminalNode* HelloParser::RelExpContext::Less() {
  return getToken(HelloParser::Less, 0);
}

tree::TerminalNode* HelloParser::RelExpContext::Greater() {
  return getToken(HelloParser::Greater, 0);
}

tree::TerminalNode* HelloParser::RelExpContext::LessEqual() {
  return getToken(HelloParser::LessEqual, 0);
}

tree::TerminalNode* HelloParser::RelExpContext::GreaterEqual() {
  return getToken(HelloParser::GreaterEqual, 0);
}


size_t HelloParser::RelExpContext::getRuleIndex() const {
  return HelloParser::RuleRelExp;
}


std::any HelloParser::RelExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitRelExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::RelExpContext* HelloParser::relExp() {
  RelExpContext *_localctx = _tracker.createInstance<RelExpContext>(_ctx, getState());
  enterRule(_localctx, 58, HelloParser::RuleRelExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(326);
    addExp();
    setState(329);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1006632960) != 0)) {
      setState(327);
      _la = _input->LA(1);
      if (!((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & 1006632960) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(328);
      addExp();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EqExpContext ------------------------------------------------------------------

HelloParser::EqExpContext::EqExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::RelExpContext *> HelloParser::EqExpContext::relExp() {
  return getRuleContexts<HelloParser::RelExpContext>();
}

HelloParser::RelExpContext* HelloParser::EqExpContext::relExp(size_t i) {
  return getRuleContext<HelloParser::RelExpContext>(i);
}

tree::TerminalNode* HelloParser::EqExpContext::Equal() {
  return getToken(HelloParser::Equal, 0);
}

tree::TerminalNode* HelloParser::EqExpContext::NotEqual() {
  return getToken(HelloParser::NotEqual, 0);
}


size_t HelloParser::EqExpContext::getRuleIndex() const {
  return HelloParser::RuleEqExp;
}


std::any HelloParser::EqExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitEqExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::EqExpContext* HelloParser::eqExp() {
  EqExpContext *_localctx = _tracker.createInstance<EqExpContext>(_ctx, getState());
  enterRule(_localctx, 60, HelloParser::RuleEqExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(331);
    relExp();
    setState(334);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HelloParser::Equal

    || _la == HelloParser::NotEqual) {
      setState(332);
      _la = _input->LA(1);
      if (!(_la == HelloParser::Equal

      || _la == HelloParser::NotEqual)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(333);
      relExp();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LAndExpContext ------------------------------------------------------------------

HelloParser::LAndExpContext::LAndExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::EqExpContext *> HelloParser::LAndExpContext::eqExp() {
  return getRuleContexts<HelloParser::EqExpContext>();
}

HelloParser::EqExpContext* HelloParser::LAndExpContext::eqExp(size_t i) {
  return getRuleContext<HelloParser::EqExpContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::LAndExpContext::AndAnd() {
  return getTokens(HelloParser::AndAnd);
}

tree::TerminalNode* HelloParser::LAndExpContext::AndAnd(size_t i) {
  return getToken(HelloParser::AndAnd, i);
}


size_t HelloParser::LAndExpContext::getRuleIndex() const {
  return HelloParser::RuleLAndExp;
}


std::any HelloParser::LAndExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitLAndExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::LAndExpContext* HelloParser::lAndExp() {
  LAndExpContext *_localctx = _tracker.createInstance<LAndExpContext>(_ctx, getState());
  enterRule(_localctx, 62, HelloParser::RuleLAndExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(336);
    eqExp();
    setState(341);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::AndAnd) {
      setState(337);
      match(HelloParser::AndAnd);
      setState(338);
      eqExp();
      setState(343);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LOrExpContext ------------------------------------------------------------------

HelloParser::LOrExpContext::LOrExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HelloParser::LAndExpContext *> HelloParser::LOrExpContext::lAndExp() {
  return getRuleContexts<HelloParser::LAndExpContext>();
}

HelloParser::LAndExpContext* HelloParser::LOrExpContext::lAndExp(size_t i) {
  return getRuleContext<HelloParser::LAndExpContext>(i);
}

std::vector<tree::TerminalNode *> HelloParser::LOrExpContext::OrOr() {
  return getTokens(HelloParser::OrOr);
}

tree::TerminalNode* HelloParser::LOrExpContext::OrOr(size_t i) {
  return getToken(HelloParser::OrOr, i);
}


size_t HelloParser::LOrExpContext::getRuleIndex() const {
  return HelloParser::RuleLOrExp;
}


std::any HelloParser::LOrExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitLOrExp(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::LOrExpContext* HelloParser::lOrExp() {
  LOrExpContext *_localctx = _tracker.createInstance<LOrExpContext>(_ctx, getState());
  enterRule(_localctx, 64, HelloParser::RuleLOrExp);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(344);
    lAndExp();
    setState(349);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HelloParser::OrOr) {
      setState(345);
      match(HelloParser::OrOr);
      setState(346);
      lAndExp();
      setState(351);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CharacterContext ------------------------------------------------------------------

HelloParser::CharacterContext::CharacterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HelloParser::CharacterContext::getRuleIndex() const {
  return HelloParser::RuleCharacter;
}


std::any HelloParser::CharacterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HelloVisitor*>(visitor))
    return parserVisitor->visitCharacter(this);
  else
    return visitor->visitChildren(this);
}

HelloParser::CharacterContext* HelloParser::character() {
  CharacterContext *_localctx = _tracker.createInstance<CharacterContext>(_ctx, getState());
  enterRule(_localctx, 66, HelloParser::RuleCharacter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);

   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void HelloParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  helloParserInitialize();
#else
  ::antlr4::internal::call_once(helloParserOnceFlag, helloParserInitialize);
#endif
}
