//tests order of constructor and destuctor for inheritance when nothing is virtual
#include <iostream>
#include <string>

void output(std::string in=""){
    std::cout << in << std::endl;
}

//order of linear inheritance
class A{
    public:
     A(){
        output("A");
    }
    ~A(){
        output("~A");
    }
};

class B:public A{
    public:
    B(){
        output("B");
    }
    ~B(){
        output("~B");
    }
};

class C: public B{
    public:
    C(){
        output("C");
    }
    ~C(){
        output("~C");
    }
};

//order of multiple inheritance
class X{
    public:
    X(){
        output("X");
    }
    ~X(){
        output("~X");
    }
};

class Y: public X, public B{
    public:
    Y(){
        output("Y");
    }
    ~Y(){
        output("~Y");
    }
};

int main(){
    //experiments for linear inheritance
    //test most derived class in normal situation
    C * myC = new C;
    delete myC;
    output();
    //test what happens with lower pointer to higher class
    B * myBC = new C;
    delete myBC;
    output();

    //test what happens with multiple inheritance
    //normal pointer
    Y * myY = new Y;
    delete myY;
    output();

    //base pointer
    X * myXY = new Y;
    delete myXY;
    output();

    return 0;
}

