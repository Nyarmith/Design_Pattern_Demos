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

//so first thing we want is a deep copy, but how do we want to do that? A specific interface or more ordinary c++?

struct Address
{
  string street, city;
  int suite;

  Address(const string &street, const string &city, int suite) :
    street(street), city(city), suite(suite) {}

  //v2
  //Give a copy-constructor here s.t. you get a nicer more recursive structure
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
//v1
//  //copy-constructor is lowest-investment method
//  Contact (const Contact& other) : name(other.name),
//        address(new Address{other.address->street, other.address->city, other.address->suite}){}
//  //this constructor w/ new in it is black-magic
//  //
//
  //v2
  Contact (const Contact& other) : name(other.name),
        address(new Address{*other.address}){}

  friend ostream& operator<<(ostream& os, const Contact& obj)
  {
    return os
      << "name: " << obj.name
      << " works at " << *obj.address << endl;
  }
};

int main(){
  Contact john{"John Doe", new Address{"123 East Dr", "New York", 404}};
  Contact janny = john; //shallow copy
  janny.name = "Janny Smith";
  janny.address->suite = 405;

  cout << john << janny << endl;

}

