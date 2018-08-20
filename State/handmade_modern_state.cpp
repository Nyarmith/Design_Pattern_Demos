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
#define ll long long

//Scenario: Modeling a phone-call
//
//Model states as enum members

enum class State
{
  off_hook,
  connecting,
  connected,
  on_hold,
  on_hook
};

inline std::ostream& operator<<(std::ostream& os, const State& s) //ah, I see, we use the class enum for nice ostream formatting!
{
  switch (s)
  {
  case State::off_hook:
    os << "off the hook";
    break;
  case State::connecting:
    os << "connecting";
    break;
  case State::connected: 
    os << "connected";
    break;
  case State::on_hold:
    os << "on hold";
    break;
  case State::on_hook:
    os << "on the hook";
    break;
  }
  return os;
}

//triggers are events that cause a transition from one event to another
enum class Trigger{
  call_dialed,
  hung_up,
  call_connected,
  placed_on_hold,
  taken_off_hold,
  left_message,
  stop_using_phone
};

inline std::ostream& operator<<(std::ostream& os, const Trigger& t)
{
  switch (t)
  {
  case Trigger::call_dialed:
    os << "call dialed";
    break;
  case Trigger::hung_up:
    os << "hung up";
    break;
  case Trigger::call_connected:
    os << "call connected";
    break;
  case Trigger::placed_on_hold:
    os << "placed on hold";
    break;
  case Trigger::taken_off_hold:
    os << "taken off hold";
    break;
  case Trigger::left_message: 
    os << "left message";
    break;
  case Trigger::stop_using_phone:
    os << "putting phone on hook";
    break;
  default: break;
  }
  return os;
}

int main(){
  //our state-machine is basically treated as a map/graph now
  std::map<State,
    std::vector< std::pair <Trigger,State> > > rules;

  rules[State::off_hook] = {
    {Trigger::call_dialed, State::connecting},
    {Trigger::stop_using_phone, State::on_hook}
  };

  rules[State::connecting] = {
    {Trigger::hung_up, State::off_hook},
    {Trigger::call_connected, State::connected}
  };

  rules[State::connected] = {
    {Trigger::left_message, State::off_hook},
    {Trigger::hung_up, State::off_hook},
    {Trigger::placed_on_hold, State::on_hold}
  };

  rules[State::on_hold] = {
    {Trigger::taken_off_hold, State::connected},
    {Trigger::hung_up, State::off_hook}
  };

  State currentState{ State::off_hook },
        exitState{ State::on_hook };

  while(true)
  {
    std::cout << "The phone is currently " << currentState << "\n";
select_trigger :
    std::cout << "Select a trigger:\n";
    int i=0;
    for (auto item : rules[currentState])
    {
      std::cout << i++ << ". " << item.first << "\n";
    }
    int input;
    std::cin >> input;
    if (input < 0 || input >= rules[currentState].size())
    {
      std::cout << "Incorrect option. Please try again\n";
      goto select_trigger;
    }

    currentState = rules[currentState][input].second;
    if (currentState == exitState) break;
  }

  std::cout << "We are done using the phone\n";
}

