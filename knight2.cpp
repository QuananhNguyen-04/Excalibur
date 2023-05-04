#include "knight2.h"

/* * * BEGIN implementation of class BaseOpponent * * */
bool BaseOpponent::result() {
    if (levelO > klevel) return 0;
    return 1;
}
void BaseOpponent::dmg() {
    hpLose = BaseDamage * (levelO - klevel);
}
BaseOpponent * BaseOpponent::create(int i, int id) {
    BaseOpponent * opponent;
    switch (id) {
    case MADBEAR: 
        opponent = new MadBear(i, id);
        break;
    case BANDIT: 
        opponent = new Bandit(i, id);
        break;
    case LORDLUPIN: 
        opponent = new LordLupin(i, id);
        break;
    case ELF: 
        opponent = new Elf(i, id);
        break;
    case TROLL: 
        opponent = new Troll(i, id);
        break;
    case TORNBERY: 
        opponent = new Tornbery(i, id);
        break;
    case QUEEN: 
        opponent = new Queen(i, id);
        break;
    case NINA: 
        opponent = new Nina(i, id);
        break;
    case DURIAN: 
        opponent = new Durian(i, id);
        break;
    case OMEGA: 
        opponent = new Omega(i, id);
        break;
    case HADES: 
        opponent = new Hades(i, id);
        break;
    case ULTIMECIA:
        opponent = new Ultimecia(i, id);
        break;
    default:
        break;
    }
    return opponent;
}
OpponentType BaseOpponent::type() {
    return id;
}
void BaseOpponent::init(int i, int id) {
    this->i = i;
    this->id = static_cast<OpponentType> (id);
    if (id >= 1 and id <= 5) {
        this->gilGain = gilTable[id];
        this->BaseDamage = baseDmg[id];
    }
    this->levelO = (i + id) % 10 + 1;
}
/* * * END implementation of class BaseOpponent * * */

/* * * BEGIN implementation of class BaseItem * * */
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
Antidote::~Antidote(){}

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
PhoenixI::~PhoenixI(){}

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
PhoenixII::~PhoenixII(){}

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
PhoenixIII::~PhoenixIII(){}

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
PhoenixIV::~PhoenixIV(){}
/* * * END implementation of class BaseItem * * */

/* * * BEGIN implementation of class BaseBag * * */
List::~List() {
    while (headNode != nullptr) remove(0);
}
bool List::isFull() {
    if (contain == maxSize) return true;
    return 0;
}
void List::insertFirst(BaseItem * item) {
    Node * node = new Node(item);
    if (headNode == nullptr) {
        this->headNode = node;
        return;
    }
    Node * tempNode = headNode;
    node->next = tempNode;
    this->headNode = node;
}
string List::toString() const {
    string s = "Bag[count=";
    s += to_string(contain);
    string temp = ";";
    Node * tempNode = headNode;
    while (tempNode != NULL) {
        temp += tempNode->item->getClass();
        if (tempNode->next != nullptr) temp += ',';
        tempNode = tempNode->next;
    }
    s += temp + "]";
    return s;
}
void List::remove(int n) {
    if (n == 0) {
        Node * temp = headNode;
        headNode = headNode->next;
        this->contain--;
        delete temp;
        return;
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
}
pair<BaseItem*, int> List::search(ItemType item, int startPos) {
    if (item == PHOENIX) {
        int ans = 0;
        Node * tempNode = headNode;
        while (tempNode != nullptr) {
            if (ans < startPos) {
                tempNode = tempNode->next;
                ans++;
                continue;
            }
            ItemType type = tempNode->item->type();
            if (type == PHOENIX1 or type == PHOENIX2 or type == PHOENIX3 or type == PHOENIX4) {
                return {tempNode->item, ans};
            }
            tempNode = tempNode->next;
            ans++;
        }
        return {nullptr, -1};
    }
    else {
        int ans = 0;
        Node * tempNode = headNode;
        while (tempNode != nullptr) {
            if (tempNode->item->type() == item) {
                return {tempNode->item, ans};
            }
            tempNode = tempNode->next;
            ans++;
        }
    }
    return {nullptr, -1};
}

void BaseBag::drop(int num, int pos = 0) {
    for (int i = 0; i < num; ++i) {
        if (listOfItems.contain == 0) return;
        listOfItems.remove(pos);
    }
}

PaladinBag::PaladinBag(int p1, int anti) {
    this->maxSize = Size;
    listOfItems.maxSize = this->maxSize;
    while (p1--) {
        BaseItem * item = new PhoenixI;
        if (!insertFirst(item)) {
            delete item;
        }
    }
    while (anti--) {
        BaseItem * item = new Antidote;
        if (!insertFirst(item)) {
            delete item;
        }
    }
}
bool PaladinBag::insertFirst(BaseItem * item) {
    if (listOfItems.isFull()) return 0;
    listOfItems.contain++;
    listOfItems.insertFirst(item);
    return 1;
} 
BaseItem* PaladinBag::get(ItemType item) {
    pair<BaseItem *, int> p = listOfItems.search(item);
    int pos = p.second;
    if (p.first == nullptr) return nullptr;
    BaseItem * tempItem;
    switch(p.first->type()) {
        case ANTIDOTE:
            tempItem = new Antidote;
            break;
        case PHOENIX1:
            tempItem = new PhoenixI;
            break;
        case PHOENIX2:
            tempItem = new PhoenixII;
            break;
        case PHOENIX3:
            tempItem = new PhoenixIII;
            break;
        case PHOENIX4:
            tempItem = new PhoenixIV;
            break;
    }
    if (tempItem != nullptr) {
        listOfItems.remove(pos);
    }
    return tempItem;
}
string PaladinBag::toString() const {
    return listOfItems.toString();
}

LancelotBag::LancelotBag(int p1, int anti) {
    this->maxSize = Size;
    listOfItems.maxSize = this->maxSize;
    while (p1--) {
        BaseItem * item = new PhoenixI;
        if (!insertFirst(item)) {
            delete item;
        }
    }
    while (anti--) {
        BaseItem * item = new Antidote;
        if (!insertFirst(item)) {
            delete item;
        }
    }
}
bool LancelotBag::insertFirst(BaseItem * item) {
    if (listOfItems.isFull()) return 0;
    listOfItems.contain++;
    listOfItems.insertFirst(item);
    return 1;
} 
BaseItem* LancelotBag::get(ItemType item) {
    pair<BaseItem *, int> p = listOfItems.search(item);
    int pos = p.second;
    if (p.first == nullptr) return nullptr;
    BaseItem * tempItem;
    switch(p.first->type()) {
        case ANTIDOTE:
            tempItem = new Antidote;
            break;
        case PHOENIX1:
            tempItem = new PhoenixI;
            break;
        case PHOENIX2:
            tempItem = new PhoenixII;
            break;
        case PHOENIX3:
            tempItem = new PhoenixIII;
            break;
        case PHOENIX4:
            tempItem = new PhoenixIV;
            break;
    }
    if (tempItem != nullptr) {
        listOfItems.remove(pos);
    }
    return tempItem;
}
string LancelotBag::toString() const {
    return listOfItems.toString();
}

DragonBag::DragonBag(int p1) {
    this->maxSize = Size;
    listOfItems.maxSize = this->maxSize;
    while (p1--) {
        BaseItem * item = new PhoenixI;
        if (!insertFirst(item)) {
            delete item;
        }
    }
}
bool DragonBag::insertFirst(BaseItem * item) {
    if (item->type() == ANTIDOTE) return 0;
    if (listOfItems.isFull()) return 0;
    listOfItems.contain++;
    listOfItems.insertFirst(item);
    return 1;
} 
BaseItem* DragonBag::get(ItemType item) {
    pair<BaseItem *, int> p = listOfItems.search(item);
    int pos = p.second;
    if (p.first == nullptr) return nullptr;
    BaseItem * tempItem;
    switch(p.first->type()) {
        case ANTIDOTE:
            tempItem = new Antidote;
            break;
        case PHOENIX1:
            tempItem = new PhoenixI;
            break;
        case PHOENIX2:
            tempItem = new PhoenixII;
            break;
        case PHOENIX3:
            tempItem = new PhoenixIII;
            break;
        case PHOENIX4:
            tempItem = new PhoenixIV;
            break;
    }
    if (tempItem != nullptr) {
        listOfItems.remove(pos);
    }
    return tempItem;
}
string DragonBag::toString() const {
    return listOfItems.toString();
}

NormalBag::NormalBag(int p1, int anti) {
    this->maxSize = Size;
    this->listOfItems.maxSize = this->maxSize;
    while (p1--) {
        BaseItem * item = new PhoenixI();
        if (!insertFirst(item)) {
            delete item;
        }
    }
    while (anti--) {
        BaseItem * item = new Antidote();
        if (!insertFirst(item)) {
            delete item;
        }
    }
}
bool NormalBag::insertFirst(BaseItem * item) {
    if (listOfItems.isFull()) return 0;
    listOfItems.contain++;
    listOfItems.insertFirst(item);
    return 1;
} 
BaseItem* NormalBag::get(ItemType item) {
    pair<BaseItem *, int> p = listOfItems.search(item);
    int pos = p.second;
    if (p.first == nullptr) return nullptr;
    BaseItem * tempItem;
    switch(p.first->type()) {
        case ANTIDOTE:
            tempItem = new Antidote;
            break;
        case PHOENIX1:
            tempItem = new PhoenixI;
            break;
        case PHOENIX2:
            tempItem = new PhoenixII;
            break;
        case PHOENIX3:
            tempItem = new PhoenixIII;
            break;
        case PHOENIX4:
            tempItem = new PhoenixIV;
            break;
    }
    if (tempItem != nullptr) {
        listOfItems.remove(pos);
    }
    return tempItem;
}
string NormalBag::toString() const {
    return listOfItems.toString();
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
BaseKnight::~BaseKnight() {}
BaseKnight * BaseKnight::create(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote) {
    BaseKnight *knight;
    if (isPrime(maxhp)) {
        knight = new Paladin;
        knight -> bag = new PaladinBag(phoenixdownI, antidote);
    }
    else if (maxhp == 888) {
        knight = new Lancelot;
        knight->bag = new LancelotBag(phoenixdownI, antidote);
    }
    else if (isPythagoras(maxhp)) {
        knight = new Dragon;
        knight->bag = new DragonBag(phoenixdownI);
    }
    else {
        knight = new Normal;
        knight->bag = new NormalBag(phoenixdownI, antidote);
    }
    knight -> id = id;
    knight -> hp = maxhp;
    knight -> maxhp = maxhp;
    knight -> level = level;
    knight -> gil = gil;
    knight -> antidote = antidote;
    return knight;
}
bool BaseKnight::revive() {
    if (hp > 0) {
        int pos = 0;
        while (pos < bag->listOfItems.contain) {
            pair<BaseItem *, int> p = bag->listOfItems.search(PHOENIX, pos);
            if (p.second == -1) return 1;
            BaseItem * Item = p.first;
            if (Item->canUse(this)) {
                Item->use(this);
                bag->get(Item->type());
                return 1;
            }
            pos = p.second + 1;
        }
    }
    if (this->hp <= 0) {
        BaseItem * Item;
        Item = bag->get(PHOENIX);
        if (Item != nullptr) {
            Item->init(this);
            switch (Item->type())
            {
            case PHOENIX1:
                Item->use(this);    
                break;
            case PHOENIX2:
                Item->use(this);
                break;
            case PHOENIX3:
                Item->use(this);
                break;
            case PHOENIX4:
                Item->use(this);
                break;
            
            default:
                break;
            }
        }
        delete Item;
    }
    if (this->hp > 0) return 1;
    if (gil >= 100) {
        this->usePhoenix(maxhp / 2);
        gil -= 100;
        if (this->hp <= 0) return 0;
        return 1;
    }
    return 0;
}
void BaseKnight::updateInfo(int *itemList)
{
    if (itemList[5] > 0) {
        if (gil + itemList[5] >= 999) {
                itemList[5] -= (999 - gil);
                this->gil = 999;
            }
        else {
            this->gil += itemList[5];
            itemList[5] = 0;
        }
    }
    if (knightType != DRAGON) {
        while (itemList[0] > 0) {
            BaseItem * item = new Antidote;
            if (bag->insertFirst(item)) {
                itemList[0]--;
            }
            else {
                break;
            }
        }
    }
    while (itemList[1] > 0) {
        BaseItem * item = new PhoenixI;
        if (bag->insertFirst(item)) {
            itemList[1]--;
        }
        else {
            break;
        }
    }
    while (itemList[2] > 0) {
        BaseItem * item = new PhoenixII;
        if (bag->insertFirst(item)) {
            itemList[2]--;
        }
        else {
            break;
        }
    }
    while (itemList[3] > 0) {
        BaseItem * item = new PhoenixIII;
        if (bag->insertFirst(item)) {
            itemList[3]--;
        }
        else {
            break;
        }
    }
    while (itemList[4] > 0) {
        BaseItem * item = new PhoenixIV;
        if (bag->insertFirst(item)) {
            itemList[4]--;
        }
        else {
            break;
        }
    }
}

bool Paladin::fight(BaseOpponent *opponent, int type, int *itemList) {
    opponent->klevel = level;
    bool win = 1;
    switch (type) {
        case 1 ... 5: {
            itemList[5] += opponent->reward();
            break;
        }
        case 6: {
            if (opponent->result()) {
                if (level + 1 <= 10) this->level++;
            }
            else {
                BaseItem * item = bag->get(ANTIDOTE);
                if (item == nullptr) {
                    bag->drop(3);
                    this->hp -= opponent->lose();
                    if (hp <= 0) win = 0;
                }
                else {
                    item->use(this);
                    delete item;
                }
            }
            break;
        }
        case 7: {
            if (opponent->result()) {
                if (gil * 2 > 999) {
                    itemList[5] += (gil * 2 - 999);
                    this->gil = gil * 2 - 999;
                }
                else this->gil *= 2;
            }
            break;
        }
        case 8: {
            if (hp < maxhp / 3) {
                this->hp += (maxhp / 5);
            }
            break;
        }
        case 10: {
            if (level == 10 and hp == maxhp) {
                this->gil = 999;
            }
            else {
                this->hp = 0;
                win = 0;
            }
            break;
        }
        case 11: {
            if (level >= 8) {
                this->hp = 0;
                win = 0;
            }
            break;
        }
        case 99: {
            opponent->hpRemain(this->Dmg * hp * level);
            if (opponent->gethp() < 0) win = 1;
            else win = 0;
            break;
        }
        default:
            break;
    }
    if (win) {
        updateInfo(itemList);
        return win;
    }
    return win;
}
Paladin::~Paladin() {
    delete bag;
}

bool Lancelot::fight(BaseOpponent *opponent, int type, int *itemList) {
    opponent->klevel = level;
    bool win = 1;
    switch (type) {
        case 1 ... 5: {
            itemList[5] += opponent->reward();
            break;
        }
        case 6: {
            if (opponent->result()) {
                if (level + 1 <= 10) this->level++;
            }
            else {
                BaseItem * item = bag->get(ANTIDOTE);
                if (item == nullptr) {
                    bag->drop(3);
                    this->hp -= opponent->lose();
                    if (hp <= 0) win = 0;
                }
                else {
                    item->use(this);
                    delete item;
                }
            }
            break;
        }
        case 7: {
            if (opponent->result()) {
                if (gil * 2 > 999) {
                    itemList[5] += (gil * 2 - 999);
                    this->gil = gil * 2 - 999;
                }
                else this->gil *= 2;
            }
            else this->gil /= 2;
            break;
        }
        case 8: {
            if (gil >= 50) {
                if (hp < maxhp / 3) {
                    this->hp += (maxhp / 5);
                    this->gil -= 50;
                }
            }
            break;
        }
        case 10: {
            if (level == 10 and hp == maxhp) {
                this->gil = 999;
            }
            else {
                this->hp = 0;
                win = 0;
            }
            break;
        }
        case 11: {
            if (level < 10) {
                this->hp = 0;
                win = 0;
            }
            break;
        }
        case 99: {
            opponent->hpRemain(this->Dmg * hp * level);
            if (opponent->gethp() < 0) win = 1;
            else win = 0;
            break;
        }
        default:
            break;
    }
    if (win) {
        updateInfo(itemList);
        return win;
    }
    return win;
}
Lancelot::~Lancelot() {
    delete bag;
}

bool Dragon::fight(BaseOpponent *opponent, int type, int *itemList) {
    opponent->klevel = level;
    bool win = 1;
    switch (type) {
        case 1 ... 5: {
            if (opponent->result()) {
                itemList[5] += opponent->reward();
            }
            else {
                this->hp -= opponent->lose();
                if (hp <= 0) win = 0;
            }
            break;
        }
        case 6: {
            if (opponent->result()) {
                if (level + 1 <= 10) this->level++;
            }
            break;
        }
        case 7: {
            if (opponent->result()) {
                if (gil * 2 > 999) {
                    itemList[5] += (gil * 2 - 999);
                    this->gil = gil * 2 - 999;
                }
                else this->gil *= 2;
            }
            else this->gil /= 2;
            break;
        }
        case 8: {
            if (gil >= 50) {
                if (hp < maxhp / 3) {
                    this->hp += (maxhp / 5);
                    this->gil -= 50;
                }
            }
            break;
        }
        case 10: {
            this->gil = 999;
            break;
        }
        case 11: {
            if (level < 10) {
                this->hp = 0;
                win = 0;
            }
            break;
        }
        case 99: {
            opponent->hpRemain(this->Dmg * hp * level);
            if (opponent->gethp() < 0) win = 1;
            else win = 0;
            break;
        }
        default:
            break;
    }
    if (win) {
        updateInfo(itemList);
        return win;
    }
    return win;
}
Dragon::~Dragon() {
    delete bag;
}

bool Normal::fight(BaseOpponent * opponent, int type, int * itemList) {
    opponent->klevel = level;
    bool win = 1;
    switch (type) {
        case 1 ... 5: {
            if (opponent->result()) {
                itemList[5] += opponent->reward();
            }
            else {
                this->hp -= opponent->lose();
                if (hp <= 0) win = 0;
            }
            break;
        }
        case 6: {
            if (opponent->result()) {
                if (level + 1 <= 10) this->level++;
            }
            else {
                BaseItem * item = bag->get(ANTIDOTE);
                if (item == nullptr) {
                    bag->drop(3);
                    this->hp -= opponent->lose();
                    if (hp <= 0) win = 0;
                }
                else {
                    item->use(this);
                    delete item;
                }
            }
            break;
        }
        case 7: {
            if (opponent->result()) {
                if (gil * 2 > 999) {
                    itemList[5] += (gil * 2 - 999);
                    this->gil = 999;
                }
                else this->gil *= 2;
            }
            else this->gil /= 2;
            break;
        }
        case 8: {
            if (gil >= 50) {
                if (hp < maxhp / 3) {
                    this->hp += (maxhp / 5);
                    this->gil -= 50;
                }
            }
            break;
        }
        case 10: {
            if (level == 10 and hp == maxhp) {
                this->gil = 999;
            }
            else {
                this->hp = 0;
                win = 0;
            }
            break;
        }
        case 11: {
            if (level < 10) {
                this->hp = 0;
                win = 0;
            }
            break;
        }
        default:
            break;
    }
    if (win) {
        updateInfo(itemList);
        return win;
    }
    return win;
}
Normal::~Normal() {
    delete bag;
}

string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
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
void ArmyKnights::fight(BaseOpponent * opponent, int type, int * itemList) {
    if (type == 99) {
        int tmp = numsOfKnights;
        int check[tmp]; for (int i = 0; i <= tmp; ++i) check[i] = 0;
        for (int i = numsOfKnights - 1; i >= 0; --i) {
            if (KnightList[i]->returnType() != NORMAL) {
                if (!KnightList[i]->fight(opponent, type, itemList)) {
                    check[i] = 1;
                    this->numsOfKnights--;
                    delete KnightList[i];
                }
                else break;
            }
        }
        tempList = new BaseKnight*[numsOfKnights];
        for (int i = 0, j = 0; i < tmp; ++i) {
            if (!check[i]) {
                tempList[j] = KnightList[i];
                j++;
            }
        }
        delete []KnightList;
        KnightList = tempList;
        return;
    }
    while (1) {
        if(last->fight(opponent, type, itemList) == 1) {
            last->revive();
            if (type == 10) isMeetOmega = 1;
            if (type == 11) {
                isMeetHades = 1;
                PaladinShield = 1;
            }
            return;
        }
        else {
            if (last->revive()) return;
            this->numsOfKnights--;
            delete last;
            if (numsOfKnights > 0) last = KnightList[numsOfKnights - 1];
            else return;
        }
    }
}
int ArmyKnights::count() const {return numsOfKnights;}

void ArmyKnights::getSpecialItem(int event) {
    switch (event)
    {
    case 95:
        this->PaladinShield = 1;
        break;
    case 96:
        this->LancelotSpear = 1;
        break;
    case 97:
        this->GuinevereHair = 1;
        break;
    case 98:
        if (PaladinShield and LancelotSpear and GuinevereHair) this->ExcaliburSword = 1;
        break;
    
    default:
        break;
    }
}
bool ArmyKnights::adventure(Events * events) {
    itemList = new int[6];
    bool win = 1;
    for (int i = 0; i < 6; ++i) itemList[i] = 0;
    for (int i = 0; i < events->count(); ++i) {
        int event = events->get(i);
        BaseOpponent * opponent = nullptr;
        switch (event) {
        case 1 ... 8: {
            BaseOpponent * tempOpponent;
            opponent = tempOpponent->create(i, event);
            fight(opponent, event, itemList);
            break;
        }
        case 9: {
            last->usePhoenix(last->getHP_maxHP().second);
            break;
        }
        case 10: {
            if (isMeetOmega) break;
            BaseOpponent * tempOpponent;
            opponent = tempOpponent->create(i, event);
            fight(opponent, 10, itemList);
            break;
        }
        case 11: {
            if (isMeetHades) break;
            BaseOpponent * tempOpponent;
            opponent = tempOpponent->create(i, event);
            fight(opponent, 11, itemList);
            break;
        }
        case 112 ... 114: {
            switch (event)
            {
            case 112: 
                itemList[2]++;
                break;
            case 113: 
                itemList[3]++;
                break;
            case 114:
                itemList[4]++;
                break;
            default:
                break;
            }
            last->updateInfo(itemList);
        }
        case 95 ... 98: {
            getSpecialItem(event);
            break;
        }
        case 99: {
            if (!hasExcaliburSword()) {
                win = 0;
                if (hasPaladinShield() and hasLancelotSpear() and hasGuinevereHair()) {
                    BaseOpponent * tempOpponent;
                    opponent = tempOpponent->create(i, event);
                    fight(opponent, 99, itemList);
                    for (int i = 0; i < numsOfKnights; ++i) {
                        if (KnightList[i]->returnType() != NORMAL) {
                            win = 1;
                        }
                    }
                }
            }
            if (win == 0) {
                calledTemp = 1;
                while (numsOfKnights > 0) {
                    delete KnightList[numsOfKnights - 1];
                    numsOfKnights--;
                }
                delete []KnightList;
            }
            break;
        }
        default:
            break;
        }
        printInfo();
        if (numsOfKnights <= 0 and !win) {
            delete []itemList;
            delete opponent;
            return 0;
        }
        delete opponent;
    }
    delete []itemList;
    if (numsOfKnights > 0) return 1;
    return 0;
}
BaseKnight * ArmyKnights::lastKnight() const {
    // last = KnightList[numsOfKnights - 1];
    return KnightList[numsOfKnights - 1];
}
bool ArmyKnights::hasPaladinShield() const
{
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
        << '\n'
        << string(50, '-') << endl;
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
    army->printResult(army->adventure(events));
}

/* * * END implementation of class KnightAdventure * * */
