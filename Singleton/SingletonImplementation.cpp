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
#include <fstream>
#include <cmath>
#include <boost/lexical_cast.hpp>
#define ll long long
using namespace std;
using namespace boost;

class SingletonDatabase
{
  SingletonDatabase()
  {
    cout << "Initializing database\n";
      ifstream ifs("capitals.txt");

    string s, s2;
    while(getline(ifs,s)){
      getline(ifs,s2);
      int pop = lexical_cast<int>(s2);
      capitals[s] = pop;
    }
  }
  map<string, int>  capitals;
  public:
  SingletonDatabase(SingletonDatabase const&) = delete;
  void operator=(SingletonDatabase const&) = delete;

  static SingletonDatabase& get()
  {
    static SingletonDatabase db;
    return db;
  }

  int get_population(const string& name)
  {
    return capitals[name];
  }
};

int main()
{
  auto &db = SingletonDatabase::get();
  cout << "Tokyo has population " << db.get_population("Tokyo");
}
