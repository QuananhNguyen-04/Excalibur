#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

inline int IsPrime(int n){
    if (n < 2) return 0;
    for (int i = 2; i < n; i++)
        if (n % i == 0) return 0;
    return 1;
}
inline int IsPythagoras(int a, int b, int c){
    if (a * a + b * b == c * c) return 1;
    else if (a * a + c * c == b * b) return 1;
    else if (b * b + c * c == a * a) return 1;
    return 0;
}
inline int IsDragonKnight(int n){
    int a, b, c = n % 10;
    n = n / 10;
    b = n % 10;
    n = n / 10;
    a = n % 10;
    if (IsPythagoras(a, b, c)) return 1;
    else return 0;
}

// enum ItemType {PALADIN_SHIELD = 95, LANCELOT_SPEAR, GUINEVERE_HAIR, EXCALIBUR, ANTIDOTE = 101,PHOENIXDOWN_I,
//         PHOENIXDOWN_II = 112, PHOENIXDOWN_III, PHOENIXDOWN_IV, NOTHING = INT_MAX};
class Events;
class BaseKnight;
/*
class BaseItem {
public:
    BaseItem(){
        Identity = NOTHING;
    }
    BaseItem(ItemType itemType){
        Identity = itemType;
    }
    ItemType Identity = NOTHING;
    virtual bool canUse (BaseKnight * knight);
    virtual void use (BaseKnight * knight );
};

class BaseBag {
public:
    BaseBag *SubBag = 0;
    BaseItem *Holding = 0;
    BaseKnight *knight = nullptr;
    ~BaseBag(){
        delete [] SubBag;
        delete [] Holding;
    }
    virtual bool insertFirst(BaseItem * item){
        BaseBag *temp = nullptr;
        temp = new BaseBag;
        temp->Holding = item;
        temp->SubBag = SubBag;
        delete [] SubBag;
        SubBag = temp;
        return true;
    }
    virtual void Drop(int n){
        BaseBag *Temp = nullptr;
        if (BagSize() >= n){
            for (int i = 0; i < n; i++){
                Temp = SubBag->SubBag;
                delete [] SubBag;
                SubBag = Temp;
            }
        }
        else
            while (SubBag != nullptr){
                Temp = SubBag->SubBag;
                delete [] SubBag;
                SubBag = Temp;
            }
    }
    virtual int const BagSize() const {
        if (SubBag == nullptr) return 0;
        return SubBag->BagSize() + 1;
    }
    virtual BaseBag *TheBagAt(int n){
        if (n == 0) return SubBag;
        if (SubBag == nullptr) return nullptr;
        else return SubBag->TheBagAt(n - 1);
    }
    virtual BaseBag *ItemFound(ItemType itemType){
        if (SubBag != nullptr)
        {
            if (SubBag->Holding->Identity == itemType) return this;
            return SubBag->ItemFound(itemType);
        }
        else return nullptr;
    }
    virtual BaseBag * get(ItemType itemType){
        BaseBag *FirstRootBag = nullptr, *DestinationRootBag = nullptr, *temp1 = nullptr, *temp2 = nullptr, *temp3 = nullptr, *temp4 = nullptr;
        BaseBag *TempBag;
        DestinationRootBag = ItemFound(itemType);
        FirstRootBag = this;
        if (DestinationRootBag == nullptr) return nullptr;
        if (this ->SubBag == nullptr) return nullptr;
        if ((DestinationRootBag != FirstRootBag) && FirstRootBag->SubBag != DestinationRootBag){
            temp1 = DestinationRootBag->SubBag;
            temp2 = FirstRootBag -> SubBag;
            temp3 = FirstRootBag -> SubBag -> SubBag;
            temp4 = DestinationRootBag->SubBag->SubBag;
            this->SubBag = temp1;
            temp1->SubBag = temp3;
            DestinationRootBag->SubBag = temp2;
            temp2->SubBag = temp4;
            // Do not delete temp1, temp2, temp3, temp4
        }
        if (FirstRootBag->SubBag == DestinationRootBag){
            temp1 = DestinationRootBag->SubBag;
            temp2 = FirstRootBag -> SubBag;
            temp3 = FirstRootBag -> SubBag -> SubBag;
            temp4 = DestinationRootBag->SubBag->SubBag;
            this ->SubBag = temp1;
            temp1->SubBag = DestinationRootBag;
            DestinationRootBag->SubBag = temp4;
        }
        TempBag = this ->SubBag;
        this ->SubBag = this ->SubBag ->SubBag;
        return TempBag;
    }
    string const RecursiveToString(BaseBag *TheBag) const;

    virtual string toString() const{
        string str = "Bag[count=";
        str.append(to_string(BagSize()));
        str.append(";");
        return str.append(RecursiveToString(this->SubBag));
    }
    virtual BaseBag *DesperatelySearchingForPhoenixDown(){
        bool temp = CanUsePhoenixDownOfType(this->SubBag->Holding->Identity);
        if (temp) return this;
        if (this->SubBag->SubBag == nullptr) return nullptr;
        return this->SubBag->DesperatelySearchingForPhoenixDown();
    }
    virtual BaseBag *TakeHandBag(BaseBag *TheRootBagContainsUsefulItem){
        BaseBag *temp1, *temp2, *temp3, *temp4;
        if (TheRootBagContainsUsefulItem == nullptr) return nullptr;
        temp1 = TheRootBagContainsUsefulItem->SubBag;
        temp2 = this->SubBag;
        temp3 = TheRootBagContainsUsefulItem->SubBag->SubBag;
        temp4 = this->SubBag->SubBag;
        if ((TheRootBagContainsUsefulItem != this->SubBag) && (TheRootBagContainsUsefulItem != this)) {
            temp1->SubBag = nullptr;
            this->SubBag = temp4;
            temp2->SubBag = temp3;
            TheRootBagContainsUsefulItem->SubBag = temp2;
            return temp1;
        }
        else if (TheRootBagContainsUsefulItem == this){
            temp1->SubBag = nullptr;
            this->SubBag = temp3;
            return temp1;
        }
        else{
            temp1->SubBag = nullptr;
            TheRootBagContainsUsefulItem->SubBag = temp3;
            return temp1;
        }

    }
    void UsePhoenixDown(BaseBag *TheBag);
    bool CanUsePhoenixDownOfType(ItemType item);
};
inline string const BaseBag::RecursiveToString(BaseBag *TheBag) const {
    string str;
    ItemType temp = NOTHING;
    if (TheBag == nullptr) return "";
    temp = TheBag->Holding->Identity;
    if (temp == ANTIDOTE) {
        str = ", ANTIDOTE";
        return str.append(RecursiveToString(TheBag->SubBag));
    }
    if (temp == PALADIN_SHIELD) {
        str = ", PALADIN_SHIELD";
        return str.append(RecursiveToString(TheBag->SubBag));
    }
    if (temp == LANCELOT_SPEAR) {
        str = ", LANCELOT_SPEAR";
        return str.append(RecursiveToString(TheBag->SubBag));
    }
    if (temp == GUINEVERE_HAIR) {
        str = ", GUINEVERE_HAIR";
        return str.append(RecursiveToString(TheBag->SubBag));
    }
    if (temp == PHOENIXDOWN_I) {
        str = ", PHOENIX DOWN I";
        return str.append(RecursiveToString(TheBag->SubBag));
    }
    if (temp == PHOENIXDOWN_II) {
        str = ", PHOENIX DOWN II";
        return str.append(RecursiveToString(TheBag->SubBag));
    }
    if (temp == PHOENIXDOWN_III) {
        str = ", PHOENIX DOWN III";
        return str.append(RecursiveToString(TheBag->SubBag));
    }
    if (temp == PHOENIXDOWN_IV) {
        str = ", PHOENIX DOWN IV";
        return str.append(RecursiveToString(TheBag->SubBag));
    }
    if (temp == EXCALIBUR){
        str = ", EXCALIBUR";
        return str.append(RecursiveToString(TheBag->SubBag));
    }
    return str;
}
class MadBear{
public:
    int gil = 0;
    int LevelO = 0;
    int BaseDamage = 10;
    int IsMadBear = 0;
    int MadBearEventCode = 1;
    void FullFillMadBear(int Order){
        IsMadBear = 1;
        gil = 100;
        BaseDamage = 10;
        LevelO = (MadBearEventCode + Order) % 10;
    }
};
class Bandit{
public:
    int LevelO = 0;
    int gil = 0;
    int BaseDamage = 15;
    int IsBandit = 0;
    int BanditEventCode = 2;
    void FullFillBandit(int Order){
        IsBandit = 1;
        BaseDamage = 15;
        gil = 150;
        LevelO = (BanditEventCode + Order) % 10;
    }
};
class LordLupin{
public:
    int LevelO = 0;
    int BaseDamage = 45;
    int IsLupin = 0;
    int gil = 0;
    int LupinEventCode = 3;
    void FullFillLupin(int Order){
        IsLupin = 1;
        BaseDamage = 45;
        gil = 450;
        LevelO = (LupinEventCode + Order) % 10;
    }
};
class Elf{
public:
    int LevelO = 0;
    int BaseDamage = 75;
    int IsElf = 0;
    int gil = 0;
    int ElfEventCode = 4;
    void FullFillElf(int Order){
        IsElf = 1;
        BaseDamage = 75;
        gil = 750;
        LevelO = (ElfEventCode + Order) % 10;
    }
};
class Troll{
public:
    int LevelO = 0;
    int BaseDamage = 95;
    int IsTroll = 0;
    int gil = 0;
    int TrollEventCode = 5;
    void FullFillTroll(int Order){
        IsTroll = 1;
        BaseDamage = 95;
        gil = 800;
        LevelO = (TrollEventCode + Order) % 10;
    }
};
class TornBerry{
public:
    int LevelO = 0;
    int IsTornBerry = 0;
    int TornBerryEventCode = 6;
    int TornBerryDamage = 0;
    void FullFillTornBerry(int Order){
        IsTornBerry = 1;
        LevelO = (TornBerryEventCode + Order) % 10;
        TornBerryDamage = 10;
    }
};
class QueenOfCards{
public:
    int LevelO = 0;
    int IsQueenOfCards = 0;
    int QueenOfCardsEventCode = 7;
    void FullFillQueenOfCards(int Order){
        IsQueenOfCards = 1;
        LevelO = (QueenOfCardsEventCode + Order) % 10;
    }
};
class NinaDeRings{
public:
    int IsNinaDeRings = 0;
    void FullFillNinaDeRings(){
        IsNinaDeRings = 1;
    }
};
class DurianGarden{
public:
    int IsDurianGarden = 0;
    void FullFillDurianGarden(){
        IsDurianGarden = 1;
    }
};
class OmegaWeapon{
public:
    int IsOmegaWeapon = 0;
    void FullFillOmegaWeapon(){
        IsOmegaWeapon = 1;
    }
};
class Hades{
public:
    int IsHades = 0;
    void FullFillHades(){
        IsHades = 1;
    }
};
class Ultimecia{
public:
    int IsUltimecia = 0;
    float UltimeciaHP = 0;
    void FullFillUltimecia(){
        IsUltimecia = 1;
        UltimeciaHP = 5000;
    }
};
class PhoenixDown{
public:
    int IsPhoenixDownIV = 0, IsPhoenixDownII = 0, IsPhoenixDownIII = 0;
    void FullFillPhoenixDown(ItemType item){
        if (item == PHOENIXDOWN_II) IsPhoenixDownII = 1;
        if (item == PHOENIXDOWN_III) IsPhoenixDownIII = 1;
        if (item == PHOENIXDOWN_IV) IsPhoenixDownIV = 1;
    }
};
class ItemFromTheGround{
public:
    int IsGuinevereHair = 0, IsLanceLotSpere = 0, IsPaladinShield = 0, IsExcalibur = 0;
    void FullFillMagicItem(ItemType item){
        if (item == GUINEVERE_HAIR) IsGuinevereHair = 1;
        if (item == LANCELOT_SPEAR) IsLanceLotSpere = 1;
        if (item == PALADIN_SHIELD) IsPaladinShield = 1;
        if (item == EXCALIBUR) IsExcalibur = 1;
    }
};
class BaseOpponent: public virtual MadBear, public virtual Bandit,
        public virtual LordLupin, public virtual Elf, public virtual Troll,
        public virtual TornBerry, public virtual QueenOfCards, public NinaDeRings,
        public DurianGarden, public OmegaWeapon, public Hades, public Ultimecia,
        public virtual PhoenixDown, public virtual ItemFromTheGround
        {
public:
    BaseOpponent(int order, int EventCode){
        if (EventCode == 1) FullFillMadBear(order);
        if (EventCode == 2) FullFillBandit(order);
        if (EventCode == 3) FullFillLupin(order);
        if (EventCode == 4) FullFillElf(order);
        if (EventCode == 5) FullFillTroll(order);
        if (EventCode == 6) FullFillTornBerry(order);
        if (EventCode == 7) FullFillQueenOfCards(order);
        if (EventCode == 8) FullFillNinaDeRings();
        if (EventCode == 9) FullFillDurianGarden();
        if (EventCode == 10) FullFillOmegaWeapon();
        if (EventCode == 11) FullFillHades();
        if (EventCode == 99) FullFillUltimecia();
        if ((EventCode <= 114) && (EventCode >= 112)) FullFillPhoenixDown(ItemType(EventCode));
        if (EventCode == (int) PHOENIXDOWN_II) FullFillPhoenixDown(PHOENIXDOWN_II);
        if (EventCode == (int) PHOENIXDOWN_III) FullFillPhoenixDown(PHOENIXDOWN_III);
        if (EventCode == (int) PHOENIXDOWN_IV) FullFillPhoenixDown(PHOENIXDOWN_IV);
        if ((EventCode >= 95) && (EventCode <= 98)) FullFillMagicItem(ItemType(EventCode));
    }
};
*/
class ArmyKnights;


enum KnightType {PALADIN = 0, LANCELOT, DRAGON, NORMAL};
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    // BaseBag *HandBag = new BaseBag;
    //BaseBag * bag = new BaseBag;
    KnightType knightType;
    BaseKnight *NextKnight = nullptr;
public:
    ~BaseKnight(){
        // delete [] HandBag;
        delete [] NextKnight;
    }
    BaseKnight(){
        // HandBag ->knight = this;
    }
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
        BaseKnight * d = new BaseKnight;
        d -> id = id;
        d -> antidote = antidote;
        d -> maxhp = d -> hp = maxhp;
        d -> level = level;
        d -> gil = gil;
        if (IsPrime(d -> hp)) d -> knightType = PALADIN;
        else if (d -> hp == 888) d -> knightType = LANCELOT;
        else if (IsDragonKnight(d -> hp )) d -> knightType = DRAGON;
        else d -> knightType = NORMAL;
        return d;
    }
    string toString() const;
    friend ArmyKnights;
    // friend BaseItem;
    // friend BaseBag;
};

// inline void BaseItem::use(BaseKnight *knight) {

// }
// inline void BaseBag::UsePhoenixDown(BaseBag *TheBag){
//     ItemType item;
//     if (TheBag == nullptr) return;
//     item = TheBag->Holding->Identity;
//     delete [] TheBag;
//     if (item == PHOENIXDOWN_I) knight->hp = knight->maxhp;
//     if (item == PHOENIXDOWN_II) knight->hp = knight->maxhp;
//     if (item == PHOENIXDOWN_III)
//         if (knight->hp < 0)
//             knight->hp = knight->maxhp / 3;
//         else knight ->hp += knight->maxhp / 4;
//     if (item == PHOENIXDOWN_IV)
//         if (knight->hp < 0)
//             knight->hp = knight->maxhp / 2;
//         else
//             knight->hp += knight->maxhp / 5;
// }
class ArmyKnights {
public:
    int *HP = nullptr, *Level = nullptr, *Phoenix = nullptr, *gil = nullptr, *antidote = nullptr;
    int IsHurt = 0;
    int KnightCount = 0;
    int OmegaWeaponSold = 0;
    int HadesIsDead = 0;
    int Victory = 0;
    float LanceLotBaseDamage = 0.05, PaladinBaseDamage = 0.06, DragonBaseDamage = 0.075;
    string file_army_knight = "";
    BaseKnight *TheKnight = nullptr;
    BaseKnight *HeadSoldier = nullptr;
    ArmyKnights (const string & file_armyknights){
        ifstream f(file_armyknights);
        file_army_knight = file_armyknights;
        f >> KnightCount;
        int *a = new int[KnightCount];
        int *b = new int[KnightCount];
        int *c = new int[KnightCount];
        int *d = new int[KnightCount];
        int *e = new int[KnightCount];
        TheKnight = new BaseKnight[KnightCount];
        for (int i = 0; i < KnightCount; i++)
        {
            // BaseKnight *Temp = nullptr;
            f >> a[i];
            f >> b[i];
            f >> c[i];
            f >> d[i];
            f >> e[i];
            TheKnight[i] = *BaseKnight::create(i, a[i], b[i], d[i], e[i], c[i]);
            // delete [] Temp;
        }
        for (int i = 1; i < KnightCount; i++){
            TheKnight[i].NextKnight = &TheKnight[i - 1];
        }
        HeadSoldier = &TheKnight[KnightCount - 1];
        HP = a;
        Level = b;
        Phoenix = c;
        gil = d;
        antidote = e;
        // Do not delete a, b, c, d, e
        f.close();
    }
    ~ArmyKnights(){
        delete [] HP;
        delete [] gil;
        delete [] Level;
        delete [] antidote;
        delete [] Phoenix;
        delete [] TheKnight;
    }
    // void ItemRecieve(BaseItem *item){
    //     for (int i = KnightCount - 1; i >= 0; i--){
    //         if (TheKnight[i].knightType == PALADIN){
    //             TheKnight[i].HandBag->insertFirst(item);
    //             break;
    //         }
    //         if (TheKnight[i].knightType == DRAGON){
    //             if (item->Identity != ANTIDOTE)
    //                 if (TheKnight[i].HandBag->BagSize() < 14) {
    //                     TheKnight[i].HandBag->insertFirst(item);
    //                     break;
    //                 }
    //             else continue;
    //         }
    //         if (TheKnight[i].knightType == LANCELOT)
    //             if (TheKnight[i].HandBag->BagSize() < 16) {
    //                 TheKnight[i].HandBag->insertFirst(item);
    //                 break;
    //             }
    //         if (TheKnight[i].knightType == NORMAL)
    //             if (TheKnight[i].HandBag->BagSize() < 19) {
    //                 TheKnight[i].HandBag->insertFirst(item);
    //                 break;
    //             }
    //     }
    // }
    // bool StoringThe(ItemType item) const {
    //     bool Temp = false;
    //     for (int i = 0; i < KnightCount; i++)
    //         Temp = Temp || TheKnight[i].HandBag->ItemFound(item);
    //     return Temp;
    // }
    // void MoneyReceive(int BonusGils, int index){
    //     int Spare;
    //     if (index == -1) return;
    //     TheKnight[index].gil += BonusGils;
    //     Spare = TheKnight[index].gil - 999;
    //     if (Spare < 0) Spare = 0;
    //     else
    //         TheKnight[index].gil = 999;
    //     MoneyReceive(Spare, index - 1);

    // }
    // int HeadSoldierSurvived(){ // The HeadSoldier survived
    //     BaseBag *TheTempBag;

    //     if (IsHurt) {
    //         TheTempBag = HeadSoldier->HandBag->TakeHandBag(HeadSoldier->HandBag->DesperatelySearchingForPhoenixDown());
    //         HeadSoldier->HandBag->UsePhoenixDown(TheTempBag);
    //     }
    //     if (HeadSoldier->hp > 0) return 1;
    //     else return 0;
    // }
    // int Survived(){ // The team survived
    //     if (!HeadSoldierSurvived()){
    //         if (KnightCount == 1)
    //         {
    //             KnightCount = 0;
    //             return 0;
    //         }
    //         if (KnightCount > 1) {
    //             KnightCount -= 1;
    //             HeadSoldier = &TheKnight[KnightCount - 1];
    //         }
    //     }
    //     return 1;
    // }
    // void UseAntidote(){
    //     HeadSoldier->antidote -= 1;
    // }

    // void EmotionalDamage(BaseOpponent * TheOpponent){
    //     int temp = HeadSoldier->hp;
    //     if (TheOpponent -> IsMadBear) HeadSoldier ->hp -= TheOpponent ->MadBear::BaseDamage * (TheOpponent ->MadBear::LevelO - HeadSoldier->level);
    //     if (TheOpponent -> IsBandit) HeadSoldier->hp -= TheOpponent ->Bandit::BaseDamage * (TheOpponent->Bandit::LevelO - HeadSoldier->level);
    //     if (TheOpponent -> IsLupin) HeadSoldier->hp -= TheOpponent ->LordLupin::BaseDamage * (TheOpponent->LordLupin::LevelO - HeadSoldier->level);
    //     if (TheOpponent -> IsElf) HeadSoldier->hp -= TheOpponent ->Elf::BaseDamage * (TheOpponent->Elf::LevelO - HeadSoldier ->level);
    //     if (TheOpponent -> IsTroll) HeadSoldier -> hp -= TheOpponent->Troll::BaseDamage * (TheOpponent ->Troll::LevelO - HeadSoldier ->level);
    //     if (TheOpponent -> IsTornBerry) HeadSoldier ->hp -= TheOpponent->TornBerry::TornBerryDamage;
    //     if (TheOpponent -> IsHades) HeadSoldier->hp = 0;
    //     if (temp > HeadSoldier ->hp) IsHurt = 1;
    // }
    // void TornBeryFear(BaseOpponent * TornBerry){
    //     if (HeadSoldier->antidote > 0) UseAntidote();
    //     else if (HeadSoldier->knightType != DRAGON) {
    //         HeadSoldier->HandBag->Drop(3);
    //         EmotionalDamage(TornBerry);
    //     }
    // }
    // void RegainHP(int BonusHP){
    //     HeadSoldier->hp += BonusHP;
    //     if (HeadSoldier->hp > HeadSoldier->maxhp) HeadSoldier->hp = HeadSoldier->maxhp;
    // }
    // void NinaTransaction(){
    //     if ((HeadSoldier->gil >= 50) || (HeadSoldier->knightType == PALADIN)){
    //         if (HeadSoldier ->hp < HeadSoldier ->maxhp / 3){
    //             PayForTransaction(50);
    //             RegainHP(HeadSoldier->hp / 5);
    //         }
    //     }
    // }
    // void GilUp(int Gils){
    //     MoneyReceive(Gils, KnightCount - 1);
    // }
    // void PayTheDept(int n){
    //     if (HeadSoldier->knightType != PALADIN)
    //         HeadSoldier -> gil /= n;
    // }
    // void PayForTransaction(int gils){
    //     if (HeadSoldier->knightType != PALADIN)
    //         HeadSoldier -> gil -= gils;
    // }
    // void LevelUp(int ExtraLevel){
    //     HeadSoldier -> level += ExtraLevel;
    //     if (HeadSoldier->level > 10) HeadSoldier->level = 10;
    // }
    // void PickExcaliburUp(){
    //     if (StoringThe(GUINEVERE_HAIR) && StoringThe(LANCELOT_SPEAR) && StoringThe(PALADIN_SHIELD))
    //         ItemRecieve(new BaseItem(EXCALIBUR));
    // }
    // void SellOmegaWeaponAtTheBlackMarket(){
    //     LevelUp(10);
    //     HeadSoldier->gil = 999;
    //     OmegaWeaponSold = 1;
    // }
    // void BeingBeatenByOmegaWeapon(){
    //     HeadSoldier->hp = 0;
    // }
    // void DefeatTheHades(){
    //     BaseItem *temp = new BaseItem(PALADIN_SHIELD);

    //     if (StoringThe(PALADIN_SHIELD) == false)
    //         ItemRecieve(temp);
    //     HadesIsDead = 1;
    // }
    // void FightTheMadBear(BaseOpponent *TheMadBear){
    //     if ((HeadSoldier->knightType == LANCELOT) || (HeadSoldier->knightType == PALADIN))
    //         GilUp(TheMadBear->MadBear::gil);
    //     else
    //         if (HeadSoldier -> level < TheMadBear ->MadBear::LevelO) EmotionalDamage(TheMadBear);
    //         else GilUp(TheMadBear->MadBear::gil);
    // }
    // void FightTheBandit(BaseOpponent *TheBandit){
    //     if ((HeadSoldier->knightType == LANCELOT) || (HeadSoldier->knightType == PALADIN))
    //         GilUp(TheBandit->Bandit::gil);
    //     else
    //         if (HeadSoldier ->level  < TheBandit -> Bandit::LevelO) EmotionalDamage(TheBandit);
    //         else GilUp(TheBandit->Bandit::gil);
    // }
    // void FightTheLupin(BaseOpponent *TheLupin){
    //     if ((HeadSoldier->knightType == LANCELOT) || (HeadSoldier->knightType == PALADIN))
    //         GilUp(TheLupin->LordLupin::gil);
    //     else
    //         if (HeadSoldier ->level < TheLupin ->LordLupin::LevelO) EmotionalDamage(TheLupin);
    //         else GilUp(TheLupin ->LordLupin::gil);
    // }
    // void FightTheElf(BaseOpponent *TheElf){
    //     if ((HeadSoldier->knightType == LANCELOT) || (HeadSoldier->knightType == PALADIN))
    //         GilUp(TheElf->Elf::gil);
    //     else
    //         if (HeadSoldier ->level < TheElf->Elf::LevelO) EmotionalDamage(TheElf);
    //         else GilUp(TheElf->Elf::gil);
    // }
    // void FightTheTroll(BaseOpponent *TheTroll){
    //     if ((HeadSoldier->knightType == LANCELOT) || (HeadSoldier->knightType == PALADIN))
    //         GilUp(TheTroll->Troll::gil);
    //     else
    //         if (HeadSoldier ->level < TheTroll ->Troll::LevelO) EmotionalDamage(TheTroll);
    //         else GilUp(TheTroll->Troll::gil);
    // }
    // void FightTornBery(BaseOpponent *TornBery){
    //     if (HeadSoldier -> level < TornBery->TornBerry::LevelO) TornBeryFear(TornBery);
    //     else LevelUp(1);
    // }
    // void FightTheQueen(BaseOpponent *TheQueen){
    //     if (TheQueen->QueenOfCards::LevelO > HeadSoldier->level) PayTheDept(2);
    //     else GilUp(HeadSoldier->gil);
    // }
    // void MeetNinaDeRing(BaseOpponent *TheNina){
    //     NinaTransaction();
    // }
    // void LostInTheDurianGarden(BaseOpponent *TheGarden){
    //     RegainHP(HeadSoldier->maxhp);
    // }
    // void FightOmegaWeapon(BaseOpponent *TheMonster){
    //     if (!OmegaWeaponSold)
    //         if ((HeadSoldier->hp == HeadSoldier->maxhp) && (HeadSoldier->level == 10) || (HeadSoldier->knightType == DRAGON))
    //             SellOmegaWeaponAtTheBlackMarket();
    //         else BeingBeatenByOmegaWeapon();
    // }
    // void FightHades(BaseOpponent *TheHades){
    //     if (!HadesIsDead)
    //         if ((HeadSoldier->level == 10) || ((HeadSoldier->knightType == PALADIN) && (HeadSoldier->level >= 8)))
    //             DefeatTheHades();
    //         else EmotionalDamage(TheHades);
    // }
    // void FightUltimecia(BaseOpponent *TheBoss){
    //     if (StoringThe(EXCALIBUR)) {
    //         Victory = 1;
    //         return;
    //     }
    //     if ((StoringThe(GUINEVERE_HAIR)) && (StoringThe(LANCELOT_SPEAR)) && (StoringThe(PALADIN_SHIELD))){
    //         while ((TheBoss->UltimeciaHP > 0) || (KnightCount > 0)){
    //             float Damage = 0;
    //             if (TheKnight[KnightCount - 1].knightType == LANCELOT)
    //                 Damage = HeadSoldier->hp * HeadSoldier->level * LanceLotBaseDamage;
    //             if (TheKnight[KnightCount - 1].knightType == DRAGON)
    //                 Damage = HeadSoldier->hp * HeadSoldier->level * DragonBaseDamage;
    //             if (TheKnight[KnightCount - 1].knightType == PALADIN)
    //                 Damage = HeadSoldier->hp * HeadSoldier->level * PaladinBaseDamage;
    //             TheBoss->UltimeciaHP -= Damage;
    //             if (TheBoss->UltimeciaHP <= 0){
    //                 Victory = 1;
    //                 return;
    //             }
    //             else
    //                 KnightCount--;
    //         }
    //     }
    //     KnightCount = 0;
    // }
    // bool fight(BaseOpponent * opponent){
    //     FightTheOpponent:
    //     if (opponent->IsMadBear) FightTheMadBear(opponent);
    //     else if (opponent->IsBandit) FightTheBandit(opponent);
    //     else if (opponent->IsLupin) FightTheLupin(opponent);
    //     else if (opponent->IsElf) FightTheElf(opponent);
    //     else if (opponent->IsTroll) FightTheTroll(opponent);
    //     else if (opponent->IsTornBerry) FightTornBery(opponent);
    //     else if (opponent->IsQueenOfCards) FightTheQueen(opponent);
    //     else if (opponent->IsNinaDeRings) MeetNinaDeRing(opponent);
    //     else if (opponent->IsDurianGarden) LostInTheDurianGarden(opponent);
    //     else if (opponent->IsOmegaWeapon) FightOmegaWeapon(opponent);
    //     else if (opponent->IsHades) FightHades(opponent);
    //     else if (opponent -> IsPhoenixDownII) ItemRecieve(new BaseItem(PHOENIXDOWN_II));
    //     else if (opponent -> IsPhoenixDownIII) ItemRecieve(new BaseItem(PHOENIXDOWN_III));
    //     else if (opponent -> IsPhoenixDownIV) ItemRecieve(new BaseItem(PHOENIXDOWN_IV));
    //     else if (opponent -> IsExcalibur) PickExcaliburUp();
    //     else if (opponent -> IsUltimecia) FightUltimecia(opponent);
    //     if ((!HeadSoldierSurvived()) && (Survived())) goto FightTheOpponent;
    //     delete [] opponent;
    //     if (KnightCount == 0) return false;
    //     return true;
    // }
    // bool adventure (Events * events){
    //     printInfo();
    //     return true;
    // }
    int count() const{
        return KnightCount;
    }
    BaseKnight * lastKnight() const{
        return HeadSoldier;
    }

    // bool hasPaladinShield() const{
    //     return StoringThe(PALADIN_SHIELD);
    // }
    // bool hasLancelotSpear() const{
    //     return StoringThe(LANCELOT_SPEAR);
    // }
    // bool hasGuinevereHair() const{
    //     return StoringThe(GUINEVERE_HAIR);
    // }
    // bool hasExcaliburSword() const{
    //     return StoringThe(EXCALIBUR);
    // }
    void printInfo() const
    {
        cout << endl << endl;
        for (int i = 0; i < KnightCount; i++){
            printf("The knight in the location %d has the info:\n", i);
            printf("HP(%d), level(%d), gil(%d), antidote(%d) \n",
            TheKnight[i].hp, TheKnight[i].level, TheKnight[i].gil, TheKnight[i].antidote);
        }
    }
    void printResult(bool win) const;
    // friend BaseItem;
};
// inline bool BaseItem::canUse(BaseKnight *knight) {
//     if (knight->HandBag->ItemFound(Identity)) return true;
//     else return false;
// }


class Events {
public:
    string file_of_events = "";
    int EventsCode[999];
    int EventCount;
    Events (const string & file_events){
        file_of_events = file_events;
        ifstream f(file_of_events);
        f >> EventCount;
        for (int i = 0; i < EventCount; i++)
            f >> EventsCode[i];
        f.close();
    }
    int count() const{
        return EventCount;
    }
    int get(int i) const{
        return EventsCode[i];
    }
};
// inline bool BaseBag::CanUsePhoenixDownOfType(ItemType item){
//     if (item == PHOENIXDOWN_I)
//         return (knight->hp <= 0);
//     if (item == PHOENIXDOWN_II)
//         return (knight->hp < knight->maxhp / 4);
//     if (item == PHOENIXDOWN_III)
//         return (knight->hp < knight->maxhp / 3);
//     if (item == PHOENIXDOWN_IV)
//         return (knight->hp < knight->maxhp / 2);
//     return false;
// }

class KnightAdventure {
private:
    ArmyKnights * armyKnights = nullptr;
    Events * events = nullptr;
    int EventCount;
    int KnightsCount;
public:
    KnightAdventure();
    ~KnightAdventure(){
        //delete [] armyKnights;
        //delete [] events;
    }

    void loadArmyKnights(const string &b){
        // ArmyKnights *p;
        // p = new ArmyKnights(b);
        // armyKnights = p; //Error
        // EventCount = armyKnights->KnightCount;
        armyKnights = new ArmyKnights(b);
    }
    void loadEvents(const string &b)
    {
        events = new Events(b);
    }
    void run(){
        for (int EventOrder = 0; EventOrder < EventCount; EventOrder++)
        {
            int EventCode = events->get(EventOrder);
            // if(!armyKnights->fight(new BaseOpponent(EventOrder, EventCode))) break;
            armyKnights->printInfo();
        }
    }
};

#endif // __KNIGHT2_H__