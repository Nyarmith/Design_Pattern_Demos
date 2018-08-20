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
using namespace std;

#define ll long long

#pragma once

struct ChatRoom;

struct Person {
  string name;
  ChatRoom* room{nullptr};
  vector<string> chat_log;

  Person(const string &name);

  void say(const string& message) const;
  void pm(const string& who, const string& message) const;
  void receive(const string& origin, const string& message);
  bool operator==(const Person &rhs) const;
  bool operator!=(const Person &rhs) const;
};

struct ChatRoom
{
  vector<Person*> people;
  void broadcast(const string& origin, const string& message);
  void join(Person* p);

  void message(const string& origin,
      const string& who,
      const string& message)
  {
    auto target = find_if(
        begin(people),
        end(people),
        [&](const Person *p) {
          return p->name == who;
        });
    if (target != end(people))
    {
      (*target)->receive(origin, message);
    }
  }
};
