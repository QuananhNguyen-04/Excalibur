#include <bits/stdc++.h>

using namespace std;

class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    // BaseBag * bag;
    // KnightType knightType;
    
public:
    BaseKnight() {}
    static BaseKnight * create(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote){
        BaseKnight * knight = new BaseKnight;
        knight -> id = id;
        knight -> hp = maxhp;
        knight -> maxhp = maxhp;
        knight -> level = level;
        knight -> gil = gil;
        knight -> antidote = antidote;
        return knight;
    };
    ~BaseKnight() {
    }
    string toString() const;
};

string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id: " + to_string(id) 
        + " hp: " + to_string(hp) 
        + " maxhp: " + to_string(maxhp)
        + " level: " + to_string(level)
        + " gil: " + to_string(gil)
        // + bag->toString()
        // + "knight_type:" + typeString[knightType]
        + "]";
    return s;
}

class ArmyKnights {
private:
public:
    int numsOfKnights;
    BaseKnight * knights;
    ArmyKnights(const string &file_armyknights);
    ~ArmyKnights() {
        delete knights;
    }
    void ListedKnights();

};

ArmyKnights::ArmyKnights (const string & file_armyknights) {
    ifstream inFile(file_armyknights);
    string tmp; getline(inFile, tmp);
    this->numsOfKnights = stoi(tmp);
    // init knights
    knights = new BaseKnight[numsOfKnights];
    for (int i = 0; i < numsOfKnights; ++i) {
        string knightInfo; getline(inFile, knightInfo);
        stringstream ss(knightInfo);
        int info[5];
        for (int j = 0; j < 5; ++j) {
            ss >> info[j];
        }
        knights[i].create(i + 1, info[0], info[1], info[2], info[3], info[4]);
        // cout << knightInfo << endl;
    }
}

void ArmyKnights::ListedKnights() {
    for (int i = 0; i < numsOfKnights; ++i) {
        cout << knights[i].toString() << endl;
    }
}

class Events {
private: 
    int numsOfEvents;
    int * list;
public:
    Events(const string & fileEvents) {
        ifstream inFile(fileEvents);
        string tmp;
        getline(inFile, tmp);
        numsOfEvents = stoi(tmp);
        list = new int[numsOfEvents];
        getline(inFile, tmp);
        stringstream ss(tmp);
        for (int i = 0; i < numsOfEvents; ++i) {
            ss >> list[i];
        }
        inFile.close();
    }
    ~Events() {
        delete[] list;
    }
    int count() const {
        return numsOfEvents;
    }
    int get(int i) const {
        return list[i];
    }
};

class Adventure {
private:
    ArmyKnights *army;
    Events * events; 
public:
    Adventure() {
        army = nullptr;
        events = nullptr;
    }
    ~Adventure() {
        army->~ArmyKnights();
        events->~Events();
    }
    void loadArmy(const string & fileArmy) {
        army = new ArmyKnights(fileArmy);
    }
    void loadEvents(const string & fileEvents) {
        events = new Events(fileEvents);
    }
    void run() {
        for (int i = 0; i < events->count(); ++i) {
            cout << events->get(i) << endl;
            army->ListedKnights();
        }
    }
};

enum OpponentType {MADBEAR = 1, BANDIT, LORDLUPIN, ELF, TROLL, TORNBERY, QUEEN, NINA, DURIAN, OMEGA, HADES, ULTIMECIA = 99};
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
        BaseDamage = baseDmg[id];
        gilGain = gilTable[id];
        levelO = (i + id) % 10 + 1;
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

BaseOpponent * BaseOpponent::create(int i, int id) {
    this->i = i;
    this->id = static_cast<OpponentType> (id);
    BaseOpponent * opponent = nullptr;
    switch (id) {
    case MADBEAR: {
        opponent = new MadBear;
        break;
    }
    case BANDIT: {
        opponent = new Bandit;
        break;
    }
    
    default:
        cout << "not opponent\n"; 
        break;
    }
    return opponent;
}
int main() {
    string file1 = "tc1_armyknights", file2 = "tc1_events";
    // Adventure * adventure = new Adventure();
    // adventure->loadArmy(file1);
    // adventure->loadEvents(file2);
    // adventure->run();
    // adventure->~Adventure();
    Events * events = new Events(file2);
    for (int i = 0; i < events->count(); ++i) {
        int event = events->get(i);
        cout << event << ": \n";
        BaseOpponent * opponent;
        switch (event)
        {
        case 1 ... 11: {
            opponent = new Bandit;
            opponent->create(i, event);
            // fight(opponent);
            delete opponent;
            break;
        }
        default:
            break;
        }
    }
}