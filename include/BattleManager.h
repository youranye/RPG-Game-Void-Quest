// Describes result of the battle
enum BattleOutcome { WIN, FLEE, DEATH, ONGOING };

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

class BattleManager
{
    public:
        BattleManager(Character& playerCharacter, Character& enemyCharacter)
            : player(playerCharacter), enemy(enemyCharacter), result(ONGOING)
        {}
        void runBattle();
        BattleOutcome getBattleOutcome();

    private:
        Character& player;
        Character& enemy;
        BattleOutcome result;

        void chooseAction();
        void attack(Character& attacker, Character& target);
        bool determineAttackSuccess(int successValue);
        void displayAttack(const Character& attacker, const Character& target, int success, int damage);
};

