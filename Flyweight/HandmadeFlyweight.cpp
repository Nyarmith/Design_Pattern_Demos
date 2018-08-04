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
#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#define ll long long

using namespace std;
using namespace boost;


//here we're going with the MMO user-name simulation thing

typedef uint32_t key; //key to our db

struct User
{
  key first_name, last_name;
  User(const string& first_name, const string& last_name)
    : first_name{add(first_name)}
    , last_name{add(last_name)} {}

  const string& get_first_name() const
  {
    return names.left.find(first_name)->second;
  }

  const string& get_last_name() const
  {
    return names.left.find(last_name)->second;
  }
protected:
  static bimap<key,string> names;
  static key seed;

  static key add(const string& s)
  {
    auto it = names.right.find(s);
    if (it == names.right.end())
    {
      key id = ++seed;
      names.insert({seed,s});
      return id;
    }
    return it->second;
  }
};

key User::seed{0};
bimap<key,string> User::names{};

ostream &operator<<(ostream &os, const User &user) {
  os << "first_name: " << user.get_first_name() << "(" << user.first_name << ")" << " last_name: " << user.get_last_name() << "(" << user.last_name << ")";
  return os;
}

//cool, bimaps are cool

int main()
{
  User user1{"John", "Smith"};
  User user2{"Jane", "Smith"};
  cout << user1 << endl;
  cout << user2 << endl;
}
