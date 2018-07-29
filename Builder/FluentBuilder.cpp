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

//improvements on the previous ver
//
//we're adding a *Fluent Interface*

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

  //this static builder ref gives a hint to the user to use a builder
  static HtmlBuilder build(string root_name)
  {
    return {root_name}; //this is wizardry
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

  //changing this from void to a reference to itself lets you chain add_child calls
  HtmlBuilder& add_child(string child_name, string child_text){
    HtmlElement e{child_name, child_text}; //wtf is this syntax
    root.elements.emplace_back(e);
    return *this;
  }

  string str() const { return root.str(); }

  operator HtmlElement() const { return root; //if you know this is the last operation you'll do, you can return std::move(root);
  }
};

int main(){
  HtmlBuilder builder{"ul"};
  //now we can do
  builder.add_child("li", "hello").add_child("li", "ayy"); //cool!
  builder.add_child("li", "lma");
  cout << builder.str();

  auto builder2 = HtmlElement::build("ul").add_child("","");

  //icing on cake, builder to html-element by defining an operator HtmlElement cast for the builder
  HtmlElement elem = HtmlElement::build("ul").add_child("","");
}

//you can enforce this EVEN MORE by making HtmlElement's constructors private and only letting HtmlBuilder use them via friend class, thus the only way the user can create HtmlElements is now with the builder class!!

//side-topic: a reference-api is better than a pointer API
