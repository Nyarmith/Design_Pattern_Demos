Proxy Design Pattern:
- An interface for accesing a particular __resource__
- Different than an adapter in that it's resource-oriented, and the interface looks just like the resource's interface

Motivation:
- Useful if you want to refactor all resource operations in a single thread/process, to avoid changing your code in the future
- i.e. beind the scenes, it would transmit the info to that thread/process behind the scenes (this is called a communication proxy)
- Other Proxy Types: logger, virtual, guarding

Formally:
__Proxy__ : A class that functions as an interface to a particular resource. That resource may be remote, expensive to construct, or may require logging or some other added functionality

Proxy vs. Decorator:
* Proxy tries to provide an identical interface whereas a decorator tries to enhance that interface
* Decorator typically aggregates (or has reference to) what it is decorating; proxy doesn't have to do any of that, it just has to mimic the og interface
* Proxy might not even be working with a constructed object (corrolary of above)

Summary:
- idk everything is pretty well summarized above
- there are a large variety of proxies out there!
