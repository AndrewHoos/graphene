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
  return parser.parse();
}

Token Parser::readToken()
{
  return this->currentToken = tokens.getToken();
}

ExpressionTreePtr Parser::parse()
{
  return parseFile();
}

//this method called on current token == null
//this method returns on current token == EOF
ExpressionTreePtr Parser::parseFile()
{
  unique_ptr<FileTree> file(new FileTree);
  
  readToken();
  while (currentToken.ID() != tok_eof)
  {
    file->push(parseLine());
    readToken();
  }
  return move(file);
}


//this method called on current token == indent
//this method returns on current token == dedent
ExpressionTreePtr Parser::parseBlock()
{
  if(currentToken.ID() != tok_indent)
  {
    cerr << "parseBlock: expected an indent token" << endl;
    cerr << "ID: " << currentToken.ID() << " Content: " << currentToken.content() << endl;
  }
  unique_ptr<BlockTree> block(new BlockTree);
  
  readToken();
  while (currentToken.ID() != tok_dedent)
  {
    block->push(parseLine());
    readToken();
  }
  return move(block);
}

//this method is called after consuming a newline token
//this method returns after encountering a newline token
ExpressionTreePtr Parser::parseLine()
{
  //skip all the empty newline
  while(currentToken.ID() == tok_newline)
  {
    readToken();
  }
  
  ExpressionTreePtr line = nullptr;
  
  if(currentToken.isPrimary())
  {
    line = parsePrimary();
    if (currentToken.ID() == tok_binop)
    {
      line = parseBinary(move(line), -1);
    }
    else if (currentToken.ID() != tok_newline)
    {
      cerr << "parseLine: expected an newline or binop token" << endl;
      cerr << "ID: " << currentToken.ID() << " Content: " << currentToken.content() << endl;
      exit(1);
    }
  }
  else if(currentToken.ID() == tok_indent)
  {
    line = parseBlock();
  }
  else if(currentToken.ID() == tok_if)
  {
      //TODO parse
  }
  else if(currentToken.ID() == tok_class)
  {
    
  }
  return line;
}

//this method called on binop
//this method returns on newline
ExpressionTreePtr Parser::parseBinary(ExpressionTreePtr leftExpression,int precedence)
{
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
  //if the next token is not a binop
  if(currentToken.ID() != tok_binop)
  {
    cerr << "parseLine: expected an newline or binop token" << endl;
    cerr << "ID: " << currentToken.ID() << " Content: " << currentToken.content() << endl;
    exit(1);
  }
  else if(currentToken.precedence() > lop.precedence())
  {
    return ExpressionTreePtr (new BinaryOpTree(lop.content(), move(leftExpression), parseBinary(move(rightExpression), -1)));
  }
  else
  {
    return parseBinary(ExpressionTreePtr (new BinaryOpTree(lop.content(),move(leftExpression),move(rightExpression))), lop.precedence());
  }
}

//This method called on isPrimary
//This method returns on end after unop? primary unop?
ExpressionTreePtr Parser::parsePrimary()
{
  ExpressionTreePtr exp(new ExpressionTree());
  
  Token prefixToken;
  bool prefix = false;
  
  //store prefix
  if(currentToken.ID() == tok_unop)
  {
    prefix = true;
    prefixToken = currentToken;
    readToken();
  }
  
  //handle literal/identifier
  if (currentToken.ID() == tok_identifier)
  {
    exp = ExpressionTreePtr (new IdentifierTree(currentToken.content()));
    readToken();
  }
  else if (currentToken.ID() == tok_integer)
  {
    exp = ExpressionTreePtr (new IntegerTree(std::stoi(currentToken.content())));
    readToken();
  }
  else if (currentToken.ID() == tok_float)
  {
    exp = ExpressionTreePtr(new FloatTree(std::stof(currentToken.content())));
    readToken();
  }
  else
  {
    std::cerr << "unexpected tokens in parsePrimary" << std::endl;
  }
  
  //handle prefix
  if(prefix)
  {
    exp = ExpressionTreePtr(new UnaryOpTree(prefixToken.content(), true, move(exp)));
  }
  
  //handle postfix
  if(currentToken.ID() == tok_unop)
  {
    exp = ExpressionTreePtr(new UnaryOpTree(currentToken.content(), false, move(exp)));
    readToken();
  }
  
  return exp;
}