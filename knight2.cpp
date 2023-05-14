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

/* * * Begin implementation of class BaseOpponent* * */
void increaseLevel(BaseKnight *knight) {
    if (knight->getLevel() < 10) {
        knight->setLevel( knight->getLevel() + 1 );
    }
}


BaseOpponent *BaseOpponent::create(int id, int eventID) {
    if (eventID == 1) {
        return new MadBear(id, eventID);
    }
    else if (eventID == 2) {
        return new Bandit(id, eventID);
    }
    else if (eventID == 3) {
        return new LordLupin(id, eventID);
    }
    else if (eventID == 4) {
        return new Elf(id, eventID);
    }
    else if (eventID == 5) {
        return new Troll(id, eventID);
    }
    else if (eventID == 6) {
        return new TornBery(id, eventID);
    }
    else if (eventID == 7) {
        return new QueenOfCards(id, eventID);
    }
    else if (eventID == 8) {
        return new NinaDeRings(id, eventID);
    }
    else if (eventID == 9) {
        return new DurianGarden(id, eventID);
    }
    else if (eventID == 10) {
        return new OmegaWeapon(id, eventID);
    }
    else /*if (eventID == 11)*/ {
        return new Hades(id, eventID);
    }
};

MadBear::MadBear(int id, int eventID) {
    this->id = id;
    levelO = (id+eventID)%10-1;
    gil = 100;
    baseDamage = 10;
    this->eventID = eventID;
}

bool MadBear::fight(BaseKnight *knight) {
    if ( knight->getType() == LANCELOT || knight->getType() == PALADIN || knight->getLevel() >= levelO ) {
        return true;
    }
    else {
        return false;
    }
}

Bandit::Bandit(int id, int eventID) {
    this->id = id;
    levelO = (id+eventID)%10 - 1;
    gil = 150;
    baseDamage = 15;
    this->eventID = eventID;
}

bool Bandit::fight(BaseKnight *knight) {
    if ( knight->getType() == LANCELOT || knight->getType() == PALADIN || knight->getLevel() >= levelO ) {
        return true;
    }
    else {
        return false;
    }
}

LordLupin::LordLupin(int id, int eventID) {
    this->id = id;
    levelO = (id+eventID)%10 - 1;
    gil = 450;
    baseDamage = 45;
    this->eventID = eventID;
}

bool LordLupin::fight(BaseKnight *knight) {
    if ( knight->getType() == LANCELOT || knight->getType() == PALADIN || knight->getLevel() >= levelO ) {
        return true;
    }
    else {
        return false;
    }
}

Elf::Elf(int id, int eventID) {
    this->id = id;
    levelO = (id+eventID)%10 - 1;
    gil = 750;
    baseDamage = 75;
    this->eventID = eventID;
}

bool Elf::fight(BaseKnight *knight) {
    if ( knight->getType() == LANCELOT || knight->getType() == PALADIN || knight->getLevel() >= levelO ) {
        return true;
    }
    else {
        return false;
    }
}

Troll::Troll(int id, int eventID) {
    this->id = id;
    levelO = (id+eventID)%10 - 1;
    gil = 800;
    baseDamage = 95;
    this->eventID = eventID;
}

bool Troll::fight(BaseKnight *knight) {
    if ( knight->getType() == LANCELOT || knight->getType() == PALADIN || knight->getLevel() >= levelO ) {
        return true;
    }
    else {
        return false;
    }
}

TornBery::TornBery(int id, int eventID) {
    this->id = id;
    levelO = (id+eventID)%10 - 1;
    this->eventID = eventID;
}

bool TornBery::fight(BaseKnight *knight) {
    if ( knight->getLevel() >= levelO ) {
        increaseLevel(knight);
        return true;
    }
    else {
        knight->setAntidoting(true);
        BaseItem *temp = knight->getBag()->head;               

        while (temp != NULL) {
            if ( temp->canUse(knight) ) {         //Khi duyet tui do neu vat pham do dung duoc
                temp = knight->getBag()->get(temp->item);
                temp->use(knight);

                //Xoa di item do, chua hoan thien
                break;      //Thoat vong duyet tui do
            }
            else {
                temp = temp->after;             //Di den vat pham ke tiep trong tui do
            }
        }

        if (knight->getAntidoting() == true) {
            if (knight->getBag()->bag_num_now <= 3) {
                knight->getBag()->head = nullptr;
                knight->getBag()->bag_num_now = 0;
            }
            else {
                for (int z = 1; z <=3; z++) {
                    BaseItem *temp = knight->getBag()->head;
                    knight->getBag()->head = temp->after;
                }
                knight->getBag()->bag_num_now -= 3;
            }
            knight->setHp(knight->getHp() - 10);
            if (knight->getHp() <= 0) {
                BaseItem *temp = knight->getBag()->head;               

                while (temp != NULL) {
                    if ( temp->canUse( knight ) ) {         //Khi duyet tui do neu vat pham do dung duoc
                        temp = knight->getBag()->get(temp->item);
                        temp->use( knight );

                        //Xoa di item do, chua hoan thien
                        break;      //Thoat vong duyet tui do
                    }
                    else {
                        temp = temp->after;             //Di den vat pham ke tiep trong tui do
                    }
                }

                if (knight->getHp() <= 0){
                    return false;
                }
            }
        }
        
    }

    return true;
}

QueenOfCards::QueenOfCards(int id, int eventID) {
    this->id = id;
    levelO = (id+eventID)%10 - 1;
    this->eventID = eventID;
}

bool QueenOfCards::fight(BaseKnight *knight) {
    return true;
}

NinaDeRings::NinaDeRings(int id, int eventID) {
    this->id = id;
    levelO = (id+eventID)%10 - 1;
    this->eventID = eventID;
}

bool NinaDeRings::fight(BaseKnight *knight) {
    return true;
}

DurianGarden::DurianGarden(int id, int eventID) {
    this->id = id;
    levelO = (id+eventID)%10 - 1;
    this->eventID = eventID;
}

bool DurianGarden::fight(BaseKnight *knight) {
    knight->setHp( knight->getMaxHp() );
    return true;
}

OmegaWeapon::OmegaWeapon(int id, int eventID) {
    this->id = id;
    levelO = (id+eventID)%10 - 1;
    this->eventID = eventID;
}

bool OmegaWeapon::fight(BaseKnight *knight) {
    if ( (knight->getLevel() == 10 && knight->getHp() == knight->getMaxHp()) || knight->getType() == DRAGON ) {
        return true;
    }
    else {
        return false;
    }
}

Hades::Hades(int id, int eventID) {
    this->id = id;
    levelO = (id+eventID)%10 - 1;
    this->eventID = eventID;
}

bool Hades::fight(BaseKnight *knight) {
    if (knight->getLevel() == 10 || (knight->getType() == PALADIN && knight->getLevel() >= 8)) {
        return true;
    }
    else {
        return false;
    }
}
/* * * END implement of class BaseOpponent * * */

/* * * BEGIN implementation of class BaseKnight * * */
bool check_Prime(int n ) {              //Kiem tra so nguyen to
    int count  = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i  == 0) {
            count++;
        }
    }
    if (count  == 2) {
        return true;
    }
    else {
        return false;
    }
}

bool check_Pythagoras(int n) {          //Kiem tra so Pythagoras   
    int a,b,c;
    if (n >= 100) {
        a = n % 10;
        b = (n % 100) / 10;
        c = n / 100;
    }
    if (a*a + b*b == c*c || a*a + c*c == b*b || b*b + c*c == a*a) {
        return true;
    }
    else {
        return false;
    }
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