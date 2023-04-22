#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

#define debug(x) cerr << #x << ": [" << x << "]" << endl;

bool isPrime(int n);
bool isPythagoras(int n);

enum ItemType {ANTIDOTE = -1, PHOENIX, PHOENIX1, PHOENIX2 = 112, PHOENIX3, PHOENIX4, SHIELD = 95, HAIR, SWORD};
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
enum OpponentType {MADBEAR = 1, BANDIT, LORDLUPIN, ELF, TROLL, TORNBERY, QUEEN, NINA, DURIAN, OMEGA, HADES, ULTIMECIA = 99};

class BaseItem;
class Node {
private: 
    int numsOfNode = 0;
    Node * headNode = NULL;
    bool canAdd() {
        if (defaultSize <= numsOfNode) {
            return 0;
        }
        return 1;
    }
public:
    int defaultSize;
    BaseItem * Item;
    Node * next;

    Node(BaseItem * item, Node * nextptr = NULL) {
        this->Item = item;
        this->next = nextptr;
    }
    ~Node() {
        delete Item;
        delete next;
    }
    bool insertFirst(Node * item) {
        if (!canAdd()) return 0;
        item->next = this;
        this->numsOfNode ++;
        headNode = item;
        return 1;
    }
    Node * deleteNode() {
        Node * tempNode = this;
        this->next = headNode->next;
        headNode->next = tempNode->next;
        
    }
    int count() {
        return numsOfNode;
    }
    BaseItem * get(ItemType ItemType) {
        for (Node * i = this; i != NULL; i = i->next) {
            if (i->Item->type() == ItemType) {
                return i->Item;
            }
        }
        return NULL;
    }
    void toString() {
        string tmp = "";
        for (Node * i = headNode; i != NULL; i = i->next) {
            tmp += i->Item->getClass();
            if (i->next != NULL) {
                tmp += ",";
            }
        }
        string s = "";
        s = s + "Bag[" + "count=" + to_string(numsOfNode) + ";" + tmp + "]";
        cout << s;
    }

};

class BaseBag {
public:
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
};
class BaseOpponent;
class Events;
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    // BaseBag * bag;
    KnightType knightType;

public:
    int status = 1; // 1: normal, -1: 
    BaseKnight() {}
    static BaseKnight * create(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote){
        BaseKnight *knight = new BaseKnight;
        knight -> id = id;
        knight -> hp = maxhp;
        knight -> maxhp = maxhp;
        knight -> level = level;
        knight -> gil = gil;
        knight -> antidote = antidote;
        // knight -> bag = new BaseBag[5];
        if (isPrime(maxhp)) {knight -> knightType = PALADIN;}
        else if (maxhp == 888) knight -> knightType = LANCELOT;
        else if (isPythagoras(maxhp)) knight -> knightType = DRAGON;
        else knight -> knightType = NORMAL;
        return knight;
    }
    string toString() const;
    bool revive(){return 1;}
    int remainGil(int gilGain);
    int fight(BaseOpponent * opponent);
    pair<int, int> getHP_maxHP() {
        return {hp, maxhp};
    }
    void usePhoenix(int hp) {
        this->hp = hp;
    }
};

class BaseOpponent {
protected: 
    int levelO;
    int i;
    OpponentType id;
    int BaseDamage;
    int gilGain;
    int hpLose;
    int gilTable[6] = {0,100,150,450,750,800};
    int baseDmg[6] = {0, 10, 15, 45, 75, 95};
public:
    int klevel;
    BaseOpponent * create(int i, int id);
    ~BaseOpponent() {}
    bool result();
    void dmg();
    void init(int i, int id);
    virtual int reward() {
        return gilGain;
    }
    virtual int lose() {
        dmg();
        return hpLose;
    }
};

class MadBear: public BaseOpponent {
public: 
    MadBear(int i, int id)  {
        init(i, id);
        // debug(gilGain);
    }
};
class Bandit: public BaseOpponent {
public: 
    Bandit(int i, int id) {
        init(i, id);
    }
};
class LordLupin: public BaseOpponent {
public: 
    LordLupin(int i, int id) {
        init(i, id);
    }
};
class Elf: public BaseOpponent {
public: 
    Elf(int i, int id) {
        init(i, id);
    }
};
class Troll: public BaseOpponent {
public:
    Troll(int i, int id) {
        init(i, id);
    }
};
class Tornbery: public BaseOpponent {
public: 
    Tornbery(int i, int id) {
        init(i, id);
    }
    int reward();
};
class Queen: public BaseOpponent {
public: 
    Queen(int i, int id) {
        init(i, id);
    }
};
class Nina: public BaseOpponent {
public: 
    Nina(int i, int id) {
        init(i, id);
    }
};
class Durian: public BaseOpponent {
public: 
    Durian(int i, int id) {
        init(i, id);
    }
};
class Omega: public BaseOpponent {
public: 
    Omega(int i, int id) {
        init(i, id);
    }
};
class Hades: public BaseOpponent {
public: 
    Hades(int i, int id) {
        init(i, id);
    }
};
class ArmyKnights {
private:
    BaseKnight ** KnightList;
    BaseKnight * last;
    int numsOfKnights;
    bool PaladinShield;
    bool LancelotSpear;
    bool GuinevereHair;
    bool ExcaliburSword;
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights() {
        delete []KnightList;
        delete last;
    }
    void fight(BaseOpponent * opponent);
    
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;
    
    void printInfo() const;
    void printResult(bool win) const;
};

inline void ArmyKnights::printInfo() const {
    for (int i = 0; i < numsOfKnights; ++i) {
        cout << KnightList[i]->toString() << endl;
    }
    // cout << lastKnight() -> toString();
}

class BaseItem {
public:
    virtual ItemType type() {
        return PHOENIX;
    }
    virtual string getClass() = 0;
    int hp, maxhp;
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    void init(BaseKnight * knight);
};

class Antidote : public BaseItem {
public:
    ItemType type() {
        return ANTIDOTE;
    }
    string getClass() {
        return "Antidote";
    }
    bool canUse(BaseKnight * knight) {
        return 1;
    }
    void use(BaseKnight * knight) {
        knight->status = 1;
    }
};
class PhoenixI : public BaseItem {
public:
    ItemType type() {
        return PHOENIX1;
    }
    bool canUse(BaseKnight * knight) {
        init(knight);
        if (hp <= 0) return 1;
        return 0;
    }
    string getClass() {
        return "PhoenixI";
    }
    void use(BaseKnight * knight) {
        knight->usePhoenix(maxhp);
    }
};
class PhoenixII : public BaseItem {
public:
    ItemType type() {
        return PHOENIX2;
    }
    bool canUse(BaseKnight * knight) {
        init(knight);
        if (hp < maxhp / 4) return 1;
        return 0;
    }
    void use(BaseKnight * knight) {
        knight->usePhoenix(maxhp);
    }
    string getClass() {
        return "PhoenixII";
    }
};
class PhoenixIII : public BaseItem {
public:
    ItemType type() {
        return PHOENIX3;
    }
    bool canUse(BaseKnight * knight) {
        init(knight);
        if (hp < maxhp / 3) return 1;
        return 0;
    }
    void use(BaseKnight * knight) {
        if (hp <= 0) knight->usePhoenix(maxhp / 3);
        else knight->usePhoenix(maxhp / 4);
    }
    string getClass() {
        return "PhoenixIII";
    }
};
class PhoenixIV : public BaseItem {
public:
    ItemType type() {
        return PHOENIX4;
    }
    bool canUse(BaseKnight * knight) {
        init(knight);
        if (hp < maxhp / 2);
    }
    void use(BaseKnight * knight) {
        if (hp <= 0) knight->usePhoenix(maxhp / 2);
        else knight->usePhoenix(maxhp / 5);
    }
    string getClass() {
        return "PhoenixIV";
    }
};
class Events {
private: 
    int numsOfEvents;
    int * list;
public:
    Events(const string & fileEvents);
    ~Events() {
        delete list;
    }
    int count() const;
    int get(int i) const;
};

class KnightAdventure {
private:
    ArmyKnights * army;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure() {
        army->~ArmyKnights();
        events->~Events();
    };
    void loadArmyKnights(const string & fileArmy);
    void loadEvents(const string & fileEvent);
    void run();
};

#endif // __KNIGHT2_H__