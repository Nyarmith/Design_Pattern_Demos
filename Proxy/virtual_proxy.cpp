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

//virtual proxy gives you the appearance of working with the object you're used to working with, even though the object might not have even been created!

//let's define this interface
struct Image
{
  virtual void draw() = 0;
};

//suppose we come up with an API for a bitmap
struct Bitmap : Image
{
  //say we eagerly load the image
  Bitmap(const string& filename)
  {
    cout << "Loading bitmap from " << filename << endl;
    //the issue here is that we don't need to load the bitmap until we draw it
    //BUT we don't want to modify the orignal class (OCP) or perhaps we can't (3rd party code)
    //and we're given this interface and we have to work with it
  }
  void draw() override {
    cout << "Drawing bitmap" << endl;
  }
};

//we can build a virtual proxy that has the same interface as the bitmap, BUT this defers the loading of the original bitmap until somebody wants to draw it
struct LazyBitmap : Image
{
  LazyBitmap(const string &filename) : filename(filename)
  {
  }

  void draw() override
  {
    if(!bmp)
      bmp = new Bitmap(filename);
    bmp->draw();
  }
private:
  string filename;
  Bitmap *bmp{nullptr};
};

int main()
{
  cout << "new" << endl;
  Bitmap bmp{"pokemon.png"};
  cout << "here" << endl;
  bmp.draw();

  cout << "new" << endl;
  LazyBitmap bmp2{"pokemon.png"};
  cout << "here" << endl;
  bmp2.draw();

  return 0;
}

