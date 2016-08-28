
class Undead : Monster {
    public:
        virtual void attack(Player &x){
            x.health += m_attack;
        };

        virtual void move(){
            //cabbage flies
            m_position += m_speed;
            m_elavation += m_speed/2;
        };
    private:
        int m_elavation;
}
