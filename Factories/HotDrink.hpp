#pragma once
#include <memory>
#include <iostream>
using namespace std;

//HotDrink Interface
struct HotDrink
{
  virtual ~HotDrink() = default;
  virtual void prepare(int volume) = 0;
};

//now we'll have a family of different products
struct Tea : HotDrink
{
  void prepare(int volume) override {
    cout << "Take tea bag, boil water, pour " << volume << "ml, add some lemon\n";
  }
};

struct Coffee : HotDrink
{
  void prepare(int volume) override {
    cout << "Grind some beans, boil water, pour " << volume << "ml, no cream, enjoy!\n";
  }
};

//so we have a family of objects, now we could have a family of factories
