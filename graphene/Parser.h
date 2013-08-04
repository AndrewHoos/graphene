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

class Parser
{
    Token currentToken;
    Tokenizer tokens;
    unique_ptr<ExpressionTree> parsePrimary();
    unique_ptr<ExpressionTree> parseBinary(unique_ptr<ExpressionTree> leftTree,int precidence);
    Token readToken();
    
public:
    Parser(){};
    Parser(Tokenizer tokens):tokens(tokens){};
    unique_ptr<ExpressionTree>  Parse();
    friend unique_ptr<ExpressionTree> operator>>(Tokenizer tokens, Parser &parser);
};

#endif /* defined(__bliss__Parser__) */
