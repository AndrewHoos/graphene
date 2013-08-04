//
//  SyntaxTree.h
//  bliss
//
//  Created by Mac on 5/11/13.
//  Copyright (c) 2013 Mac. All rights reserved.
//

#ifndef __bliss__SyntaxTree__
#define __bliss__SyntaxTree__

#include <iostream>


using namespace std;

class ExpressionTree
{
public:
  ExpressionTree(){};
  std::string logTree(){return "";};
};

class IntegerTree : public ExpressionTree
{
  int val;
public:
  IntegerTree(int const val)
  :val(val){};
  std::string logTree(){
    return "IntTree: " + std::to_string(val);
  };
};

class FloatTree : public ExpressionTree
{
  float val;
public:
  FloatTree(float const val)
  :val(val){};
  std::string logTree(){
    return "FloatTree: " + std::to_string(val);
  };
};

class IdentifierTree : public ExpressionTree
{
  std::string identifier;
public:
  IdentifierTree(std::string const identifier)
  :identifier(identifier){};
  std::string logTree(){
    return "IdentifierTree: " + identifier;
  };
};

class BinaryOpTree : public ExpressionTree
{
  std::string binOp;
  unique_ptr<ExpressionTree>  leftTree;
  unique_ptr<ExpressionTree> rightTree;
public:
  BinaryOpTree(std::string const op, unique_ptr<ExpressionTree> left, unique_ptr<ExpressionTree> right)
  : binOp(op),leftTree(move(left)),rightTree(move(right)){};
  std::string logTree()
  {
    std::string rVal = "BinopTree: " + binOp + "\n";
    rVal += "  " + leftTree->logTree() + "\n";
    rVal += "  " + rightTree->logTree() + "\n";
    return rVal;
  };
};

class UnaryOpTree: public ExpressionTree
{
  std::string unOp;
  bool prefix;
  unique_ptr<ExpressionTree> expression;
public:
  UnaryOpTree(std::string const unOp, bool prefix, unique_ptr<ExpressionTree> expression)
  : unOp(unOp),prefix(prefix),expression(move(expression)){};
  std::string logTree()
  {
    std::string rVal = "UnopTree: " + unOp + "\n";
    rVal += "  " + expression->logTree() + "\n";
    return rVal;
  };
};


#endif /* defined(__bliss__SyntaxTree__) */
