#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"
#define MAX_LEVEL 10
#define MAX_GIL 999
#define MAX_ITEM_NORMAL 19
#define MAX_ITEM_LANCELOT 16
#define MAX_ITEM_DRAGON 14
#define MAX_HP 999
#define MADBEAR_DAMAGE 10
#define BANDIT_DAMAGE 15
#define LORDLUPIN_DAMAGE 45
#define ELF_DAMAGE 75
#define TROLL_DAMAGE 95
#define MADBEAR_GIL 100
#define BANDIT_GIL 150
#define LORDLUPIN_GIL 450
#define ELF_GIL 750
#define TROLL_GIL 800
// #define DEBUG
class Events;
class BaseKnight;
class ArmyKnights;
class BaseOpponent;
class BaseItem;
class BaseBag;
class KnightAdventure;

class Events {
public:
    int eventNum;
    int *event;
    Events(const string & file_events);
    int count() const;
    int get(int i) const;
    ~Events();
};

enum ItemType {ANTIDOTE = 0, PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII, PHOENIXDOWNIV};
class BaseOpponent{
protected:
    int order;
    int eventCode;
    int baseDamage;
    int gil;
    int levelO;
public:
    int getOrder() const; //havent done this
    void setOrder(int order);
    int getGilReward() const;
    void setGilReward(int gil);
    int getEventCode() const;
    void setEventCode(int eventCode);
    void setBaseDamage(int damage);
    int getBaseDamage() const;
};

class BaseItem {
public:
    ItemType item;
    BaseItem * next;
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};
class Antidote : public BaseItem{
public:
    Antidote();
    bool canUse(BaseKnight * knight);
    void use (BaseKnight * knight);
};

class PhoenixDownI : public BaseItem{
public:
    PhoenixDownI();
    bool canUse(BaseKnight * knight);
    void use (BaseKnight * knight);
};

class PhoenixDownII : public BaseItem{
public:
    PhoenixDownII();
    bool canUse(BaseKnight * knight);
    void use (BaseKnight * knight);
};

class PhoenixDownIII : public BaseItem{
public:
    PhoenixDownIII();
    bool canUse(BaseKnight * knight);
    void use (BaseKnight * knight);
};

class PhoenixDownIV : public BaseItem{
public:
    PhoenixDownIV();
    bool canUse(BaseKnight * knight);
    void use (BaseKnight * knight);
};

class BaseBag {
protected:
    int maxItem;
public:
    BaseItem* head = NULL;
    int getMaxItem();
    void setMaxItem(int maxItem);
    BaseKnight * knight;
    void addItemHead(ItemType item);
    int itemCount();
    virtual bool insertFirst(BaseItem * item) = 0;
    void use(BaseKnight * knight, BaseItem * item);
    void removeItemHead();
    void swapItemHead(BaseItem * need);
    BaseItem * searchPhoenixFirst(BaseKnight * knight);
    BaseItem *search(ItemType item);
    virtual string toString() const;
    ~BaseBag();
};
class bagNormal : public BaseBag {
public:
    bagNormal(BaseKnight *knight, int numPhoenixDownI, int numantidote);
    bool insertFirst(BaseItem * item);
};
class bagPaladin : public BaseBag {
public:
    bagPaladin(BaseKnight *knight, int numPhoenixDownI, int numantidote);
    bool insertFirst(BaseItem * item);
};
class bagLancelot : public BaseBag {
public:
    bagLancelot(BaseKnight *knight, int numPhoenixDownI, int numantidote);
    bool insertFirst(BaseItem * item);
};
class bagDragon : public BaseBag {
public:
    bagDragon(BaseKnight *knight, int numPhoenixDownI, int numantidote);
    bool insertFirst(BaseItem * item);
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
    BaseBag * bag;
    KnightType knightType;
public:
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    void setId(int id);
    int getId() const;
    void setHP(int hp);
    int getHP() const;
    void setMaxHP(int maxhp);
    int getMaxHP() const;
    void setLevel(int level);
    int getLevel() const;
    void setGil(int gil);
    int getGil() const;
    void setPhoenix(int phoenixdownI);
    int getPhoenix() const;
    void setAntidote(int antidote);
    int getAntidote() const;
    BaseBag *getBag();
    void setType(KnightType type);
    bool checkRecover();    
    KnightType getType() const;
};

class ArmyKnights{
public:
    int knightNum;
    int lastID;
    BaseKnight **knight;
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    void transferGil(); // edit more
    void transferItem(ItemType item); //edit more
    int count() const;
    BaseKnight * lastKnight() const;
    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;
    void printInfo() const;
    void printResult(bool win) const;
};

class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;
public:
    KnightAdventure();
    ~KnightAdventure();
    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__