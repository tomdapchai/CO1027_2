#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG
class Events {
public:
    Events(const string & file_events);
    int count() const;
    int get(int i) const;
    ~Events();
};

enum ItemType {ANTIDOTE = 0, PHOENIXDOWNI, PHOENIXDOWNII, PHOENIXDOWNIII, PHOENIXDOWNIV};
class BaseOpponent{

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
    BaseBag * bag;
    KnightType knightType;
public:
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    void setId(int i);
    int getId(int i);
    void setHP(int i, int hp);
    int getHP(int i);
    void setMaxHP(int i, int maxhp);
    int getMaxHP(int i);
    void setLevel(int i, int level);
    int getLevel(int i);
    void setGil(int i,int gil);
    int getGil(int i);
    void setAntidote(int i, int antidote);
    int getAntidote(int i);
};
class PaladinKnight : public BaseKnight{

};

class LancelotKnight : public BaseKnight{

};
class DragonKnight : public BaseKnight{

};
class NormalKnight : public BaseKnight{

};
class ArmyKnights : public BaseKnight{
public:
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
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class Antidote : public BaseItem{

};

class PhoenixDownI : public BaseItem{

};

class PhoenixDownII : public BaseItem{

};

class PhoenixDownIII : public BaseItem{

};

class PhoenixDownIV : public BaseItem{

};
class BaseBag {
public:
    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
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