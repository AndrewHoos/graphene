//
//  Tokenizer.cpp
//  bliss
//
//  Created by Mac on 5/11/13.
//  Copyright (c) 2013 Mac. All rights reserved.
//

#include "Tokenizer.h"
#include <regex>

std::istream& operator>>(std::istream &in, Tokenizer &tokenizer)
{
    
    in >> std::noskipws;
    std::istream_iterator<char> it(in);
    std::istream_iterator<char> end;
    std::string word(it,end);
    
    std::regex identifier("^[:alpha:][_[:alnum:]]*");
    std::regex binop("^[-\\+\\*/=\\^\\.]");// - + * / = ^ .
    std::regex unop("^(\\+|-|\\+\\+|--|!)");// + - ++ -- !
    std::regex newline("^\\n");
    std::regex integer("^([1-9][0-9]*)|(0x[1-9a-f][0-9a-f]*)|(0[1-7][0-7]*)|(0)");
    std::regex floating("^(([1-9][0-9]*)|(0))\\.[0-9]+");
    std::regex whitespace("^[ \t]+");
    
    std::smatch match;
    
    while (word.length()>0)
    {
        Token currentToken;
        if(std::regex_search(word, match, identifier))
        {
            if(tokenizer.keywords[match[0]])
            {
                currentToken = Token(tokenizer.keywords[match[0]], match[0]);
            }
            else
            {
                currentToken = Token(tok_identifier, match[0]);
            }
            word = std::regex_replace(word, identifier, "");
        }
        else if(std::regex_search(word, match, binop))
        {
            currentToken = Token(tok_binop,match[0]);
            word = std::regex_replace(word, binop, "");
        }
        else if(std::regex_search(word, match, unop))
        {
            currentToken = Token(tok_unop,match[0]);
            word = std::regex_replace(word, unop, "");
        }
        else if(std::regex_search(word, match, newline))
        {
            currentToken = Token(tok_newline,match[0]);
            word = std::regex_replace(word, newline, "");
        }
        else if(std::regex_search(word, match, integer))
        {
            currentToken = Token(tok_integer,match[0]);
            word = std::regex_replace(word, integer, "");
        }
        else if(std::regex_search(word, match, floating))
        {
            currentToken = Token(tok_float,match[0]);
            word = std::regex_replace(word, floating, "");
        }
        else
        {
            std::cerr<<"unrecognised token: " << word << std::endl;
        }
        tokenizer.tokens.push(currentToken);
        if(std::regex_search(word, match, whitespace))
        {
            //this is just removing whitespace as it occurs
            word = std::regex_replace(word, whitespace, "");
        }
    }
    return in;
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
    tokens = std::queue<Token>();
}

Token Tokenizer::getToken()
{
    Token temp = this->tokens.front();
    this->tokens.pop();
    return temp;
}