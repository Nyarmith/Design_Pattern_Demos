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
using std::pair;
using std::initializer_list;

//the closest thing acceptable to embedding html in your c++ is to construct a domain-specific language
//that allows you to construct html-like constructs in valid c++ using uniform initialization syntax


//the following is the domain-specific language using the builder pattern

struct Tag
{
  string name, text;
  vector<Tag> children;
  vector<pair<string,string>> attributes; //attrname=attrvalue

  //defining stream output operator to print out all the tags, but this isn't the interesting part
  friend std::ostream& operator<<(std::ostream& os, const Tag& tag)
  {
    os << "<" << tag.name;
    for (const auto& att : tag.attributes)
      os << " " << att.first << "=\"" << att.second << "\"";

    if (tag.children.size() == 0 && tag.text.length() == 0)
    {
      os << "/>" << std::endl;
    } 
    else
    {
      os << ">" << std::endl;
      if (tag.text.length())
        os << tag.text << std::endl;

      for (const auto& child : tag.children)
        os << child;

      os << "</" << tag.name << ">" << std::endl;
    }
    return os;
  }

  protected:
  public:
  Tag(const string& name, const string& text) : name(name), text(text) {}
  Tag(const string& name, const vector<Tag> &children)
    :name(name), children(children) {}

};

//paragraph html type
struct P : Tag
{
  P(const string& text) : Tag("p",text) {}
  P(initializer_list<Tag> children)
    : Tag{"p", children} {}
};

struct IMG : Tag
{
  explicit IMG(const string& url)
    : Tag{"img", ""}
  {
    attributes.emplace_back(std::make_pair("src",url));
  }
};

int main(){
  //here is the steak
  cout <<
    P{
      IMG { "http://google.com/logo.png" }
    }
    << endl;
  //wow this is sooo cool!!

  return 0;
}
//you can constrain what elements go inside other elements by restricting the constructors!!
//very cool!

