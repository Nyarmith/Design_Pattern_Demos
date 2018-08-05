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
#define ll long long

using namespace std;
//apparently the smart-pointer class is itself a proxy class
struct BankAccount
{
  virtual ~BankAccount() = default;
  virtual void deposit(int amount) = 0;
  virtual void withdraw(int amount) = 0;
};

struct CurrentAccount : BankAccount // checking
{
  explicit CurrentAccount(const int balance)
    : balance(balance)
  {
  }

  void deposit(int amount) override
  {
    balance += amount;
  }

  void withdraw(int amount) override
  {
    if (amount <= balance) balance -= amount;
  }

  friend ostream& operator<<(ostream& os, const CurrentAccount& obj)
  {
    return os << "balance: " << obj.balance;
  }

private:
  int balance;
};


int main()
{
  //working with raw pointers
  BankAccount * a = new CurrentAccount(123);
  a->deposit(321);
  delete a;

  auto b = make_shared<CurrentAccount>(123); //this is a proxy to an ordinary pointer
  BankAccount* actual = b.get(); // enhancement

  //if (b) //same interface as pointer!
  //so a proxy is an object that looks and behaves as if it's the original object, but it adds some additional benefit (e.g. here you don't have to delete, or you don't have to worry about something being in a thread). These additional services are the point of making a proxy.

  return 0;
}
