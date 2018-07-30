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
#include <cmath>
#include <functional>
#include "HotDrinkFactory.hpp"
#define ll long long
using namespace std;

//this is way better IMO

class DrinkFactory
{
    map<string,unique_ptr<HotDrinkFactory>> hot_factories;
  public:
    DrinkFactory()
    {
      hot_factories["coffee"] = make_unique<CoffeeFactory>();
      hot_factories["tea"]    = make_unique<TeaFactory>();
    };

    unique_ptr<HotDrink> make_drink(const string& name){
      auto drink = hot_factories[name]->make();
      drink->prepare(200);
      return drink;
    }
};

class DrinkWithVolumeFactory
{
  map<string,function<unique_ptr<HotDrink>()>> factories;
  public:
  DrinkWithVolumeFactory(){
    factories["tea"] = []{
      auto tea = make_unique<Tea>();
      tea->prepare(200);
      return tea;
    };
  }

  unique_ptr<HotDrink> make_drink(const string& name)
  {
    return factories[name]();
  }
};


int main(){
  DrinkFactory df;
  auto d = df.make_drink("tea");
  return 0;
}
