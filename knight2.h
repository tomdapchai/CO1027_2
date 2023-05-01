#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"
#define MAX_LEVEL 10
#define MAX_GIL 999
#define MAX_ITEM_NORMAL 19
#define MAX_ITEM_LANCELOT 16
#define MAX_ITEM_DRAGON 14
#define MAX_HP 999
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
    int eventCode;
    int baseDamage;
public:
    int getEventCode(){
        return eventCode;
    }
    void setBaseDamage(int damage) {
        this->baseDamage = damage;
    }
    int getBaseDamage(){
        return baseDamage;
    }
    void fight();
};

class MadBear : public BaseOpponent{};
class Bandit : public BaseOpponent{};
class LordLupin : public BaseOpponent{};
class Elf : public BaseOpponent{};
class Troll : public BaseOpponent{};
class Tornbery : public BaseOpponent{};
class QueenOfCards : public BaseOpponent{};
class NinaDeRings : public BaseOpponent{};
class DurianGarden : public BaseOpponent{};
class OmegaWeapon : public BaseOpponent{};
class Hades : public BaseOpponent{};

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
    void setType(KnightType type);    
    KnightType getType();
};
class PaladinKnight : public BaseKnight{};
class LancelotKnight : public BaseKnight{};
class DragonKnight : public BaseKnight{};
class NormalKnight : public BaseKnight{};

class ArmyKnights{
public:
    int knightNum;
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
    BaseItem * head = NULL;
    int maxItem;
    BaseKnight * knight;
    void addItemHead(ItemType item);
    int itemCount();
    virtual bool insertFirst(BaseItem * item);
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