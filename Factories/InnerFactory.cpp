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


//so far the biggest issue here is that none of our factory methods/things have been clear to the user that they should use it
//so to make the user "get" that they should use a factory, we should go back to making everything private, and circumvent the OG factory's OCP violation issue by putting the factory itself _inside_ of the class, hence it is an inner class



enum class PointType
{
  cartesian,
  polar
};


// // v1 of vid
//class Point
//{
//  Point(const float x, const float y)
//    : x{x},
//      y{y}
//  {
//  }
//  float x,y;
//public:
//  friend std::ostream& operator<<(std::ostream& os, const Point& obj)
//  {
//    return os
//      << "x: " << obj.x << " y: " << obj.y;
//  }
//
//  //inner class, the only way the user can make Point objects
//  struct PointFactory
//  {
//    static Point NewCartesian(float x, float y)
//    {
//      return { x,y };
//    }
//    static Point NewPolar(float r, float theta)
//    {
//      return { r*cos(theta), r*sin(theta) };
//    }
//  };
//};



//pt 2, ok now we're going to make the pointfactory private as well 0_0
class Point
{
  Point(const float x, const float y)
    : x{x},
      y{y}
  {
  }
  float x,y;

  struct PointFactory
  {
    static Point NewCartesian(float x, float y)
    {
      return { x,y };
    }
    static Point NewPolar(float r, float theta)
    {
      return { r*cos(theta), r*sin(theta) };
    }
  };
public:
  friend std::ostream& operator<<(std::ostream& os, const Point& obj)
  {
    return os
      << "x: " << obj.x << " y: " << obj.y;
  }

  //now we expose a singleton isntance of the PointFactory at one point
  static PointFactory Factory;
};


int main(){
//  // so this is somewhat better, as ths user sees that most of the members are private but they see that the inner class is public and they get to see the api through that inner class
//  auto p = Point::PointFactory::NewPolar(5, M_PI_4);
//
//  std::cout << p;
//  return 0;


  //pt2, now if we take a point, the only member we can see is a factory
  auto p = Point::Factory.NewCartesian(1,4);
  cout << p << endl;
  return 0;
  // so this literally forces the user to see the options for creating the point as soon as they type the dot after Point::Factory
  //
  // This is essentially the canonical "Inner Factory", but its up to you whether you want it to be private/public/static/whatever, but the main benefit is that you have acceess to the private constructor, and you can control its lifetime by making the factory private and only giving access through your own restricted getter methods
}


