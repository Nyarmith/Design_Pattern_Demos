## Command: A Hierarchy of Instructions

Motivation:
- Ordinary C++ statements are "perishable" i.e. there is no undo button in our normal assembly steps
- We want an object that represents an operation
- e.g. GUI-programs usually have an "undo button", this is because the actions of the program are stored internally
- This lets us serialize a sequence of actions/calls/commands themselves!

Formally:
__Command__ : An object which represents an instruction to perform a particular action. Contains all the information necessary for the action to be taken.


Side-Idea: Command-Query-Separation
- Command put into the format of a query
- Query = asking for information (e.g. please give me your attack value)
- CQS = having separate means of sending commands and queries
GoF doesn't mention queries, only commands are refernces, but we can make a distinction. Both ideas are encapsulated in the command design pattern.

