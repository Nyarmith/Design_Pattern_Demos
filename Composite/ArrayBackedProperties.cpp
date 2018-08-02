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
#include <array>
#include <memory>
#define ll long long
using namespace std;

//Intersection of composite and proxy design patterns
//
//deals with how fields are exposed from objects

//class Creature
//{
//  int strength, agility, intelligence;
//public:
//  void set_intelligence(int intl)
//  {
//    intelligence = intl;
//  }
//  void set_strength(int str)
//  {
//    strength = str;
//  }
//  void set_agility(int agi)
//  {
//    agility = agi;
//  }
//  int get_intelligence() const
//  {
//    return intelligence;
//  }
//  int get_strength() const
//  {
//    return strength;
//  }
//  int get_agility() const
//  {
//    return agility;
//  }
//
//  int max(){
//    return std::max({strength, agility, intelligence});
//  }
//  
//  int average(){
//    return (strength + agility + intelligence);
//  }
//};

class Creature
{
  enum Abilities {str, agl, intl, count}; //last thing is terminating element as well as count of abilities
  //now lets use the count to make an array
  array<int, count> abilities;
public:
  //IDEs don't know about this array-based approach so no auto-get/set
  int get_strength() const { return abilities[str]; }
  void set_strength(int value) { abilities[str] = value; }
  int get_agility() const { return abilities[agl]; }
  void set_agility(int value) { abilities[agl] = value; }
  int get_intelligence() const { return abilities[intl]; }
  void set_intelligence(int value) { abilities[intl] = value; }

  int sum() const{
    return accumulate(abilities.begin(), abilities.end(), 0);
  }
  int average() const{
    return sum()/(double)count;
  }
  int max() const{
    return *max_element(abilities.begin(), abilities.end());
  }
};

int main(){
  Creature orc;
  orc.set_strength(16);
  orc.set_agility(11);
  orc.set_intelligence(9);

  cout << "The orc has an average stat value of " << orc.average() << endl;
}


//main takeaway: this is a really convenient, modular, and efficient way to implement extensible uniform attributes for things like stats screens or other enumerations of simple states
