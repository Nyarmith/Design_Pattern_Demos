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

//observer and observable
template <typename T>
class Observer
{
  virtual void field_changed(
    T& source,
    const std::string field_name
  )=0;
};

struct ConsolePersonObserver
  : public Observer<Person>
{
private:
  void field_changed(Person &source, const std::string &field_name) override
  {
    std::cout << "Person's" << field_name << " has changed to ";
    if (field_name == "age") std::cout << source.get_age();
    std::cout << "\n";
  }
};


template <typename> struct Observer;

template <typename T>
struct Observable
{
  std::vector<Observer<T>*> observers;
public:
  void notify(T& source, const std::string& field_name)
  {
    for (auto observer : observers)
      observer->field_changed(source, field_name);
  }

  void subscribe(Observer<T>& observer)
  {
    observers.push_back(&observer);
  }

  void unsubscribe(Observer<T>& observer)
  {
    observers.erase(
      std::remove(observers.begin(),observers.end(), observer)
    );
  }
};

int main(){
}
