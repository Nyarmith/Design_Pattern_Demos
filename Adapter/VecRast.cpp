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
#include <memory>
using namespace std;
#define ll long long

struct Point
{
  int x,y;
};

struct Line
{
  Point start, end;
};

struct VectorObject
{
  virtual vector<Line>::iterator begin();
  virtual vector<Line>::iterator end();
};

struct VectorRectangle : VectorObject
{
  VectorRectangle(int x, int y, int width, int height)
  {
    lines.emplace_back(Line{ Point{ x,y }, Point{ x + width,y } });
    lines.emplace_back(Line{ Point{ x + width,y }, Point{ x + width, y + height } });
    lines.emplace_back(Line{ Point{ x,y }, Point{ x,y + height } });
    lines.emplace_back(Line{ Point{ x,y + height }, Point{ x + width, y + height } });
  }
  private:
    vector<Line> lines;
};

//this thing only accepts pixels! doesn't now how to draw vector objects
void DrawPoint(std::vector<Point>::iterator start, std::vector<Point>::iterator end){
  for ( auto i=start; i != end; ++i)
    cout << i->x << " " << i->y << endl;
}

vector<shared_ptr<VectorObject>> vectorObjects {
  make_shared<VectorRectangle>(10,10,100,100),
  make_shared<VectorRectangle>(30,30,60,60),
};

//build an adapter between lines and pixels
struct LineToPointAdapter
{
    typedef vector<Point> Points;

    LineToPointAdapter(Line& line)
    {
    }

    virtual Points::iterator begin() { return points.begin(); }
    virtual Points::iterator end() { return points.end(); }
  private:
    Points points;
};

int main(){
}

