## Decorator
- Adding functionality to an object without rewriting or altering existing code
- e.g. if you don't have the source code you can't directly modify the class, and you also can't violate the OCP
- This lets you keep new functionality separate (SRP)
- The key here is how to interact with existing structures

Types:
- Aggregate the decorated objects
- Inherit fromt he decorated object

Formally:
__Decorator__ : Facilitates the addition of behavior to existing objects

Summary:
- Dynamic decorator keeps the reference to a decorated object(s)
- A static decorator uses mixin inheritance (coolest imo)
- Both approaches allow limitless composition
- Functional decorator is basically an extension of static to function composition

