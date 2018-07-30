## Summary Tips
- A buidler is a separate component for building an object
- You can either give the builder a constructor or return it via a static function (ideally in the class you want to build)
- To make a builder fluent, return \*this
- Different facets of an object can be built with different builders working in tandem via a base class (the base class lets you switch between builders)

note: the exercise was simple it wasn't worth transcribing( but I did use the member default {val} initialzer!!)


Main Lessons:
- Factory method is a static method
- Factory is delegated object creation
- Factory can be external(may break ocp) or inner(if cool)
- Hierarchies of factories can be used to create related objects
- The abstract factory hierarchy thing isn't really used so much nowadays
