## Memento - Keeps a memento of an object's state to return to that state

Motivation:
- An object and system goes through changes
- Instead of keeping track of commands and undo's of commands, we can save a snapshot of the system (and often you don't need the details of a whole system, hence we can think of the token as a memento, usually a subset of the system)

Formally:
__Memento__ : A token/handle representing the system state. Lets us roll back to the state when the token was generated. May or may not directly expose state information.
