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

// so this is totally different than how we make state-machiens nowadays, but we shouldn't ever do this in real code

class LightSwitch;

//so right off the bat, we could just do the below with an enum...

struct State
{
  virtual void on(LightSwitch* lhs)
  {
    std::cout << "Light is already on\n";
  }

  virtual void off(LightSwitch* lhs)
  {
    std::cout << "Light is already off\n";
  }
};

//so, you only want o override the function the opposite fo what you're in, to offer an interface to switch to the ohter state
struct OnState : State
{
  OnState()
  {
    std::cout << "The light is on\n";
  }

  void off(LightSwitch* lhs) override;
};

struct OffState : State
{
  OffState()
  {
    std::cout << "The light is off\n";
  }
  void on(LightSwitch* lhs) override;
};


//state controller
class LightSwitch
{
  State *state;
public:
  LightSwitch()
  {
    state = new OffState();
  }

  void set_state(State* state)
  {
    this->state = state;
  }

  void on() {
    state->on(this);
  }
  void off() {
    state->off(this);
  }
};

void OnState::off(LightSwitch* lhs) {
  std::cout << "Switching light off...\n";
  lhs->set_state(new OffState());
  delete this; //red flag!
}
void OffState::on(LightSwitch* lhs) {
  std::cout << "Switching light on...\n";
  lhs->set_state(new OnState());
  delete this;
}
int main(){
  LightSwitch ls;
  ls.on();
  ls.off();
  ls.off();
}

