#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */
BaseBag::insertFirst(BaseItem * item) {
    bool result = false;
    if (bag_num_now < max_bag || max_bag == 999) {
        result = true;
    }
    if (item->item == Antidotex && bag_knight->getType() == DRAGON) {
        result = false;
    }

    return result;
}

class PhoenixDownI : public BaseItem {
    public:
        PhoenixDownI():BaseItem(){item = PhoenixDownIx;}
        bool canUse( BaseKnight * knight ) {
            if (knight->getHp() <= 0 ) {
                return true;
            }
            else {
                return false;
            }
        }

        void use ( BaseKnight * knight ) {
            int temp_maxHP = knight->getMaxHp();
            knight->setHp(temp_maxHP);
        }

};

class PhoenixDownII : public BaseItem {
    public:
        PhoenixDownII() {item = PhoenixDownIIx;}
        bool canUse( BaseKnight * knight ) {
            int temp_maxHP = knight->getMaxHp();
            int temp_nowHP = knight->getHp();
            if (temp_nowHP < temp_maxHP/4) {
                return true;
            }
            else {
                return false;
            }
        }

        void use ( BaseKnight * knight ) {
            int temp_maxHP = knight->getMaxHp();
            knight->setHp(temp_maxHP);
        }

};

class PhoenixDownIII : public BaseItem {
    public:
        PhoenixDownIII() {item = PhoenixDownIIIx;}
        bool canUse( BaseKnight * knight ) {
            int temp_maxHP = knight->getMaxHp();
            int temp_nowHP = knight->getHp();
            if (temp_nowHP < temp_maxHP/3) {
                return true;
            }
            else {
                return false;
            }
        }

        void use ( BaseKnight * knight ) {
            int temp_maxHP = knight->getMaxHp();
            int temp_nowHP = knight->getHp();
            if (temp_nowHP <= 0) {
                knight->setHp(temp_maxHP/3);
            }
            else {
                knight->setHp(temp_nowHP + temp_maxHP/4);
            }

        }

};

class PhoenixDownIV : public BaseItem {
    public:
        PhoenixDownIV() {item = PhoenixDownIVx;}
        bool canUse( BaseKnight * knight ) {
            int temp_maxHP = knight->getMaxHp();
            int temp_nowHP = knight->getHp();
            if (temp_nowHP < temp_maxHP/2) {
                return true;
            }
            else {
                return false;
            }            
        }

        void use ( BaseKnight * knight ) {
            int temp_maxHP = knight->getMaxHp();
            int temp_nowHP = knight->getHp();
            
            if (temp_nowHP <= 0) {
                knight->setHp(temp_maxHP/2);
            }
            else {
                knight->setHp(temp_nowHP + temp_maxHP/5);
            }
        }

};

BagPaladin::BagPaladin(int phoenixdownI, int antidote) {
    for (int q = 0; q < phoenixdownI; q++) {
        BaseItem* abc = new PhoenixDownI();
        abc->after = head;
        head = abc;  
    }

    for (int i = 0; i < antidote; i++) {
        BaseItem* abc = new Antidote();
        abc->after = head;
        head = abc;
    }

    bag_num_now = phoenixdownI + antidote;
    max_bag = 999; 
}


/* * * END implementation of class BaseBag * * */

/* * * BEGIN implementation of class BaseKnight * * */
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
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

/* * * END implementation of class ArmyKnights * * */

/* * * BEGIN implementation of class KnightAdventure * * */
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

/* * * END implementation of class KnightAdventure * * */