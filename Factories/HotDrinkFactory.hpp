#pragma once
#include "HotDrink.hpp"

//the abstract factory : aka the interface you expect a factory to follow
struct HotDrinkFactory
{
  virtual unique_ptr<HotDrink> make() const = 0;
};

struct TeaFactory : HotDrinkFactory
{
  unique_ptr<HotDrink> make() const override {
    return make_unique<Tea>();
  }
};

struct CoffeeFactory : HotDrinkFactory
{
  unique_ptr<HotDrink> make() const override {
    return make_unique<Coffee>();
  }
};

//usually the above would be more different, of course...
