class Undead : Monster {
    public:
        virtual void attack(Player &x){
            x.health -= m_attack;
        };

        virtual void move(){
            m_position += m_speed;
        };
    private:
        int m_decay;
}
