#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
class BaseKnight;
class BaseBag;
class BaseOpponent;
class BaseItem;
class Events;
class ArmyKnights;
class KnightAdventure;

bool check_Prime(int n);
bool check_Pythagoras(int n);


enum ItemType {Antidotex = 0, PhoenixDownIx, PhoenixDownIIx, PhoenixDownIIIx, PhoenixDownIVx};            //Cac loai vat pham

class BaseBag {
protected:
    BaseKnight* bag_knight;
    BaseItem* head = NULL;
    int bag_num_now = 0;
    int max_bag;

public:
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
    friend class TornBery;

    BaseItem* getHead() {
        return head;
    }
    void setHead(BaseItem* head) {
        this->head = head;
    }

    void setNumBag(int n) {
        bag_num_now += n;
    }

    int getNumBag() {
        return bag_num_now;
    }
    
    
};

class BagPaladin : public BaseBag {
    public:
        BagPaladin(int phoenixdownI, int antidote);      
};

class BagLanceLot : public BaseBag {
    public:
        BagLanceLot(int phoenixdownI, int antidote);     
};

class BagDragon : public BaseBag {
    public:
        BagDragon(int phoenixdownI);
   
};

class BagNormal : public BaseBag {
    public:
        BagNormal(int phoenixdownI, int antidote);
        
};

class BaseOpponent {
    protected:
        int id;
        int levelO;
        int gil;
        int baseDamage;
        int eventID;
        bool ren_kiem = false;

    public:
        static BaseOpponent *create(int id, int eventID);

        virtual bool fight(BaseKnight *knight){
            return true;
        }
        //void hoi_mau(BaseKnight *knight);
        //void increaseLevel(BaseKnight *knight);

        int getId() const {
            return id;
        }
        int getGil() {
            return gil;
        }
        int getBaseDamage() {
            return baseDamage;
        }

        int getLevelO() {
            return levelO;
        }
        int getEventID() {
            return eventID;
        }

};

class MadBear : public BaseOpponent {
    public:
        MadBear(int id, int eventID);
        bool fight(BaseKnight *knight);
};
class Bandit : public BaseOpponent {
    public:
        Bandit(int id, int eventID);
        bool fight(BaseKnight *knight);
};

class LordLupin : public BaseOpponent {
    public:
        LordLupin(int id, int eventID);
        bool fight(BaseKnight *knight);
};
class Elf : public BaseOpponent {
    public:
        Elf(int id, int eventID);
        bool fight(BaseKnight *knight);
};

class Troll : public BaseOpponent {
    public:
        Troll(int id, int eventID);
        bool fight(BaseKnight *knight);
};
class TornBery : public BaseOpponent {
    public:
        TornBery(int id, int eventID);
        bool fight(BaseKnight *knight);
};

class QueenOfCards : public BaseOpponent {
    public:
        QueenOfCards(int id, int eventID);
        bool fight(BaseKnight *knight);
};
class NinaDeRings : public BaseOpponent {
    public:
        NinaDeRings(int id, int eventID);
        bool fight(BaseKnight *knight);
};
class DurianGarden : public BaseOpponent {
    public:
        DurianGarden(int id, int eventID);
        bool fight(BaseKnight *knight);
};
class OmegaWeapon : public BaseOpponent {
    public:
        OmegaWeapon(int id, int eventID);
        bool fight(BaseKnight *knight);
};
class Hades : public BaseOpponent {
    public:
        Hades(int id, int eventID);
        bool fight(BaseKnight *knight);
};



enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    int phoenixdownI;
    float knightBaseDamage;
    BaseBag * bag;
    KnightType knightType;

    //Khai bao them method cho baseKnight
    bool antidoting = false;
    bool win_Omega = false;
    bool win_Hades = false;

public:
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;        //Do nothing

    KnightType getType() {
        return knightType;
    }
    BaseBag* getBag() {
        return bag;
    }
    float getKnightBaseDamage() {
        return knightBaseDamage;
    }
    int getId() {
        return id;
    }
    int getMaxHp() {
        return maxhp;
    }
    int getHp() {
        return hp;
    }
    void setHp(int hp) {
        this->hp = hp;
    }
    int getLevel(){
        return level;
    }
    void setLevel(int level) {
        this->level = level;
    }
    int getGil() {
        return gil;
    }
    void setGil(int gil) {
        this->gil = gil;
    }
    int getAntidote(){
        return antidote;
    }
    void setAntidote(int antidote) {
        this->antidote = antidote;
    }
    int getPhoenixdownI() {
        return phoenixdownI;
    }
    void setPhoenixdownI(int phoenixdownI) {
        this->phoenixdownI = phoenixdownI;
    }
    bool getAntidoting() {
        return antidoting;
    }
    void setAntidoting(bool antidoting) {
        this->antidoting = antidoting;
    }
    bool get_win_Omega() {
        return win_Omega;
    }
    void set_win_Omega(bool win_Omega) {
        this->win_Omega = win_Omega;
    }
    bool get_win_Hades() {
        return win_Hades;
    }
    void set_win_Hades(bool win_Hades) {
        this->win_Hades = win_Hades;
    }
};

class PaladinKnight : public BaseKnight {
    public:
        PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class LancelotKnight : public BaseKnight {
    public:
        LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class DragonKnight : public BaseKnight {
    public:
        DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};
class NormalKnight : public BaseKnight {
    public:
        NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
};

class ArmyKnights {
protected:
    int num_armyknight;
    BaseKnight** arr_armyknight;

    //Khai bao them method cho doi quan hiep si
    bool shield = false;
    bool spear = false;
    bool hair = false;
    bool sword = false;
    bool meet_omega = false;
    bool meet_hades = false;
public:
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const {
        if (num_armyknight == 0) {
            return NULL;
        }
        else {
            return arr_armyknight[num_armyknight-1];
        }
    };

    //Ve khien cua Paladin
    void setShield(bool shield) {
        this->shield = shield;
    }
    bool hasPaladinShield() const;

    //Ve ngon giao cua LanceLot
    void setSpear(bool spear) {
        this->spear = spear;
    }
    bool hasLancelotSpear() const;

    //Ve Toc cua Guiniver
    void setGuiniHair(bool guini_hair) {
        this->hair = guini_hair;
    }
    bool hasGuinevereHair() const;

    //Ve Guom Excalibur
    void setSword(bool sword) {
        this->sword = sword;
    }
    bool hasExcaliburSword() const;

    //Do nothing below
    void printInfo() const;
    void printResult(bool win) const;
};

class BaseItem {
public:
    BaseItem(){};
    BaseItem* after = nullptr;
    ItemType item;
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};


class Events {
private:
    int num_event;        //Khai bao can thiet 
    int *arr_event;
public:
    Events(const string & file_events);

    int count() const {
        return num_event;
    }
    int get(int i) const {
        return arr_event[i];
    }

    ~Events();
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure() {
        delete armyKnights;
        delete events;
    }

    void loadArmyKnights(const string &file_army) {
        armyKnights = new ArmyKnights(file_army);
    }
    void loadEvents(const string &file_events) {
        events = new Events(file_events);
    }
    void run() {
        bool xyz = armyKnights->adventure(events);
        armyKnights->printResult(xyz);
    }
};

#endif // __KNIGHT2_H__