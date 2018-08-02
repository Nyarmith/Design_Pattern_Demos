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
#include <memory>
#define ll long long

using namespace std;

//non-canonical implementation; also a manifestation of the bridge design pattern
//this idiom is all about hiding the details of a class by hiding its implementation details

class Person {
  public:
    string name;

    class PersonImpl;
    PersonImpl* impl;

    Person();
    ~Person();

    void greet();
};
//the idea of the pimpl idiom, is that the implementation, which could be inlined here, are actually put in a separate class

//Person.cpp

class Person::PersonImpl
{
  public:
    //this implementatino must be done in the cpp file for the idiom to be true
    void greet(Person* p){
      cout << "hello watashi wa " << p->name << endl;
    };
};

Person::Person() : impl(new PersonImpl){

}
Person::~Person() {
  delete impl;
}

void Person::greet(){
  //when we want to use greet, we relat the request to the implementation
  impl->greet(this);
}

int main(){
}

//so we would do this in order to hide the implementation details; i.e. the person consuming our library headers isn't being exposed to any of the private methods or implementation details. If there was a private section a lot of secret functions would clog up the user and worse would give you the opportunity to them to see all your secret files that might have trade secrets or you may not want them to see for whatever otehr reason
//
//Main benefit: you don't have to ship any of the private or implementation stuff since it's in the cpp file!!
//furthermore, the internal implementation can be really nice as it is separated from the interface!
//side-bonus: compilation speed is faster because you can change the internal implementatinons without changing the surface api, so you don't add binary incompatability!
