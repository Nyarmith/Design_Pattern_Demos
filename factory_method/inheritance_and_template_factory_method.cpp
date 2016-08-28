#include <iostream>
#include <string>

void output(std::string in=""){
    std::cout << in << std::endl;
}
//templating example
template<class output_object>
class templateFactory{
    public output_object* produce_item(){
        return new output_object;
    }
}

//inheritance factory example
//we have separate factories for two products now!
class Steel{
    public:
        Steel(std::string quality){
            m_quality=quality;
        }
        std::string get_quality(){
            return m_quality;
        }
    private:
        std::string m_quality;
}

class Glass{
    public:
        Glass(std::string opacity){
            m_opacity=opacity;
        }
        std::string get_opacity(){
            return m_opacity;
        }
    private:
        std::string m_opacity;
}
class Gun(){
    public:
    Gun(Steel* gun_steel, Glass* gun_glass){
        m_description = "A fine gun made out of ";
        m_descrption += (gun_steel->get_quality + " and " +
                         gun_glass->get_opacity + "!");
    }
    std::string get_description(){
        return m_description;
    }
    private:
    std::string m_description;
}
class Factory{
    public:
        //factory methods
        virtual Steel* makeSteel() const{
            return new Steel("nice steel");
        }
        virtual Glass* makeGlass() const{
            return new Glass("dark glass");
        }
        virtual Gun* makeGuns() const{
            Steel* mySteel = makeSteel();
            Glass* myGlass = makeGlass();
            return new Gun(mySteel, myGlass);
        }
};
class SugoiFactory : public Factory{
    public:
    //creating a whole new factory method for a new product!
    virtual Steel* makeSteel() const{
        return new Steel("thousand folded steel");
    }
};

int main(){
    Gun* ourGun;
    //what our normal factory just produces a nice gun
    Factory myFact;
    ourGun = myFact.make_guns();
    ourGun->get_description();
    delete ourGun;

    //now lets see our advanced factory's production
    SugoiFactory wowFact;
    ourGun = wowFact.make_guns();
    ourGun->get_description();
    delete ourGun;

    return 0;
}
