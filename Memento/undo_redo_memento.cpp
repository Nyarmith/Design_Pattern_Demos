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

//implementing a more realistic undo/redo feature

class Memento
{
  int balance;
public:
  Memento(int balance) : balance(balance) {}
  friend class BankAccount;
  friend class BankAccount2;
};

class BankAccount
{
  int balance{0};
public:
  BankAccount(int balance) : balance(balance) {}

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

class BankAccount2
{
  int balance{0};
  vector<shared_ptr<Memento>> changes; //store every Memento ever made
  int current; // index to current Memento
public:
  BankAccount2(int balance) : balance(balance)
  {
    changes.emplace_back(make_shared<Memento>(balance));
    current = 0;
  }

  shared_ptr<Memento> deposit(int amount)
  {
    balance += amount;
    auto m = make_shared<Memento>(balance);
    changes.push_back(m);
    ++current;
    return m;
  }

  void restore(const shared_ptr<Memento>& m)
  {
    if (m)
    {
      balance = m->balance;
      changes.push_back(m);
      current = changes.size()-1;
    }

  }

  shared_ptr<Memento> undo()
  {
    if (current > 0)
    {
      --current;
      auto m = changes[current];
      balance = m->balance;
      return m;
    }
    return {};
  }

  shared_ptr<Memento> redo()
  {
    if (current < changes.size()-1){
      ++current;
      auto m = changes[current];
      balance = m->balance;
      return m;
    }
    return {};
  }
  friend ostream &operator<<(ostream& os, const BankAccount2 &account) {
    os << "balance: " << account.balance;
    return os;
  }
};

int main(){
  BankAccount2 ba{100};
  ba.deposit(50);
  ba.deposit(25);

  ba.undo();
  cout << "Undo 1: " << ba << endl;
  ba.undo();
  cout << "Undo 2: " << ba << endl;
  ba.redo();
  cout << "Redo 1: " << ba << endl;
  
  return 0;
}
