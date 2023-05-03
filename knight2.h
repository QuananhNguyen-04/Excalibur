#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

#define debug(x) cerr << #x << ": [" << x << "]" << endl;
#define LancelotDmg 0.05
#define PaladinDmg 0.06
#define DragonDmg 0.075
bool isPrime(int n);
bool isPythagoras(int n);

enum ItemType {ANTIDOTE = -1, PHOENIX, PHOENIX1, PHOENIX2 = 112, PHOENIX3, PHOENIX4, SHIELD = 95, SPEAR, HAIR, SWORD};
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
    KnightType knightType;
    BaseBag * bag;
    double Dmg;
public:
    int status = 1; // 1: normal, -1: poisoned
    virtual ~BaseKnight();
    static BaseKnight * create(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote);
    string toString() const;
    bool revive();
    virtual bool fight(BaseOpponent * opponent, int type, int * itemList) = 0;
    KnightType returnType() {
        return knightType;
    }
    void updateInfo(int * itemList);
    pair<int, int> getHP_maxHP() {
        return {hp, maxhp};
    }
    void usePhoenix(int hp) {
        this->hp = min(max(hp + this->hp, hp), maxhp);
    }
};

class Paladin: public BaseKnight {
public: 
    Paladin() {
        this->knightType = PALADIN;
        this->Dmg = PaladinDmg;
    }
    ~Paladin();
    bool fight(BaseOpponent * opponent, int type, int * itemList);
};
class Lancelot: public BaseKnight {
public:
    Lancelot() {
        this->knightType = LANCELOT;
        this->Dmg = LancelotDmg;
    }
    ~Lancelot();
    bool fight(BaseOpponent * opponent, int type, int * itemList);
};
class Dragon: public BaseKnight {
public:
    Dragon() {
        this->knightType = DRAGON;
        this->Dmg = DragonDmg;
    }
    ~Dragon();
    bool fight(BaseOpponent * opponent, int type, int * itemList);
};
class Normal: public BaseKnight {
public:
    Normal() {
        this->knightType = NORMAL;
        this->Dmg = 0;
    }
    ~Normal();
    bool fight(BaseOpponent * opponent, int type, int * itemList);
};

class BaseItem {
protected:
public:
    virtual ItemType type() = 0;
    virtual string getClass() = 0;
    virtual ~BaseItem() {}
    int hp, maxhp;
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
    void init(BaseKnight * knight);
};

class Antidote : public BaseItem {
public:
    Antidote() {}
    ItemType type();
    string getClass();
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
    ~Antidote();
};
class PhoenixI : public BaseItem {
public:
    ItemType type();
    string getClass();
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
    ~PhoenixI();
};
class PhoenixII : public BaseItem {
public:
    ItemType type();
    string getClass();
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
    ~PhoenixII();
};
class PhoenixIII : public BaseItem {
public:
    ItemType type();
    string getClass();
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
    ~PhoenixIII();
};
class PhoenixIV : public BaseItem {
public:
    ItemType type();
    string getClass();
    bool canUse(BaseKnight * knight);
    void use(BaseKnight * knight);
    ~PhoenixIV();
};

class Node {
public:
    BaseItem * item = nullptr;
    Node * next;
    Node() {
        this->next = nullptr;
    }
    Node(BaseItem * item, Node * ptrNext = nullptr) {
        this->item = item;
        this->next = ptrNext;
    }
    ~Node() {
        next = nullptr;
        delete item;
    }
};
class List {
private:
    Node * headNode = nullptr;
public: 
    int contain = 0;
    int maxSize;
    List() {}
    ~List();
    bool isFull();
    void insertFirst(BaseItem * item);
    string toString() const;
    void remove (int n);
    pair<BaseItem*, int> search(ItemType item, int startPos = 0);
};

class BaseBag {
public:
    BaseBag() {}
    virtual ~BaseBag() {}
    int maxSize;
    List listOfItems;
    void drop(int num, int pos);
    virtual bool insertFirst(BaseItem * item) = 0;
    virtual BaseItem * get(ItemType item) = 0;
    virtual string toString() const = 0;
};

class PaladinBag: public BaseBag {
private:
    const int Size = 5000;
public:
    PaladinBag(int p1, int anti);
    ~PaladinBag() {}
    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    string toString() const;
};
class LancelotBag: public BaseBag {
private:
    const int Size = 16;
public:
    LancelotBag(int p1, int anti);
    ~LancelotBag() {}
    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    string toString() const;
};
class DragonBag: public BaseBag {
private:
    const int Size = 14;
public:
    DragonBag(int p1);
    ~DragonBag() {}
    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    string toString() const;
};
class NormalBag: public BaseBag {
private:
    const int Size = 19;
public:
    NormalBag(int p1, int anti);
    ~NormalBag() {}
    bool insertFirst(BaseItem * item);
    BaseItem * get(ItemType itemType);
    string toString() const;
};

class BaseOpponent {
protected: 
    int hp = 0;
    int i;
    OpponentType id;
    int BaseDamage = 0;
    int gilGain = 0;
    int hpLose = 0;
    int gilTable[6] = {0,100,150,450,750,800};
    int baseDmg[6] = {0, 10, 15, 45, 75, 95};
public:
    int klevel;
    int levelO;
    BaseOpponent * create(int i, int id);
    ~BaseOpponent() {}
    bool result();
    void dmg();
    OpponentType type();
    void init(int i, int id);
    int gethp() {
        return hp;
    }
    void hpRemain(int dmg) {
        this->hp -= dmg;
    }
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
    }
    ~MadBear(){};
};
class Bandit: public BaseOpponent {
public: 
    Bandit(int i, int id) {
        init(i, id);
    }
    ~Bandit(){};
};
class LordLupin: public BaseOpponent {
public: 
    LordLupin(int i, int id) {
        init(i, id);
    }
    ~LordLupin(){};
};
class Elf: public BaseOpponent {
public: 
    Elf(int i, int id) {
        init(i, id);
    }
    ~Elf(){};
};
class Troll: public BaseOpponent {
public:
    Troll(int i, int id) {
        init(i, id);
    }
    ~Troll(){};
};
class Tornbery: public BaseOpponent {
public: 
    Tornbery(int i, int id) {
        init(i, id);
    }
    ~Tornbery(){};
    int lose() {
        return 10;
    }
};
class Queen: public BaseOpponent {
public: 
    Queen(int i, int id) {
        init(i, id);
    }
    ~Queen(){};
};
class Nina: public BaseOpponent {
public: 
    Nina(int i, int id) {
        init(i, id);
    }
    ~Nina(){};
};
class Durian: public BaseOpponent {
public: 
    Durian(int i, int id) {
        init(i, id);
    }
    ~Durian(){};
};
class Omega: public BaseOpponent {
public: 
    Omega(int i, int id) {
        init(i, id);
    }
    ~Omega(){};
};
class Hades: public BaseOpponent {
public: 
    Hades(int i, int id) {
        init(i, id);
    }
    ~Hades(){};
};
class Ultimecia: public BaseOpponent {
public:
    Ultimecia(int i, int id) {
        init(i, id);
        this->hp = 5000;
    } 
    ~Ultimecia(){};
};
class ArmyKnights {
private:
    BaseKnight ** KnightList;
    BaseKnight ** tempList;
    BaseKnight * last;
    int numsOfKnights;
    int *itemList; // ANTIDOTE, PHOENIX1, PHOENIX2, PHOENIX3, PHOENIX4, GIL
    bool calledTemp = 0;
    bool PaladinShield = 0;
    bool LancelotSpear = 0;
    bool GuinevereHair = 0;
    bool ExcaliburSword = 0;
    bool isMeetHades = 0;
    bool isMeetOmega = 0;
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights() {
        for (int i = 0; i < numsOfKnights; ++i) {
            delete KnightList[i];
        }
        if (!calledTemp) {
            delete []KnightList;
        } 
        // else delete []tempList;
    }
    void fight(BaseOpponent * opponent, int type, int * itemList);
    
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;
    void getSpecialItem(int event);
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
        delete []list;
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
        delete army;
        delete events;
    };
    void loadArmyKnights(const string & fileArmy);
    void loadEvents(const string & fileEvent);
    void run();
};

#endif // __KNIGHT2_H__