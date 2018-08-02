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
#define ll long long

using namespace std;

//looking at a more large implementatino of a bridge design pattern
//Imageine we have different shapes, and different ways to render them
//
// Shapes   - circle, square
// Renderer - raster, vector
//
// to avoid a 2x2 renderer/shape cartesian implementsplosion


struct Renderer
{
  virtual void render_circle(float x, float y, float radius) = 0;
};

struct VectorRenderer : Renderer
{
  void render_circle(float x, float y, float radius) override {
    cout << "Drawing a vector circle of radius " << radius << endl;
  }
};

struct RasterRenderer : Renderer
{
  void render_circle(float x, float y, float radius) override {
    cout << "Rasterizing a circle of radius " << radius << endl;
  }
};

struct Shape
{
  protected:
    Renderer& renderer;
    Shape(Renderer &renderer) : renderer(renderer) {}
  public:
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};


struct Circle : Shape
{
  Circle(Renderer &renderer,
      float x, float y, float radius) : Shape(renderer),
      x{x}, y{y}, radius{radius}
  {}

  float x, y, radius;

  void draw() override {
    renderer.render_circle(x, y, radius);
  };

  void resize(float factor) override{
    radius *= factor;
  }
};

int main()
{
  RasterRenderer rr;
  Circle raster_circle{rr, 5, 5, 5};
  raster_circle.draw();
  raster_circle.resize(2);
  raster_circle.draw();
}
