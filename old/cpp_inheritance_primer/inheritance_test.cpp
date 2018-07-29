#include <iostream>
#include <string>

void output(std::string in=""){
    std::cout << in << std::endl;
}

class Factory{
    public:
        virtual void makeSteel() const{
            output("nice steel");
        }
        virtual void makeGlass() const{
            output("nice glass");
        }
        virtual void makeGuns() const{
            makeSteel();
            makeGlass();
            output("nice guns!");
        }
};

class SugoiFactory : public Factory{
    public:
    virtual void makeSteel() const{
        output("thousand folded steel");
    }
    virtual void makeGuns() const{
        makeSteel();
        makeGlass();
        output("sugoiiii!!!");
    }
};

int main(){
    //what does the basic guy do?
    Factory myFact;
    myFact.makeGuns();
    output();

    //what does a derived pointer to the derived class do?
    SugoiFactory wowFact;
    wowFact.makeGuns();
    output();

    //what does a base pointer to the derived class do?
    Factory * ptrFact = new SugoiFactory;
    ptrFact->makeGuns();
    output();

    return 0;
}
