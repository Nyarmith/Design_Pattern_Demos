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


// === DONT START HERE ===
// property proxy is a teplate class
template <typename T> struct Property
{
  T value;
  Property(T value)
  {
    *this = value;
  }

  operator T()
  {
    return value;
  }

  T operator=(T new_value)
  {
    cout << "Assignment!\n";
    return value = new_value;
  };
};

// === START HERE ===
struct Creature
{
  Property<int> strength{10};
  Property<int> agility{10};
};

// so here we could make getter and setters here, but 
// that would change how we want to call the object (i.e. as if it was a simple struct type)
// so we want to make a property proxy that we can customize to give enhancements on the original behavior
// (go up to Property class)

int main(){
  Creature c;
  c.strength = 15;
  int x = c.agility; //so here we enhanced the assignment operator with a proxy

  return 0;
}

//this is pretty useful in general for a getter-setter enhancement, and this example in particular is pretty good about showing some background construction details
