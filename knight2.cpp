#include "knight2.h"
int *event = new int[1000];
BaseKnight *knight = new BaseKnight[1000];
int eventNum, knightNum;
bool paladinShield = false;
bool lancelotSpear = false;
bool guinevereHair = false;
bool poison = false;
ItemType item;
bool primeCheck(int a){
    if (a <= 1) return false;
    if (a == 2 || a == 3) return true;
    for (int i = 2; i <= a / 2; i++)
        if (a % i == 0) return false;
    return true;
}
bool pythagorasCheck(int a, int b, int c){
    if ((pow(a, 2) + pow(b, 2) == pow(c, 2)) ||
        (pow(b, 2) + pow(c, 2) == pow(a, 2)) ||
        (pow(c, 2) + pow(a, 2) == pow(b, 2))
    )
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
struct Item{
    ItemType ItemID;
    Item *next;
};
Item *createItem(ItemType item){
    Item *newItem = new Item();
    newItem->ItemID = item;
    newItem->next = NULL;
    return newItem;
}
void traverse(Item *head){
    while (head->next != NULL) {
        cout << head->ItemID;
        head = head->next;
    }
}
int itemCount(Item *head){
    int count = 0;
    while (head != NULL){
        count ++;
        head = head->next;
    }
    return count;
}
void itemSearch(ItemType item, Item *head) {
    while (head != NULL){
        if (item == head->ItemID) break;
        else head = head->next;
    }
    //add more later, still not figure out what to do
}
ItemType itemGet(Item *head, int index){
    int k = 0;
    while (k < index) {
        k++;
        head = head->next;
    }
    return head->ItemID;
}
void addItemHead(Item *&head, ItemType item){
    Item *newItem = createItem(item);
    newItem->next = head;
    head = newItem;
}
void addItemEnd(Item *&head, ItemType item){
    Item *newItem = createItem(item);
    Item *temp = head;
    if (head == NULL) {
        head = newItem;
        return;
    }
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = newItem;
    newItem->next = NULL;
}
void addItemMid(Item *&head, ItemType item, int pos){
    if (pos == 1) {
        addItemHead(head, item);
        return;
    }
    Item *newItem = createItem(item);
    Item *temp = head;
    int count = 0;
    while (count != pos) {
        temp = temp->next;
        count++;
    }
    newItem->next = temp->next;
    temp->next = newItem;
}
void removeItemHead(Item *&head) {
    if (head == NULL) return;
    Item *temp = head;
    head = head->next;
    delete temp;
}
void removeItemEnd(Item *&head) {
    if (head == NULL) return;
    Item *temp = head;
    if (temp->next == NULL) {
        head = NULL;
        delete temp;
        return;
    }
    while ((temp->next)->next != NULL) {
        temp = temp->next;
    }
    Item *temp1 = temp->next;
    temp->next = NULL;
    delete temp1;
}
void removeItemMid(Item *&head, int pos) {
    Item *temp = head;
    int count = 0;
    while (count != (pos - 1)) {
        temp = temp->next;
        count ++;
    }
    Item *temp1 = temp->next;
    temp->next = (temp->next)->next;
    delete temp1;
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
bool BaseBag::insertFirst(BaseItem *item) {

}

/* * * END implementation of class BaseBag * * */
/*BEGIN BaseItem*/
bool Antidote::canUse(BaseKnight * knight) {
    if (poison && knight->getType() != DRAGON && knight->getAntidote()) return true;
    else return false;
}
void Antidote::use(BaseKnight * knight) {
    poison = false;
}
bool PhoenixDownI::canUse(BaseKnight * knight) {
    if (knight->getHP() <= 0) return true;
    else return false;
}
void PhoenixDownI::use(BaseKnight * knight) {
    knight->setHP(knight->getMaxHP());
}
bool PhoenixDownII::canUse(BaseKnight * knight) {
    if (knight->getHP() < (knight->getMaxHP() / 4)) return true;
    else return false;
}
void PhoenixDownII::use(BaseKnight * knight) {
    knight->setHP(knight->getMaxHP());
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
    knight->knightType = knightCheck(maxhp);
    knight->id = id;
    knight->maxhp = maxhp;
    knight->hp = maxhp;
    knight->level = level;
    knight->gil = gil;
    knight->antidote = antidote;
    return knight;
}
void BaseKnight::setId(int id){
    this->id = id + 1;
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
void BaseKnight::setType(KnightType type){
    this->knightType = type;
}
KnightType BaseKnight::getType() {
    return knightType;
}

/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string & file_armyknights){
    ifstream f;
    f.open(file_armyknights);
    f >> knightNum;
    for (int i = 0; i < knightNum; i++){
        int hp, level, phoenixdownI, gil, antidote;
        f >> hp >> level >> phoenixdownI >> gil >> antidote;
        knight[i].setId(i);
        knight[i].setHP(hp);
        knight[i].setMaxHP(hp);
        knight[i].setLevel(level);
        knight[i].setGil(gil);
        knight[i].setAntidote(antidote);
    }
    f.close();
}

bool ArmyKnights::fight(BaseOpponent * opponent) {
    if (opponent->getEventCode() >= 1 && opponent->getEventCode() <= 5){

    }
}

bool ArmyKnights::adventure(Events * event) {

}

int ArmyKnights::count() const {

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

/* * * END implementation of class KnightAdventure * * */