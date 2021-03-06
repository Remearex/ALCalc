#pragma once
#include <vector>
#include <string>
#include "../HeaderFiles//ParameterClasses.h"

double getActualRldTime(RldPL pl);
double getLaunchCdCalc(LaunchCdPL pl);
double getAirResistance(double aa, double aaBonus);
double getRammingDmg(int ownShipMaxHp, int otherShipMaxHp, double otherShipRamAtkBonus, double ownShipRamDefBonus);
double getPullRate(double rateOfShip, int pulls);
double getIndividualBarrageDmgCalc(Barrage barrage);
double getGunDmgCalc(GunPL pl);
double getTorpDmgCalc(TorpPL pl);
double getPlaneGroundDmgCalc(PlaneGroundDmgPL planeDmgPL);
double getAirStrikeDmgCalc(std::vector<Plane> planes, std::vector<double> effs, PlaneGroundDmgPL pl);
double getFloodDmgCalc(FloodPL pl);
double getBurnDmgCalc(BurnPL pl);
double getHitRateCalc(AccPL accPL);
double getCritRateCalc(AccPL pl);
double getGunEDPS(GunPL gunPl, AccPL accPl, double rldDuration, AmmoSkill ammoSkill);
double getBarrageEDPS(WholeBarrage wholeBarrage, AccPL accPl, AmmoSkill ammoSkill);

std::vector<std::string> split(std::string s, char c);