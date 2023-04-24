#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

#define debug(x) cerr << #x << ": [" << x << "]" << endl;

bool isPrime(int n);
bool isPythagoras(int n);

enum ItemType {ANTIDOTE = -1, PHOENIX, PHOENIX1, PHOENIX2 = 112, PHOENIX3, PHOENIX4, SHIELD = 95, HAIR, SWORD};
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
enum OpponentType {MADBEAR = 1, BANDIT, LORDLUPIN, ELF, TROLL, TORNBERY, QUEEN, NINA, DURIAN, OMEGA, HADES, ULTIMECIA = 99};

class BaseBag;
class BaseItem;
class BaseOpponent;
class Events;
class BaseKnight;

class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    BaseBag * bag;
    KnightType knightType;

public:
    int status = 1; // 1: normal, -1: 
    BaseKnight() {}
    static BaseKnight * create(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote);
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

class Paladin: public BaseKnight {
public: 
    Paladin() {
        knightType = PALADIN;
    }
};
class Lancelot: public BaseKnight {

};
class Dragon: public BaseKnight {

};
class Normal: public BaseKnight {

};

class BaseItem {
protected:
public:
    virtual ItemType type() = 0;
    virtual string getClass() = 0;
    int hp, maxhp;
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    void init(BaseKnight * knight);
};

class Antidote : public BaseItem {
public:
    ItemType type();
    string getClass();
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};
class PhoenixI : public BaseItem {
public:
    ItemType type();
    string getClass();
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};
class PhoenixII : public BaseItem {
public:
    ItemType type();
    string getClass();
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};
class PhoenixIII : public BaseItem {
public:
    ItemType type();
    string getClass();
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};
class PhoenixIV : public BaseItem {
public:
    ItemType type();
    string getClass();
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
};

class Node {
public:
    BaseItem * item = nullptr;
    Node * next;
    Node(BaseItem * item, Node * ptrnext = nullptr) {
        this->item = item;
        this->next = ptrnext;
    }
    ~Node() {
        delete next;
        item->~BaseItem();
    }
};
class List {
private:
    Node * headNode = nullptr;
public: 
    int contain = 0;
    int maxSize;
    List() {}
    ~List() {
        delete headNode;
    }
    void insertFirst(BaseItem * item);
    string toString() const;
    void remove (int n);
    BaseItem * search(ItemType item);
};

class BaseBag {
public:
    BaseBag() {}
    int maxSize;
    List listOfItems;
    void drop(int num);
    virtual bool insertFirst(BaseItem * item) = 0;
    virtual BaseItem * get(ItemType item) = 0;
    virtual string toString() const = 0;
};

class PaladinBag: public BaseBag {
private:
    const int Size = 5000;
public:
    PaladinBag(int p1, int anti);
    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    string toString() const;
};
class LancelotBag: public BaseBag {
private:
    const int Size = 16;
public:
    LancelotBag(int p1, int anti);
    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    string toString() const;
};
class DragonBag: public BaseBag {
private:
    const int Size = 14;
public:
    DragonBag(int p1);
    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    string toString() const;
};
class NormalBag: public BaseBag {
private:
    const int Size = 19;
public:
    NormalBag(int p1, int anti);
    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    string toString() const;
};

class BaseOpponent;
class Events;

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