## State : Fun with Finite State Machines
But wait, isn't everything a state machine?

Motivation:
- Often times you want to make an explicit state-machine to run things inside of
- Changes in state can be explicit or in response to an event (observer)


Formally:
__State__ : A pattern in which the object's behavior is determined by its stae. An obhect transitions from one state to another (something needs to __trigger__ a transition) A formalized construct which manages state and transitions is called a __state machine__.

Summary:
- Given sufficient complexity, it pays to formally define possible states and events/triggers
- You can get into details, like state entry/exit behavior, guard conditions enabling/disabling a transition, default action when no transitions are found

