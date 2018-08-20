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
#include <iterator>
#define ll long long

using namespace std;

int main(){
  vector<string> names { "john", "jane", "jill", "jack"};
  vector<string>::iterator it = names.begin(); //or newer syntax: begin(names); begin() also works for arrays!
  cout << "first name is " << *it << endl;

  ++it; //this is an expected part of the iterator's interface
  it->append(" goodall"s);
  cout << "seocnd name is " << *it << endl;

  while (++it != names.end()){  //nice technique!
    cout << "another name is " << *it << endl;
  }

  //reverse order thing
  for ( auto ri = rbegin(names); ri != rend(names); ++ri )
  //also, use rbegin when you just want the last element of a thing
  {
    cout << *ri;
    if (ri+1 != rend(names))  //cool technique
      cout << ", ";
  }
  cout << endl;

  //ok, constant iterators don't let you do stuff like it->append(), to modify the underlying elements (good stuff)
  vector<string>::const_reverse_iterator jack = crbegin(names);
  //*jack += "reacher"s; //No longer allowed!


  //latest and freshest way to iterate, but there is no reverse-version of it
  for (auto&& name : names) //this only requires a type to implement begin/end
    cout << "name = " << name << endl;

  //guide to range-fors
  //      auto : names  => value-copy
  //      auto& : names => reference
  //      auto&& name   => rvalue reference (safest approach, use 99% of the time)
  return 0;
}
