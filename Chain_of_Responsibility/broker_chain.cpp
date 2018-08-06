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
#include <boost/signals2.hpp>
#define ll long long

using namespace boost;
using namespace boost::signals2;
using namespace std;


//we're going to be building an event broker = chain-of-resp + observer (signals2) + command-query-separation(splitting the system into commands and queries)

struct Query
{
  string creature_name;
  //this is the command-query separation part
  enum Argument { attack, defense } argument; //defining enum and giving it a member var
  int result; //result of query is stored here

  Query(const string& creature_name, Argument argument, int result) :
    creature_name{creature_name},argument(argument), result(result) {}
};


struct Game //mediator: every creature has a reference to this
{
  signal<void(Query&)> queries;
};

//same scenario as before
struct Creature
{
  Game& game;
  int attack, defense;
public:
  Creature(Game &game, int attack, int defense, const string &name) :
    game(game), attack(attack), defense(defense), name(name) {}
  string name;

  //in order to actually get the attack-values with the modifiers applied, you have to have a getter which runs the query
  //note-to-self: could use Property<> proxy to do this for us
  int get_attack() const
  {
    //how signals work: we create a query and invoke
    Query q{name, Query::Argument::attack, attack}; //specify name, arg and initial-value
    game.queries(q); //invoking the query
    return q.result; //the query result
  }

  friend ostream& operator<<(ostream& os, const Creature &creature)
  {
    os << " attack: " << creature.get_attack()  << " name : " << creature.name;
    return os;
  }
};


//now a creature modifier: it references the mediator and subscribes to the queries because it wants to modify the creature


//modifier interface
class CreatureModifier
{
  Game& game;
  Creature& creature;
public:
  CreatureModifier(Game &game, Creature &creature) : game(game), creature(creature) {}
  virtual ~CreatureModifier() = default;
};

//double modifier attack
class DoubleAttackModifier : public CreatureModifier
{
  connection conn; //we can save the connection so we can disconnect
public:
  DoubleAttackModifier(Game &game, Creature &creature)
    : CreatureModifier(game, creature)
  {
    conn = game.queries.connect([&](Query& q)
      {
        //if this query is appropriate for the creature!
        if (q.creature_name == creature.name && 
            q.argument == Query::Argument::attack)
        {
          q.result *= 2; //ah, so we're modifying the query result itself, not the object directly!(I guess that's what the GoF chain did too)
        }
      });
  }

  ~DoubleAttackModifier(){ conn.disconnect(); }
};

//when you want to query something from the game, you give the game query a signal, and you invoke it, and every subscriber can do something with a signal

int main()
{
  Game game;
  Creature goblin{game,2,2,"Strong Goblin"};
  cout << goblin << endl;
  {
    DoubleAttackModifier dam{game,goblin};
    cout << goblin << endl;
    //the modifier should disappear once it destructs/disconnects/exits scope!
  }
  cout << goblin << endl;
  return 0;
}
//summary of arch:
// Creature --has reference of--> Game
// ^
// \- Query
// 
// When you want to query something from the game, you give the signal a query and invoke it, the query then goes through every subscriber(modifiers) and they can modify the query
// 
// to get Creature's attributes, you must query it. The Game will give us queries by having a singal<Query>
// x can subscribe to the query


//Takeaway: This is really cool but sort of tough. I might use something similar to this for a more complicated game engine, or a simplified version for the current one!
//also: boost/signal2 is useful af!

//Key elements of the pattern:
//-chain of responsibility objects aren't aggregated(like I thought they would be similar to decorator)
//-modifiers have a reference to the modificee
//-in this case, there is a mediator to simplify the chain's root, and a signal to help simplify the iteration of objects
