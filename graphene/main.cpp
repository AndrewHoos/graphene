//
//  main.cpp
//  bliss
//
//  Created by Mac on 5/11/13.
//  Copyright (c) 2013 Mac. All rights reserved.
//

#include <iostream>

#include "Tokenizer.h"
#include "Parser.h"
#include "SyntaxTree.h"
int main(int argc, const char * argv[])
{
  Token t = Token(tok_identifier, "Test");
  Tokenizer tokenizer = Tokenizer();
  while(std::cin >> tokenizer);
  Parser parse = Parser(tokenizer);
  unique_ptr<ExpressionTree> tree = parse.parse();
  
  std::cout << tree->logTree();

  std::cout << "done";
  return 0;
}