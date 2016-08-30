#include <iostream>
#include <string>
#include <vector>
using namespace std;

void output(string in="\n"){
    cout<<in;
}

class Parfait{
    public:
        void print_description(){
            output("This delicious parfait is topped with: ");
            for (int i=0; i<toppings.size(); i++){
                output(toppings[i]+" ");
            }
        }
        void add_topping(string topping){
            toppings.push_back(topping);
        }
    private:
        vector<string> toppings;
};

class Abstract_Parfaictory{ //base class of all parfait makers
    public:
        virtual Parfait* make_parfait()=0;
        //some other file
};

class Chocolate_Parfaictory : public Abstract_Parfaictory{
    public:
        virtual Parfait* make_parfait(){
            Parfait * parf = new Parfait;
            parf->add_topping("chocolate flakes");
            parf->add_topping("fudge");
            return parf;
        }
};

class Fruit_Parfaictory : public Abstract_Parfaictory{
    public:
        virtual Parfait* make_parfait(){
            Parfait * parf = new Parfait;
            parf->add_topping("blackberries");
            parf->add_topping("strawberries");
            return parf;
        }
};

//a big application is to have distinct, separate
//products with different uses and prices ;-)
int main(){
    Abstract_Parfaictory * parfait_maker;
    //now we can assign any parfaictory, and get a parfait
    //with the same, comfortable ordering system
    parfait_maker = new Chocolate_Parfaictory;
    parfait_maker->make_parfait()->print_description();
    output();
    //we might not know what parfait_maker is at a time,
    //but we can still rely on our interface
    parfait_maker = new Fruit_Parfaictory;
    parfait_maker->make_parfait()->print_description();

    return 0;
}
