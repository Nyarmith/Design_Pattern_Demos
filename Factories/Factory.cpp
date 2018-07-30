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
public:
  Point(const float x, const float y)
    : x{x},
      y{y}
  {
  }
  float x,y;
  friend std::ostream& operator<<(std::ostream& os, const Point& obj)
  {
    return os
      << "x: " << obj.x << " y: " << obj.y;
  }

  //friend class PointFactory; //ocp violation!!, don't do this!
  //better to make your constructor public at this point
};

//now we are making a factory(think of it as a concrete factory) (not in original GoF)
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

int main(){
  //    //consider: you may want to construct a factory itself
  //PointFactory pf
  //    //or you can avoid it by making everything in the factory static
  Point pt{3,4};
  cout << pt << endl;

  auto pt2 = PointFactory::NewPolar(5,M_PI_4);
  cout << pt2 << endl;
  return 0;
}


//Lesson: Don't break the OCP when implementing a factory, try to make interface clear for constructor tho(like x,y is probably good enough of a hint there)


