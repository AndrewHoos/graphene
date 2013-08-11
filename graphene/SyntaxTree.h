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
#include <vector>

class ExpressionTree;

using namespace std;
typedef unique_ptr<ExpressionTree> ExpressionTreePtr;

class ExpressionTree
{
public:
  ExpressionTree(){};
  virtual string logTree(){return this->logTree("");};
  virtual string logTree(string prefix){return prefix;};
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
  ExpressionTreePtr leftTree;
  ExpressionTreePtr rightTree;
public:
  BinaryOpTree(string const op, ExpressionTreePtr left, ExpressionTreePtr right)
  : binOp(op),leftTree(move(left)),rightTree(move(right)){};
  string logTree()
  {
    return this->logTree("");
  };
  string logTree(string prefix){
    string rVal = prefix + "BinopTree: " + binOp + "\n";
    rVal += prefix + leftTree->logTree(prefix + "  ");
    rVal += prefix + rightTree->logTree(prefix + "  ");
    return rVal;
  };

};

class UnaryOpTree: public ExpressionTree
{
  string unOp;
  bool prefix;
  ExpressionTreePtr expression;
public:
  UnaryOpTree(string const unOp, bool prefix, ExpressionTreePtr expression)
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

class BlockTree: public ExpressionTree
{
  vector<ExpressionTreePtr> statements;
public:
  void push(ExpressionTreePtr exp){statements.push_back(move(exp));};
  string logTree()
  {
    return this->logTree("");
  };
  string logTree(string prefix){
    string rString = prefix + "Block Tree:\n";
    for(ExpressionTreePtr &expression : statements)
    {
      rString += expression->logTree(prefix + "  ");
    }
    return rString;
  };
};


class FileTree: public ExpressionTree
{
  vector<ExpressionTreePtr> statements;
  public:
  void push(ExpressionTreePtr exp){statements.push_back(move(exp));};
  string logTree()
  {
    return this->logTree("");
  };
  string logTree(string prefix){
    string rString = prefix + "File Tree:\n";
    for(ExpressionTreePtr &expression : statements)
    {
      rString += expression->logTree(prefix + "  ");
    }
    return rString;
  };
};


#endif /* defined(__bliss__SyntaxTree__) */
