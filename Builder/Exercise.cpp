#include <string>
#include <ostream>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct ClassObj

{
    string name;
    vector<pair<string,string>> attributes;
};



class CodeBuilder
{
private:
    ClassObj bclass;
public:
  CodeBuilder(const string& class_name)
  {
    bclass.name = class_name;
  }

  CodeBuilder& add_field(const string& name, const string& type)
  {
    std::pair<string,string> f{name, type};
    bclass.attributes.emplace_back(f);
    return *this;
  }

  friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
  {
    os << "class " << obj.bclass.name << endl;
    os << "{" << endl;
    for (const auto& e : obj.bclass.attributes)
      os << "  " << e.second << " " << e.first << ";" << endl;
    os << "};";
    return os;
  }
};

int main(){
  auto cb = CodeBuilder{"Person"}.add_field("name","string").add_field("age","int");
  cout << cb;
}
