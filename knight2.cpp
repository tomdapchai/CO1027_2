#include "knight2.h"
int *event = new int[1000];
BaseKnight *knight = new BaseKnight[1000];
int eventNum, knightNum;

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
    head = head->next;
}
void removeItemEnd(Item *&head) {
    Item *temp = head;
    while ((temp->next)->next != NULL) {
        temp = temp->next;
    }
    temp->next = NULL;
}
void removeItemMid(Item *&head, int pos) {
    Item *temp = head;
    int count = 0;
    while (count != (pos - 1)) {
        temp = temp->next;
        count ++;
    }
    temp->next = (temp->next)->next;
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

/* * * END implementation of class BaseBag * * */
/*BEGIN BaseItem*/
bool BaseItem::canUse(BaseKnight * knight) {
    
}
void BaseItem::use(BaseKnight * knight) {

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
void BaseKnight::setId(int i){
    knight[i].id = i;
}
int BaseKnight::getId(int i){
    return knight[i].id;
}
void BaseKnight::setHP(int i, int hp){
    knight[i].hp = hp;
}
int BaseKnight::getHP(int i){
    return knight[i].hp;
}
void BaseKnight::setLevel(int i, int level){
    knight[i].level = level;
}
int BaseKnight::getLevel(int i){
    return knight[i].level;
}
void BaseKnight::setMaxHP(int i, int maxhp){
    knight[i].maxhp = maxhp;
}
int BaseKnight::getMaxHP(int i){
    return knight[i].maxhp;
}
void BaseKnight::setGil(int i, int gil){
    knight[i].gil = gil;
}
int BaseKnight::getGil(int i){
    return knight[i].gil;
}
void BaseKnight::setAntidote(int i, int antidote){
    knight[i].antidote = antidote;
}
int BaseKnight::getAntidote(int i){
    return knight[i].antidote;
}
/* * * END implementation of class BaseKnight * * */

/* * * BEGIN implementation of class ArmyKnights * * */
ArmyKnights::ArmyKnights(const string & file_armyknights){
    ifstream f;
    f.open(file_armyknights);
    f >> knightNum;
    for (int i = 1; i <= knightNum; i++){
        int hp, level, phoenixdownI, gil, antidote;
        f >> hp >>level >> phoenixdownI >> gil >> antidote;
        knight[i].setId(i);
        knight[i].setHP(i, hp);
        knight[i].setMaxHP(i, hp);
        knight[i].setLevel(i, level);
        knight[i].setGil(i, gil);
        knight[i].setAntidote(i, antidote);
    }
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