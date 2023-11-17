//Character stub, put in test file soon
class Character
{
    public:
        Character(int h, int s, int atk, int dfs, int dex)
        : hp(h) , sp(s), attack(atk), defense(dfs), dexterity(dex)
        {}

        int getHP() { return hp; }
        int getSP() { return sp; }
        int getAttack() { return attack; }
        int getDefense() { return defense; }
        int getDexterity()  { return dexterity; }

        void heal(int amount) { hp = hp + amount; }
        void takeDamage(int amount) { hp = hp - amount; }

    private:
        int hp;
        int sp;
        int attack;
        int defense;
        int dexterity;
};