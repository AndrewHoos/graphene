//
//  token.h
//  bliss
//
//  Created by Mac on 5/11/13.
//  Copyright (c) 2013 Mac. All rights reserved.
//

#ifndef __bliss__token__
#define __bliss__token__

#include <iostream>

typedef enum
{
    tok_eof = -1,
    tok_identifier = -2,
    tok_integer = -3,
    tok_break = -4,
    tok_continue = -5,
    tok_return = -6,
    tok_yield = -7,
    tok_class = -8,
    tok_space = -9,
    tok_struct = -10,
    tok_interface = -11,
    tok_pass = -12,
    tok_float = -13,
    tok_binop = -14,
    tok_unop = -15,
    tok_unsused = -16,
    tok_newline = -17
} token_id;



class Token
{
    token_id tokenID;
    std::string tokenContent;
public:
    //constructors
    Token(token_id const tokID, std::string const &content)
    : tokenID(tokID), tokenContent(content){}
    Token(){};
    
    //operators
    friend std::ostream& operator<<(std::ostream& cout, const Token& t);
    
    //methods
    int precedence();
    bool isPrimary();
    
    //accesors
    token_id ID(){return tokenID;};
    std::string content(){return tokenContent;};
};




#endif /* defined(__bliss__token__) */
