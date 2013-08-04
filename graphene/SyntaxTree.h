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
  virtual string logTree(){return "";};
};

class IntegerTree : public ExpressionTree
{
  int val;
public:
  IntegerTree(int const val)
  :val(val){};
  string logTree(){
    return this->logTree("");
  };
  string logTree(string prefix){
    return prefix + "IntTree: " + to_string(val) + "\n";
  };
};

class FloatTree : public ExpressionTree
{
  float val;
public:
  FloatTree(float const val)
  :val(val){};
  string logTree(){
    return this->logTree("");
  };
  string logTree(string prefix){
    return prefix + "FloatTree: " + to_string(val) + "\n";
  };
};

class IdentifierTree : public ExpressionTree
{
  string identifier;
public:
  IdentifierTree(string const identifier)
  :identifier(identifier){};
  string logTree(){
    return this->logTree("");
  };
  string logTree(string prefix){
    return prefix + "IdentifierTree: " + identifier + "\n";
  };
};

class BinaryOpTree : public ExpressionTree
{
  string binOp;
  unique_ptr<ExpressionTree> leftTree;
  unique_ptr<ExpressionTree> rightTree;
public:
  BinaryOpTree(string const op, unique_ptr<ExpressionTree> left, unique_ptr<ExpressionTree> right)
  : binOp(op),leftTree(move(left)),rightTree(move(right)){};
  string logTree()
  {
    return this->logTree("");
  };
  string logTree(string prefix){
    string rVal = prefix + "BinopTree: " + binOp + "\n";
    rVal += prefix + "  " + leftTree->logTree() + "\n";
    rVal += prefix + "  " + rightTree->logTree() + "\n";
    return rVal;
  };

};

class UnaryOpTree: public ExpressionTree
{
  string unOp;
  bool prefix;
  unique_ptr<ExpressionTree> expression;
public:
  UnaryOpTree(string const unOp, bool prefix, unique_ptr<ExpressionTree> expression)
  : unOp(unOp),prefix(prefix),expression(move(expression)){};
  string logTree()
  {
    return this->logTree("");
  };
  string logTree(string prefix){
    string rVal = prefix + "UnopTree: " + unOp + "\n";
    rVal += prefix + "  " + expression->logTree() + "\n";
    return rVal;
  };
};


#endif /* defined(__bliss__SyntaxTree__) */
