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
#include <boost/di.hpp>
#include <boost/lexical_cast.hpp>
#define ll long long
using namespace std;
using namespace boost;

//relying on inversion of control in a typical dependency injection to basically create a singleton for you
//in the IContainer is you allow yourself to create something with a specific lifetime

struct IFoo
{
  virtual string name() = 0;
};

struct Foo : IFoo
{
  static int id;
  Foo() { ++id; }
  string name() override {
    return "foo"s + lexical_cast<string>(id);
  };
};

int Foo::id = 0;


struct Bar
{
  std::shared_ptr<IFoo> foo;
};

int main(){
  //whenever anyone asks for an IFoo, we are going to map it to Foo, BUT we want a singleton
  auto injector = di::make_injector(
      di::bind<IFoo>.to<Foo>().in(di::singleton)
  );
  auto bar1 = injector.create<std::shared_ptr<Bar>>();
  auto bar2 = injector.create<std::shared_ptr<Bar>>();

  cout << bar1->foo->name() << endl;
  cout << bar2->foo->name() << endl;

  cout << boolalpha
       << (bar1->foo.get() == bar2->foo.get())
       << endl;
}

// Main takeaway: you can create singletons for free with dependency injection!
