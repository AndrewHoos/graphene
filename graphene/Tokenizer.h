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

class Tokenizer
{
    std::queue<Token> tokens;
    std::map<std::string,token_id> keywords;
public:
    friend std::istream& operator>>(std::istream &in, Tokenizer &tokenizer);
    Tokenizer();
    Token getToken();
};


#endif /* defined(__bliss__Tokenizer__) */
