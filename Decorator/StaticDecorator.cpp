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

// Static Decorator For When you know what decorations you want in advance (i.e. the decorators are finite)

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

template <typename T> struct ColoredShape2 : T
{
  static_assert(is_base_of<Shape,T>:: value,
      "Template argument must be a shape");

  string color;

  ColoredShape2() {}
  //you want something like
  //TransparentShape2<ColoredShape2<Square>> sq{10, "red", 44}
  template <typename...Args>
  ColoredShape2(const string& color, Args ...args)
    : T(std::forward<Args>(args)...), color{color} {}

  string str() const override
  {
    ostringstream oss;
    oss << T::str() << " has the color " << color;
    return oss.str();
  }
};

template <typename T> struct TransparentShape2 : T
{
  static_assert(is_base_of<Shape,T>:: value,
      "Template argument must be a shape");

  uint8_t transparency;

  TransparentShape2() {}
  //you want something like
  //TransparentShape2<ColoredShape2<Square>> sq{10, "red", 44}
  template <typename...Args>
  TransparentShape2(const uint8_t transparency, Args ...args)
    : T(std::forward<Args>(args)...), transparency{transparency} {}

  string str() const override
  {
    ostringstream oss;
    oss << T::str() << " has " << static_cast<float>(transparency) / 255.0f * 100.f << "% transparency";
    return oss.str();
  }
};

int main()
{
  ColoredShape2<Circle> green_circle{"green", 5};
  green_circle.resize(1.8); //this is amazing
  cout << green_circle.str() << endl;

  TransparentShape2<ColoredShape2<Square>> square{51, "blue", 10};
  cout << square.str() << endl;
}

//Takewaway: This may be the most important part of this course: template decarators
