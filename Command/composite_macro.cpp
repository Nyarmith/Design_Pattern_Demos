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
#define ll long long

using namespace std;

struct BankAccount
{
  int balance{0};
  int overdraft_limit{-500};

  void deposit(int amount)
  {
    balance += amount;
    cout << "deposited " << amount << ", balance is now " << balance << endl;
  }

  bool withdraw(int amount){
    if (balance - amount >= overdraft_limit)
    {
      balance -= amount;
      cout << "withdrew " << amount << ", balance is now " << balance << endl;
      return true;
    }
    return false;
  }
};

struct Command
{
  bool succeed;
  virtual void call() = 0;
  virtual void undo() = 0;
};

struct BankAccountCommand : Command
{
  BankAccount& account;
  enum Action {deposit, withdraw} action;
  int amount;
  BankAccountCommand(BankAccount &account, Action action, int amount) :
    account(account), action(action),
    amount(amount) { succeed = false; }

  void call() override {
    switch(action)
    {
      case deposit:
        account.deposit(amount);
        succeed = true;
        break;
      case withdraw:
        succeed = account.withdraw(amount);
        break;
    }
  }

  void undo() override {
    if (!succeed) return;
    switch(action)
    {
      //naive way
      case deposit:
        account.withdraw(amount);
        break;
      case withdraw:
        account.deposit(amount);
        break;
    }
  }
};

//we're turning a vector of commands into a thing that has the same interface (undo) of the individual command -%-% warning: composite design pattern approaches!
struct CompositeBankAccountCommand : vector<BankAccountCommand>, Command
{
  CompositeBankAccountCommand(const initializer_list<BankAccountCommand> &items) : vector(items) {}

  void call(){
    for (auto& cmd : *this)
      cmd.call();
  }

  void undo(){
    for (auto it = rbegin(); it != rend(); ++it)
      it->undo();
  }
};

struct MoneyTransferCommand : CompositeBankAccountCommand
{
  MoneyTransferCommand(
    BankAccount& from,
    BankAccount& to,
    int amount
  ) : CompositeBankAccountCommand(
    {
      BankAccountCommand{from, BankAccountCommand::withdraw, amount},
      BankAccountCommand{to, BankAccountCommand::deposit, amount},
    }) {}
};

int main(){
  BankAccount ba, ba2;
  ba.deposit(100);

  MoneyTransferCommand cmd{ba,ba2,50};
  cmd.call();

  cout << ba.balance << endl << ba2.balance << endl;

  cmd.undo();

  cout << ba.balance << endl << ba2.balance << endl;
}

