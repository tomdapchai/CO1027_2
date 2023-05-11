#include "knight2.h"
bool omegaWeapon = false;
bool hades = false;
bool paladinShield = false;
bool lancelotSpear = false;
bool guinevereHair = false;
bool excaliburSword = false;
bool poison = false;
bool ultimecia = false;
bool win = false; // to check if win all or not
int checkLevel(int level) {
    if (level >= MAX_LEVEL) level = MAX_LEVEL;
    return level;
}
bool checkGil(int gil) {
    if (gil > MAX_GIL) return false;
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
/*BEGIN Event class*/
Events::Events(const string & file_events){
    ifstream f;
    f.open(file_events);
    f >> eventNum;
    event = new int[eventNum];
    for (int i = 0; i < eventNum; i++){
        f >> event[i];
    }
    f.close();
}
Events::~Events(){
    delete [] event;
    event = NULL;
    eventNum = 0;
}
int Events::count() const{
    return eventNum;
}
int Events::get(int i) const{
    return event[i];
}
/*END Event class*/

/* * * BEGIN implementation of class BaseBag * * */
BaseBag::~BaseBag() {
    delete head;
    head = NULL;
}
void BaseBag::setMaxItem(int maxItem) {
    this->maxItem = maxItem;
}
int BaseBag::getMaxItem() {
    return maxItem;
} 
int BaseBag::itemCount(){
    if (head == NULL)
        return 0;
    int count = 0;
    BaseItem * temp;
    temp = head;
    while (temp != NULL){
        count ++;
        temp = temp->next;
    }
    delete temp;
    return count;
}
void BaseBag::addItemHead(ItemType item){
    BaseItem * newItem;
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
        }
    newItem->next = head;
    head = newItem;
}
void BaseBag::removeItemHead() {
    if (head == NULL) return;
    BaseItem *temp = head;
    head = head->next;
    delete temp;
}
BaseItem *BaseBag::search(ItemType item) {
    if (head == NULL)
        return NULL;
    BaseItem * temp = head;
    while (temp->item != item && temp != NULL) {
        temp = temp->next;
    }
    return temp;
}
void BaseBag::swapItemHead(BaseItem * need) {
    if (head == need || head == NULL || head->next == NULL)
        return;
    BaseItem* prev = NULL;
    BaseItem* curr = head;
    while (curr != NULL && curr != need) {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL) {
        return;
    }
    BaseItem* temp = head;
    head = need;
    prev->next = temp;
    BaseItem* tempNext = need->next;
    need->next = temp->next;
    temp->next = tempNext;
}

BaseItem * BaseBag::searchPhoenixFirst(BaseKnight * knight) {
    BaseItem * temp = head;
    while (temp != NULL && !(temp->canUse(knight) && (temp->item == PHOENIXDOWNI || temp->item == PHOENIXDOWNII || temp->item == PHOENIXDOWNIII || temp->item == PHOENIXDOWNIV))) {
        temp = temp->next;
    }
    return temp;
}
void BaseBag::use(BaseKnight * knight, BaseItem * item) {
    swapItemHead(item);
    knight->getBag()->head->use(knight);
    removeItemHead();
}

bagNormal::bagNormal(BaseKnight * knight, int phoenixDownI, int antidote) {
    head = NULL;
    this->setMaxItem(MAX_ITEM_NORMAL);
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
    if (itemCount() < this->getMaxItem()) return true;
    else return false;
}
bagLancelot::bagLancelot(BaseKnight * knight, int phoenixDownI, int antidote) {
    head = NULL;
    this->setMaxItem(MAX_ITEM_LANCELOT);    
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
    if (itemCount() < this->getMaxItem()) return true;
    else return false;
}
bagPaladin::bagPaladin(BaseKnight * knight, int phoenixDownI, int antidote) {
    head = NULL;
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
    head = NULL;
    this->setMaxItem(MAX_ITEM_DRAGON);
    if (phoenixDownI > 0) {
        for (int i = 0; i < phoenixDownI; i++) {
            addItemHead(PHOENIXDOWNI);
        }
    }
}
bool bagDragon::insertFirst(BaseItem * item) {
    if (itemCount() < this->getMaxItem()) return true;
    else return false;
}
string BaseBag::toString() const{
    string s = "";
    int count = 0;
    BaseItem * temp = head;
    string list = "";
    while (temp != NULL) {
        switch (temp->item) {
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
        temp = temp->next;
        count ++;
    }
    s = "Bag[count=" + to_string(count) + ";" + list + "]";
    if (count > 0)
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
    if (poison && (knight->getType() != DRAGON) && knight->getAntidote()) return true;
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
    item = PHOENIXDOWNII;
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
    item = PHOENIXDOWNIII;
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
int BaseOpponent::getBaseDamage() const{
    return baseDamage;
}
void BaseOpponent::setBaseDamage(int damage){
    this->baseDamage = damage;
}
int BaseOpponent::getEventCode() const{
    return eventCode;
}
void BaseOpponent::setEventCode(int eventCode) {
    this->eventCode = eventCode;
}
int BaseOpponent::getGilReward() const{
    return gil;
}
void BaseOpponent::setGilReward(int gil) {
    this->gil = gil;
}
void BaseOpponent::setOrder(int order) {
    this->order = order;
}
int BaseOpponent::getOrder() const{
    return order;
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
    BaseKnight *knight = new BaseKnight(); //error?
    knight->id = id;
    knight->maxhp = maxhp;
    knight->hp = maxhp;
    knight->level = level;
    knight->gil = gil;
    knight->antidote = antidote;
    knight->phoenixdownI = phoenixdownI;
    knight->knightType = knightCheck(maxhp);
    switch (knight->knightType){
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
        knight->bag = new bagNormal(knight, phoenixdownI,antidote);
        break;
    }
    return knight;
}
void BaseKnight::setId(int id){
    this->id = id;
}
int BaseKnight::getId() const{
    return id;
}
void BaseKnight::setHP(int hp){
    this->hp = hp;
}
int BaseKnight::getHP() const{
    return hp;
}
void BaseKnight::setLevel(int level){
    this->level = level;
}
int BaseKnight::getLevel() const{
    return level;
}
void BaseKnight::setMaxHP(int maxhp){
    this->maxhp = maxhp;
}
int BaseKnight::getMaxHP() const{
    return maxhp;
}
void BaseKnight::setAntidote(int antidote){
    this->antidote = antidote;
}
int BaseKnight::getAntidote() const{
    return antidote;
}
void BaseKnight::setPhoenix(int phoenixdownI) {
    this->phoenixdownI = phoenixdownI;
}
int BaseKnight::getPhoenix() const{
    return phoenixdownI;
}
void BaseKnight::setGil(int gil){
    this->gil = gil;
}
int BaseKnight::getGil() const{
    return gil;
}
BaseBag *BaseKnight::getBag(){
    return bag;
}
void BaseKnight::setType(KnightType type){
    this->knightType = type;
}
KnightType BaseKnight::getType() const{
    return knightType;
}
bool BaseKnight::checkRecover() {
    if (bag->searchPhoenixFirst(this) != NULL) {
        bag->use(this, bag->searchPhoenixFirst(this));
        return true;
    }
    else if (gil >= 100) {
        gil -= 100;
        hp = maxhp / 2;
        return true;
    }
    else {
        return false;
    }
}
/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string & file_armyknights){
    ifstream f;
    f.open(file_armyknights);
    f >> knightNum;
    lastID = knightNum;
    knight = new BaseKnight*[knightNum];
    for (int i = 0; i < knightNum; i++){
        int hp, level, phoenixdownI, gil, antidote;
        f >> hp >> level >> phoenixdownI >> gil >> antidote;
        knight[i] = BaseKnight::create(i + 1, hp, level, gil, antidote, phoenixdownI);
    }
    f.close();
}
void ArmyKnights::transferGil() {
    int i = lastID - 1;
    while (i > 0) {
        int diff = knight[i]->getGil() - MAX_GIL;
        if (diff > 0) {
            knight[i]->setGil(MAX_GIL);
            knight[i - 1]->setGil(knight[i - 1]->getGil() + diff);
        }
        else
            break;
        i--;
    }
    if (knight[0]->getGil() > MAX_GIL)
        knight[0]->setGil(MAX_GIL);
         //this might works well
}
void ArmyKnights::transferItem(ItemType item) { // actually just transfer PhoenixII, PhoenixIII, phoenixIV
    int i = lastID - 1;
    while (i > 0) {
        if (knight[i]->getBag()->itemCount() == knight[i]->getBag()->getMaxItem()) {
            i--;
            continue;
        }
        else {//only < maxItem
            knight[i]->getBag()->addItemHead(item);
            break;
        }
    }
}
bool ArmyKnights::fight(BaseOpponent * opponent) {//use to check if lastKnight still alive
    switch (opponent->getEventCode()) {
    case 1: {
        opponent->setBaseDamage(MADBEAR_DAMAGE);
        opponent->setGilReward(MADBEAR_GIL);
        break;
    }
    case 2: {
        opponent->setBaseDamage(BANDIT_DAMAGE);
        opponent->setGilReward(BANDIT_GIL);
        break;
    } 
    case 3: {
        opponent->setBaseDamage(LORDLUPIN_DAMAGE);
        opponent->setGilReward(LORDLUPIN_GIL);
        break;
    }
    case 4: {
        opponent->setBaseDamage(ELF_DAMAGE);
        opponent->setGilReward(ELF_GIL);
        break;
    }
    case 5: {
        opponent->setBaseDamage(TROLL_DAMAGE);
        opponent->setGilReward(TROLL_GIL);
        break;
    }
    }
    if (opponent->getEventCode() <= 5) {
        if (lastKnight()->getType() == PALADIN || lastKnight()->getType() == LANCELOT || (lastKnight()->getLevel() >= levelO(opponent->getOrder(), opponent->getEventCode()))) {
            lastKnight()->setGil(lastKnight()->getGil() + opponent->getGilReward());
            if (!checkGil(lastKnight()->getGil())) 
                transferGil();
        }
        else {
            lastKnight()->setHP(lastKnight()->getHP() - opponent->getBaseDamage() * (levelO(opponent->getOrder(), opponent->getEventCode()) - lastKnight()->getLevel()));
            if (lastKnight()->getHP() <= 0 && !lastKnight()->checkRecover()) 
            {
                return false;
            }
        }
        return true;
    }
    if (opponent->getEventCode() == 6) {
        if (lastKnight()->getLevel() >= levelO(opponent->getOrder(), opponent->getEventCode())) {
            lastKnight()->setLevel(lastKnight()->getLevel() + 1);
            lastKnight()->setLevel(checkLevel(lastKnight()->getLevel()));
        }
        else {
            if (lastKnight()->getType() != DRAGON) {
                if (lastKnight()->getAntidote()) {
                    lastKnight()->getBag()->use(lastKnight(), lastKnight()->getBag()->search(ANTIDOTE));
                    lastKnight()->setAntidote(lastKnight()->getAntidote() - 1);
                }
                else {
                    if (lastKnight()->getBag()->itemCount() >= 3) {
                        for (int i = 0; i < 3; i++) {
                            lastKnight()->getBag()->removeItemHead();
                        }
                    }
                    else {
                        if (lastKnight()->getBag()->itemCount() > 0) {
                            int c = lastKnight()->getBag()->itemCount();
                            for (int i = 0; i < c; i++)
                                lastKnight()->getBag()->removeItemHead();
                        }
                            
                    }
                    lastKnight()->setHP(lastKnight()->getHP() - 10);
                    if (lastKnight()->getHP() <= 0 && !lastKnight()->checkRecover())
                        return false;
                }
            }
        }
        return true;
    }
    if (opponent->getEventCode() == 7) {
        if (lastKnight()->getLevel() >= levelO(opponent->getOrder(), opponent->getEventCode())) {
            lastKnight()->setGil(lastKnight()->getGil() * 2);
            if (!checkGil(lastKnight()->getGil()))
                transferGil();
        }
        else {
            if (lastKnight()->getType() != PALADIN)
                lastKnight()->setGil(lastKnight()->getGil() / 2);
        }
        return true;
    }
    if (opponent->getEventCode() == 8) {
        if ((lastKnight()->getGil() >= 50 || lastKnight()->getType() == PALADIN) && (lastKnight()->getHP() < lastKnight()->getMaxHP() / 3)) {
            if (lastKnight()->getType() != PALADIN)
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
        }  
        else {
            //HP = 0, implement method and function to either recover or not
            lastKnight()->setHP(0);
            if (!lastKnight()->checkRecover())
                return false;
        }
        omegaWeapon = true;
        return true;
    }
    if (opponent->getEventCode() == 11) {
        //not hard
        if (lastKnight()->getLevel() == 10 || (lastKnight()->getType() == PALADIN && lastKnight()->getLevel() >= 8)) 
            paladinShield = true;
        else {
            lastKnight()->setHP(0);
            if (!lastKnight()->checkRecover()) {
                return false;
            }
        }
        hades = true;
        return true;
    }
    if (opponent->getEventCode() == 112) {
        //PhoenixII
        if ((lastKnight()->getBag()->itemCount() < lastKnight()->getBag()->getMaxItem()) || lastKnight()->getType() == PALADIN) {  
            lastKnight()->getBag()->addItemHead(PHOENIXDOWNII);
        }
        else {
            transferItem(PHOENIXDOWNII);
        }
        return true;
    }
    if (opponent->getEventCode() == 113) {
        //PhoenixIII
        if ((lastKnight()->getBag()->itemCount() < lastKnight()->getBag()->getMaxItem()) || lastKnight()->getType() == PALADIN) {
            lastKnight()->getBag()->addItemHead(PHOENIXDOWNIII);
        }
        else {
            transferItem(PHOENIXDOWNIII);
        }
        return true;
    }
    if (opponent->getEventCode() == 114) {
        //PhoenixIV
        if ((lastKnight()->getBag()->itemCount() < lastKnight()->getBag()->getMaxItem()) || lastKnight()->getType() == PALADIN) {
            lastKnight()->getBag()->addItemHead(PHOENIXDOWNIV);
        }
        else {
            transferItem(PHOENIXDOWNIV);
        }
        return true;
    }
    if (opponent->getEventCode() == 95) {
        paladinShield = true;
        return true;
    }
    if (opponent->getEventCode() == 96) {
        lancelotSpear = true;
        return true;
    }
    if (opponent->getEventCode() == 97) {
        guinevereHair = true;
        return true;
    }
    if (opponent->getEventCode() == 98) {
        if (hasPaladinShield() && hasLancelotSpear() && hasGuinevereHair()) {
            excaliburSword = true;
        }
        return true;
    }
    if (opponent->getEventCode() == 99) {
        ultimecia = true;
        if (hasExcaliburSword()) {
            win = true;
            return true;
        }
        else if (hasPaladinShield() && hasLancelotSpear() && hasGuinevereHair()) {
            int ultimeciaHP = 5000;
            for (int i = lastKnight()->getId() - 1; i >= 0; i--) {
                double knightBaseDamage;
                if (knight[i]->getType() != NORMAL) {
                    if (knight[i]->getType() == LANCELOT) 
                        knightBaseDamage = 0.05;
                    if (knight[i]->getType() == PALADIN)
                        knightBaseDamage = 0.06;
                    if (knight[i]->getType() == DRAGON)
                        knightBaseDamage = 0.075;
                    ultimeciaHP -= knight[i]->getHP() * knight[i]->getLevel() * knightBaseDamage;
                    if (ultimeciaHP > 0 && knightNum > 0) {
                        lastID--;
                        knightNum --;
                        if (knightNum == 0) {
                            win = false;
                            return false;
                        }
                        else
                            continue;
                    }
                    if (ultimeciaHP <= 0 && knightNum > 0) {
                        win = true;
                        return true;
                    }
                }
                else
                    continue;
            }
            knightNum = 0;
            win = false;
            return false;
        }
        else {
            knightNum = 0;
            win = false;
            return false;
        }
    }
}

bool ArmyKnights::adventure(Events * event) {//use to perform action, the final return is if the army win or not
    for (int i = 0; i < event->count(); i++) {
        int currentHP = lastKnight()->getHP();
        int currentId = lastID;
        if (omegaWeapon && event->get(i) == 10) {
            printInfo();
            continue;
        }
        if (hades && event->get(i) == 11) {
            printInfo();
            continue;
        }
        BaseOpponent * opponent = new BaseOpponent();
        opponent->setEventCode(event->get(i));
        opponent->setOrder(i);
        if (fight(opponent)) {
            goto here;
        } 
        else {
            if (knightNum == 0) {
                delete opponent;
                printInfo();
                return false;
            }
            if (!(lastKnight()->checkRecover())) {
                lastID--;
                knightNum--;
            }
            if (knightNum == 0) {
                delete opponent;
                printInfo();
                return false;
            }  
        }
        here:
        if (lastKnight()->getHP() < currentHP && lastKnight()->getId() == currentId)
            if (lastKnight()->getBag()->searchPhoenixFirst(lastKnight()) != NULL)
                lastKnight()->getBag()->use(lastKnight(), lastKnight()->getBag()->searchPhoenixFirst(lastKnight()));
        delete opponent;
        printInfo();
        continue;
    }
    if (!ultimecia)
        win = true;
    return win;
}

int ArmyKnights::count() const {//use to count number of knight left
    return knightNum;
}
BaseKnight *ArmyKnights::lastKnight() const{
    if (knightNum == 0) return NULL;
    else return knight[lastID - 1];
}
bool ArmyKnights::hasPaladinShield() const{
    return paladinShield;
}

bool ArmyKnights::hasLancelotSpear() const{
    return lancelotSpear;
}

bool ArmyKnights::hasGuinevereHair() const{
    return guinevereHair;
}

bool ArmyKnights::hasExcaliburSword() const{
    if (hasPaladinShield() && hasLancelotSpear() && hasGuinevereHair() && excaliburSword)
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
ArmyKnights::~ArmyKnights() {
    if (knightNum > 0)
        for (int i = 0; i < knightNum; i++) {
            delete knight[i];
        }
    delete [] knight;
    knight = NULL;
    knightNum = 0;
};
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
    if (armyKnights && events) 
        armyKnights->printResult(armyKnights->adventure(events));
}
KnightAdventure::~KnightAdventure() {
    if (armyKnights && events) {
        delete armyKnights;
        delete events;
    }
}
/* * * END implementation of class KnightAdventure * * */