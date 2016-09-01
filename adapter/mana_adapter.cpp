#include <iostream>
#include <cmath>
using namespace std;

class AncientMana{
    public:
    AncientMana(int depth){
        m_mana = depth;
    }
    //ugh, why did the ancients have so
    //many parameters for their magic?
    int ancientIncantation(int focus, double nature_energy,
                           int protagonist_power, int distractions){
        return (m_mana+focus*nature_energy*protagonist_power)/distractions;
    }
    private:
    int m_mana;
};

//the standard for how everyone casts magic
class Mana{
    public:
        virtual int cast(int power, int nature_energy)=0;
};

class AncientManaAdapter : public AncientMana, public Mana{
    public:
    //area has become the default measure of mana
    AncientManaAdapter(int area):AncientMana(sqrt(area)){
    }
    //nowadays heroes just specify their power and nature energy
    int cast(int power, int nature_energy){
        return ancientIncantation(1,nature_energy,power,1);
    }
};

int main(){
    Mana * dank_mana_pool = new AncientManaAdapter(36);
    //so modern!!
    cout << dank_mana_pool->cast(100,100);
}
