#include "knight2.h"

bool BaseOpponent::result() {
    if (levelO > klevel) return 0;
    return 1;
}
void BaseOpponent::dmg() {
    hpLose = BaseDamage * (levelO - klevel);
}
BaseOpponent * BaseOpponent::create(int i, int id) {
    BaseOpponent * opponent = nullptr;
    switch (id) {
    case MADBEAR: {
        opponent = new MadBear(i, id);
        break;
    }
    case BANDIT: {
        opponent = new Bandit(i, id);
        break;
    }
    case LORDLUPIN: {
        opponent = new LordLupin(i, id);
        break;
    }
    case ELF: {
        opponent = new Elf(i, id);
        break;
    }
    case TROLL: {
        opponent = new Troll(i, id);
        break;
    }
    case TORNBERY: {
        opponent = new Tornbery(i, id);
        break;
    }
    case QUEEN: {
        opponent = new Queen(i, id);
        break;
    }
    case NINA: {
        opponent = new Nina(i, id);
        break;
    }
    case DURIAN: {
        opponent = new Durian(i, id);
        break;
    }
    case OMEGA: {
        opponent = new Omega(i, id);
        break;
    }
    case HADES: {
        opponent = new Hades(i, id);
        break;
    }
    default:
        break;
    }
    return opponent;
}
void BaseOpponent::init(int i, int id) {
    this->i = i;
    this->id = static_cast<OpponentType> (id);
    this->BaseDamage = baseDmg[id];
    this->gilGain = gilTable[id];
    this->levelO = (i + id) % 10 + 1;
}
int Tornbery::reward() {
    return 1;
}


void BaseItem::init(BaseKnight * knight) {
        pair<int, int> info = knight->getHP_maxHP();
        this->hp = info.first;
        this->maxhp = info.second;
    }


/* * * BEGIN implementation of class BaseBag * * */

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
bool isPrime(int n) {
    if (n < 2) return 0;
    for (int i = 2; i < n; ++i) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}
bool isPythagoras(int n) {
    if (int(log10(n) + 1) != 3) return 0;
    int a = n % 10; n /= 10;
    int b = n % 10; n /= 10;
    int c = n % 10; n /= 10;
    int sum = a + b + c, hypo= max(a, max(b, c)), sqEdge = min(a, min(b, c)); // hypotenuse
    if (hypo * hypo == sqEdge * sqEdge + pow (sum - hypo - sqEdge, 2)) {
        return 1;
    }
    return 0;
}
int BaseKnight::remainGil(int gilGain) {
        if (gil + gilGain >= 999) {
                gilGain -= (999 - gil);
                gil = 999;
            }
        else {
            gil += gilGain;
            gilGain = 0;
        }
        this->gil = gil;
        // debug(gilGain);
        return gilGain;
    }
int BaseKnight::fight(BaseOpponent * opponent) {
    int gilGain;
    opponent->klevel = level;
        if (opponent->result()) {
            gilGain = opponent->reward();
            // debug(gilGain);
            return remainGil(gilGain);
        }
        else {
            hp -= opponent->lose();
            if (!revive()) return -1;
        }
        return 0;
}
string BaseKnight::toString() const {
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

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string & file_armyknights) {
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
void ArmyKnights::fight(BaseOpponent * opponent) {
        int temp = last->fight(opponent);
        debug(temp);
        if (temp > 0) {
            for (int i = numsOfKnights - 2; i >= 0; --i) {
                temp = KnightList[i]->remainGil(temp);
            }
        }
    }
int ArmyKnights::count() const {
        return numsOfKnights;
    }
bool ArmyKnights::adventure(Events * events) {
    for (int i = 0; i < events->count(); ++i) {
        int event = events->get(i);
        cout << event << ": \n";
        BaseOpponent * opponent = nullptr;
        switch (event)
        {
        case 1 ... 11: {
            BaseOpponent * tempOpponent = new BaseOpponent;
            opponent = tempOpponent->create(i, event);
            fight(opponent);
            delete tempOpponent;
            break;
        }
        default:
            break;
        }
        printInfo();
    }
    if (numsOfKnights > 0) return 1;
    return 0;
}
BaseKnight * ArmyKnights::lastKnight() const {
        return last;
    }
bool ArmyKnights::hasPaladinShield() const {
        return PaladinShield;
    }
bool ArmyKnights::hasLancelotSpear() const {
    return LancelotSpear;
}
bool ArmyKnights::hasGuinevereHair() const {
    return GuinevereHair;
}
bool ArmyKnights::hasExcaliburSword() const {
    return ExcaliburSword;
}
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string('-', 50) << endl;
}
void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

/* * * END implementation of class ArmyKnights * * */

Events::Events(const string & fileEvents) {
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
int Events::count() const {
        return numsOfEvents;
    }
int Events::get(int i) const {
    return list[i];
}

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    army = nullptr;
    events = nullptr;
}
void KnightAdventure::loadArmyKnights(const string & fileArmy) {
    army = new ArmyKnights(fileArmy);
}
void KnightAdventure::loadEvents(const string & fileEvent) {
    events = new Events(fileEvent);
}
void KnightAdventure::run() {
    army->adventure(events);
}

/* * * END implementation of class KnightAdventure * * */