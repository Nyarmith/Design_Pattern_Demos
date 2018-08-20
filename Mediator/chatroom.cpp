#include "chatroom.hpp"

//a chatroom is apparently the canonical mediator example
//this demonstration necessitates a header!

//people generally keep a reference to the mediator, which is either a global static variable or somethign that gets passed in on construction


Person::Person(const string &name) :
  name(name) {}

void Person::say(const string &message) const
{
  room->broadcast(name, message);
}

void Person::pm(const string& who, const string &message) const
{
  room->message(name,who,message);
}

void Person::receive(const string& origin, const string& message)
{
  string s{origin + ":" + message};
  cout << s << " : " << name << endl;
  chat_log.emplace_back(s);
}

bool Person::operator==(const Person &rhs) const{
  return name == rhs.name;
}
bool Person::operator!=(const Person &rhs) const{
  return name != rhs.name;
}

void ChatRoom::broadcast(const string& origin, const string& message){
  for (auto p : people)
    if (p->name != origin)
      p->receive(origin, message);
}

void ChatRoom::join(Person* p){
  string join_msg = p->name + " joins the room";
  broadcast("room", join_msg);
  p->room = this;
  people.push_back(p);
}

int main(){
  ChatRoom room;

  Person john{"john"};
  Person jane{"jane"};

  room.join(&john);
  room.join(&jane);

  john.say("Hi room");
  jane.say("oh, hi john");

  Person simon{"simon"};
  room.join(&simon);

  jane.pm("simon", "glad you found us, simon!");
}
