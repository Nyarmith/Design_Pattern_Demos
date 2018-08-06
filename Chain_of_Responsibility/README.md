## Blame-Games: Chain of Responsibility Pattern
- We've got a _hierarchical_ system, but who takes the buck for a particular event??

Simple Example: Unethical behavior; who takes the blame? It typically goes up the chain.
- Employee (this guy, he messed up, we're going to fire him and forget about it, but what if...)
- Manager (did he know about this? it could be the department policy to lie or cheat, or...)
- Manager (if he knew about this, then the entire company is corrupt! if so, a total fine and reform is necessary)

So based on the exact behavior, some hierarchical line of this gets to handle it

More Practical Example - Clicking on a graphical event on a form:
- If button handles it, it stops further processing
- If it doesn't, and the underlying group box handles it, it stops there
- If THAT doesn't handle it, we go to the underlying window's handler!

Collectible Card Game:
- Each creature has attack and defense values
- These can be boosted by other cards
- Those cards can be boosted by other cards! So you have to walk the whole chain of responsibility

Formally
__Chain of Responsibility__ : A chain of components who all get a change to process a command or a query, optionally having default processing implementation and an ability to terminate the processing chain.


Summary:
- New form is sort of like a query, where you nest the state-machine for its effects (i.e. if the callee is me do X, else Y
- This can be viewed/implemented as a linked-list as well, but the chain can be represented in many structures, so it seems more conceptual than a specific dependency to me
- We can implement this as: a chain of pointers (sort of decentralized), centralized vector, centralized list(w. observer),
- Enlist objects in the chain, possibly controlling their order (if it matters)
- This is basically just a graph-traversal problem with a query being modifies
- Removal from chain involves removal from the data structure, or simply a disconnect from a signal

