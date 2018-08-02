## Composite
Treating individual and aggregate objects uniformly

Motivation:
- Objects use other objects' field/properties/members through inheritence and composition

Composition lets us make compound objects:
- e.g. a mathematical expression composed of simple expressions; or a grouping of shapes that consists of several shapes
- Composite design patterns is used to treat both single and composite objects uniformly

i.e. Foo and Collect<Foo> would have some common interface, you shouldn't have to know whether the object is a composition or single instance!


Formally: __Composite__ : A mechanism for treating individual (scalar) objects and compositions of objects in a uniform manner

Summary:
- Make composite and singular objects implement a common interface for convenience
- c++ uses duck-typing for begin() end() to determine if you have a container, and so a single objct can masquerade as this! Enumeration of objects becomes easy.


 
