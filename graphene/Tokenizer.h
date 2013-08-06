//
//  Tokenizer.h
//  bliss
//
//  Created by Mac on 5/11/13.
//  Copyright (c) 2013 Mac. All rights reserved.
//

#ifndef __bliss__Tokenizer__
#define __bliss__Tokenizer__

#include <iostream>
#include "Token.h"
#include <queue>
#include <map>
#include <string>

using namespace std;

class Tokenizer
{
  queue<Token> tokens;
  map<string,token_id> keywords;
  void tokenizeIndent(string const newIndent);
  void tokenizeDedent(string const newIndent);
  void tokenizeIndentation(string const newIndent);
  void tokenizeAToken(string & word);
  
  Token currentToken;
  
  string currentIndent;
  string indentSize;

public:
  friend istream& operator>>(istream &in, Tokenizer &tokenizer);
  Tokenizer();
  Token getToken();
};


#endif /* defined(__bliss__Tokenizer__) */
