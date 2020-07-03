#pragma once
#include <vector>

//this might be useful later
enum class PlaneType {
	Fighter,
	DiveBomber,
	TorpedoBomber,
};

class Barrage {
public:
	double avgShellsHit;
	double baseDmg;
	double coefficient;
	int count;
	double armorMod;
	double scaling;
	int lvDifference;
	double dmgBonus;
	double enemyDebuff;
	double hunterBonus;
	double scalingStat;
	double scalingStatFromGear;
	double formationBonus;
	double scalingStatBonus;
	bool critBit;
	double critBonus;
};

class WholeBarrage {
public:
	std::vector<Barrage> barrages;
	double rldDuration;
	double procChance;
	bool ammoBuffBit;
	bool guaranteedCrit;
};

class GunPL {
public:
	double avgShellsHit;
	int mgms;
	double baseDmg;
	double coefficient;
	int count;
	double slotEff;
	double armorMod;
	int lvDifference;
	bool ammoBuffBit;
	double dmgBonus;
	double ammoTypeMod;
	double enemyDebuff;
	double hunterBonus;
	double fp;
	double fpFromGear;
	double formationBonus;
	double fpBonus;
	bool critBit;
	double critBonus;
};

class TorpPL {
public:
	double baseDmg;
	double coefficient;
	int count;
	double slotEff;
	double armorMod;
	int lvDifference;
	bool ammoBuffBit;
	double dmgBonus;
	double enemyDebuff;
	double hunterBonus;
	double trp;
	double trpFromGear;
	double formationBonus;
	double trpBonus;
	bool critBit;
	double critBonus;
};

class Plane {
public:
	std::string name;
	PlaneType planeType;
	double cd;
	std::vector<double> bombDmgs;
	std::vector<double> bombDmgArmorMods;
	std::vector<double> torpDmgs;
	std::vector<double> torpDmgArmorMods;
	std::vector<double> aaGunDmgs;
};

class PlaneGroundDmgPL {
public:
	Plane plane;
	double slotEff;
	int lvDifference;
	bool AmmoBuffBit;
	double dmgBonus;
	double enemyAirResistance;
	double enemyDebuff;
	double hunterBonus;
	double avi;
	double aviFromGear;
	double aviBonus;
	bool critBit;
	double critBonus;
};

class AccPL {
public:
	int attackerHit;
	double attackerHitBonus;
	int attackerLuck;
	double attackerLuckBonus;
	int defenderEva;
	double defenderEvaBonus;
	int defenderLuck;
	double defenderLuckBonus;
	int lvDifference;
	double attackerAccBonus;
	double defenderEvaRateBonus;
	double critRateBonus;
};

class FloodPL {
public:
	int duration;
	int tickInterval;
	double baseDmg;
	double coefficient;
	double scalingStat;
	double scalingStatFromGear;
	double formationBonus;
	double scalingStatBonus;
	double floodCoef;
};

class BurnPL {
public:
	int duration;
	int tickInterval;
	double burnDmgBonus;
	double baseDmg;
	double coefficient;
	double slotEff;
	double fp;
	double fpFromGear;
	double formationBonus;
	double fpBonus;
	double burnCoef;
};


class AmmoSkill {
public:
	bool burn;
	bool pierce;
	bool armorBreak;
	bool flood;

	BurnPL burnPl;
	FloodPL floodPl;
};

class RldPL {
public:
	double weaponRldDuration;
	double rld;
	double rldBonus;
	bool tempRldBonus;
	double rldBonusDuration;
};

class LaunchCdPL {
public:
	std::vector<double> planeCds;
	std::vector<int> planeCounts;
	double rld;
	double rldBonus;
	double cdReduction;
	bool withHomingBeacon;
};