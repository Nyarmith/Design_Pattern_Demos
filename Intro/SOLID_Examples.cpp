
//SOLID
//Single-responsibility principle
// *S*ingle-Responsibility Principle
// *O*pen-Closed Principle
// *L*iskov-Substitution Principle
// *I*nterface-Segregation Principle
// *D*ependency-Inversion Principle


#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
using std::string;
using std::vector;
using std::tuple;

//---------------------------------------------
//---- (1) Single-Responsibility Principle ----
//---------------------------------------------

// Idea: Maintain separation of concerns w.r.t. objects and the ideas they have to be accountable for
// We make a journal class, whose whole responsibility is to be a journal

struct Journal{
  string title;
  vector<string> entries;
  Journal(const string &title) : title(title) {}

  void add_entry(const string& entry)
  {
    static int count = 1;
    entries.push_back(std::to_string(count) + ": " + entry);
  }

  //DON'T DO this
  void save(const string& filename)
  {
    std::ofstream ofs(filename);
    for (auto &e : entries)
      ofs << e << std::endl;
  }
};

//DO THIS instead
struct PersistenceManager
{
  static void save(const Journal& j, const string& filename){
    std::ofstream ofs(filename);
    for (auto& e : j.entries)
      ofs << e << std::endl;
  }
};

void single_resp(){
  Journal journal{"Classified"};
  journal.add_entry("consumed steak");
  journal.add_entry("cried blood");

  //ok so now we want to searlize it, and one of the intuitive things you might want to do is to write a
  //serializer inside the journal class, so in-addition to the journal just keeping entries and modify entries,
  //you add another idea of persistence so you add a function called save() and it goes into the entries and saves
  //them into somewhere
  //However! the problem with this approach is that now the journal has two concerns: maintaining journal entries and persistence. However, if you change the persistence model you have to change the persistence in all classes that have compartmentalized it. 
  //So, separate concerns by making a persistence manager

  PersistenceManager pm;
  pm.save(journal, "diary.txt");
}


//---------------------------------------------
//--------- (2) Open-Closed Principle ---------
//---------------------------------------------
// Your systems should be opoen to extension but closed to modification
//Premise: Say we have a bunch of products we want to be able to filter based on some traits

//traits
enum class Color { red, green, blue };
enum class Size { small, medium, large };

struct Product
{
  string name;
  Color color;
  Size size;
};

struct ProductFilter
{
  //so this is the naive way to implement a filter
  vector<Product*> by_color(vector<Product*> items, Color color)
  {
    vector<Product*> result;
    for (auto& i : items)
      if (i->color == color)
        result.push_back(i);
    return result;
  }
};

//Build a better filter with specification pattern

//*defining a specification interface
//
// define the interface any kind of specifiable(aka filterable)
// object must satisfy
template <typename T> struct Specification
{
  virtual bool is_satisfied(T* item) = 0;
};

//*defining a filter interface
//
// defines the interface any kind of filter needs to implement
template <typename T> struct Filter
{
  virtual vector<T*> filter(vector<T*> items,
                            Specification<T>& spec) = 0;
};

struct BetterFilter : Filter<Product>
{
  vector<Product*> filter(vector<Product *> items,
                          Specification<Product> &spec) override
  {
    vector<Product*> result;
    for (auto& item : items)
      if (spec.is_satisfied(item))
        result.push_back(item);
    return result;
  }
};

struct ColorSpecification : Specification<Product>
{
  Color color;
  ColorSpecification(Color color) : color(color){};
  bool is_satisfied(Product *item) override {
    return item->color == color;
  }
};

struct SizeSpecification : Specification<Product>
{
  Size size;
  SizeSpecification(Size size) : size(size){};
  bool is_satisfied(Product *item) override {
    return item->size == size;
  }
};

//generic way of getting two
template <typename T> struct AndSpecification : Specification<T>
{
  Specification<T>& first;
  Specification<T> & second;
  AndSpecification(Specification<T>& first,
      Specification<T>& second);
  bool is_satisfied(T *item){
    return (first.is_satisfied(item) && second.is_satisfied(item));
  }
};

void open_closed(){
  Product apple{"Apple", Color::green, Size::small};
  Product tree{"Tree", Color::green, Size::large};
  Product house{"House", Color::blue, Size::large};

  vector<Product*> items { &apple, &tree, &house };

  //naively applying the easiest filter
  ProductFilter pf;
  auto green_thigns = pf.by_color(items, Color::green);
  std::cout << "Green Filter Naive:\n";
  for ( auto& item : green_thigns)
    std::cout << item->name << "is Green\n";
  //STOP -- ok so this looks nice, BUT as soon as you have to start filtering by other critereon, you start copy/pasting your original filter code. You modify your interface and start copying/pasting the code, and you have to modify original code when your original function wants to be overloaded by addition critereon -> bad! The original approach taken was not open to extension via inheritance!
  
  
  //better approach
  BetterFilter bf;
  ColorSpecification green(Color::green);
  for (auto& item : bf.filter(items, green))
    std::cout << item->name << " is Green\n";

  SizeSpecification large(Size::large);
  for (auto& item : bf.filter(items, large))
    std::cout << item->name << " is Large\n";

  //large and green
  AndSpecification<Product> green_and_large(green, large);
  for (auto& item : bf.filter(items, green_and_large))
    std::cout << item->name << " is Green and Large\n";

  //now this guy starts suggesting to write an and operator with filters so you can intuitively and them together
}


//---------------------------------------------
//----- (3) Liskov-Substitution Principle -----
//---------------------------------------------
// Subtypes should be immediately substitutable for their base-types

class Rectangle
{
  protected:
    int width;
    int height;
  public:
    Rectangle(int width, int height) : width(width), height(height) { };

    virtual void setWidth (int width) { Rectangle::width=width; }
    int getWidth () const { return width; }
    virtual void setHeight(int height) { Rectangle::height = height; }
    int getHeight() const { return height; }

    int area() const { return width * height; }
};


void process(Rectangle & r)
{
  int w = r.getWidth();
  r.setHeight(10);
  std::cout << "Expected area = " << (w*10)
            << ", got " << r.area() << std::endl;
}

class Square : public Rectangle
{
  public:
    Square(int size): Rectangle(size, size) {}
    //the below intent is nice but this overriding violates the liskov-substitution principle!!
    void setWidth(int width) override {
      this->width = this->height = width;
    }
    void setHeight(int height) override {
      this->width = this->height = height;
    }
    //don't take shortcuts that violate principles, even if they are cool
};

void lisov_subst()
{
  Rectangle r{3,4};
  process(r);
}

struct RectangleFactory
{
  static Rectangle create_rectangle(int w, int h);
  static Rectangle create_square(int size);
};
//conclusion: in this case don't make a separate class for squares, just make a factory that creates squares
//because squares can be made as rectangles, we can specify a subset rather than having to specialize via a class
//adding aclass adds nothing extra or new


//---------------------------------------------
//---- (4) Interface-Segregation Principle ----
//---------------------------------------------

struct Document;

struct IMachine
{
  virtual void print(Document& doc) = 0;
  virtual void scan(Document& doc) = 0;
  virtual void fax(Document& doc) = 0;
};

struct MFP : IMachine
{
  //inherit each thing and implement
  void print(Document& doc) override {};
  void scan(Document& doc)  override {};
  void fax(Document& doc) override {};
}

//but what if I just want to make a scanner?
struct Scanner : IMachine
{
  void scan(Document &doc) override {
    //ok
  }
  void print(Document &doc) override {
  }
  void fax(Document &doc) override {
  }
}
//despite this being a scanner, the interface implies it can print despite the implementatino maybe throwing an exception or even being null

//Better Approach:
struct IPrinter
{
  virtual void print(Document& doc) = 0;
};

struct IScanner
{
  virtual void scan(document& doc) = 0;
};

struct IFax
{
  virtual void fax(document& doc) = 0;
};

//wow, better

//now if you want to make a combination, you can make a new interface that also remains abstract

struct ICombo : IPrinter, IScanner {};

struct Machine : ICombo
{
  IPrinter& printer;
  IScanner& scanner;

  Machine(IPrinter & printer, IScanner &scanner) : printer(printer), scanner(scanner){}

  //can do a decorator thing
  void print(Document &doc){
    printer.print(doc);
  }
  void scan(Document& doc){
    scanner.scan(doc);
  }
};

// Moral of the story: break up your interface into separate small interfaces, ideally the smallest interface that encapsulates an idea
// conversely: do NOT create intefaces which are too large, or that require implementers to create too much


//---------------------------------------------
//---- (5) Dependency-Inversion Principle -----
//---------------------------------------------
// A. High-level modules should not depend on low-level modules. (this is counter-intuitive) Both should, instead, depend on abstractions
// B. Abstractions should not depend on details. Details should depend on abstractions.

enum class Relationship
{
  parent,
  child,
  sibling
};

struct Person
{
  string name;
};
// 1st-pass
////maybe we want low-level cnostrct to hold relationships
//struct Relationships //this is a "low-level module"
//{
//  vector<tuple<Person, Relationship, Person>> relations;
//  void add_parent_and_child(const Person& parent, const Person& child)
//  {
//    relations.push_back({parent, Relationship::parent, child});
//    relations.push_back({child, Relationship::child, parent});
//  }
//};
//
////if you wanted to perform research you'd have to have a high-level module
//struct Research
//{
//  Research(Relationships& Relationships)
//  {
//    auto& relations = relatinoships.relations;
//    for (auto&& [first,rel,second] : relations) //cool c++17
//    {
//      if (first.name == "John" && rel == Relationship::parent)
//      {
//        std::cout << "John has a child called " << second.name << std::endl;
//      }
//    }
//  }
//}

struct RelationshipBroswer
{
  virtual vector<Person> find_all_children_of(const string& name) = 0;
};

struct Relationships : RelationshipBrowser  //low-level
{
  vector<tuple<Person, Relationship, Person>> relations;

  void add_parent_and_child(const Person& parent, const Person& child)
  {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }

  vector<Person> find_all_children_of(const string &name) override
  {
    vector<Person> result;
    for (auto&& [first,rel,second] : relations) //cool c++17
    {
      if (first.name == name && rel == Relationship::parent)
      {
        result.push_back(second);
      }
    }
    return second;
  }
}

struct Research
{
  Research(RelationshipBrowser& browser)
  {
    for (auto& child : browser.find_all_children_of("John"))
    {
      std::cout << "John has a child named " << child.name << std::endl;
    }
  }
}


void DepInv(){
  Person parent{"John"};
  Person child1{"Chris"}, child2{"Matt"};

  Relationship relatinoships;
  relations.add_parent_and_child(parent,child1);
  relations.add_parent_and_child(parent,child2);

  Research _(relationships);

  //so here, if the low-level implementation detail changes, then everything else does, so instead of depending on Relationships, introduce an abstraction
}
//lesson to me: depend on abstract interfaces instead of concrete classes



//side-note: dependency injection specifies defaults, like making RelationshipBrowser work on a specific concrete type
