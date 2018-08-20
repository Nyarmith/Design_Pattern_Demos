#include <string>
#include <vector>
#include <locale>
#include <map>
#include <iostream>

using namespace std;

struct Token{
  enum Type { NUM, ADD, SUB, ID } type;
  string value;
  Token(Type type, string value) : type(type), value(value) {}
};

vector<Token> tokenize(const string& expr){
  vector<Token> ret;
  int i=0;
  while (i < expr.length()){
    switch(expr[i]){
      case '+':
        ret.push_back( Token{Token::ADD, "+"});
        ++i;
        break;
      case '-':
        ret.push_back( Token{Token::SUB, "-"});
        ++i;
        break;
      default: //really this splits into sub-cases
        if (isdigit(expr[i])){
          int j=1;
          while(i+j < expr.length() && isdigit(expr[i+j]))
            ++j;
          ret.push_back( Token{Token::NUM, expr.substr(i,j)} );
          i+=j;
        } else {
          ret.push_back( Token{Token::ID, string(1,expr[i])} );
          ++i;
        }
    }
  }
  return ret;
}

struct ExpressionProcessor
{
  map<char,int> variables;

  int performOp(Token::Type op, int cur, int arg){
    switch(op){
      case Token::ADD:
        cur += arg;
        break;
      case Token::SUB:
        cur -= arg;
        break;
    }
    return cur;
  }

  int calculate(const string& expression)
  {
    vector<Token> tokens = tokenize(expression);
    bool justSawVar = false;
    int curVal=0;
    Token::Type curOp = Token::ADD;
    for (Token& tkn : tokens) {
      if (tkn.type == Token::ID){
        if (justSawVar == true)
          return 0;
        justSawVar = true;
      } else
        justSawVar = false;
      switch(tkn.type){
        case(Token::ADD):
          curOp = Token::ADD;
          break;
        case(Token::SUB):
          curOp = Token::SUB;
          break;
        case(Token::NUM):
          curVal = performOp(curOp, curVal, stoi(tkn.value));
          break;
        case(Token::ID):
          int val = variables[tkn.value[0]];
          curVal = performOp(curOp, curVal, val);
          break;
      }
    }
    return curVal;
  }
};
int main(){
  ExpressionProcessor e;
  cout << e.calculate("1+2+3");
}
