//
//  token.cpp
//  bliss
//
//  Created by Mac on 5/11/13.
//  Copyright (c) 2013 Mac. All rights reserved.
//

#include "Token.h"
#include <map>

std::ostream& operator<<(std::ostream& cout, const Token& t)
{
    return cout << t.tokenID << " " << t.tokenContent << std::endl;
}

int Token::precedence()
{
  if(ID() == tok_binop)
  {
    if (!content().compare("."))
    {
      return 40;
    }
    else if (!content().compare("*"))
    {
        return 10;
    }
    else if (!content().compare("/"))
    {
        return 10;
    }
    else if (!content().compare("+"))
    {
        return 5;
    }
    else if (!content().compare("-"))
    {
        return 5;
    }
  }
  return -1;
}

bool Token::isPrimary()
{
    token_id tok_id = ID();
    if (tok_id == tok_unop || tok_id == tok_identifier || tok_id == tok_integer || tok_id == tok_float)
    {
        return true;
    }
    return false;
}



