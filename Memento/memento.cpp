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

//implementing bank-account with memento pattern

class Memento
{
  int balance;
public:
  Memento(int balance) : balance(balance) {}
  friend class BankAccount;
  //could make memento an inner class of BankAccount instead, like builder/factory pattern examples
};

struct BankAccount
{
  int balance{0};
  BankAccount(int balance) : balance(balance) {}

  //deposit now returns a memento
  Memento deposit(int amount)
  {
    balance += amount;
    return {balance};
  }

  void restore(const Memento& m)
  {
    balance = m.balance;
  }

  friend ostream &operator<<(ostream& os, const BankAccount &account) {
    os << "balance: " << account.balance;
    return os;
  }
};

int main(){
  BankAccount ba{100};
  auto m1 = ba.deposit(50);
  auto m2 = ba.deposit(25);

  cout << ba << "\n";

  ba.restore(m1);
  cout << "back to m1: " << ba << "\n";

  ba.restore(m2);
  cout << "back to m2: " << ba << "\n";

  return 0;
}

//FYI: typically a memento is an immutable object

