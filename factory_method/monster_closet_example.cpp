#include <iostream>
#include <stdio.h>
#include <string>
void output(std::string in="\n"){
    std::cout<<in;
}
void combat_message(std::string a, int b, std::string c){
    output(a+std::to_string(b)+c); output();
}

//our base abstract class
class Monster{
    public:
        virtual void attack_player()=0;
        virtual void move()=0;
        virtual ~Monster(){};
    protected:
        int m_power;
        int m_speed;
};

class Undead : public Monster{
    public:
        Undead(){
            m_power=15;
            m_speed=2;
        }
    protected:
        void attack_player(){
            combat_message("Zombie hits player for ", m_power, "damage!");
        }
        void move(){
            combat_message("Zombie shambles ", m_speed, "paces!");
        }
};

class Cabbage : public Monster{
    public:
        Cabbage(){
            m_power=5;
            m_speed=20;
            m_elevation=0;
        }
        void attack_player(){
            combat_message("Cabbage smacks into player for ", m_power, " damage!");
        }
        void move(){
            //Cabbage flies
            m_elevation += m_speed/2;
            combat_message("Cabbage zooms ", m_speed, " paces!");
        }
    protected:
        int m_elevation;
};

class Closet{
    public:
        //factory method
        Monster* spawn_monster(){
            int seed = rand()%2;
            switch(seed){
            case 1: return new Undead;
                    break;
            case 0: return new Cabbage;
                    break;
            }
        }
};

//test out the closet
int main(){
    Monster *chum;  //pointer of the base type
    Closet corridor_closet;
    for (int i=0; i<10; i++){
        chum = corridor_closet.spawn_monster();
        chum->attack_player();
        delete chum;
    }
    return 0;
}
