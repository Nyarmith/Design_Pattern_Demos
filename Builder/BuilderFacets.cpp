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
#include <sstream>
#include <fstream>
#include <memory>
#include <tuple>
#define ll long long
using namespace std;

// so now imagine an object so complicated that has to many components that we have multiple builders
// in a sense we are building a builder facade!


class PersonBuilder;
class PersonJobBuilder;
class PersonAddressBuilder;

class Person
{
  // addresss
  std::string street_address, post_code, city;

  // employment
  std::string company_name, position;
  int annual_income{0}; //what is this INSANE syntax?!

  public:
    static PersonBuilder create();

    friend class PersonBuilder;
    friend class PersonJobBuilder;
    friend class PersonAddressBuilder;
    friend std::ostream& operator<<(std::ostream& os, const Person& obj)
     {
       return os
         << "street_address: " << obj.street_address
         << " post_code: " << obj.post_code
         << " city: " << obj.city
         << " company_name: " << obj.company_name
         << " position: " << obj.position
         << " annual_income: " << obj.annual_income;
     }
};

//this is a dedicated builder, but since we want to use this as a base class
//for a PersonJobBuilder and PersonAddressBuilder, However, if you inherit from it,
//then you replicate the object being built up over and over and over again
//---
//A Solution: Use a base class that doesn't have the object but just a reference, and a derived class that does have the object
//this solution is exceptionally tricky


class BasePersonBuilder{
  protected:
    Person & person;

  public:
    operator Person() const {
      return std::move(person);
    }

    BasePersonBuilder(Person& person);
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;

};

class PersonBuilder : public BasePersonBuilder{
  public:
    PersonBuilder();

  private:
    Person p;
  public:
};

class PersonAddressBuilder : public BasePersonBuilder{
  typedef PersonAddressBuilder Self; //woah, typedefs can be class scoped?
  public:
    PersonAddressBuilder(Person &person) : BasePersonBuilder(person) {}

    Self& at(string street_address)
    {
      person.street_address = street_address;
      return *this;
    }

    Self& with_postcode(std::string post_code){
      person.post_code = post_code;
      return *this;
    }

    Self& in(std::string city){
      person.city = city;
      return *this;
    }
};

class PersonJobBuilder : public BasePersonBuilder{
  typedef PersonJobBuilder Self; //woah, typedefs can be class scoped?
  public:
    PersonJobBuilder(Person &person) : BasePersonBuilder(person) {}

    Self& at(string company_name)
    {
      person.company_name = company_name;
      return *this;
    }

    Self& as_a(std::string position){
      person.position = position;
      return *this;
    }

    Self& earning(int annual_income){
      person.annual_income = annual_income;
      return *this;
    }
};

PersonBuilder Person::create(){
  return PersonBuilder();
}

//declare these later so they can use the information about PerxonXBuilder constructors
BasePersonBuilder::BasePersonBuilder(Person& person) : person(person) {};

PersonAddressBuilder BasePersonBuilder::lives() const {
  return PersonAddressBuilder{person};
}

PersonJobBuilder BasePersonBuilder::works() const {
  return PersonJobBuilder{person};
}

//THIS is such a good trick
PersonBuilder::PersonBuilder() : BasePersonBuilder(p) {}


int main()
{
  Person p = Person::create()
    .lives().at("404 Void Road")
            .with_postcode("124816")
            .in("Seattle")
    .works().at("MemSoft")
            .as_a("Skript-Psycker")
    .earning(10e6);

  cout << p << endl;
}

//moral of story:
//When you have a complex object you can break it into several builders that work in tandem
