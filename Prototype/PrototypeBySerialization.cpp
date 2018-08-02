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
#include <sstream>


#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#define ll long long
using namespace std;
using namespace boost;

//big limitation of prototyping so far: having to implement the object copying yourself
//i.e. for every single part of the object graph you have to have either a copy-constructor or assignment or explicit clone function to create something new
// "there is no magic bullet"

// since there's no reflection, no iterating over object attributed!

// Prototype-Serialization Idea; instead of writing code for replication (via constructors), you should write code for serialization and deserialization: this is essentially more general than the above
// so we would only write this code once instead of multiple ways of cloning the object


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

  //now we have to have an address seralizer
  friend class serialization::access;
  template <class archive>
    void serialize(archive& ar, const unsigned version)
    {
      ar & street;
      ar & city;
      ar & suite;
    }
  Address(){}
};

struct Contact
{
  string name;
  Address* address;
  Contact(){} //apparently you need a default constructor for the serialization method
  Contact(const string &name, Address *address) : name(name), address(address) {}
  Contact (const Contact& other) : name(other.name),
        address(new Address{*other.address}){}

  ~Contact() { delete address; }

  friend ostream& operator<<(ostream& os, const Contact& obj)
  {
    return os
      << "name: " << obj.name
      << " works at " << *obj.address << endl;
  }
  private:
    friend class serialization::access;
;
    template<class archive>
      void serialize(archive &ar, const unsigned version)
      {
        ar & name;
        ar & address; //woah, boost knows to follow the pointer!!
      }
};

Contact mainOffice{"",new Address{"123 East Dr", "New York", 666}};
struct EmployeeFactory 
{
  public:
    //you apparently do need a default constructor for seralization
    static unique_ptr<Contact> new_main_office_employee
      (const string& name, const int suite)
    {
      static Contact p{"", new Address{"123 East Dr", "New York", 0}}; 
      return new_employee(name,suite,p); 
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
  //prototype cloning method!
  auto clone = [](const Contact &c) {
    ostringstream oss;
    archive::text_oarchive oa(oss);
    oa << c;
    string s = oss.str(); //RAW string representation
    cout << s << endl;

    istringstream iss(s);
    archive::text_iarchive ia(iss);
    Contact result;
    ia >> result;
    return result;
  };

  auto john = EmployeeFactory::new_main_office_employee("Jim", 333);
  auto janny = clone(*john);
}
//main lesson here is that you can use serialization as your core mechanism for cloning objects
//this approach forces you to ensure that every part of the object graph has a serialize representation
