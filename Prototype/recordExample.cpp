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
using namespace std;

/*
 
// v1

struct Address
{
  string street, city;
  int suite;

  Address(const string &street, const string &city, int suite) :
    street(street), city(city), suite(suite) {}
  
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
  Address address;
  Contact(const string &name, const Address &address) : name(name), address(address) {}


  friend ostream& operator<<(ostream& os, const Contact& obj)
  {
    return os
      << "name: " << obj.name
      << " works at " << obj.address; // note the star here
  }
};

int main(){
  Contact john{"John Doe", Address{"123 East Dr", "New York", 404}};
  //imagine we have a lot of other contacts in the same building, is it worth replicating all this over and over again?
  Contact jane{"Jane Doe", Address{"123 East Dr", "New York", 404}};
  Contact jimmy{"Jimmy Doe", Address{"123 East Dr", "New York", 404}};

  //this is less work, and it's the idea that the prototype pattern stems from
  Contact janny = john;
  janny.name = "Janny Smith";
  janny.address.suite = 405;

  cout << john << jane << janny << endl;

}

*/



// v2
//
// what happens when we introduce some non-value storage? e.g. pointers or references?

struct Address
{
  string street, city;
  int suite;

  Address(const string &street, const string &city, int suite) :
    street(street), city(city), suite(suite) {}
  
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


  friend ostream& operator<<(ostream& os, const Contact& obj)
  {
    return os
      << "name: " << obj.name
      << " works at " << *obj.address; // note the star here
  }
};

int main(){
  Contact john{"John Doe", new Address{"123 East Dr", "New York", 404}};
  Contact janny = john; //now this thing will point to john's address PTR unless we make a better copy contructor
  janny.name = "Janny Smith";
  janny.address->suite = 405;

  cout << john << janny << endl;

}

//so copy constructor and assignment constructors can be problematic
//and we should immediately consider the prototype pattern when copying and modifying objects containing pointers & refs
