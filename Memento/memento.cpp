#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <cstdio>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>
#include <utility>
#include <queue>
#include <memory>
using namespace std;

class Memento
{
  int balance;
public:
  Memento(int balance) : balance(balance) {}
};

class BankAccount
{
  int balance{0};
  BankAccount(int balance) : balance(balance) {}

  Memento deposit(int amount)
  {
    balance += amount;
    return {balance};
  }
};

int main(){
}

