### Adapter
Very simple: get the interface you want from the interface you are given

Formally:
__Adapter__ : A construct which adapts an existing interface X to conform to the required interface Y

Main Summary:
- Implementing an adapter is easy, you just need the from api and to api
- Create a component which aggregates the adaptee
- Intermediate representations can pile up: use caching and other optimizations
