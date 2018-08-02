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
#include <sstream>
#include <fstream>
using namespace std;
#define ll long long

//Monostate design pattern is a popular variation of singleton

class Printer
{
  static int id;
  public:
    int get_id() const { return id; }
    void set_id(int value) { id=value; }
};

int main()
{
  //for the consumer, they are working with an ordinary type
  Printer p;
  int my_id = p.get_id(); //behind the scenes, this is static, so it doesn't matter if you make a new printer

  Printer p2;
  //this is bad because it isn't inheritable. so it's inflexible. Worst of all, the client doesn't know it's a de-facto singleton

}

//tl;dr this is a bad solution so don't do it. this entire video was a warning
