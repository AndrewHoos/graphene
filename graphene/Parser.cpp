//
//  Parser.cpp
//  bliss
//
//  Created by Mac on 5/11/13.
//  Copyright (c) 2013 Mac. All rights reserved.
//

#include "Parser.h"
bool isPrimary(Token possible);
int tokenPrecedence(Token token);

ExpressionTreePtr operator>>(Tokenizer &tokens, Parser &parser)
{
  parser = Parser(tokens);
  return parser.Parse();
}

Token Parser::readToken()
{
  return this->currentToken = tokens.getToken();
}

ExpressionTreePtr Parser::Parse()
{
  this->readToken();
  
  
  while (currentToken.ID() != tok_eof)
  {
    ExpressionTreePtr tree = nullptr;
    while (currentToken.ID() !=tok_newline)
    {
      tree = move(this->parsePrimary());
      if(currentToken.ID() == tok_newline)
      {
        return tree;
      }
      else if (currentToken.ID() == tok_binop)
      {
        return parseBinary(move(tree), -1);
      }
      else
      {
        std::cerr << "unexpected token in Parse";
      }
      std::cout << tree->logTree();
    }
    return tree;
  }
  return ExpressionTreePtr (new ExpressionTree());
}

ExpressionTreePtr Parser::parseBinary(ExpressionTreePtr leftExpression,int precedence)
{
  //assume the next token should be an operator or newline
  if(currentToken.ID() != tok_binop)
  {
    std::cerr << "expected binop";
  }
  
  //save this op we need to compare
  Token lop = currentToken;
  
  Token rightToken = this->readToken();
  if(!rightToken.isPrimary())
  {
    //parse error
  }
  ExpressionTreePtr rightExpression = parsePrimary();
  
  //If there is no more opps then we have a newline and we return
  if(currentToken.ID() == tok_newline)
  {
    return ExpressionTreePtr (new BinaryOpTree(lop.content(), move(leftExpression), move(rightExpression)));
  }
  if(currentToken.precedence() > lop.precedence())
  {
    return ExpressionTreePtr (new BinaryOpTree(lop.content(), move(leftExpression), parseBinary(move(rightExpression), -1)));
  }
  else
  {
    return parseBinary(ExpressionTreePtr (new BinaryOpTree(lop.content(),move(leftExpression),move(rightExpression))), lop.precedence());
  }
}

ExpressionTreePtr Parser::parsePrimary()
{
  ExpressionTreePtr exp(new ExpressionTree());
  
  Token prefixToken;
  bool prefix = false;
  
  if(currentToken.ID() == tok_unop)
  {
    prefix = true;
    prefixToken = currentToken;
    this->readToken();
  }
  if (currentToken.ID() == tok_identifier)
  {
    exp = ExpressionTreePtr (new IdentifierTree(currentToken.content()));
  }
  else if (currentToken.ID() == tok_integer)
  {
    exp = ExpressionTreePtr (new IntegerTree(std::stoi(currentToken.content())));
  }
  else if (currentToken.ID() == tok_float)
  {
    exp = ExpressionTreePtr(new FloatTree(std::stof(currentToken.content())));
  }
  else
  {
    std::cerr << "unexpected tokens in parsePrimary" << std::endl;
  }
  if(prefix)
  {
    exp = ExpressionTreePtr(new UnaryOpTree(prefixToken.content(), true, move(exp)));
  }
  this->readToken();
  if(currentToken.ID() == tok_unop)
  {
    exp = ExpressionTreePtr(new UnaryOpTree(currentToken.content(), false, move(exp)));
  }
  return exp;
}