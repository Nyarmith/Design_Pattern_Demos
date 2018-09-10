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
#include <boost/signals2/signal.hpp>
#define ll long long

using namespace boost::signals2;

//to make the observer more efficient, we would have some sort of structure that lets us traverse all of them more eficiently, so that spacial events can be mapped to spatial objects better

class Person
{
  int age;
public:
  int get_age() const
  {
    return age;
  }
  void set_age(int age)
  {
    if (this->age == age) return;
    Person::age = age;
  }
};


template <typename T> struct Observable2
{
  signal<void(T&, const std::string&)> field_changed;
};

class Person2 : public Observable2<Person2>
{
  int age;
public:
  int get_age() const
  {
    return age;
  }

  void set_age(int age)
  {
    if (this->age == age) return;
    this->age = age;
    field_changed(*this, "age");
  }
};



int main(int ag, char* av[]){
  Person2 p2;

  auto conn = p2.field_changed.connect(
    [](Person2& p, const std::string& field_name)
    {
      std::cout << field_name << " has changed\n";
    }
    );

  p2.set_age(20);
  conn.disconnect();
}
