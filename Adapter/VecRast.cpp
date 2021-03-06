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
  virtual vector<Line>::iterator begin()=0;
  virtual vector<Line>::iterator end()=0;
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

  std::vector<Line>::iterator begin() override {
    return lines.begin();
  }

  std::vector<Line>::iterator end() override {
    return lines.end();
  }

  private:
    vector<Line> lines;
};

//this thing only accepts pixels! doesn't now how to draw vector objects
void DrawPoints(std::vector<Point>::iterator start, std::vector<Point>::iterator end){
  for ( auto i=start; i != end; ++i)
    cout << i->x << " " << i->y << endl;
}

vector<shared_ptr<VectorObject>> vectorPointObjects {
  make_shared<VectorRectangle>(10,10,100,100),
  make_shared<VectorRectangle>(30,30,60,60),
};

//build an adapter between lines and pixels
struct LineToPointAdapter
{
    typedef vector<Point> Points;

    LineToPointAdapter(Line& line)
    {
      static int count = 0;

      // no interpolation
      int left = min(line.start.x, line.end.x);
      int right = max(line.start.x, line.end.x);
      int top = min(line.start.y, line.end.y);
      int bottom = max(line.start.y, line.end.y);
      int dx = right - left;
      int dy = line.end.y - line.start.y;

      // only vertical or horizontal lines
      if (dx == 0)
      {
        // vertical
        for (int y = top; y <= bottom; ++y)
        {
          points.emplace_back(Point{ left,y });
        }
      }
      else if (dy == 0)
      {
        for (int x = left; x <= right; ++x)
        {
          points.emplace_back(Point{ x, top });
        }
      }
    }

    virtual Points::iterator begin() { return points.begin(); }
    virtual Points::iterator end() { return points.end(); }
  private:
    Points points;
};

int main(){

  for (auto& o : vectorPointObjects){
    for( auto& l  :  *o)
    {
      LineToPointAdapter lpo {l};
      DrawPoints(lpo.begin(), lpo.end());
    }
  }
}

//tl;dr adapters are rally simple, shouldn't be overthought about, and can solve really tough-seeming interface mismatch problems (esp with iterators)
