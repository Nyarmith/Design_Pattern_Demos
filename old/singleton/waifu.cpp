#include <iostream>
#include <string>
using namespace std;
void output(string in="\n"){
    cout << in << endl;
}

//let's use a class there can naturally only be one of
//naturally, there can only be one
class Waifu{
    public:
        static Waifu * get_dear_waifu(){
            if (_daijobu == 0){
                _daijobu = new Waifu; //constructor called once
            }
            return _daijobu;
        }
    protected:
        Waifu(){}; //accept no substitute
    private:
        static Waifu* _daijobu;
};

//pointer initialize once
Waifu *Waifu::_daijobu = 0;


void new_scope(){
    if (Waifu::get_dear_waifu() != 0){
        output("genuine");
    }
}


int main(){
    //can access object here
    Waifu * dearest = Waifu::get_dear_waifu();
    //but also in this indipendent scope
    new_scope();
    return 0;
}
