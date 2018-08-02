#include <iostream>
#include <vector>
#include <string>
#include <memory>
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
using namespace std;

struct Address
{
  string street, city;
  int suite;

  Address(const string &street, const string &city, int suite) :
    street(street), city(city), suite(suite) {}

  Address(const Address& o) :
    street(o.street), city(o.city), suite(o.suite) { }
  
  friend ostream& operator<<(ostream& os, const Address& obj)
  {
    return os
      << "street: " << obj.street
      << " city: " << obj.city
      << " suite: " << obj.suite;

  }
};

struct Contact
{
  string name;
  Address* address;
  Contact(const string &name, Address *address) : name(name), address(address) {}
  Contact (const Contact& other) : name(other.name),
        address(new Address{*other.address}){}

  friend ostream& operator<<(ostream& os, const Contact& obj)
  {
    return os
      << "name: " << obj.name
      << " works at " << *obj.address << endl;
  }
};

Contact mainOffice{"",new Address{"123 East Dr", "New York", 666}};

//for prototype factory, heavily consider making constructors private
struct EmployeeFactory 
{
  public:
    static unique_ptr<Contact> new_main_office_employee
      (const string& name, const int suite)
    {
      static Contact p{"", new Address{"123 East Dr", "New York", 0}}; //prototype
      return new_employee(name,suite,p); //use prototype to make a thing
    }
  private:
    static unique_ptr<Contact> new_employee(const string& name, int suite, const Contact& prototype)
    {
      auto result = make_unique<Contact>(prototype);
      result->name = name;
      result->address->suite = suite;
      return result;
    };
};

int main(){
  Contact john{"John Doe", new Address{"123 East Dr", "New York", 404}};
  Contact janny = john;
  janny.name = "Janny Smith";
  janny.address->suite = 405;

  cout << john << janny << endl;
}

//TL;DR this is a way of keeping the prototypes in a safe-place and to use them along with constructors and factory methods to create new complex objects with a simple interface
