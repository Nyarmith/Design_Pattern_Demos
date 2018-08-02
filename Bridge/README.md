## Bridge Design Pattern

Motivation:
- Bridge prevents "Cartesian Product Explosion"
  - e.g. base class ThreadScheduler can be made preemptive, cooperative and windows or linux and you may be tempted to make a subclass for each combination of these possibilities(e.g. PreeWinSched, PreeUnixSched, CoopWinSched, CoopUnixSched)
- Instead, you can make a general scheduler, and that can depend on the scheduler interface and inherit from the preemptive/coop scheduelr type

formally:
__Bridge__ : A mechanism that decouples an interface hierarchy from an implementation hierarchy.

So the idea is that you don't rely on inheritance as much as inheritance as much as on aggregation.

You can think of a bridge as a stronger form of encapsulation
