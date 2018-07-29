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
using std::string;
using std::vector;
using std::endl;
using std::cout;

//Builder Design Pattern
// - Some objects are simple and can be created in a single constructor call
// - Other objects require a lot of ceremony to create
// The builder design pattern is for ceremonial objects
// 
// Why?
// - Having an object with 10 constructor arguments is not an efficient abstraction
// \-> Instead, opt for piece-wise construction. Create a neat api for constructing an object step-by-step

// Relevance to my application: Think of using the builder design pattern when putting together the entities, backgrounds and all components involved in creating a runnable game
// 
// Rephrasing: create an object-oriented structure that represents the construction and supports the transformation to the final product

//so, e.g. instead of concatenating strings to make html, let's do some builder

//just a utility class for modeling an html class
struct HtmlElement
{
  string name, text;
  vector<HtmlElement> elements;

  const size_t indent_size = 2;

  HtmlElement(){};
  HtmlElement(const string &name, const string &text) : name(name), text(text){ };

  // turn into an str representation with recursive indentation
  string str(int indent = 0) const {
    std::ostringstream oss;
    string i(indent_size*indent, ' ');
    oss << i << "<" << name << ">" << endl;
    if (text.size() > 0)
      oss << string(indent_size*(indent + 1), ' ') << text << endl;

    for (const auto& e : elements)
      oss << e.str(indent + 1); //woah!

    oss << i << "</" << name << ">" << endl;
    return oss.str();
  }
};

//but a builder should be a separate struct/class
struct HtmlBuilder
{
  HtmlElement root;

  //it's inconvenient for the builder to work in our elements, so let's do the interface in terms of strings
  //in general the interface should be convenient regardless of the underlying abstractions! (honestly not something I would have done by default)
  HtmlBuilder(string root_name){
    root.name = root_name;
  }

  void add_child(string child_name, string child_text){
    HtmlElement e{child_name, child_text}; //wtf is this syntax
    root.elements.emplace_back(e);
  }

  string str() const { return root.str(); }
};

int main(){
  HtmlBuilder builder{"ul"};
  builder.add_child("li", "hello");
  builder.add_child("li", "ayy");
  builder.add_child("li", "lma");
  cout << builder.str(); //holy crap, that was satisfying
}

//I love this

