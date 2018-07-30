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
#include "HotDrinkFactory.hpp"
#define ll long long
using namespace std;

//so, we've basically only done the factory method
// * The Abstract Factory - Helps create families of factories and use inheritance to actually allow to polymorphically call on different factories
// 
// sample: convoluted hot-drink machine


////now we're going to make a method that utilizes these abstract factory interface and makes the correct drink!!
//unique_ptr<HotDrink> make_drink(string type)
//{
//  unique_ptr<HotDrink> drink;
//  //typically, if you weren't using an AbstractFacotry, you'd do an if (type == "tea") type thing and make it manually
//  //but since we're using an abstract factory...
//  
//}

//so we're going to make a class that constucts drinks on the basis of the different factories
class DrinkFactory
{
    map<string,unique_ptr<HotDrinkFactory>> hot_factories;
  public:
    DrinkFactory()
    {
      //we do this manually in c++ ugh!
      hot_factories["coffee"] = make_unique<CoffeeFactory>();
      hot_factories["tea"]    = make_unique<TeaFactory>();
    };

    //interface to make drink
    unique_ptr<HotDrink> make_drink(const string& name){
      auto drink = hot_factories[name]->make();
      drink->prepare(200);
      return drink;
    }
    //so intead of doing an if-statement, we use a map that references the correct Factory
};


int main(){
  DrinkFactory df;
  auto d = df.make_drink("coffee");
  return 0;
}
