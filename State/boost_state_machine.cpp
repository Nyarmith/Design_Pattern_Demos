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
#include <boost/msm/back/state_machine.hpp>
//front-end
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;

using namespace msm::front;
using namespace std;

//boost actually has 2 state-machines... (i.e. one other than the one we're using here)

vector<string> state_names{
  "off hook"s,
  "connecting"s,
  "connected"s,
  "on hold"s,
  "destroyed"s
};

struct CallDialed{};
struct HungUp{};
struct CallConnected{};
struct PlacedOnHold{};
struct TakenOffHold{};
struct LeftMessage{};
struct PhoneThrownIntoWall{};

//we have to inherit from bosot:msm::front::state_machine_def
//also, CRTP!!
struct PhoneStateMachine : state_machine_def<PhoneStateMachine>
{
  bool angry{true}; //field state-machine can use
  struct OffHook : state<> {};

  //customization for additional behavior
  struct Connecting : state<>
  {
    template <class Event, class FSM>
    void on_entry(const Event &evt, FSM &fsm)
    {
      std::cout << "We are connecting...\n";
    }
  };
  struct Connected : state<> {};
  struct OnHold : state<> {};
  struct PhoneDestroyed : state<> {};
  struct PhoneBeingDestroyed
  {
    template <class EVT, class FSM, class SourceState, class TargetState>
    void operator()(EVT const&, FSM&, SourceState&, TargetState&)
    {
      std::cout << "Phone breaks into a million pieces\n";
    }
  };
  
  struct CanDestroyPhone
  {
    template <class EVT, class FSM, class SourceState, class TargetState>
    bool operator()(EVT const&, FSM& fsm, SourceState&, TargetState&)
    {
      return fsm.angry;
    }
  };
  //the actual state machine (well the graph)
  struct transition_table : mpl::vector<
    Row<OffHook, CallDialed, Connecting>,
    Row<Connecting, CallConnected, Connected>,
    Row<Connected, PlacedOnHold, OnHold>,
    Row<OnHold, PhoneThrownIntoWall, PhoneDestroyed,
        PhoneBeingDestroyed, CanDestroyPhone>
  > {};
  //well at least the table is nice

  //this is how we set the starting state
  typedef OffHook initial_state;

  // what happens if there's nowhere to go
  template <class FSM, class Event>
  void no_transition(Event const& e, FSM&, int state)
  {
    cout << "No transition from state " << state_names[state]
      << " on event " << typeid(e).name() << endl;
  }
};


int main(){
  msm::back::state_machine<PhoneStateMachine> phone;

  auto info = [&]()
  {
    auto i = phone.current_state()[0];
    std::cout << "The phone is currently " << state_names[i] << "\n";
  };

  info();
  phone.process_event(CallDialed{});
  info();
  phone.process_event(CallConnected{});
  info();
  phone.process_event(PlacedOnHold{});
  info();
  phone.process_event(PhoneThrownIntoWall{});
  info();

  phone.process_event(CallDialed{});  //it will complain about no transitions, which is great!
}

//Takeaway: use boost state machines when you want to do something serious
// there is also way more customization than shown here

