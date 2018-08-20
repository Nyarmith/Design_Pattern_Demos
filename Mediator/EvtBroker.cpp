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
#include <boost/signals2.hpp>
#define ll long long

using namespace std;
using namespace boost::signals2;

//in this version, we're mostly intersted in handling events in a centralized manner. We're combining observer and mediator

struct EventData
{
  virtual void print() const = 0;
};

struct PlayerScoredData : EventData
{
  string player_name;
  int goals_scored_so_far;
  PlayerScoredData(const string &player_name, int goals_scored_so_far) : player_name(player_name), goals_scored_so_far(goals_scored_so_far) {}

  void print() const override
  {
    cout << player_name << " has scored! (their "
         << goals_scored_so_far << " goal)\n";
  }
};

struct Game
{
  signal<void(EventData*)> events;
};

struct Player
{
  string name;
  int goals_scored{0};
  Game& game;
  Player(const string &name, Game &game) : name(name), game(game) {}

  void score()
  {
    goals_scored++;
    PlayerScoredData ps{name, goals_scored};
    game.events(&ps);
  }
};

struct Coach
{
  Game& game;

  Coach(Game &game) : game(game) {
    game.events.connect([](EventData* e)
        {
          PlayerScoredData* ps = dynamic_cast<PlayerScoredData*>(e);
          if (ps && ps->goals_scored_so_far < 3)
          {
          cout << "coach says: well_done, " << ps->player_name << "!\n";
          }
        });
  }
};

//woah, everyone is subscribing to some stream of events and multiple entities can listen to it. Wild.

int main(){
  Game game;
  Player player{"sam", game};
  Coach coach{game};
  player.score();
  player.score();
  player.score();
}
