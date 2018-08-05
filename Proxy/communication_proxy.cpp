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

//interface of service
struct Pingable
{
  virtual string ping(const string& message) = 0;
};

//making a ping-pong service, this is the resource
struct Pong : Pingable
{
  string ping(const string& message) override
  {
    return message + "pong";
  }
};

void tryit(Pingable& pp)
{
  cout << pp.ping("ping") << "\n";
}

//so we want to make a communication-proxy for ping-pong
//we want to keep the interface the same, but when we use pong,
//we want it to happen on a remote server
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

//so this is our proxy, which maintains the same interface and illussion, but when you call it
//you connect to the resource
struct RemotePong : Pingable
{
  string ping(const string& message) override
  {
    string result;
    http_client client{"http://localhost:64959/"};
    uri_builder builder{"/api/values/"};
    builder.append(message);
    auto task = client.request(methods::GET, builder.to_string())
      .then([=](http_response r)
    {
      return r.extract_string();
    });

    task.wait();
    return task.get();
  }
};

int main()
{
  Pong pp;
  for ( size_t i=0; i<3; ++i)
  {
    tryit(pp);
  }

  //now with remote
  RemotePong pp2;
  for ( size_t i=0; i<3; ++i)
  {
    tryit(pp2);
  }

  return 0;
}


