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
#define ll long long
using namespace std;

// Dynamic Decorator Scenario:

struct Shape
{
  virtual string str() const = 0;
};

struct Circle : Shape
{
  float radius;

  Circle() {}
  Circle(float radius) : radius(radius) {}

  string str() const override {
    ostringstream oss;
    oss << "A circle of radius " << radius;
    return oss.str();
  }

  void resize (float factor){
    radius *= factor;
  }
};

struct Square : Shape
{
  float side;

  Square(float side): side(side) { }

  string str() const override {
    ostringstream oss;
    oss << "A square with side " << side;
    return oss.str();
  }
};

//we want to add colors to the existing shapes
struct ColoredShape : Shape
{
  Shape& shape;
  string color;
  ColoredShape(Shape &shape, const string &color) : shape(shape), color(color) {}

  string str() const override {
    ostringstream oss;
    oss << shape.str() << " has the color " << color;
    return oss.str();
  }
};

//mixing decorators
struct TransparentShape : Shape
{
  Shape& shape;
  uint8_t transparency;
  TransparentShape(Shape &shape, uint8_t transparency) : shape(shape), transparency(transparency) {}
  string str() const override {
    ostringstream oss;
    oss << shape.str() << " has "
        << static_cast<float>(transparency) / 255.f * 100.f
        << "% transparency";
    return oss.str();
  }
};


int main()
{
  Square square{5};
  ColoredShape red_square{square, "red"};
  cout << square.str() << endl << red_square.str() << endl;

  //mixin
  TransparentShape my_square{red_square, 51};
  cout << my_square.str() << endl;
  //downside of this approach: 
  Circle circle{5};
  ColoredShape red_circle{circle, "red"};
  //red_circle.resize() doesn't exist!!!
  //no access to underlying api to the object you're decorating unless it's a part of some interface!!
}

