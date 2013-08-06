//
//  Tokenizer.cpp
//  bliss
//
//  Created by Mac on 5/11/13.
//  Copyright (c) 2013 Mac. All rights reserved.
//

#include "Tokenizer.h"
#include <regex>

////////
//
// Tokenizer:
//
// This tokenizer will
//
/////

istream& operator>>(istream &in, Tokenizer &tokenizer)
{
  
  in >> noskipws;
  istream_iterator<char> it(in);
  istream_iterator<char> end;
  string word(it,end);
  string currentIndent = "";
  string indentSize = "";

  tokenizer.tokenizeAToken(word);
  while (word.length()>0)
  {
      tokenizer.tokens.push(tokenizer.currentToken);
      tokenizer.tokenizeAToken(word);
  }
  tokenizer.tokenizeIndentation("");
  tokenizer.tokens.push(tokenizer.currentToken);
  tokenizer.tokens.push(Token(tok_eof, ""));
  return in;
}


// This function will tokenize one indent
// 1. It will push the current token
// 2. It will set the current token to indent
void Tokenizer::tokenizeIndent(string const newIndent)
{
  smatch smatch;
  if(indentSize == "")
  {
    indentSize = newIndent;
  }
  
  if(newIndent == currentIndent + indentSize)
  {
    tokens.push(currentToken);
    currentToken = Token(tok_indent,indentSize);
    currentIndent = newIndent;
    return;
  }
  
  cerr << "unexpected indent" << endl;
  cerr << "'" << indentSize << "' expected" << endl;
  cerr << "'" << regex_replace(newIndent,regex(currentIndent), "'") << "' received" << endl;
}


//tokenizeDedent will tokenize <n> dedents
// It will push the current token
// It will push <n - 1> dedent tokens
// It will set the current token to dedent
void Tokenizer::tokenizeDedent(string const newIndent)
{
  //dedent the current indent once
  currentIndent = regex_replace(currentIndent,regex(indentSize),"");
  //push the parsed token
  tokens.push(currentToken);
  currentToken =  Token(tok_dedent, indentSize);
  //if you dededent than once
  while (currentIndent != newIndent)
  {
    tokens.push(currentToken);
    currentIndent = regex_replace(currentIndent,regex(indentSize),"");
  }
}

//This method will determine the type of indent
//This method will update the current indentation
// If the indent is unchanged it is a noop
// If the indent is changed it will call tokenizeIndent or tokenizeDedent
void Tokenizer::tokenizeIndentation(string const newIndent)
{
  smatch match;
  if(newIndent == currentIndent)
  {
    return;
  }
  else if(regex_search(newIndent,match,regex(currentIndent+"( |\t)+")))
  {
    tokenizeIndent(newIndent);
  }
  else
  {
    tokenizeDedent(newIndent);
  }
}


//This method will tokenize a single token from the word.
//This method will remove the content of the token from the word.
//It will set the currentToken, but it will not push it on the stack
void Tokenizer::tokenizeAToken(string & word)
{
  smatch match;
  
  regex identifier("^[[:alpha:]](_|[[:alnum:]])*");
  regex binop("^[-\\+\\*/=\\^\\.]");// - + * / = ^ .
  regex unop("^(\\+|-|\\+\\+|--|!)");// + - ++ -- !
  regex newline("^\\n");
  regex integer("^([1-9][0-9]*)|(0x[1-9a-f][0-9a-f]*)|(0[1-7][0-7]*)|(0)");
  regex floating("^(([1-9][0-9]*)|(0))\\.[0-9]+");
  regex whitespace("^( |\t)+?");
  
  if(regex_search(word, match, identifier))
  {
    if(keywords[match[0]])
    {
      currentToken = Token(keywords[match[0]], match[0]);
    }
    else
    {
      currentToken = Token(tok_identifier, match[0]);
    }
    word = regex_replace(word, identifier, "");
  }
  else if(regex_search(word, match, binop))
  {
    currentToken = Token(tok_binop,match[0]);
    word = regex_replace(word, binop, "");
  }
  else if(regex_search(word, match, unop))
  {
    currentToken = Token(tok_unop,match[0]);
    word = regex_replace(word, unop, "");
  }
  else if(regex_search(word, match, newline))
  {
    currentToken = Token(tok_newline,match[0]);
    word = regex_replace(word, newline, "");
    //special case to check for indent/dedent
    if(regex_search(word, match, whitespace))
    {
      tokenizeIndentation(match[0]);
      word = regex_replace(word, whitespace, "");
    }
  }
  else if(regex_search(word, match, integer))
  {
    currentToken = Token(tok_integer,match[0]);
    word = regex_replace(word, integer, "");
  }
  else if(regex_search(word, match, floating))
  {
    currentToken = Token(tok_float,match[0]);
    word = regex_replace(word, floating, "");
  }
  else
  {
    cerr<<"unrecognised token: " << word << endl;
  }
  
  //trim whitespace
  if(regex_search(word, match, whitespace))
  {
    //this is just removing whitespace as it occurs
    word = regex_replace(word, whitespace, "");
  }
}


Tokenizer::Tokenizer()
{
  keywords["break"] = tok_break;
  keywords["continue"] = tok_continue;
  keywords["pass"] = tok_pass;
  keywords["return"] = tok_return;
  keywords["yield"] = tok_yield;
  keywords["class"] = tok_class;
  keywords["space"] = tok_space;
  keywords["struct"] = tok_struct;
  keywords["interface"] = tok_interface;
  tokens = queue<Token>();
}

Token Tokenizer::getToken()
{
  Token temp = this->tokens.front();
  this->tokens.pop();
  return temp;
}