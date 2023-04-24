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

ItemType Antidote::type() {
    return ANTIDOTE;
}
string Antidote::getClass() {
    return "Antidote";
}
bool Antidote::canUse(BaseKnight * knight) {
    return 1;
}
void Antidote::use(BaseKnight * knight) {
    knight->status = 1;
}
ItemType PhoenixI::type() {
    return PHOENIX1;
}
bool PhoenixI::canUse(BaseKnight * knight) {
    init(knight);
    if (hp <= 0) return 1;
    return 0;
}
string PhoenixI::getClass() {
    return "PhoenixI";
}
void PhoenixI::use(BaseKnight * knight) {
    knight->usePhoenix(maxhp);
}
ItemType PhoenixII::type() {
    return PHOENIX2;
}
bool PhoenixII::canUse(BaseKnight * knight) {
    init(knight);
    if (hp < maxhp / 4) return 1;
    return 0;
}
void PhoenixII::use(BaseKnight * knight) {
    knight->usePhoenix(maxhp);
}
string PhoenixII::getClass() {
    return "PhoenixII";
}
ItemType PhoenixIII::type() {
    return PHOENIX3;
}
bool PhoenixIII::canUse(BaseKnight * knight) {
    init(knight);
    if (hp < maxhp / 3) return 1;
    return 0;
}
void PhoenixIII::use(BaseKnight * knight) {
    if (hp <= 0) knight->usePhoenix(maxhp / 3);
    else knight->usePhoenix(maxhp / 4);
}
string PhoenixIII::getClass() {
    return "PhoenixIII";
}
ItemType PhoenixIV::type() {
    return PHOENIX4;
}
bool PhoenixIV::canUse(BaseKnight * knight) {
    init(knight);
    if (hp < maxhp / 2) return 1;
    return 0;
}
void PhoenixIV::use(BaseKnight * knight) {
    if (hp <= 0) knight->usePhoenix(maxhp / 2);
    else knight->usePhoenix(maxhp / 5);
}
string PhoenixIV::getClass() {
    return "PhoenixIV";
}

/* * * BEGIN implementation of class BaseBag * * */
void List::insertFirst(BaseItem * item) {
    Node * node = nullptr;
    if (headNode == nullptr) {
        this->headNode = node;
        return;
    }
    node->next = headNode;
    this->headNode = node;
}
string List::toString() {
    string s = "Bag[count=";
    s += to_string(contain);
    string temp = ";";
    Node * tempNode = headNode;
    while (tempNode != nullptr) {
        temp += tempNode->item->getClass();
        if (tempNode->next != nullptr) temp += ',';
        tempNode = tempNode->next;
    }
    s += temp + "]";
    return s;
}
void List::remove(int n) {
    if (n == 0) {
        headNode = headNode->next;
    }
    Node * temp = headNode;
    Node * tempHeadNode = headNode->next;
    Node * node = headNode;
    for (int i = 0; i < n; ++i) {
        node = node->next;
    }
    if (n == 1) {
        headNode->next = node->next;
        return;
    }
    while (temp != nullptr) {
        if (temp->next == node) {
            temp->next = headNode;
            temp->next->next = node->next;
            node->next = tempHeadNode;
            this->headNode = node;
            break;
        }
        temp = temp->next;
    }
    headNode = headNode->next;
    this->contain--;
    delete node;
    delete temp;
    delete tempHeadNode;
}
BaseItem * List::search(ItemType item) {
    int ans = 0;
    Node * tempNode = headNode;
    while (tempNode != nullptr) {
        if (tempNode->item->type() == item) {
            return tempNode->item;
        }
        tempNode = tempNode->next;
    }
    return nullptr;
}

PaladinBag::PaladinBag(int p1, int anti) {
    this->maxSize = Size;
    listOfItems.maxSize = this->maxSize;
    while (anti--) {
        BaseItem * item = new Antidote;
        if (!insertFirst(item)) {
            delete item;
        }
    }
    while (p1) {
        BaseItem * item = new PhoenixI;
        if (!insertFirst(item)) {
            delete item;
        }
    }
}
bool PaladinBag::insertFirst(BaseItem * item) {
    if (listOfItems.contain == listOfItems.maxSize) {
        return 0;
    }
    listOfItems.contain++;
    listOfItems.insertFirst(item);
    return 1;
} 
BaseItem* PaladinBag::get(ItemType item) {
    BaseItem * tempItem = listOfItems.search(item);
    if (tempItem != nullptr) {
        return tempItem;
    }
    return nullptr;
}

LancelotBag::LancelotBag(int p1, int anti) {
    this->maxSize = Size;
    listOfItems.maxSize = this->maxSize;
    while (anti--) {
        BaseItem * item = new Antidote;
        if (!insertFirst(item)) {
            delete item;
        }
    }
    while (p1) {
        BaseItem * item = new PhoenixI;
        if (!insertFirst(item)) {
            delete item;
        }
    }
}
bool LancelotBag::insertFirst(BaseItem * item) {
    if (listOfItems.contain == listOfItems.maxSize) {
        return 0;
    }
    listOfItems.contain++;
    listOfItems.insertFirst(item);
    return 1;
} 
BaseItem* LancelotBag::get(ItemType item) {
    BaseItem * tempItem = listOfItems.search(item);
    if (tempItem != nullptr) {
        return tempItem;
    }
    return nullptr;
}

DragonBag::DragonBag(int p1) {
    this->maxSize = Size;
    listOfItems.maxSize = this->maxSize;
    while (p1) {
        BaseItem * item = new PhoenixI;
        if (!insertFirst(item)) {
            delete item;
        }
    }
}
bool DragonBag::insertFirst(BaseItem * item) {
    if (listOfItems.contain == listOfItems.maxSize) {
        return 0;
    }
    listOfItems.contain++;
    listOfItems.insertFirst(item);
    return 1;
} 
BaseItem* DragonBag::get(ItemType item) {
    BaseItem * tempItem = listOfItems.search(item);
    if (tempItem != nullptr) {
        return tempItem;
    }
    return nullptr;
}

NormalBag::NormalBag(int p1, int anti) {
    this->maxSize = Size;
    listOfItems.maxSize = this->maxSize;
    while (anti--) {
        BaseItem * item = new Antidote;
        if (!insertFirst(item)) {
            delete item;
        }
    }
    while (p1) {
        BaseItem * item = new PhoenixI;
        if (!insertFirst(item)) {
            delete item;
        }
    }
}
bool NormalBag::insertFirst(BaseItem * item) {
    if (listOfItems.contain == listOfItems.maxSize) {
        return 0;
    }
    listOfItems.contain++;
    listOfItems.insertFirst(item);
    return 1;
} 
BaseItem* NormalBag::get(ItemType item) {
    BaseItem * tempItem = listOfItems.search(item);
    if (tempItem != nullptr) {
        return tempItem;
    }
    return nullptr;
}

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
BaseKnight * BaseKnight::create(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote) {
    BaseKnight *knight;
    if (isPrime(maxhp)) {
        knight = new Paladin;
        knight -> bag = new PaladinBag(phoenixdownI, antidote);
    }
    else if (maxhp == 888) {
        knight = new Lancelot;
        knight -> knightType = LANCELOT;
    }
    else if (isPythagoras(maxhp)) {
        knight = new Dragon;
        knight -> knightType = DRAGON;
    }
    else {
        knight = new Normal;
        knight -> knightType = NORMAL;
    }
    knight -> id = id;
    knight -> hp = maxhp;
    knight -> maxhp = maxhp;
    knight -> level = level;
    knight -> gil = gil;
    knight -> antidote = antidote;

    return knight;
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
        int temp = (last->fight(opponent));
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
