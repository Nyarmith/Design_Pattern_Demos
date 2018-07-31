# Prototype Pattern
When it's easier to copy an existing object's data to fully initialize a new one

Motivation:
Say you created a complicated object (e.g. car or something insane you made with builders), and you don't want to do that again, but you want to make something similar and maybe modify it afterwards(possibly making it better(or worse lol))
- Copying an existing complicated object allows you to iterate on that object
- So in a sense, an existing (partially or fully constructed) "design" is considered a prototype in this design pattern
- We make a copy(clone) of the prototype, and then we customize it
  - However, we must be able to make a deep/full copy

Furthermore, the cloning via this pattern must be convenient (e.g. via a factory)

