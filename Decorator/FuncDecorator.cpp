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
#include <functional>
#define ll long long
using namespace std;

//So far we were talking about a decorator over a class, but now we're talking about a decorator over a function

////here's an example for logging
//struct Logger
//{
//  function<void()> func;
//  string name;
//
//  Logger(const function<void()> &func, const string &name) : func(func), name(name) {}
//
//  void operator()() const
//  {
//    cout << "Entering" << name << endl;
//    func();
//    cout << "Exiting" << name << endl;
//  }
//};

template <typename Func>
struct Logger
{
  Func func;
  string name;

  Logger(const Func &func, const string &name) : func(func), name(name) {}

  void operator()() const
  {
    cout << "Entering" << name << endl;
    func();
    cout << "Exiting" << name << endl;
  }
};

//this lets you infer the type of Func from the argument
template <typename Func> auto make_logger(Func func, const string& name)
{
  return Logger<Func>{func, name};
}

double add(double a, double b)
{
  cout << a << "+" << b << "=" << (a+b) << endl;
  return a+b;
}


template <typename> struct Logger2;

template <typename R, typename... Args>
struct Logger2<R(Args...)>
{
  function <R(Args...)> func;
  string name;

  Logger2(const function<R(Args...)> &func, const string &name) : func(func), name(name) {}

  R operator() (Args ...args)
  {
    cout << "Entering " << name << endl;
    R result = func(args...);
    cout << "Exiting " << name << endl;
    return result;
  }
};

template <typename R, typename... Args>
auto make_logger2(R (*func)(Args...), const string& name)
{
  return Logger2<R(Args...)>(
      function<R(Args...)>(func),
      name
    );
}

int main(){
  //this won't work w/o make_logger2 because it doesn't know what type func is
  auto log = make_logger([](){ cout << "Hello" << endl;}, " HelloFunction");
  log();

  auto log_add = make_logger2(add,"Add");
  auto result = log_add(2,3);
  cout << result << endl;
}

//Main Takeaway: I need to revisit this and template metaprogramming can get wild
