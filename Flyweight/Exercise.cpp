#include <vector>
#include <locale> 
#include <iostream>


struct Sentence
{
  struct WordToken
  {
    bool capitalize;
    WordToken(bool cap) : 
      capitalize(cap) { }
  };
  const std::string textRef;
  std::vector<WordToken> capset;

  Sentence(const std::string& text) : textRef(text)
  {
      //parse string
      int i=0;
      bool isWs=true;
      while (i < text.length()){
          if (text[i] != ' ' && isWs){
              isWs = false;
              capset.push_back(WordToken{false});
          } else if (!isWs && text[i] == ' '){
              isWs = true;
          }
          ++i;
      }
  }

  WordToken& operator[](size_t index)
  {
      return capset[index];
  }

  std::string str() const
  {
    std::string ret="";
    int i=0;
    int words=-1;
    bool isWs=true;
    while (i < textRef.length()){
      char c = textRef[i];
      if (c == ' '){
          isWs=true;
          ret += c;
      } else {
        if (isWs){
          ++words;
          isWs = false;
        }
        if (capset[words].capitalize)
          ret += std::toupper(c);
        else
          ret += c;
      }
      ++i;
    }
    return ret;
  }
};

int main(){
  Sentence s{std::string("pls tO Help")};
  s[1].capitalize = true;
  std::cout << s.str() << std::endl;
}
