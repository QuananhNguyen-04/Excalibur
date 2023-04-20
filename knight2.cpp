#include "knight2.h"

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
// void ArmyKnights::printInfo() const {
//     cout << "No. knights: " << this->count();
//     if (this->count() > 0) {
//         BaseKnight * lknight = lastKnight(); // last knight
//         cout << ";" << lknight->toString();
//     }
//     // cout << ";PaladinShield:" << this->hasPaladinShield()
//     //     << ";LancelotSpear:" << this->hasLancelotSpear()
//     //     << ";GuinevereHair:" << this->hasGuinevereHair()
//     //     << ";ExcaliburSword:" << this->hasExcaliburSword()
//     //     << endl
//     //     << string('-', 50) << endl;
// }

int BaseKnight::fight(BaseOpponent * opponent) {
    int gilGain;
    opponent->klevel = level;
    if (opponent->result()) {
        gilGain = opponent->reward();
        return remainGil(gilGain);
    }
    else {
        hp -= opponent->lose();
        if (!revive()) return -1;
    }
    return 0;
}

bool ArmyKnights::adventure(Events * events) {
    for (int i = 0; i < events->count(); ++i) {
        int event = events->get(i);
        cout << event << ": \n";
        switch (event)
        {
        case 1 ... 11: {
            BaseOpponent * opponent = new BaseOpponent;
            opponent->create(i, event);
            // fight(opponent);
            delete opponent;
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

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    army = nullptr;
    events = nullptr;
}

/* * * END implementation of class KnightAdventure * * */
/* * * BEGIN implementation of class BaseBag * * */

/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */