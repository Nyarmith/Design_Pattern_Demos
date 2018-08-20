#include <iostream>
#include <vector>
#include <string>
using namespace std;

class CombinationLock
{
    vector<int> combination;
public:
    string status;

    CombinationLock(const vector<int> &combination) : combination(combination) {
      status = "LOCKED";
    }

    void enter_digit(int digit)
    {
      if (status == "LOCKED" || status == "ERROR")
        status = "";
      status += std::to_string(digit);
      if (combination[status.length()-1] != digit)
        status = "ERROR";
      else if (status.length() == combination.size())
        status = "OPEN";
    }
};

//this is fairly trivial but I like my cleverness in it :- \
