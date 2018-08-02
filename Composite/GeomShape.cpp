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
#define ll long long
using namespace std;

struct GraphicsObject
{
  virtual void draw() = 0;
};

struct Circle : GraphicsObject
{
  void draw() override {
    cout << "Circle" << endl;
  }
};

struct Group : GraphicsObject
{
  string name;
  vector<GraphicsObject*> objects;
  Group(const string& name) : name(name) {}
  void draw() override
  {
    cout << "Group " << name.c_str() << " contains:" << endl;
    for (auto&& o : objects)
      o->draw();
  }
};

int main(){
  Group root("root");
  Circle c1, c2;
  root.objects.push_back(&c1);

  Group subgroup("sub");
  subgroup.objects.push_back(&c2);
  root.objects.push_back(&subgroup); //bam, recursion!

  root.draw();
}

//main takeaway: interface enforces that groups and individual objects are treated in a uniform manner
