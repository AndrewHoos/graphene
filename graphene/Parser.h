//
//  Parser.h
//  bliss
//
//  Created by Mac on 5/11/13.
//  Copyright (c) 2013 Mac. All rights reserved.
//

#ifndef __bliss__Parser__
#define __bliss__Parser__

#include <iostream>
#include "SyntaxTree.h"
#include "Tokenizer.h"

using namespace std;
typedef unique_ptr<ExpressionTree> ExpressionTreePtr;

class Parser
{
  Token currentToken;
  Tokenizer tokens;
  ExpressionTreePtr parseFile();
  ExpressionTreePtr parseBlock();
  ExpressionTreePtr parseLine();
  ExpressionTreePtr parseExpression();
  ExpressionTreePtr parsePrimary();
  ExpressionTreePtr parseBinary(ExpressionTreePtr leftTree,int precidence);
  Token readToken();
  
public:
  Parser(){};
  Parser(Tokenizer tokens):tokens(tokens){};
  ExpressionTreePtr parse();
  friend ExpressionTreePtr operator>>(Tokenizer tokens, Parser &parser);
};

#endif /* defined(__bliss__Parser__) */
