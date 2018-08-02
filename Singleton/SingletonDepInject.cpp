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
#include <gtest/gtest.h>
#include <boost/lexical_cast.hpp>
#define ll long long
using namespace std;
using namespace boost;

//making an interface
class Database
{
  public:
    virtual int get_population(const string& name) = 0;
};

class SingletonDatabase : public Database
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

class DummyDatabase : public Database
{
  //dummy data
  map<string,int> capitals;
  public:
  DummyDatabase(){
    capitals["alpha"]  = 1;
    capitals["beta"]   = 0;
    capitals["gamma"]  = 4;
  }
  int get_population(const string& name){
    return capitals[name];
  };
};

struct SingletonRecordFinder
{
  int total_population(vector<string> names)
  {
    int result{0};
    for (auto& name : names)
      result += SingletonDatabase::get().get_population(name); //this part is a dependency
    return result;
  }
};

//so now this is a unit test
struct ConfigurableRecordFinder
{
  Database& db;
  ConfigurableRecordFinder(Database &db) : db(db) {}
  int total_population(vector<string> names)
  {
    int result{0};
    for (auto& name : names)
      result += db.get_population(name); //this part is a dependency
    return result;
  }
};

TEST(RecordFinderTests, SingletonTotalPopulationTest)
{
  SingletonRecordFinder rf;
  vector<string> names{"Tokyo","NewYon"};
  int tp = rf.total_population(names);
  EXPECT_EQ(76767 + 6666, tp);
  //so here we are depending on the details of how the data is provided
  //so... let's try a little bit of dependency injection!
  //so this means, we have a point where we're injecting this dependency instead of the original/actual object
  //so, we're going to make an interface for our database
}

//unit test
TEST(RecordFinderTests, DependantTotalPopulationTest)
{
  DummyDatabase db;
  ConfigurableRecordFinder rf{db};
  EXPECT_EQ(5,rf.total_population({"alpha", "gamma"}));
}

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}

//so the issue here is that the singleton isn't a bad idea, it's that it's a bad idea if you have a hard dependence on it. You should have your tests depend on an interface and predictable mock data
