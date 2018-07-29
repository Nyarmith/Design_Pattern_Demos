
class Monster{
    public:
    virtual void attack(Player &x) = 0;
    virtual void move() = 0;
    private:
    int m_attack;
    int m_speed;
    int m_position;
}
