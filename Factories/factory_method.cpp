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
#include <cmath>
#include <iostream>
#define ll long long

#define _USE_MATH_DEFINES
using namespace std;





enum class PointType

{

  cartesian,

  polar

};



class Point

{
//naive attempt at a flexible creation in the constructor, but bad
  /*Point(float a, float b, PointType type = PointType::cartesian)
  {
  if (type == PointType::cartesian)
  {
  x = a; b = y;
  }
  else
  {
  x = a*cos(b);
  y = a*sin(b);
  }

  }*/
  //private constructor so that we use the factory, and to force us to use/notice the static guys
  Point(const float x, const float y)
    : x{x},
      y{y}
  {
  }
public:
float x,y;
 friend std::ostream& operator<<(std::ostream& os, const Point& obj)
  {
    return os
      << "x: " << obj.x << " y: " << obj.y;
  }
 //making factory methods as static members of the class is a good idea I hadn't really considered
  static Point NewCartesian(float x, float y)
  {
    return { x,y };
  }
  static Point NewPolar(float r, float theta)
  {
    return { r*cos(theta), r*sin(theta) };
  }
};

int main(){
  auto pt = Point::NewPolar(1, M_PI_4);
  cout << pt << endl;
  return 0;
}

//TIL: You should try making factory methods/functions static functions for clarity/logic
// also: consider making the actual constructor private way more than you already have been considering
// also: M_PI_4 is a thing
