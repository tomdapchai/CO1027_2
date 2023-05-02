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
class Events {
public:
    int *event = new int[1000];
    int eventNum;
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
    int getOrder();
    void setOrder(int order);
    int getGil();
    void setGil(int gil);
    int getEventCode();
    void setBaseDamage(int damage);
    int getBaseDamage();
    void fight();
};

class MadBear : public BaseOpponent{
public:
    MadBear();
};
class Bandit : public BaseOpponent{
public:
    Bandit();
};
class LordLupin : public BaseOpponent{
public:
    LordLupin();
};
class Elf : public BaseOpponent{
public:
    Elf();
};
class Troll : public BaseOpponent{
public:
    Troll();
};
class Tornbery : public BaseOpponent{};
class QueenOfCards : public BaseOpponent{};
class NinaDeRings : public BaseOpponent{};
class DurianGarden : public BaseOpponent{};
class OmegaWeapon : public BaseOpponent{};
class Hades : public BaseOpponent{};
class PhoenixII : public BaseOpponent{};
class PhoenixIII : public BaseOpponent{};
class PhoenixIV : public BaseOpponent{};
class PaladinShield : public BaseOpponent{};
class LancelotSpear : public BaseOpponent{};
class GuinevereHair : public BaseOpponent{};

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
    int getId();
    void setHP(int hp);
    int getHP();
    void setMaxHP(int maxhp);
    int getMaxHP();
    void setLevel(int level);
    int getLevel();
    void setGil(int gil);
    int getGil();
    void setPhoenix(int phoenixdownI);
    int getPhoenix();
    void setAntidote(int antidote);
    int getAntidote();
    void setBag(BaseBag * bag);
    BaseBag *getBag();
    void setType(KnightType type);
    bool checkRecover();    
    KnightType getType();
    virtual bool fight(BaseOpponent * opponent) = 0;
};
class PaladinKnight : public BaseKnight{
public:
    PaladinKnight();
    bool fight(BaseOpponent * opponent);
};
class LancelotKnight : public BaseKnight{
public:
    LancelotKnight();
    bool fight(BaseOpponent * opponent);
};
class DragonKnight : public BaseKnight{
public:
    DragonKnight();
    bool fight(BaseOpponent * opponent);
};
class NormalKnight : public BaseKnight{
public:
    NormalKnight();
    bool fight(BaseOpponent * opponent);
};

class ArmyKnights{
public:
    int knightNum;
    BaseKnight **knight = new BaseKnight*[knightNum];
    ArmyKnights (const string & file_armyknights);
    ~ArmyKnights();
    bool fight(BaseOpponent * opponent);
    bool adventure (Events * events);
    int count() const;
    BaseKnight * lastKnight() const;
    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;
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
public:
    BaseItem* head = NULL;
    int maxItem;
    BaseKnight * knight;
    void addItemHead(ItemType item);
    int itemCount();
    virtual bool insertFirst(BaseItem * item);
    virtual void use(BaseKnight * knight, BaseItem * item);
    void removeItemHead(BaseItem *head);
    void swapItemHead(BaseItem *head, BaseItem * need);
    BaseItem * searchPhoenixFirst(BaseItem * head, BaseKnight * knight);
    BaseItem *search(BaseItem *head, ItemType item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
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
class KnightAdventure {
private:
    ArmyKnights * armyKnights;
    Events * events;

public:
    KnightAdventure();
    ~KnightAdventure(); // TODO:

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__