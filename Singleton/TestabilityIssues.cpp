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

struct SingletonRecordFinder
{
  int total_population(vector<string> names)
  {
    int result{0};
    for (auto& name : names)
      result += SingletonDatabase::get().get_population(name);
    return result;
  }
};

TEST(RecordFinderTests, SingletonTotalPopulationTest)
{
  SingletonRecordFinder rf;
  vector<string> names{"Tokyo","NewYon"};
  int tp = rf.total_population(names);
  EXPECT_EQ(76767 + 6666, tp); //in order to write this correctly, I have to go in and get the real values :-(
}
//due to the strong coupling of the database and the singleton object, our "unit-test" is actually an integration test. (we only wanted to test this function, not the db(furthermore, the DB and its data might change)). 

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}

