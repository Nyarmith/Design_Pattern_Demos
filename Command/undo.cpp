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

  //we're putting all the undo logic in this method, which handles all types of commands
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

int main(){
  BankAccount ba;
  vector<BankAccountCommand> commands
    {
      BankAccountCommand{ba, BankAccountCommand::deposit,  100},
      BankAccountCommand{ba, BankAccountCommand::withdraw, 200},
    };

  cout << ba.balance << endl;

  for (auto& cmd : commands)
    cmd.call();

  for (auto it = commands.rbegin(); it != commands.rend(); ++it)
  {
    it->undo(); //really, it's more like that particular command is getting removed (doable b/c it's symmetric)
  }

  cout << ba.balance << endl;
}

