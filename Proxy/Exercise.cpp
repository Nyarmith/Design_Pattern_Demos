#include <string>

using namespace std;

class Person
{
  int age;
public:
  Person(int age) : age(age) {}

  int get_age() const { return age; }
  void set_age(int age) { this->age=age; }

  string drink() const { return "drinking"; }
  string drive() const { return "driving"; }
  string drink_and_drive() const { return "driving while drunk"; }
};

class ResponsiblePerson
{
  Person myPers;
public:
  ResponsiblePerson(const Person& p) : myPers(p) {}
  ResponsiblePerson(int age) : myPers(age) {}
  int get_age() const { return myPers.get_age(); }
  void set_age(int age) { myPers.set_age(age); }
  
  string drink() const { return myPers.get_age() < 18 ? "too young" : "drinking"; }
  string drive() const { return myPers.get_age() < 16 ? "too young" : "driving"; }
  string drink_and_drive() const { return "dead"; }
    
};

