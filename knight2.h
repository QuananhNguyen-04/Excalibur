#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

#define debug(x) cerr << #x << ": [" << x << "]" << endl;

bool isPrime(int n);
bool isPythagoras(int n);

enum ItemType {ANTIDOTE, PHOENIX1, PHOENIX2 = 112, PHOENIX3, PHOENIX4, SHIELD = 95, HAIR, SWORD};
enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
enum OpponentType {MADBEAR = 1, BANDIT, LORDLUPIN, ELF, TROLL, TORNBERY, QUEEN, NINA, DURIAN, OMEGA, HADES, ULTIMECIA = 99};

// struct List {
//     head;

// };

// class BaseBag {
// public:
//     virtual bool insertFirst(BaseItem * item);
//     virtual BaseItem * get(ItemType itemType);
//     virtual string toString() const;
// };

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
    int remainGil(int gilGain) {
        if (gil + gilGain >= 999) {
                gilGain -= (999 - gil);
                gil = 999;
            }
        else {
            gil += gilGain;
            gilGain = 0;
        }
        this->gil = gil;
        return gilGain;
    }
    int fight(BaseOpponent * opponent);
};

inline string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id: " + to_string(id) 
        + ", hp: " + to_string(hp) 
        + ", maxhp: " + to_string(maxhp)
        + ", level: " + to_string(level)
        + ", gil: " + to_string(gil)
        // + bag->toString()
        + ", knight_type: " + typeString[knightType]
        + "]"; // added '\n' & ' ' per var
    return s;
}

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
    void init() {
        this->BaseDamage = baseDmg[id];
        this->gilGain = gilTable[id];
        this->levelO = (i + id) % 10 + 1;
    }
    ~BaseOpponent() {}
    bool result() {
        if (levelO > klevel) return 0;
        return 1;
    }
    void dmg() {
        hpLose = BaseDamage * (levelO - klevel);
    }
    int reward() {
        return gilGain;
    }
    int lose() {
        dmg();
        return hpLose;
    }
};

class MadBear: public BaseOpponent {
public: 
    MadBear()  {
        init();
    }
};
class Bandit: public BaseOpponent {
public: 
    Bandit() {
        init();
    }
};
class LordLupin: public BaseOpponent {
public: 
    LordLupin() {
        init();
    }
};
class Elf: public BaseOpponent {
public: 
    Elf() {
        init();
    }
};
class Troll: public BaseOpponent {
public:
    Troll() {
        init();
    }
};
class Tornbery: public BaseOpponent {
public: 
    Tornbery() {
        init();
    }
};
class Queen: public BaseOpponent {
public: 
    Queen() {
        init();
    }
};
class Nina: public BaseOpponent {
public: 
    Nina() {
        init();
    }
};
class Durian: public BaseOpponent {
public: 
    Durian() {
        init();
    }
};
class Omega: public BaseOpponent {
public: 
    Omega() {
        init();
    }
};
class Hades: public BaseOpponent {
public: 
    Hades() {
        init();
    }
};

inline BaseOpponent * BaseOpponent::create(int i, int id) {
    this->i = i;
    this->id = static_cast<OpponentType> (id);
    BaseOpponent * opponent = new BaseOpponent;
    switch (id) {
    case MADBEAR: {
        opponent = new MadBear;
        break;
    }
    case BANDIT: {
        opponent = new Bandit;
        break;
    }
    case LORDLUPIN: {
        opponent = new LordLupin;
        break;
    }
    case ELF: {
        opponent = new Elf;
        break;
    }
    case TROLL: {
        opponent = new Troll;
        break;
    }
    case TORNBERY: {
        opponent = new Tornbery;
        break;
    }
    case QUEEN: {
        opponent = new Queen;
        break;
    }
    case NINA: {
        opponent = new Nina;
        break;
    }
    case DURIAN: {
        opponent = new Durian;
        break;
    }
    case OMEGA: {
        opponent = new Omega;
        break;
    }
    case HADES: {
        opponent = new Hades;
        break;
    }
    default:
        break;
    }
    return opponent;
}
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
    void fight(BaseOpponent * opponent) {
        int temp = last->fight(opponent);
        if (temp > 0) {
            for (int i = numsOfKnights - 2; i >= 0; --i) {
                temp = KnightList[i]->remainGil(temp);
            }
        }
    }
    
    bool adventure (Events * events);
    int count() const {
        return numsOfKnights;
    }
    BaseKnight * lastKnight() const {
        return last;
    }

    bool hasPaladinShield() const {
        return PaladinShield;
    }
    bool hasLancelotSpear() const {
        return LancelotSpear;
    }
    bool hasGuinevereHair() const {
        return GuinevereHair;
    }
    bool hasExcaliburSword() const {
        return ExcaliburSword;
    }
    
    void printInfo() const;
    void printResult(bool win) const;
};

inline ArmyKnights::ArmyKnights(const string & file_armyknights) {
    ifstream inFile(file_armyknights);
    string num; getline(inFile, num);
    this->numsOfKnights = stoi(num);
    KnightList = new BaseKnight* [numsOfKnights];
    for (int i = 0; i < numsOfKnights; ++i) {
        string knightInfo; getline(inFile, knightInfo);
        stringstream ss(knightInfo);
        int info[5];
        for (int j = 0; j < 5; ++j) {
            ss >> info[j];
        }
        KnightList[i] = BaseKnight::create(i + 1, info[0], info[1], info[2], info[3], info[4]);
    }
    this->last = KnightList[numsOfKnights - 1];
    inFile.close();
}


inline void ArmyKnights::printInfo() const {
    for (int i = 0; i < numsOfKnights; ++i) {
        cout << KnightList[i]->toString() << endl;
    }
    // cout << lastKnight() -> toString();
}

// class BaseItem {
// public:
//     virtual bool canUse ( BaseKnight * knight ) = 0;
//     virtual void use ( BaseKnight * knight ) = 0;
// };

// void BaseItem::use(BaseKnight * knight) {
    
// }
class Events {
private: 
    int numsOfEvents;
    int * list;
public:
    Events(const string & fileEvents) {
        ifstream inFile(fileEvents);
        string tmp;
        getline(inFile, tmp);
        this->numsOfEvents = stoi(tmp);
        list = new int[numsOfEvents];
        getline(inFile, tmp);
        stringstream ss(tmp);
        for (int i = 0; i < numsOfEvents; ++i) {
            ss >> list[i];
        }
        inFile.close();
    }
    ~Events() {
        delete list;
    }
    int count() const {
        return numsOfEvents;
    }
    int get(int i) const {
        return list[i];
    }
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

    void loadArmyKnights(const string & fileArmy) {
        army = new ArmyKnights(fileArmy);
    }
    void loadEvents(const string & fileEvent) {
        events = new Events(fileEvent);
    }
    void run() {
        army->adventure(events);
    }
};

#endif // __KNIGHT2_H__