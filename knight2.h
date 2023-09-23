#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
class Events;
class BaseItem;
class PhoenixdownI;
class PhoenixdownII;
class PhoenixdownIII;
class PhoenixdownIV;
class BaseKnight;
class LancelotKnight;
class PaladinKnight;
class DragonKnight;
class NormalKnight;
class LancelotBag;
class PaladinBag;
class DragonBag;
class NormalBag;
class Antidote;
class BaseBag;
class BaseOpponent;
class Madbear;
class Bandit;
class LordLupin;
class Elf;
class Troll;
class Tornbery;
class QueenOfCards;
class NinaDeRings;
class DurianGarden;
class OmegaWeapon;
class Hades;
class Ultimecia;
class KnightAdventure;



enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL };
enum ItemType { ANTIDOTE = 0, PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII, PHOENIXDOWNIV };

//-------------------------------------------EVENTS--------------------------------------------------
class Events {
private:
    int soevents;
    int* eventcode;
public:
    Events(const string& file_events);
    ~Events();
    int count() const;
    int get(int i) const;
    void in();
};
//----------------------KNIGHT----------------------
class BaseKnight {
protected:
    int id;
    int hp;
    int maxhp;
    int level;
    int gil;
    int antidote;
    int phoenixdownI;
    BaseBag* bag;
    KnightType knightType;
    bool trungdoc = 0;
public:
    static BaseKnight* create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    static bool isPaladin(int maxhp);
    static bool isLancelot(int maxhp);
    static bool isDragon(int maxhp);
    int gethp();
    int getmaxhp();
    int getlevel();
    int getgil();
    void setgil(int a);
    void sethp(int a);
    void setlevel(int a);
    BaseBag* getbag();
    void setbag(BaseBag*b);
    bool gettrungdoc();
    void settrungdoc(bool a);
    string toString() const;
    void in();
    bool healed = false;
    int getid();
    BaseKnight* next;
    ~BaseKnight();
    

};
class LancelotKnight :public BaseKnight {
public:
    LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    
};
class PaladinKnight :public BaseKnight {
public:
    PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
   
};
class DragonKnight :public BaseKnight {
public:
    DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    
};
class NormalKnight :public BaseKnight {
public:
    NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    
};
//---------------------------ITEM-----------------

class BaseItem {
public:
    virtual bool canUse(BaseKnight* knight) = 0;
    virtual void use(BaseKnight* knight) = 0;
    BaseItem* next;
    ItemType itemtype;
    //~BaseItem();


};
class PhoenixdownI :public BaseItem {
public:
    PhoenixdownI()
    {
        this->itemtype = PHOENIXDOWNI;
    }
    virtual bool canUse(BaseKnight* knight)
    {
        if (knight->gethp() <= 0) {
           // cout << "da dung phoenix1";
            return 1;
        }
        return 0;
    }
    virtual void use(BaseKnight* knight) {
        knight->sethp(knight->getmaxhp());

    }
   
};
class PhoenixdownII :public BaseItem {
public:
    PhoenixdownII()
    {
        this->itemtype = PHOENIXDOWNII;
    }
    virtual bool canUse(BaseKnight* knight)
    {
        if (knight->gethp() < (knight->getmaxhp()) / 4) {
            return 1;
        }
        return 0;
    }
    virtual void use(BaseKnight* knight) {
        knight->sethp(knight->getmaxhp());

    }
   
};
class PhoenixdownIII :public BaseItem {
public:
    PhoenixdownIII()
    {
        this->itemtype = PHOENIXDOWNIII;
    }
    virtual bool canUse(BaseKnight* knight)
    {
        if (knight->gethp() < (knight->getmaxhp()) / 3) {
            return 1;
        }
        return 0;
    }
    virtual void use(BaseKnight* knight) {
        int maxhp = knight->getmaxhp();
        if (knight->gethp() <= 0) {
            knight->sethp((knight->getmaxhp()) / 3);
        }
        else {
            knight->sethp(knight->gethp() + maxhp / 4);

        }
    }
   
};
class PhoenixdownIV :public BaseItem {
public:
    PhoenixdownIV()
    {
        this->itemtype = PHOENIXDOWNIV;
    }
    virtual bool canUse(BaseKnight* knight)
    {
        if (knight->gethp() < (knight->getmaxhp()) / 2) {
            return 1;
        }
        return 0;
    }
     virtual void use(BaseKnight* knight) {
        int maxhp = knight->getmaxhp();
        if (knight->gethp() <= 0) {
            knight->sethp(maxhp / 2);
        }
        else {
            knight->sethp(knight->gethp() + maxhp / 5);
        }
    }
    
};
class Antidote :public BaseItem {
public:
    Antidote()
    {

        this->itemtype = ANTIDOTE;
    }
    virtual bool canUse(BaseKnight* knight)
    {
        if (knight->gettrungdoc()) {
            return 1;
        }
        return 0;
    }
    virtual void use(BaseKnight* knight) {
        knight->settrungdoc(0);
    }
   
};
//---------------------------------------------BAG-----------------------------------------
class BaseBag {
protected:
    int bag_present;
    int bag_max;
public:
    BaseItem* head = NULL;
    BaseKnight* p;
    virtual bool insertFirst(BaseItem* item);//khong xai toi'
    virtual BaseItem* get(ItemType itemType);
    void sudung(BaseKnight* knight);
    void swap(BaseItem* item);
    void themvatpham(BaseItem* item);
    void deletefirst();
    virtual bool insert() = 0;
    ~BaseBag();
    
       
    
    virtual string toString() const
    {
        string s = "";
        s += "Bag[count="; s += to_string(bag_present); s += ";";
        if (bag_present == 0) { s += ']'; return s; }
        BaseItem* p = head;
        while (p != NULL)
        {
            if (p->itemtype == PHOENIXDOWNI) s += "PhoenixI,";
            else if (p->itemtype == PHOENIXDOWNII) s += "PhoenixII,";
            else if (p->itemtype == PHOENIXDOWNIII) s += "PhoenixIII,";
            else if (p->itemtype == PHOENIXDOWNIV) s += "PhoenixIV,";
            else if (p->itemtype == ANTIDOTE) s += "Antidote,";
            p = p->next;
        }
        if (s[s.length() - 1] == ',') s[s.length() - 1] = ']';
        return s;
    }
    void show();
    int getbag_present();
};
class PaladinBag : public BaseBag {

public:
    PaladinBag(int a, int b);
    bool insert();
};
class LancelotBag : public BaseBag {

public:
    LancelotBag(int a, int b);
    bool insert();
};
class DragonBag : public BaseBag {

public:
    DragonBag(int a);
    bool insert();
};
class NormalBag : public BaseBag {

public:
    NormalBag(int a, int b);
    bool insert();
};
//------------------------------------OPPONENT----------------------------------------------------------@@
class BaseOpponent {
public:
    int hpboss = 0;
    int gilthuong=0;
    int levelO=0;
    int basedame=0;
    BaseKnight* tmp;
    virtual void fight() = 0;
   
};

class Madbear :public BaseOpponent {
public:
    Madbear(int i, Events* event,BaseKnight*p);
   virtual void fight();

};
class Bandit :public BaseOpponent {
public:
    Bandit(int i, Events* event,BaseKnight*p);
    virtual void fight();
};
class LordLupin :public BaseOpponent {
public:
    LordLupin(int i, Events* event,BaseKnight*p);
    virtual void fight();
};
class Elf :public BaseOpponent {
public:
    Elf(int i, Events* event,BaseKnight*p);
    virtual void fight();
};
class Troll :public BaseOpponent {
public:
    Troll(int i, Events* event,BaseKnight*p);
    virtual void fight();
};
class Tornbery:public BaseOpponent{
public:
    Tornbery(int i, Events* event, BaseKnight* p);
    virtual void fight();
};
class QueenOfCards :public BaseOpponent {
public:
    QueenOfCards(int i, Events* event, BaseKnight* p);
    virtual void fight();
};
class NinaDeRings :public BaseOpponent {
public:
    NinaDeRings(BaseKnight* p);
    virtual void fight();
};
class DurianGarden :public BaseOpponent {
public:
    DurianGarden(BaseKnight* p);
    virtual void fight();
};
class OmegaWeapon :public BaseOpponent {
public:
    OmegaWeapon(int i, Events* event, BaseKnight* p);
    virtual void fight();
};
class Hades :public BaseOpponent {
public:
    Hades(BaseKnight* p);
    virtual void fight();
    
};
class Ultimecia :public BaseOpponent {
public: 
    Ultimecia(int i,BaseKnight*p);
    virtual void fight();
};
//-----------------------------------------------ARMYYY----------------------------------------------------------

class ArmyKnights {

public:
    ArmyKnights(const string& file_armyknights);
    ~ArmyKnights();
         
    int sohiepsi;
    BaseKnight* head=NULL;
    bool shield = false;
    bool spear = false;
    bool hair = false;
    bool sword = false;
    int count() const;//xong
    BaseKnight* lastKnight() const;
    bool fight(BaseOpponent* opponent);
    bool adventure(Events* events);
    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;
    void in();
    void printInfo() const;
    void printResult(bool win) const;
    void resetlastknight();
    friend class Hades;
    bool danhboss(BaseOpponent* ultimecia);
    bool Omegawined = 0;
    bool Hadeswined = 0;
};
//----------------------------ADVENTURE-------------------------------------------------------------
class KnightAdventure {
public:
    ArmyKnights* armyKnights;
    Events* events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string& file_armyknights) {
        this->armyKnights = new ArmyKnights(file_armyknights);
    }
    void loadEvents(const string& file_events) {
        this->events = new Events(file_events);
    }
    void run() {
        bool win;
        if (armyKnights->adventure(events)) { win = true; }
        else { win = false; }
        armyKnights->printResult(win);
       
    }

};


#endif // __KNIGHT2_H__