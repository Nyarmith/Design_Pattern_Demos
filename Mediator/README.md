## Mediator: Facilitataes Communication btwn Components (by letting them be unaware of each other!)

Motivation:
- Components may go in and out of a system at any time
- It makes no sense for them to have direct references to one another
- Solution: Have all refer to some central component that facilitates communication (that is the mediator)

__Mediator__ : A component that facilitates communication between other components without them necessarily being aware of each other or having direct access to each other

Summary:
- Create the mediator and have each object int he system refer to it (use DI, use a field to pass, use singleton, whatever)
- Mediator engages in bidirectional communication
- Mediator has functions the components can call
- Components have functions the mediator can call
- Event processing (e.g. Rx) libraries make communication easier to implement


