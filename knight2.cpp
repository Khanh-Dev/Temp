#include "knight2.h"

/* * * BEGIN implementation of class BaseBag * * */
bool BaseBag::insertFirst(BaseItem * item) {
    bool result = false;
    if (bag_num_now < max_bag || max_bag == 999) {
        result = true;
    }
    if (item->item == Antidotex && bag_knight->getType() == DRAGON) {
        result = false;
    }

    return result;
}

BaseItem* BaseBag::get(ItemType itemType) {
    BaseItem *temp = head;
    bool result = false;

    while (temp != NULL) {
        if (temp->item = itemType) {
            result = true;
            break;
        }
        else {
            temp = temp->after;
        }
    }

    if (result == true) {       //Neu co vat pham can trong tui do
        if (bag_num_now == 1) {     //Neu co 1 vat pham trong tui do
            head = NULL;
            bag_num_now--;
        }
        else if (bag_num_now >= 2) {        //Neu co tu 2 vat pham tro len trong tui do
            if (head->item == itemType) {   //Neu pham vat can tim o dau tui do
                head = head->after;
                bag_num_now--;
            }
            else {                          //Neu vat pham khong o dau tui do
                BaseItem* currentNode = head;
                BaseItem* preNode = nullptr;
                for (int q = 1; q <= bag_num_now; q++) {
                    if (currentNode->item == itemType) {
                        //Doi cho cho 2 vat pham
                        head = currentNode->after;
                        preNode->after = head;
                        BaseItem* metmoi = currentNode;
                        currentNode = head;
                        head = metmoi;

                        //Xoa vat pham dau
                        head = head->after;
                        bag_num_now--;
                    }
                }
            }

        }
    }

    return temp;
}

string BaseBag::toString() const {              //In ra tui do theo dinh dang
    string first = "Bag[count=" + to_string(bag_num_now) + ";";
    BaseItem *temp = head;
    while (temp != NULL) {
        switch (temp->item)
        {
        case 0:
            first += "Antidote";
            break;
        case 1:
            first += "PhoenixI";
            break;
        case 2:
            first += "PhoenixII";
            break;
        case 3:
            first += "PhoenixIII";
            break;
        case 4:
            first += "PhoenixIV";
            break;
        }
        
        if (temp->after != NULL) {
            first += ",";
        }
        else {
            first += "]";
        }
    }
    return first;
}

//Kế thừa lớp BaseItem viết lại method canUse và use
class Antidote : public BaseItem {
    public:
        Antidote() {item = Antidotex;}
        bool canUse( BaseKnight * knight ) {
            if (knight->getAntidoting() == true) {
                return true;
            }
            else {
                return false;
            }
        }

        void use ( BaseKnight * knight ) {
            knight->setAntidoting(false);
        }

};

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

BagLanceLot::BagLanceLot(int phoenixdownI, int antidote) {
    for (int i = 0; i < phoenixdownI; i++) {
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
    max_bag = 16;
}

BagDragon::BagDragon(int phoenixdownI) {
    for (int i = 0; i < phoenixdownI; i++) {
        BaseItem* abc = new PhoenixDownI();
        abc->after = this->head;
        head = abc;
    }

    bag_num_now = phoenixdownI;
    max_bag = 14;
}

BagNormal::BagNormal(int phoenixdownI, int antidote) {
    for (int i = 0; i < phoenixdownI; i++) {
        BaseItem* abc = new PhoenixDownI();
        abc->after = this->head;
        head = abc;
    }

    for (int i = 0; i < antidote; i++) {
        BaseItem* abc = new Antidote();
        abc->after = this->head;
        head = abc;
    }

    bag_num_now = phoenixdownI + antidote;
    max_bag = 19;
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