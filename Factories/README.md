# Factory
Think of "Factory" as the Idea rather than having to separate "abstract factory" vs. "factory method" vs. other kinds of factories

\* The core idea is that: Object creation ofen becomes too convoluted and non-descriptive for a constructor
- If name of constructor is name of type
- Can't overload constructor with same sets of args with different names (i.e. abstract away constructor into types you've identified)
- If you turn the above into optional parameters, you start to enter "optional parameter hell"

We can outsource single individual construction statement-types for creation to a factory.
- To contrast with a builder with its fluent stuff and whatever, in a factory it's more a process of creating a type that has a lot of different flavors/varieties. e.g. create an account that can be a checking account, credit account, gold account, etc... You don't want to stick it into a single constructor, but you want something _like_ a constructor.

Popular implementations:
- Make this into a single function (factory method)
- Make a separate class that takes care of construction of objects (factory pattern)
- Make hierarchies of factories creating hierarchies of objects (more rare, the abstract factory)

So the factory idea/pattern itself is a component responsible solely for the wholesale (not piecewise) creation of objects.

