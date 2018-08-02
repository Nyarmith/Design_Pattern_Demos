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
#include <boost/predef/library/c.h>
#define ll long long

using namespace std;

struct Neuron;

//later pt : introducing a new interface
//CRTP saves the day
template <typename Self>
struct SomeNeurons
{
  template <typename T> void connect_to(T& other)
  {
    //we need to enumerate our neurons and their neurons
    for (Neuron& from : *static_cast<Self*>(this))
    {
      for (Neuron& to : other)
      {
        from.out.push_back(&to);
        to.in.push_back(&from);
      }
    }
  }
};


struct Neuron : SomeNeurons<Neuron>
{
  vector<Neuron*> in, out;
  unsigned int id;
  Neuron(){
    static int id{1};
    this->id = id++;
  };
  void connect_to(Neuron& other)
  {
    out.push_back(&other);
    other.in.push_back(this);
  };

  Neuron* begin() { return this; }
  Neuron* end() { return this+1; } //uhh, this __does__ work, and it doesn't call this guy

  friend ostream &operator<<(ostream &os, const Neuron &obj) {
    for (Neuron* n : obj.in)
    {
      os << n->id << "\t-->\t[" << obj.id << "]" << endl;
    }
    for (Neuron* n : obj.in)
    {
      os << "[" << obj.id << "]\t-->\t" << n->id << endl;
    }
    return os;
  }
};

//cardinal sin by inheriting from stl types
struct NeuronLayer : vector<Neuron>, SomeNeurons<NeuronLayer>
{
  NeuronLayer(int count)
  {
    while( count --> 0)
      emplace_back(Neuron{});
  }

  friend ostream &operator<<(ostream &os, const NeuronLayer &obj) {
    for (auto& n : obj) os << n;
    return os;
  }
};

int main(){
  Neuron n1, n2;
  n1.connect_to(n2);
  cout << n1 << n2 << endl;

  NeuronLayer layer1{2}, layer2{3};
  //n1.connect_to(layer1);
  ////cartesian functino explosion!
  //layer2.connect_to(n2);
  //layer1.connect_to(n2);
  NeuronLayer l1{5};
  Neuron n3;
  l1.connect_to(n3);

  cout << "Neuron " << n3.id << endl << n3 << endl;
  cout << "Layer " << endl << l1 << endl;

  NeuronLayer l2{ 2 }, l3{ 3 };
  l2.connect_to(l3);
  cout << "Layer l2" << endl << l2;
  cout << "Layer l3" << endl << l3;

}

//main takeaways:
//CRTP has a huge use in composite interfaces
//c++17 allows forward declaration and usage of incomplete types (this is huge, well not as much for large projects)
