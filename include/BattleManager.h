// Describes result of the battle
enum BattleOutcome { WIN, FLEE, DEATH, ONGOING };

//Character stub, put in test file soon
class Character
{
    public:
        Character(int h, int s, int atk, int dfs, int dex)
        : hp(h) , sp(s), attack(atk), defense(dfs), dexterity(dex)
        {}

        int get_hp() { return hp; }
        int get_sp() { return sp; }
        int get_attack() { return attack; }
        int get_defense() { return defense; }
        int get_dexterity()  { return dexterity; }

        void heal(int amount) { hp = hp + amount; }
        void take_damage(int amount) { hp = hp - amount; }

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

        void battle();
        void chooseAction();
        bool determineAttackSuccess();
        void dealDamage();
        void displayAttack();
        BattleOutcome getBattleOutcome();

    private:
        Character& player;
        Character& enemy;
        BattleOutcome result;
};

