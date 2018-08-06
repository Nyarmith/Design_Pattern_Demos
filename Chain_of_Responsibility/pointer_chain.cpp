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


//gang-of-four style example (i.e. not particularly modern)

//scenario: you have a game creature with some attributes
struct Creature
{
  string name;
  int attack, defense;

  Creature (const string &name, int attack, int defense) : name(name), attack(attack), defense(defense) {}
  friend ostream &operator<<(ostream &os, const Creature &creature)
  {
    os << "name: " << creature.name << " attack: " << creature.attack << " defense: " << creature.defense;
    return os;
  }
};

//say we have situations where our creature gets modified by enchantments, equipment, etc...
//this is the classic implementation of that

//this class takes the creature and modifies some of its parameters, of course we can have many modifiers
//this is basically a singly-linked list
class CreatureModifier
{
  CreatureModifier* next{nullptr};
protected:
  Creature& creature;
public:
  CreatureModifier(Creature &creature) : creature(creature) {}

  void add(CreatureModifier *cm)
  {
    if (next) next->add(cm);
    else next = cm;
  };

  virtual void handle()
  {
    //we need this default behavior, so we need to invoke the base handle every time!!
    if (next) next->handle();
  }
};

class DoubleAttackModifier : public CreatureModifier
{
public:
  explicit DoubleAttackModifier(Creature& creature)
    : CreatureModifier(creature) {}
  void handle() override {
    creature.attack *= 2;
    CreatureModifier::handle(); //yeesh, we're forced to call this MANUALLY!!!!
  }
};


class IncreaseDefenseModifier : public CreatureModifier
{
public:
  explicit IncreaseDefenseModifier(Creature& creature)
    : CreatureModifier(creature) {}
  void handle() override {
    if (creature.attack <= 2)
      ++creature.defense;
    CreatureModifier::handle();
  }
};

class NoBonusesModifier: public CreatureModifier
{
public:
  explicit NoBonusesModifier(Creature& creature)
    : CreatureModifier(creature) {}
  void handle() override {
    //delet
  }
};

int main(){
  Creature goblin{"Goblin",1,1};
  CreatureModifier root{goblin};
  DoubleAttackModifier r1{goblin};
  DoubleAttackModifier r2{goblin};
  IncreaseDefenseModifier r3{goblin};

  NoBonusesModifier curse{goblin};

  //root.add(&curse); prevents the going-down of the chain

  cout << "Before: " << goblin << endl;
  root.add(&r1);
  root.add(&r2); //a=4
  root.add(&r3); //no-op

  root.handle(); //having to do this sucks
  cout << "After: " << goblin << endl;
}

//tl;dr this is a good design pattern but wow this is too much scaffolding
//we're basically building a linked-list, so why not just build a linked-list of modifiers?
//not really how it's done anymore
