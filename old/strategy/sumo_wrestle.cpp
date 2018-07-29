#include <iostream>
#include <string>
using namespace std;

void output(string in){
    cout << in << endl;
}

class Sumo_Move{
    public:
    virtual int attack(int enemies)=0;
};

class Palm_Blast : public Sumo_Move{
    int attack(int enemies){
        output("Wrestler contentrates four men's worth of force in their palm, releasing a blast of power!");
        return (enemies-4);
    }
};

class Body_Slam : public Sumo_Move{
    int attack(int enemies){
        output("Wrestler slams their momentum into the enemy, halving the opponents standing!!");
        return (enemies/2);
    }
};

class o_soto_gari : public Sumo_Move{
    int attack(int enemies){
        output("Wrestler gallatnly flips the enemies on their backs, leaving them dazed!");
        return (2*enemies/5);
    }
};

class Sumo_Wrestler{
    public:
        int fight_enemies(int num_enemies){
            while(num_enemies > 0) {
                    num_enemies = m_strategy->attack(num_enemies);
            }
            return 0;
        }
        void set_fighting_style(Sumo_Move * fighting_style){
            m_strategy = fighting_style;
        }
    private:
        Sumo_Move * m_strategy;
};

int main(){
    //you can set strategy depending on number of enemies
    Sumo_Wrestler Taro;
    Taro.set_fighting_style(new Body_Slam);
    int enemies = 3;

    Taro.fight_enemies(enemies);    //defeats them in two iterations

    Taro.set_fighting_style(new Palm_Blast);
    Taro.fight_enemies(enemies);    //defeats them in one!

    return 0;
}
