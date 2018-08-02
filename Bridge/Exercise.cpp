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

#include <string>
using namespace std;

struct Renderer
{
    virtual string what_to_render_as() const = 0;
};

struct RasterRenderer : Renderer
{
    string what_to_render_as() const override {
        return "pixels";
    };
};

struct VectorRenderer : Renderer
{
    string what_to_render_as() const override {
        return "lines";
    };
};

struct Shape
{
    const Renderer &renderer;
    string name;
    
    Shape(const Renderer &renderer) : renderer(renderer) {}
        
    const string str() const{
        return ("Drawing " + name + " as " + renderer.what_to_render_as());
    }
};

struct Triangle : Shape
{
    Triangle(const Renderer& renderer) : Shape(renderer)
    {
        name = "Circle";
    }
};

struct Square : Shape
{
    Square(const Renderer& renderer) : Shape(renderer)
    {
        name = "Square";
    }
};



int main(){
  std::cout << Triangle(RasterRenderer()).str() << endl;

  Square ayy{RasterRenderer()};
  std::cout << ayy.str() << endl;
}
