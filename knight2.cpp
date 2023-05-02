#include "knight2.h"
bool omegaWeapon = false;
bool hades = false;
bool paladinShield = false;
bool lancelotSpear = false;
bool guinevereHair = false;
bool poison = false;
int checkLevel(int level) {
    if (level >= MAX_LEVEL) level = MAX_LEVEL;
    return level;
}
bool checkGil(int gil) {
    if (gil >= MAX_GIL) return false;
    else return true;
}
bool primeCheck(int a){
    if (a <= 1) return false;
    if (a == 2 || a == 3) return true;
    for (int i = 2; i <= a / 2; i++)
        if (a % i == 0) return false;
    return true;
}
bool pythagorasCheck(int a, int b, int c){
    if (((pow(a, 2) + pow(b, 2) == pow(c, 2)) ||
        (pow(b, 2) + pow(c, 2) == pow(a, 2)) ||
        (pow(c, 2) + pow(a, 2) == pow(b, 2))
    ) && (a > 0 && b > 0 && c > 0))
    return true;
    else return false;
}
bool dragonCheck(int a){
    int count = 0;
    int temp = a;
    while (temp > 0){
        temp /= 10;
        count ++;
    }
    if (count != 3) return false;
    else {
        int arr[3];
        for (int i = 0; i < 3; i++){
            arr[i] = a % 10;
            a /= 10;
        }
        if (pythagorasCheck(arr[0], arr[1], arr[2])) return true;
        else return false;
    }
}
bool lancelotCheck(int a){
    if (a == 888) return true;
    else return false;
}
KnightType knightCheck(int maxhp){
    if (primeCheck(maxhp)) return PALADIN;
    else if (lancelotCheck(maxhp)) return LANCELOT;
    else if (dragonCheck(maxhp)) return DRAGON;
    else return NORMAL;
}
int levelO(int i, int eventID){
    return (i + eventID) % 10 + 1;
}
int BaseBag::itemCount(){
    int count = 0;
    BaseItem * temp;
    temp = head;
    while (head != NULL){
        count ++;
        head = head->next;
    }
    return count;
}
void BaseBag::addItemHead(ItemType item){
    BaseItem *newItem;
    switch (item) {
        case ANTIDOTE:
            newItem = new Antidote();
            break;
        case PHOENIXDOWNI:
            newItem = new PhoenixDownI();
            break;
        case PHOENIXDOWNII:
            newItem = new PhoenixDownII();
            break;
        case PHOENIXDOWNIII:
            newItem = new PhoenixDownIII();
            break;
        case PHOENIXDOWNIV:
            newItem = new PhoenixDownIV();
            break;
        default:
            newItem = new Antidote();
            break;
    }
    if (head != NULL) {
        newItem->next = head;
    }
    head = newItem;
}
void BaseBag::removeItemHead(BaseItem *head) {
    if (head == NULL) return;
    BaseItem *temp = head;
    head = head->next;
    delete temp;
}
BaseItem *BaseBag::search(BaseItem *head, ItemType item) {
    BaseItem * temp = head;
    while (temp->item != item && temp != NULL) {
        temp = temp->next;
    }
    if (temp != NULL)
    return temp;
    else return NULL;
}
void BaseBag::swapItemHead(BaseItem * head, BaseItem * need) {
    BaseItem * temp = head;
    BaseItem * temp2 = head;
    BaseItem * tempNeed = need;
    while (temp->next != need) {
        temp = temp->next;
    }
    temp->next = temp2;
    temp2->next = need->next;
    need->next = head->next;
    head = need;
}
BaseItem * BaseBag::searchPhoenixFirst(BaseItem * head, BaseKnight * knight) {
    BaseItem * temp = head;
    if (knight->getHP() <= 0) {
        while (temp != NULL && (temp->item != PHOENIXDOWNI || temp->item != PHOENIXDOWNII || temp->item != PHOENIXDOWNIII || temp->item != PHOENIXDOWNIV)) {
            temp = temp->next;
        }
        if (temp == NULL) return NULL;
        else return temp;
    }
    else {
        // same as above but with canUse method, do later
    }
}
void BaseBag::use(BaseKnight * knight, BaseItem * item) {
    swapItemHead(knight->getBag()->head, item);
    knight->getBag()->head->use(knight);
    removeItemHead(head);
}
/*BEGIN Event class*/
Events::Events(const string & file_events){
    ifstream f;
    f.open(file_events);
    f >> eventNum;
    for (int i = 0; i < eventNum; i++){
        f >> event[i];
    }
    f.close();
}
int Events::count() const{
    return eventNum;
}
int Events::get(int i) const{
    return event[i];
}
/*END Event class*/
/* * * BEGIN implementation of class BaseBag * * */
bagNormal::bagNormal(BaseKnight * knight, int phoenixDownI, int antidote) {
    if (phoenixDownI > 0) {
        for (int i = 0; i < phoenixDownI; i++) {
            addItemHead(PHOENIXDOWNI);
        }
    }
    if (antidote > 0) {
        for (int i = 0; i < antidote; i++) {
            addItemHead(ANTIDOTE);
        }
    }
}
bool bagNormal::insertFirst(BaseItem * item) {
    if (itemCount() < MAX_ITEM_NORMAL) return true;
    else return false;
}
bagLancelot::bagLancelot(BaseKnight * knight, int phoenixDownI, int antidote) {
        if (phoenixDownI > 0) {
        for (int i = 0; i < phoenixDownI; i++) {
            addItemHead(PHOENIXDOWNI);
        }
    }
    if (antidote > 0) {
        for (int i = 0; i < antidote; i++) {
            addItemHead(ANTIDOTE);
        }
    }
}
bool bagLancelot::insertFirst(BaseItem * item) {
    if (itemCount() < MAX_ITEM_LANCELOT) return true;
    else return false;
}
bagPaladin::bagPaladin(BaseKnight * knight, int phoenixDownI, int antidote) {
        if (phoenixDownI > 0) {
        for (int i = 0; i < phoenixDownI; i++) {
            addItemHead(PHOENIXDOWNI);
        }
    }
    if (antidote > 0) {
        for (int i = 0; i < antidote; i++) {
            addItemHead(ANTIDOTE);
        }
    }
}
bool bagPaladin::insertFirst(BaseItem * item) {
    return true;
}
bagDragon::bagDragon(BaseKnight * knight, int phoenixDownI, int antidote) {
    if (phoenixDownI > 0) {
        for (int i = 0; i < phoenixDownI; i++) {
            addItemHead(PHOENIXDOWNI);
        }
    }
}
bool bagDragon::insertFirst(BaseItem * item) {
    if (itemCount() < MAX_ITEM_DRAGON) return true;
    else return false;
}
string BaseBag::toString() const{
    string s = "";
    int count = 0;
    BaseItem * temp = head;
    string list = "";
    while (temp != NULL) {
        switch (temp->item)
        {
        case ANTIDOTE:
            list += "Antidote,";
            break;
        case PHOENIXDOWNI:
            list += "PhoenixI,";
            break;
        case PHOENIXDOWNII:
            list += "PhoenixII,";
            break;
        case PHOENIXDOWNIII:
            list += "PhoenixIII,";
            break;
        case PHOENIXDOWNIV:
            list += "PhoenixIV,";
            break;
        default:
            break;
        }
        count ++;
    }
    s = "Bag[count=" + to_string(count) + ";" + list + "]";
    s.erase(s.length() - 2, 1);
    return s; 
}
/* * * END implementation of class BaseBag * * */
/*BEGIN BaseItem*/
Antidote::Antidote() {
    item = ANTIDOTE;
    next = NULL;
}
//TODO: add swap and deleteHead method to use, still dont know how to do
bool Antidote::canUse(BaseKnight * knight) {
    if (poison && knight->getType() != DRAGON && knight->getAntidote()) return true;
    else return false;
}
void Antidote::use(BaseKnight * knight) {
    poison = false;
}
PhoenixDownI::PhoenixDownI() {
    item = PHOENIXDOWNI;
    next = NULL;
}
bool PhoenixDownI::canUse(BaseKnight * knight) {
    if (knight->getHP() <= 0) return true;
    else return false;
}
void PhoenixDownI::use(BaseKnight * knight) {
    knight->setHP(knight->getMaxHP());
}
PhoenixDownII::PhoenixDownII() {
    item = PHOENIXDOWNIII;
    next = NULL;
}
bool PhoenixDownII::canUse(BaseKnight * knight) {
    if (knight->getHP() < (knight->getMaxHP() / 4)) return true;
    else return false;
}
void PhoenixDownII::use(BaseKnight * knight) {
    knight->setHP(knight->getMaxHP());
}
PhoenixDownIII::PhoenixDownIII() {
    item = PHOENIXDOWNIV;
    next = NULL;
}
bool PhoenixDownIII::canUse(BaseKnight * knight) {
    if (knight->getHP() < (knight->getMaxHP() / 3)) return true;
    else return false;
}
void PhoenixDownIII::use(BaseKnight * knight) {
    if (knight->getHP() <= 0) 
        knight->setHP(knight->getMaxHP() / 3);
    else
        knight->setHP(knight->getMaxHP() / 4 + knight->getHP());
}
PhoenixDownIV::PhoenixDownIV() {
    item = PHOENIXDOWNIV;
    next = NULL;
}
bool PhoenixDownIV::canUse(BaseKnight * knight) {
    if (knight->getHP() < (knight->getMaxHP() / 2)) return true;
    else return false;
}
void PhoenixDownIV::use(BaseKnight * knight) {
    if (knight->getHP() <= 0)
        knight->setHP(knight->getMaxHP() / 2);
    else
        knight->setHP(knight->getHP() + knight->getMaxHP() / 5);
}
/*END BaseItem*/
/*Begin BaseOpponent*/
int BaseOpponent::getBaseDamage() {
    return baseDamage;
}
void BaseOpponent::setBaseDamage(int damage){
    this->baseDamage = damage;
}
int BaseOpponent::getEventCode() {
    return eventCode;
}
int BaseOpponent::getGil() {
    return gil;
}
void BaseOpponent::setGil(int gil) {
    this->gil = gil;
}
MadBear::MadBear() {
    setBaseDamage(MADBEAR_DAMAGE);
    setGil(MADBEAR_GIL);
}
Bandit::Bandit() {
    setBaseDamage(BANDIT_DAMAGE);
    setGil(BANDIT_GIL);
}
LordLupin::LordLupin() {
    setBaseDamage(LORDLUPIN_DAMAGE);
    setGil(LORDLUPIN_GIL);
}
Elf::Elf() {
    setBaseDamage(ELF_DAMAGE);
    setGil(ELF_GIL);
}
Troll::Troll() {
    setBaseDamage(TROLL_DAMAGE);
    setGil(TROLL_GIL);
}

/*End BaseOpponent*/
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
BaseKnight *BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI){
    BaseKnight *knight;
    switch (knightCheck(maxhp)) {
        case PALADIN:
            knight = new PaladinKnight();
            break;
        case LANCELOT:
            knight = new LancelotKnight();
            break;
        case DRAGON:
            knight = new DragonKnight();
            break;
        default:
            knight = new NormalKnight();
            break;
    }
    knight->knightType = knightCheck(maxhp);
    knight->id = id;
    knight->maxhp = maxhp;
    knight->hp = maxhp;
    knight->level = level;
    knight->gil = gil;
    knight->antidote = antidote;
    knight->phoenixdownI = phoenixdownI;
    /*
    switch (knight->knightType)
    {
    case NORMAL:
        knight->bag = new bagNormal(knight, phoenixdownI,antidote);
        break;
    case PALADIN:
        knight->bag = new bagPaladin(knight, phoenixdownI, antidote);
        break;
    case LANCELOT:
        knight->bag = new bagLancelot(knight, phoenixdownI, antidote);
        break;
    case DRAGON:
        knight->bag = new bagDragon(knight, phoenixdownI, antidote);
        break;
    default:
        break;
    }*/
    return knight;
}
void BaseKnight::setId(int id){
    this->id = id;
}
int BaseKnight::getId(){
    return id;
}
void BaseKnight::setHP(int hp){
    this->hp = hp;
}
int BaseKnight::getHP(){
    return hp;
}
void BaseKnight::setLevel(int level){
    this->level = level;
}
int BaseKnight::getLevel(){
    return level;
}
void BaseKnight::setMaxHP(int maxhp){
    this->maxhp = maxhp;
}
int BaseKnight::getMaxHP(){
    return maxhp;
}
void BaseKnight::setGil(int gil){
    this->gil = gil;
}
int BaseKnight::getGil(){
    return gil;
}
void BaseKnight::setAntidote(int antidote){
    this->antidote = antidote;
}
int BaseKnight::getAntidote(){
    return antidote;
}
void BaseKnight::setPhoenix(int phoenixdownI) {
    this->phoenixdownI = phoenixdownI;
}
int BaseKnight::getPhoenix() {
    return phoenixdownI;
}
void BaseKnight::setBag(BaseBag *bag) {
    this->bag = bag;
}
BaseBag *BaseKnight::getBag() {
    return bag;
}
void BaseKnight::setType(KnightType type){
    this->knightType = type;
}
KnightType BaseKnight::getType() {
    return knightType;
}
bool BaseKnight::checkRecover() {
    if (this->gil < 100) {
        if (this->bag->search(this->bag->head, PHOENIXDOWNI) == NULL &&
        this->bag->search(this->bag->head, PHOENIXDOWNII) == NULL &&
        this->bag->search(this->bag->head, PHOENIXDOWNIII) == NULL &&
        this->bag->search(this->bag->head, PHOENIXDOWNIV) == NULL)
            return false;
    else {
        /*this->bag->search(this->bag->head, this->bag->searchPhoenixFirst(this->bag->head, this)->item)->use(this); */
        this->bag->use(this, this->bag->searchPhoenixFirst(this->bag->head, this));
        return true;
    }
    }
    else {
        this->gil -= 100;
        this->hp = this->maxhp / 2;
        return true;
    }
    
}
/*PaladinKnight::PaladinKnight() {
    this->bag = new bagPaladin(this, this->phoenixdownI, this->antidote); //try to create bag for each type
}
bool PaladinKnight::fight(BaseOpponent * opponent) {
    if (opponent->getEventCode() >= 1 && opponent->getEventCode() <= 5) {
        this->setGil(this->getGil() + opponent->getGil());
        return true;
    }
}
LancelotKnight::LancelotKnight() {
    this->bag = new bagLancelot(this, this->phoenixdownI, this->antidote);
}
bool LancelotKnight::fight(BaseOpponent * opponent) {
    if (opponent->getEventCode() >= 1 && opponent->getEventCode() <= 5) {
        this->setGil(this->getGil() + opponent->getGil());
        return true;
    }
}
DragonKnight::DragonKnight() {
    this->bag = new bagDragon(this, this->phoenixdownI, this->antidote);
}
bool DragonKnight::fight(BaseOpponent * opponent) {
    if (opponent->getEventCode() >= 1 && opponent->getEventCode() <= 5) {
        if (this->getHP() - opponent->getBaseDamage() * (levelO(opponent->getOrder(), opponent->getEventCode()) - this->getLevel()) > 0)
            return true;
        else {
            return checkRecover();
        }
    }
}
NormalKnight::NormalKnight() {
    this->bag = new bagNormal(this, this->phoenixdownI, this->antidote);
}
bool NormalKnight::fight(BaseOpponent * opponent) {
    if (opponent->getEventCode() >= 1 && opponent->getEventCode() <= 5) {
        if (this->getHP() - opponent->getBaseDamage() * (levelO(opponent->getOrder(), opponent->getEventCode()) - this->getLevel()) > 0)
            return true;
        else {
            return checkRecover();
        }
    }
}*/
/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string & file_armyknights){
    ifstream f;
    f.open(file_armyknights);
    f >> knightNum;
    for (int i = 1; i <= knightNum; i++){
        int hp, level, phoenixdownI, gil, antidote;
        f >> hp >> level >> phoenixdownI >> gil >> antidote;
        knight[i]->setId(i);
        knight[i]->setHP(hp);
        knight[i]->setMaxHP(hp);
        knight[i]->setLevel(level);
        knight[i]->setPhoenix(phoenixdownI);
        knight[i]->setGil(gil);
        knight[i]->setAntidote(antidote);
        if (knight[i]->getType() == DRAGON) 
            knight[i]->setAntidote(0);
        knight[i]->setType(knightCheck(knight[i]->getMaxHP()));
        switch (knight[i]->getType()) {
            case PALADIN:
                knight[i] = new PaladinKnight();
                break;
            case LANCELOT:
                knight[i] = new LancelotKnight();
                break;
            case DRAGON:
                knight[i] = new DragonKnight();
                break;
            default:
                knight[i] = new NormalKnight();
                break;
        }
    }
    f.close();
}
void ArmyKnights::transferGil() {
    knight[lastKnight()->getId() - 1]->setGil(knight[lastKnight()->getId() - 1]->getGil() + lastKnight()->getGil() - MAX_GIL);
}
bool ArmyKnights::fight(BaseOpponent * opponent) {//use to check if win an opponent
    switch (opponent->getEventCode())
    {
    case 1:
        opponent = new MadBear();
        break;
    case 2:
        opponent = new Bandit();
        break;
    case 3:
        opponent = new LordLupin();
        break;
    case 4:
        opponent = new Elf();
        break;
    case 5:
        opponent = new Troll();
        break;
    /*case 6:
        opponent = new Tornbery();
        break;
    case 7:
        opponent = new QueenOfCards();
        break;
    case 8:
        opponent = new NinaDeRings();
        break;
    case 9:
        opponent = new DurianGarden();
        break;
    case 10:
        opponent = new OmegaWeapon();
        break;
    case 11:
        opponent = new Hades();
        break;
    case 112:
        opponent = new PhoenixII();
        break;
    case 113:
        opponent = new PhoenixIII();
        break;
    case 114:
        opponent = new PhoenixIV();
        break;
    case 95:
        opponent = new PaladinShield();
        break;
    case 96:
        opponent = new LancelotSpear();
        break;
    case 97:
        opponent = new GuinevereHair();
    default:
        break;*/
    }
    if (opponent->getEventCode() <= 5) {
        if (lastKnight()->getType() == PALADIN || lastKnight()->getType() == LANCELOT) {
            lastKnight()->setGil(lastKnight()->getGil() + opponent->getGil());
            if (!checkGil(lastKnight()->getGil())) 
                transferGil();
            return true;
        }
        else {
            if (lastKnight()->getLevel() >= levelO(opponent->getOrder(), opponent->getEventCode())) 
                return true;
            else {
                lastKnight()->setHP(lastKnight()->getHP() - opponent->getBaseDamage() * (levelO(opponent->getOrder(), opponent->getEventCode()) - lastKnight()->getLevel()));
                if (lastKnight()->getHP() <= 0 && !lastKnight()->checkRecover()) 
                    knightNum--;
                return false;
            }
        }
    }
    if (opponent->getEventCode() == 6) {
        if (lastKnight()->getLevel() >= levelO(opponent->getOrder(), opponent->getEventCode())) {
            lastKnight()->setLevel(lastKnight()->getLevel() + 1);
            lastKnight()->setLevel(checkLevel(lastKnight()->getLevel()));
            return true;
        }
        else {
            if (lastKnight()->getType() != DRAGON) {
                if (lastKnight()->getAntidote()) {
                    lastKnight()->getBag()->use(lastKnight(), lastKnight()->getBag()->search(lastKnight()->getBag()->head, ANTIDOTE));
                    lastKnight()->setAntidote(lastKnight()->getAntidote() - 1);
                }
                else {
                    lastKnight()->setHP(lastKnight()->getHP() - 10);
                    if (lastKnight()->getBag()->itemCount() >= 3) {
                        for (int i = 0; i < 3; i++) {
                            lastKnight()->getBag()->removeItemHead(lastKnight()->getBag()->head);
                        }
                    }
                    else {
                        if (lastKnight()->getBag()->itemCount() > 0)
                            for (int i = 0; i < lastKnight()->getBag()->itemCount(); i++)
                                lastKnight()->getBag()->removeItemHead(lastKnight()->getBag()->head);
                    }
                    if (lastKnight()->getHP() <= 0) {
                        if (!lastKnight()->checkRecover()) 
                            knightNum--;
                    }
                }
            }
            return false;
        }
    }
    if (opponent->getEventCode() == 7) {
        if (lastKnight()->getLevel() >= levelO(opponent->getOrder(), opponent->getEventCode())) {
            lastKnight()->setGil(lastKnight()->getGil() * 2);
            if (!checkGil(lastKnight()->getGil()))
                transferGil();
            return true;
        }
        else {
            lastKnight()->setGil(lastKnight()->getGil() / 2);
            return false;
        }
    }
    if (opponent->getEventCode() == 8) {
        if (lastKnight()->getGil() >= 50 && (lastKnight()->getHP() < lastKnight()->getMaxHP() / 3)) {
            lastKnight()->setGil(lastKnight()->getGil() - 50);
            lastKnight()->setHP(lastKnight()->getHP() + lastKnight()->getMaxHP() / 5);
        }
        return true;
    }
    if (opponent->getEventCode() == 9) {
        lastKnight()->setHP(lastKnight()->getMaxHP());
        return true;
    }
    if (opponent->getEventCode() == 10) {
        if ((lastKnight()->getHP() == lastKnight()->getMaxHP() && lastKnight()->getLevel() == MAX_LEVEL) || lastKnight()->getType() == DRAGON) {
            lastKnight()->setLevel(MAX_LEVEL);
            lastKnight()->setGil(MAX_GIL);
            return true;
        }
            
        else {
            //HP = 0, implement method and function to either rescue or not
            lastKnight()->setHP(0);
            if (!lastKnight()->checkRecover())
                knightNum --;
            return false;
        }
        omegaWeapon = true;
    }
    if (opponent->getEventCode() == 11) {
        //not hard
    }
    /*return lastKnight()->fight(opponent); // implement*/
}

bool ArmyKnights::adventure(Events * event) {//use to perform action, the final return is if the army win or not

}

int ArmyKnights::count() const {//use to count number of knight left

}
BaseKnight *ArmyKnights::lastKnight() const{
    if (knightNum == 0) return NULL;
    else return knight[knightNum];
}
bool ArmyKnights::hasPaladinShield() const{
    if (paladinShield) return true;
    else return false;
}

bool ArmyKnights::hasLancelotSpear() const{
    if (lancelotSpear) return true;
    else return false;
}

bool ArmyKnights::hasGuinevereHair() const{
    if (guinevereHair) return true;
    else return false;
}

bool ArmyKnights::hasExcaliburSword() const{
    if (hasPaladinShield() && hasLancelotSpear() && hasGuinevereHair())
        return true;
    else
        return false;
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
void KnightAdventure::loadArmyKnights(const string & file_armyknights) {
    armyKnights = new ArmyKnights(file_armyknights);
}
void KnightAdventure::loadEvents(const string & file_events) {
    events = new Events(file_events);
}
void KnightAdventure::run() {
    //implement adventure
    //print result at the end
}
KnightAdventure::~KnightAdventure() {
}

/* * * END implementation of class KnightAdventure * * */