## Everyone's Favorite: Singleton
- Use of singleton is quite often a design smell


Motivation:
* Use to limit number of objects; for some components it only makes sense to have one in the system
* Some object that should only be instantiated once

Should never be used for something that is meant to be extensible

Summary:
- Making a safe singleton is easy, you have to hide all the default =, copy ctor, constructor, add static get method, (this is guaranteed to be thread-safe sicne c++11(but it's not for earlier lol)) etc...
- Types with "hard" dependencies on singletons are difficult to test since you can't decouple the singleton and supply a fake object, so try depending on an abstraction instead and make a mock object of that interface
- Use the industry strength solution of defining singleton lifetime of a normal type in a DI container!
