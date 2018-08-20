#include <string>
#include <vector>

struct Participant;

struct Mediator{
  std::vector<Participant*> participants;
  void broadcast(Participant* origin, int value);
};

struct Participant
{
    int value{0};
    Mediator& mediator;

    Participant(Mediator &mediator) : mediator(mediator)
    {
      mediator.participants.push_back(this);
    }

    void say(int value)
    {
      mediator.broadcast(this, value);
    }
};

void Mediator::broadcast(Participant* origin, int value){
  for (auto p : participants)
    p->value += p != origin ? value : 0;
}
