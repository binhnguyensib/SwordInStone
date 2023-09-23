#include "knight2.h"

//-----------EVENT-------------
Events::Events(const string& file_events) {
    ifstream fin;
    fin.open(file_events);
    fin >> soevents;
    eventcode = new int[soevents];
    for (int i = 0; i < soevents; i++) {
        fin >> eventcode[i];
    }
    fin.close();


}
int Events::count() const {
    return this->soevents;
}
int Events::get(int i) const {
    return this->eventcode[i];
}
void Events::in() {
    cout << this->soevents << endl;
    for (int i = 0; i < this->soevents; i++) {
        cout << this->eventcode[i] << " ";
    }
}
Events::~Events() {
    delete[] eventcode;
}
//----------------------KNIGHT-------------------
LancelotKnight::LancelotKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    this->id = id;
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->knightType = LANCELOT;
    this->bag = new LancelotBag(phoenixdownI, antidote);
}
PaladinKnight::PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    this->id = id;
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->knightType = PALADIN;
    this->bag = new PaladinBag(phoenixdownI, antidote);

}
DragonKnight::DragonKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    this->id = id;
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->knightType = DRAGON;
    this->bag = new DragonBag(phoenixdownI);

}
NormalKnight::NormalKnight(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    this->id = id;
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->level = level;
    this->gil = gil;
    this->antidote = antidote;
    this->phoenixdownI = phoenixdownI;
    this->knightType = NORMAL;
    this->bag = new NormalBag(phoenixdownI, antidote);

}
bool BaseKnight::isLancelot(int maxhp) {
    if (maxhp == 888) { return true; }
    else { return false; }
}
bool BaseKnight::isPaladin(int maxhp) {
    if (maxhp < 2) {
        return false;
    }
    for (int i = 2; i <= sqrt(maxhp); i++) {
        if (maxhp % i == 0) {
            return false;
        }
    }
    return true;
}
bool BaseKnight::isDragon(int maxhp) {
    if (maxhp == 345 || maxhp == 354 || maxhp == 435 || maxhp == 453 || maxhp == 534 || maxhp == 543) { return true; }
    else { return false; }
}
void BaseKnight::in() {
    cout << id << " " << maxhp << " " << level << " " << phoenixdownI << " " << gil << " " << antidote << " " << knightType << endl;
    this->bag->show();
}
int BaseKnight::gethp() {
    return hp;
}
int BaseKnight::getmaxhp() { return maxhp; }
bool BaseKnight::gettrungdoc() { return trungdoc; }
void BaseKnight::sethp(int a) {
    this->hp = a;
}
void BaseKnight::settrungdoc(bool a) {
    this->trungdoc = a;
}
int BaseKnight::getlevel() { return level; }
void BaseKnight::setgil(int a) { this->gil = a; }
int BaseKnight::getgil() { return gil; }
BaseKnight* BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
    bool islancelot = isLancelot(maxhp);
    bool ispaladin = isPaladin(maxhp);
    bool isdragon = isDragon(maxhp);
    if (islancelot) {
        BaseKnight* lancelot = new LancelotKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        return lancelot;
    }
    else if (ispaladin) {
        BaseKnight* paladin = new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        return paladin;
    }
    else if (isdragon) {
        BaseKnight* dragon = new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        return dragon;
    }
    else {
        BaseKnight* normal = new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        return normal;
    }

}
string BaseKnight::toString() const {
    string typeString[4] = { "PALADIN", "LANCELOT", "DRAGON", "NORMAL" };
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
BaseBag* BaseKnight::getbag() { return bag; }
void BaseKnight::setbag(BaseBag* b) {
    this->bag = b;
}
void BaseKnight::setlevel(int a) { this->level = a; }
int BaseKnight::getid() { return id; }
BaseKnight::~BaseKnight() {
    delete bag;
}


//-----------------BAG-------------------------------
void BaseBag::show()
{
    BaseItem* p = head;
    while (p != NULL)
    {
        cout << p->itemtype << " ";
        p = p->next;
    }
    cout << endl;
}
bool BaseBag::insertFirst(BaseItem* item) {
    return true;
}
BaseItem* BaseBag::get(ItemType itemType) {
    BaseItem* p = head;
    while (p->itemtype != itemType) {
        if (p != NULL) { p = p->next; }
        else
        {
            return NULL;
        }
    }
    return p;

}
void BaseBag::swap(BaseItem* item) {
    BaseItem* sauhead = this->head->next;
    BaseItem* sau = item->next;
    BaseItem* truoc = item;
    if (sauhead == NULL) {
        return;
    }
    if (head != item)
        if (head->next != item)
        {
            while (truoc->next != item) {
                truoc = truoc->next;
            }
            head->next = sau;
            truoc->next = head;
            item->next = sauhead;
            head = item;
        }
        else
        {
            item->next = head;
            head->next = sau;
            head = item;
        }

}
void BaseBag::themvatpham(BaseItem* item) {
    item->next = head;
    head = item;
    bag_present++;
}
void BaseBag::deletefirst() {
    if (head == NULL) { return; }
    BaseItem* tmp = head;
    head = head->next;
    delete tmp;
    bag_present--;
}
void BaseBag::sudung(BaseKnight* knight) {
    BaseItem* p = head;
    for (int i = 0; i < bag_present; i++) {
        if (p->itemtype == PHOENIXDOWNI) {
            if (p->canUse(knight)) {
                p->use(knight);
               // cout << "da dung phoenix1";
                swap(get(PHOENIXDOWNI));
                deletefirst();
                knight->healed = true;
                return;
            }
            p = p->next;

        }
        else if (p->itemtype == PHOENIXDOWNII) {
            if (p->canUse(knight)) {
                p->use(knight);
                swap(get(PHOENIXDOWNII));
                deletefirst();
                knight->healed = true;
                return;
            }
            p = p->next;
        }
        else if (p->itemtype == PHOENIXDOWNIII) {
            if (p->canUse(knight)) {
                p->use(knight);
                swap(get(PHOENIXDOWNIII));
                deletefirst();
                knight->healed = true;
                return;
             }
            p = p->next;
        }
        else if (p->itemtype == PHOENIXDOWNIV) {
            if (p->canUse(knight)) {
                p->use(knight);
                swap(get(PHOENIXDOWNIV));
                deletefirst();
                knight->healed = true;
                return;
            }
            p = p->next;
        }
        else if (p->itemtype == ANTIDOTE) {
            if (p->canUse(knight)) {
                p->use(knight);
                swap(get(ANTIDOTE));
                deletefirst();
                knight->healed = true;
                return;
            }
            p = p->next;
        }
    }
    if (knight->gethp() <= 0) {
        if (knight->getgil() >= 100) {
            knight->sethp(knight->getmaxhp() / 2);
            knight->setgil(knight->getgil() - 100);
            knight->healed = true;
        }
        else { return; }
    }

}
PaladinBag::PaladinBag(int a, int b) {
    bag_present = a + b;
    bag_max = bag_present + 1;
    for (int i = 0; i < a; i++) {
        PhoenixdownI* x = new PhoenixdownI;
        x->next = head;
        head = x;
    }
    for (int i = 0; i < b; i++) {
        Antidote* x = new Antidote;
        x->next = head;
        head = x;
    }
}
bool PaladinBag::insert() { return true; }
LancelotBag::LancelotBag(int a, int b) {
    bag_max = 16;
    bag_present = a + b;
    for (int i = 0; i < a; i++) {
        PhoenixdownI* x = new PhoenixdownI;
        x->next = head;
        head = x;
    }
    for (int i = 0; i < b; i++) {
        Antidote* x = new Antidote;
        x->next = head;
        head = x;
    }

}
bool LancelotBag::insert() {
    if (bag_present < bag_max) { return true; }
    return false;
}
DragonBag::DragonBag(int a) {
    bag_max = 14;
    bag_present = a;
    for (int i = 0; i < a; i++) {
        PhoenixdownI* x = new PhoenixdownI;
        x->next = head;
        head = x;
    }

}
bool DragonBag::insert() {
    if (bag_present < bag_max) { return true; }
    return false;
}
NormalBag::NormalBag(int a, int b) {
    bag_max = 19;
    bag_present = a + b;
    for (int i = 0; i < a; i++) {
        PhoenixdownI* x = new PhoenixdownI;
        x->next = head;
        head = x;
    }
    for (int i = 0; i < b; i++) {
        Antidote* x = new Antidote;
        x->next = head;
        head = x;
    }
}
bool NormalBag::insert() {
    if (bag_present < bag_max) { return true; }
    return false;
}
int BaseBag::getbag_present() { return bag_present; }
BaseBag::~BaseBag() {
    BaseItem* p = head;
    while (head != NULL)
    {
        p = head;
        head = head->next;
        delete p;
    }
}


//--------------------OPPONENT-------------------------------
Madbear::Madbear(int i, Events* event,BaseKnight*p) {
    this->basedame = 10;
    this->levelO = (i + event->get(i)) % 10 + 1;
    this->tmp = p;
    //cout << levelO;
}
void Madbear::fight() {
    tmp->healed = false;
    if (tmp->isLancelot(tmp->getmaxhp()) || tmp->isPaladin(tmp->getmaxhp()) || tmp->getlevel() >= levelO) {
        gilthuong = 100;
    }
    else {
        
        int dame = basedame * (levelO - tmp->getlevel());
        tmp->sethp(tmp->gethp() - dame);
        tmp->getbag()->sudung(tmp);
    }
}
Bandit::Bandit(int i, Events* event,BaseKnight*p) {
    this->basedame = 15;
    this->levelO = (i + event->get(i)) % 10 + 1;
    this->tmp = p;
}
void Bandit::fight() {
    tmp->healed = false;
    if (tmp->isLancelot(tmp->getmaxhp()) || tmp->isPaladin(tmp->getmaxhp()) || tmp->getlevel() >= levelO) {
        gilthuong = 150;
    }
    else {
        int dame = basedame * (levelO - tmp->getlevel());
        //cout << dame << endl;
        tmp->sethp(tmp->gethp() - dame);
        //cout << tmp->gethp() << endl;
        tmp->getbag()->sudung(tmp);
    }
}
LordLupin::LordLupin(int i, Events* event,BaseKnight*p) {
    this->basedame = 45;
    this->levelO = (i + event->get(i)) % 10 + 1;
    this->tmp = p;
    
}
void LordLupin::fight() {
    tmp->healed = false;
    if (tmp->isLancelot(tmp->getmaxhp()) || tmp->isPaladin(tmp->getmaxhp()) || tmp->getlevel() >= levelO) {
        gilthuong = 450;
    }
    else {
        int dame = basedame * (levelO - tmp->getlevel());
        //cout << dame << endl;
        tmp->sethp(tmp->gethp() - dame);
        //cout << tmp->gethp() << endl;
        tmp->getbag()->sudung(tmp);
    }
}
Elf::Elf(int i, Events* event,BaseKnight*p) {
    this->basedame = 75;
    this->levelO = (i + event->get(i)) % 10 + 1;
    this->tmp = p;
}
void Elf::fight() {
    tmp->healed = false;
    if (tmp->isLancelot(tmp->getmaxhp()) || tmp->isPaladin(tmp->getmaxhp()) || tmp->getlevel() >= levelO) {
        gilthuong = 750;
    }
    else {
        int dame = basedame * (levelO - tmp->getlevel());
        //cout << dame << endl;
        tmp->sethp(tmp->gethp() - dame);
        //cout << tmp->gethp() << endl;
        tmp->getbag()->sudung(tmp);
    }
}
Troll::Troll(int i, Events* event,BaseKnight*p) {
    this->basedame = 95;
    this->levelO = (i + event->get(i)) % 10 + 1;
    this->tmp = p;
}
void Troll::fight() {
    tmp->healed = false;
    if (tmp->isLancelot(tmp->getmaxhp()) || tmp->isPaladin(tmp->getmaxhp()) || tmp->getlevel() >= levelO) {
        gilthuong = 800;
    }
    else {
        int dame = basedame * (levelO - tmp->getlevel());
        //cout << dame << endl;
        tmp->sethp(tmp->gethp() - dame);
        //cout << tmp->gethp() << endl;
        tmp->getbag()->sudung(tmp);
    }
}
Tornbery::Tornbery(int i, Events* event, BaseKnight* p) {
    this->basedame = 0;
    this->levelO = (i + event->get(i)) % 10 + 1;
    this->tmp = p;
}
void Tornbery::fight(){
    tmp->healed = false;
    if (tmp->getlevel()>=levelO)
    {
        int level = tmp->getlevel();
        if (level >= 9) { tmp->setlevel(10); }
        else { tmp->setlevel(level + 1); }
    }
    else
    {
        if (tmp->isDragon(tmp->getmaxhp())) { return; }
        else {
            tmp->settrungdoc(true);
            tmp->getbag()->sudung(tmp);
            if (tmp->gettrungdoc() == true) {
                int a = tmp->getbag()->getbag_present();
                if (a <= 3) {
                    for (int i = 0; i < a; i++) {
                        tmp->getbag()->deletefirst();
                    }
                }
                else {
                    for (int i = 0; i < 3; i++) {
                        tmp->getbag()->deletefirst();
                    }
                }
                int hp = tmp->gethp();
                if (hp - 10 <= 0) {
                    tmp->sethp(hp - 10);
                    tmp->getbag()->sudung(tmp);
                }
                else { tmp->sethp(hp - 10); }

            }

        }
    }
}
QueenOfCards::QueenOfCards(int i, Events* event, BaseKnight* p) {
    this->basedame = 0;
    this->levelO = (i + event->get(i)) % 10 + 1;
    this->tmp = p;
}
void QueenOfCards::fight() {
    if (tmp->getlevel() >= levelO)
    {
        int g = tmp->getgil();
        if (2 * g > 999) {
            tmp->setgil(999);
            this->gilthuong = 2 * g - 999;
        }
        else {
            tmp->setgil(2 * g);
        }
    }
    else {
        if (tmp->isPaladin(tmp->getmaxhp())) { return; }
        int g = tmp->getgil();
        tmp->setgil(g / 2);
    }
}
NinaDeRings::NinaDeRings(BaseKnight* p) {
    this->tmp = p;
}
void NinaDeRings::fight() {
    int hp = tmp->gethp();
    int maxhp = tmp->getmaxhp();
    int gil = tmp->getgil();
    if (tmp->isPaladin(maxhp)) {
        if (hp <  maxhp/3) {
            hp = hp + maxhp / 5;
            tmp->sethp(hp);
        }
    }
    else {
        if (gil >= 50 && hp < maxhp / 3) {
            tmp->sethp(hp + maxhp / 5);
            tmp->setgil(gil - 50);
        }
    }
}
DurianGarden::DurianGarden(BaseKnight* p) {
    this->tmp = p;
}
void DurianGarden::fight() {
    tmp->sethp(tmp->getmaxhp());
}
OmegaWeapon::OmegaWeapon(int i, Events* event, BaseKnight* p) {
    this->levelO = (i + event->get(i)) % 10 + 1;
    this->tmp = p;
}
void OmegaWeapon::fight() {
    tmp->healed = false;
    int hp = tmp->gethp();
    int maxhp = tmp->getmaxhp();
    int level = tmp->getlevel();
       
        if (tmp->isDragon(maxhp) || (level == 10 && hp == maxhp)) {
            tmp->setlevel(10);
            tmp->setgil(999);
           
        }
        else {
            tmp->sethp(0);
            tmp->getbag()->sudung(tmp);
        }
    
}
Hades::Hades(BaseKnight* p) {
    this->tmp = p;
}
void Hades::fight() {
    tmp->healed = false;
    int level = tmp->getlevel();
    int maxhp = tmp->getmaxhp();
    if (tmp->getlevel() >= 10 || (tmp->isPaladin(maxhp) && tmp->getlevel() >= 8)) {
        return;
    }
    else {
        tmp->sethp(0);
        tmp->getbag()->sudung(tmp);
    }
    
}
Ultimecia::Ultimecia(int i,BaseKnight*p) {
    this->hpboss = 5000;
    this->tmp = p;
}
void Ultimecia::fight() {
    return;
}

//-------------ARMY--------------
void ArmyKnights::in() {
    BaseKnight* p = head;
    while (p != NULL) {
        p->in();
        p = p->next;
    }

}
int ArmyKnights::count()const {
    return sohiepsi;
}
BaseKnight* ArmyKnights::lastKnight()const {
    return head;
}
ArmyKnights::ArmyKnights(const string& file_armyknights) {
    ifstream fin(file_armyknights);
    fin >> this->sohiepsi;

    for (int i = 0; i < sohiepsi; i++) {
        int  maxhp, level, gil, antidote, phoenixdownI;
        fin >> maxhp >> level >> phoenixdownI >> gil >> antidote;
        BaseKnight* newknight = BaseKnight::create(i + 1, maxhp, level, gil, antidote, phoenixdownI);
        newknight->next = head;
        head = newknight;

    }
}
bool ArmyKnights::hasExcaliburSword()const {
    if (sword == true) {
        return true;
    }
    return false;
}
bool ArmyKnights::hasGuinevereHair()const {
    if (hair == true) { return true; }
    return false;
}
bool ArmyKnights::hasLancelotSpear()const {
    if (spear == true) {
        return true;
    }
    return false;
}
bool ArmyKnights::hasPaladinShield()const {
    if (shield == true) {
        return true;
    }
    return false;
}
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
    if (this->count() > 0) {
        BaseKnight* lknight = lastKnight(); // last knight

        cout << ";" << lknight->toString();
        //cout << "tim dc lastknight ne";
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
bool ArmyKnights::fight(BaseOpponent* opponent) {
    opponent->fight();
    lastKnight()->sethp(opponent->tmp->gethp());
    lastKnight()->setgil(opponent->tmp->getgil());
    lastKnight()->setbag(opponent->tmp->getbag());
    lastKnight()->setlevel(opponent->tmp->getlevel());
    lastKnight()->settrungdoc(opponent->tmp->gettrungdoc());
    BaseKnight* p = head;
    while (opponent->gilthuong > 0 && p != NULL)
    {
        if (p->getgil() + opponent->gilthuong <= 999)
        {
            p->setgil(p->getgil() + opponent->gilthuong);
            opponent->gilthuong = 0;
        }
        else
        {

            opponent->gilthuong -= 999 - p->getgil();
            p->setgil(999);
            p = p->next;
        }
    }
    //cout << lastKnight()->gethp();
    if (lastKnight()->gethp() <= 0) { return false; }
    else { return true; }
}
bool ArmyKnights::danhboss(BaseOpponent* ultimecia) {
    int sohiepsitruockhidanhboss = sohiepsi;
    for (int i = 0; i < sohiepsitruockhidanhboss; i++) {
        if (ultimecia->tmp->isLancelot(ultimecia->tmp->getmaxhp())) {
            int dame = ultimecia->tmp->gethp() * ultimecia->tmp->getlevel() * 0.05;
            if (ultimecia->hpboss - dame <= 0) {
                ultimecia->hpboss -= dame;
                break;
            }
            else {
                ultimecia->hpboss -= dame;
               // cout << "hiep si " << ultimecia->tmp->getid() << " danh boss con " << ultimecia->hpboss<<endl;
               // cout << "va tui do la " << ultimecia->tmp->getbag()->toString()<<endl;
                sohiepsi--;
                ultimecia->tmp = ultimecia->tmp->next;
            }
        }
        else if (ultimecia->tmp->isPaladin(ultimecia->tmp->getmaxhp())) {
            int dame = ultimecia->tmp->gethp() * ultimecia->tmp->getlevel() * 0.06;
            if (ultimecia->hpboss - dame <= 0) {
                ultimecia->hpboss -= dame;
                break;
            }
            else {
                ultimecia->hpboss -= dame;
                //cout << "hiep si " << ultimecia->tmp->getid() << " danh boss con " << ultimecia->hpboss<<endl;
               // cout << "va tui do la " << ultimecia->tmp->getbag()->toString()<<endl;
                sohiepsi--;
                ultimecia->tmp = ultimecia->tmp->next;
            }
        }
        else if (ultimecia->tmp->isDragon(ultimecia->tmp->getmaxhp())) {
            int dame = ultimecia->tmp->gethp() * ultimecia->tmp->getlevel() * 0.075;
            if (ultimecia->hpboss - dame <= 0) {
                ultimecia->hpboss -= dame;
                break;
            }
            else {
                ultimecia->hpboss -= dame;
               // cout << "hiep si " << ultimecia->tmp->getid() << " danh boss con " << ultimecia->hpboss<<endl;
              //  cout << "va tui do la " << ultimecia->tmp->getbag()->toString()<<endl;
                sohiepsi--;
                ultimecia->tmp = ultimecia->tmp->next;
            }
        }
        else {
            ultimecia->tmp = ultimecia->tmp->next;
        }
    }
    if (ultimecia->hpboss >= 0) {
        sohiepsi = 0;
        return false;
    }
    else
    {
        return true;
    }
}

void ArmyKnights::resetlastknight() {
    if (head == NULL) { return; }
    //if (head->next == NULL) { this->head = NULL; }
    BaseKnight* p = head;
    head = head->next;
    delete p;
    sohiepsi--;
    
}
bool ArmyKnights::adventure(Events* events) {
    for (int i = 0; i < events->count(); i++) {
        if (lastKnight() == NULL||sohiepsi==0) {
            break;
        }
        if (events->get(i) == 1) {
            Madbear* a = new Madbear(i, events,lastKnight());
            if (fight(a) == true) {
                //cout << "hiep si con song\n";
                if (a->tmp->healed == true) { printInfo(); delete a; continue; }
                delete a;
            }
            else { 
                resetlastknight();
                delete a;
                
            }
        }
        else if (events->get(i) == 2) {
            Bandit* a = new Bandit(i, events,lastKnight());
            if (fight(a) == true) {
                if (a->tmp->healed == true) { printInfo(); delete a; continue; }
                delete a; }
            else {
                resetlastknight();
                delete a;
                
            }
        }
        else if (events->get(i) == 3) {
            LordLupin* a = new LordLupin(i, events, lastKnight());
            if (fight(a) == true) {
                if (a->tmp->healed == true) { printInfo(); delete a; continue; }
                delete a; }
            else {
                resetlastknight();
                delete a;
                
            }
        }
        else if (events->get(i) == 4) {
            Elf* a = new Elf(i, events, lastKnight());
            if (fight(a) == true) {
                if (a->tmp->healed == true) { printInfo(); delete a; continue; }
                delete a; }
            else {
                resetlastknight();
                delete a;
                
            }
        }
        else if (events->get(i) == 5) {
            Troll* a = new Troll(i, events, lastKnight());
            if (fight(a) == true) { 
                if (a->tmp->healed == true) { printInfo(); delete a; continue; }
                delete a; }
            else {
                resetlastknight();
                delete a;
                
            }
        }
        else if (events->get(i) == 6) {
            Tornbery* a = new Tornbery(i, events, lastKnight());
            if (fight(a) == true) {
                if (a->tmp->healed == true) { printInfo(); delete a; continue; }
                delete a; }
            else {
                resetlastknight();
                delete a;
                
            }
        }
        else if (events->get(i) == 7) {
            QueenOfCards* a = new QueenOfCards(i, events, lastKnight());
            if (fight(a) == true) { delete a; }
            else {
                resetlastknight();
                delete a;
                
            }
        }
        else if (events->get(i) == 8) {
            NinaDeRings* a = new NinaDeRings(lastKnight());
            if (fight(a) == true) { delete a; }
            else {
                resetlastknight();
                delete a;
                
            }
        }
        else if (events->get(i) == 9) {
            DurianGarden* a = new DurianGarden(lastKnight());
            if (fight(a) == true) { delete a; }
            else {
                resetlastknight();
                delete a;
                
            }
        }
        else if (events->get(i) == 10) {
            if (Omegawined == true) { printInfo();
            continue; 
            }
            else {
                OmegaWeapon* a = new OmegaWeapon(i, events, lastKnight());
                if (fight(a) == true) {
                    if (a->tmp->healed == true) { printInfo(); delete a; continue; }
                    Omegawined = true;
                    delete a;
                }
                else {
                    resetlastknight();
                    //cout << "so hiep si la " << sohiepsi << endl;
                    delete a;

                }
            }
        }
        else if (events->get(i) == 11) {
            if (Hadeswined == true) { printInfo(); continue; }
            else {
                Hades* a = new Hades(lastKnight());
                if (fight(a) == true) {
                    if (a->tmp->healed == true) { printInfo(); delete a; continue; }
                    Hadeswined = true;
                    shield = true;
                    delete a;
                }
                else {
                    resetlastknight();
                    //cout << "so hiep si la " << sohiepsi << endl;
                    delete a;

                }
            }
        }
        else if (events->get(i) == 112) {
            BaseKnight* p = head;
                      
                for (int i = 0; i < sohiepsi; i++) {
                    if (p->getbag()->insert() == true) {
                        PhoenixdownII* a = new PhoenixdownII;
                        p->getbag()->themvatpham(a);
                        break;
                    }
                    else
                    {
                        p = p->next;
                    }
                }
            
        }
        else if (events->get(i) == 113) {
            BaseKnight* p = head;

            for (int i = 0; i < sohiepsi; i++) {
                if (p->getbag()->insert() == true) {
                    PhoenixdownIII* a = new PhoenixdownIII;
                    p->getbag()->themvatpham(a);
                    break;
                }
                else
                {
                    p = p->next;
                }
            }

        }
        else if (events->get(i) == 114) {
            BaseKnight* p = head;

            for (int i = 0; i < sohiepsi; i++) {
                if (p->getbag()->insert() == true) {
                    PhoenixdownIV* a = new PhoenixdownIV;
                    p->getbag()->themvatpham(a);
                    break;
                }
                else
                {
                    p = p->next;
                }
            }

        }
        else if (events->get(i) == 95) { shield = true; }
        else if (events->get(i) == 96) { spear = true; }
        else if (events->get(i) == 97) { hair = true; }
        else if (events->get(i) == 98) {
            if (shield == true && spear == true && hair == true) {
                sword = true;
            }
        }
        else if (events->get(i) == 99) {
            if (sword == false) { 
                if (shield == true && spear == true && hair == true) {
                    Ultimecia* boss = new Ultimecia(5000, lastKnight());
                    danhboss(boss);
                }
                else { sohiepsi = 0; }
            }
        }
              
        //cout << " cout lan thu i= " << i << endl;
        printInfo();
        
    }
    //cout << sohiepsi;
    if (lastKnight() == nullptr||sohiepsi==0) { return false; }
    else { return true; }

}
ArmyKnights::~ArmyKnights() {
    BaseKnight* p = head;
    while (head != NULL)
    {
        p = head;
        head = head->next;
        delete p;
    }
}


//----------------ADVENTURE-------------
KnightAdventure::~KnightAdventure() {
    delete armyKnights;
    delete events;
    }
KnightAdventure::KnightAdventure() {
    armyKnights = nullptr;
    events = nullptr;
}

