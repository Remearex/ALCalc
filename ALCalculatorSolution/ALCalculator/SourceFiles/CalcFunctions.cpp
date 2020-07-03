#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../HeaderFiles/ParameterClasses.h"

//not called by Main
double getBasicRldTime(double weaponRldDuration, double rld, double rldBonus) {
	return weaponRldDuration * sqrt(200 / (rld * (1 + rldBonus) + 100));
}

double getActualRldTime(RldPL pl) {
	double finalRldTime;
	double weaponRldDuration = pl.weaponRldDuration;
	double rld = pl.rld;
	double rldBonus = pl.rldBonus;
	bool tempRldBonus = pl.tempRldBonus;
	double rldBonusDuration = pl.rldBonusDuration;
	//without tempRldBonus
	if (!tempRldBonus) {
		finalRldTime = getBasicRldTime(weaponRldDuration, rld, rldBonus);
	}
	//with tempRldBonus
	else if (tempRldBonus) {
		double buffedRldDuration = getBasicRldTime(weaponRldDuration, rld, rldBonus);
		double buffedRldRate = 1 / buffedRldDuration;
		double amountOfRldDone = buffedRldRate * rldBonusDuration;
		//if the duration lasts for the entire rld
		if (amountOfRldDone >= 1) {
			finalRldTime = buffedRldDuration;
		}
		//if the duration doesn't last the entire rld
		else if (amountOfRldDone < 1) {
			double unBuffedRldRate = 1 / getBasicRldTime(weaponRldDuration, rld, 0);
			double amountOfRldRemaining = 1 - amountOfRldDone;
			finalRldTime = amountOfRldRemaining / unBuffedRldRate + rldBonusDuration;
		} else {
			std::cout << "something went wrong with the 'amountOfRldDone' parameter";
			return NULL;
		}
	} else {
		std::cout << "something went wrong with the 'tempRldBonus' parameter";
		return NULL;
	}
	return finalRldTime;
}

double getLaunchCdCalc(LaunchCdPL pl) {
	std::vector<double> planeCds = pl.planeCds;
	std::vector<int> planeCounts = pl.planeCounts;
	double rld = pl.rld;
	double rldBonus = pl.rldBonus;
	double cdReduction = pl.cdReduction;
	bool withHomingBeacon = pl.withHomingBeacon;
	if (planeCds.size() != planeCounts.size()) {
		std::cout << " you have " << planeCds.size() << " plane cooldown values but " << planeCounts.size() << " plane count values";
		return 0;
	}
	double summedPlaneCdsAndCounts = 0;
	double summedPlaneCounts = 0;
	double cdTime;
	for (int i = 0; i < planeCds.size(); i++) {
		summedPlaneCdsAndCounts += planeCds.at(i) * planeCounts.at(i);
		summedPlaneCounts += planeCounts.at(i);
	}
	if (withHomingBeacon) cdReduction += 0.04;
	cdTime = (1 - cdReduction) * (summedPlaneCdsAndCounts / summedPlaneCounts) * 2.2 * sqrt(200 / (100 + rld*(1 + rldBonus))) + 0.1;
	return cdTime;
}

double getAirResistance(double aa, double aaBonus) {
	return 1 - 150/(150 + aa*(1+aaBonus));
}

double getRammingDmg(int ownShipMaxHp, int otherShipMaxHp, double otherShipRamAtkBonus, double ownShipRamDefBonus) {
	return std::min(0.05*ownShipMaxHp, 0.025*sqrt(ownShipMaxHp*otherShipMaxHp)) * (1+otherShipRamAtkBonus)*(1-ownShipRamDefBonus);
}

double getPullRate(double rateOfShip, int pulls) {
	return 1 - std::pow(1-rateOfShip, pulls);
}

double getIndividualBarrageDmgCalc(Barrage barrage, bool ammoBuffBit) {
	double finalDmg = barrage.baseDmg * barrage.count * barrage.coefficient * barrage.armorMod * (1 + 2*(double)(barrage.lvDifference)/100) * (1 + ammoBuffBit*0.1 + barrage.dmgBonus) *
		(1 + barrage.enemyDebuff) * (1 + barrage.hunterBonus) * (1 + (barrage.scalingStat+barrage.scalingStatFromGear)/100 * (1 + barrage.formationBonus + barrage.scalingStatBonus) * barrage.scaling) *
		(1 + barrage.critBit*(0.5 + barrage.critBonus));
	return finalDmg;
}

double getGunDmgCalc(GunPL pl) {
	double finalDmg = pl.mgms * pl.baseDmg * pl.coefficient * pl.count * pl.slotEff * pl.armorMod * (1 + 2*(double)(pl.lvDifference)/100) *
		(1 + pl.ammoBuffBit*0.1 + pl.dmgBonus) * (1 + pl.ammoTypeMod) * (1 + pl.enemyDebuff) * (1 + pl.hunterBonus) *
		(1 + (pl.fp+pl.fpFromGear)/100 * (1 + pl.formationBonus + pl.fpBonus)) * (1 + pl.critBit*(0.5 + pl.critBonus));
	return finalDmg;
}

double getTorpDmgCalc(TorpPL pl) {
	double finalDmg = pl.baseDmg * pl.coefficient * pl.count * pl.slotEff * pl.armorMod * (1 + 2*(double)(pl.lvDifference)/100) *
		(1 + pl.ammoBuffBit*0.1 + pl.dmgBonus) * (1 + pl.enemyDebuff) * (1 + pl.hunterBonus) *
		(1 + (pl.trp+pl.trpFromGear)/100 * (1 + pl.formationBonus + pl.trpBonus)) * (1 + pl.critBit*(0.5 + pl.critBonus));
	return finalDmg;
}

double getPlaneGroundDmgCalc(PlaneGroundDmgPL pl) {
	double finalGroundDmg = 0;
	Plane plane = pl.plane;
	for (int i = 0; i < plane.bombDmgs.size(); i++) {
		finalGroundDmg += plane.bombDmgs.at(i) * pl.slotEff * plane.bombDmgArmorMods.at(i) * (1 + 2*(double)(pl.lvDifference)/100) *
			(1 + pl.AmmoBuffBit*0.1 + pl.dmgBonus) * (1 - pl.enemyAirResistance) * (1 + pl.enemyDebuff) * (1 + pl.hunterBonus) *
			(1 + (pl.avi+pl.aviFromGear)/100 * 0.8 * (1 + pl.aviBonus)) * (1 + pl.critBit*(0.5 + pl.critBonus));
	}
	for (int i = 0; i < plane.torpDmgs.size(); i++) {
		finalGroundDmg += plane.torpDmgs.at(i) * pl.slotEff * plane.torpDmgArmorMods.at(i) * (1 + 2*(double)(pl.lvDifference)/100) *
			(1 + pl.AmmoBuffBit*0.1 + pl.dmgBonus) * (1 - pl.enemyAirResistance) * (1 + pl.enemyDebuff) + (1 + pl.hunterBonus) *
			(1 + (pl.avi+pl.aviFromGear)/100 * (1 + pl.aviBonus)) * (1 + pl.critBit*(0.5 + pl.critBonus));
	}
	return finalGroundDmg;
}

double getAirStrikeDmgCalc(std::vector<Plane> planes, std::vector<double> effs, PlaneGroundDmgPL pl) {
	double finalAirStrikeGroundDmg = 0;
	for (int i = 0; i < planes.size(); i++) {
		pl.plane = planes.at(i);
		pl.slotEff = effs.at(i);
		finalAirStrikeGroundDmg += getPlaneGroundDmgCalc(pl);
	}
	return finalAirStrikeGroundDmg;
}

double getFloodDmgCalc(FloodPL pl) {
	double finalFloodDmg = (pl.duration/pl.tickInterval) * (pl.baseDmg * pl.coefficient *
		(1 + (pl.scalingStat+pl.scalingStatFromGear)/100 * (1+pl.formationBonus+pl.scalingStatBonus)) * pl.floodCoef + 10);
	return finalFloodDmg;
}

double getBurnDmgCalc(BurnPL pl) {
	double finalBurnDmg = (pl.duration/pl.tickInterval) * (1+pl.burnDmgBonus) * (pl.baseDmg * pl.coefficient * pl.slotEff *
		(1 + (pl.fp+pl.fpFromGear)/100 * (1+pl.formationBonus+pl.fpBonus)) * pl.burnCoef + 5);
	return finalBurnDmg;
}

double getHitRateCalc(AccPL accPL) {
	double finalAttackerHit = accPL.attackerHit * (1+accPL.attackerHitBonus);
	double finalAttackerLuck = accPL.attackerLuck * (1+accPL.attackerLuckBonus);
	double finalDefenderEva = accPL.defenderEva * (1+accPL.defenderEvaBonus);
	double finalDefenderLuck = accPL.defenderLuck * (1+accPL.defenderLuckBonus);
	double finalHitRate = 0.1 + finalAttackerHit/(finalAttackerHit+finalDefenderEva+2) +
		(finalAttackerLuck-finalDefenderLuck+accPL.lvDifference)/1000 + accPL.attackerAccBonus - accPL.defenderEvaRateBonus;
	if(finalHitRate < 1) return finalHitRate;
	else return 1;
}

double getCritRateCalc(AccPL pl) {
	double finalAttackerHit = pl.attackerHit * (1+pl.attackerHitBonus);
	double finalAttackerLuck = pl.attackerLuck * (1+pl.attackerLuckBonus);
	double finalDefenderEva = pl.defenderEva * (1+pl.defenderEvaBonus);
	double finalDefenderLuck = pl.defenderLuck * (1+pl.defenderLuckBonus);
	double finalCritRate = 0.05 + (finalAttackerHit/(finalAttackerHit+finalDefenderEva+2000)) +
		((finalAttackerLuck-finalDefenderLuck+pl.lvDifference)/5000) + pl.critRateBonus;
	if(finalCritRate < 1) return finalCritRate;
	else return 1;
}

double getGunEDPS(GunPL gunPl, AccPL accPl, double rldDuration, AmmoSkill ammoSkill) {
	double nonCritDmg;
	double critDmg;
	double critRate;
	double avgDmg;
	double shellingEDPS;
	double skillDmg = 0; //dmg from main gun skill(s)
	double skillEDPS;
	double eHitRate;
	double netEDPS;

	//nonCritDmg
	gunPl.critBit = false;
	nonCritDmg = getGunDmgCalc(gunPl);
	//critDmg
	gunPl.critBit = true;
	critDmg = getGunDmgCalc(gunPl);
	//critRate
	critRate = getCritRateCalc(accPl);
	//avgDmg
	avgDmg = (critRate*critDmg) + ((1-critRate)*nonCritDmg);
	//effectiveHitRate
	eHitRate = (gunPl.avgShellsHit/((double)gunPl.mgms*gunPl.count)) * getHitRateCalc(accPl);
	//shellingEDPS
	shellingEDPS = (avgDmg*eHitRate) / rldDuration;
	//skillDmg
	if (ammoSkill.burn) skillDmg += getBurnDmgCalc(ammoSkill.burnPl);
	if (ammoSkill.flood) skillDmg += getFloodDmgCalc(ammoSkill.floodPl);
	//skillEDPS
	skillEDPS = skillDmg / rldDuration;
	//netEDPS
	netEDPS = shellingEDPS + skillEDPS;
	return netEDPS;
}

double getTorpEDPS() {
	return 0;
}

double getAirStrikeEDPS() {
	return 0;
}

double getBarrageEDPS(WholeBarrage wholeBarrage, AccPL accPl, AmmoSkill ammoSkill) {
	double barrageEDPS = 0;
	double skillEDPS;
	double finalEDPS;

	//barrage edps
	double rngHitRate = getHitRateCalc(accPl);
	for (int i = 0; i < wholeBarrage.barrages.size(); i++) {
		bool ammoBuffBit = wholeBarrage.ammoBuffBit;
		Barrage thisBarrage = wholeBarrage.barrages.at(i);
		//get the avg raw dmg (factoring crit)
		thisBarrage.critBit = 0;
		double rawBarrageNonCritDmg = getIndividualBarrageDmgCalc(thisBarrage, ammoBuffBit);
		thisBarrage.critBit = 1;
		double rawBarrageCritDmg = getIndividualBarrageDmgCalc(thisBarrage, ammoBuffBit);
		double critRate;
		if(wholeBarrage.guaranteedCrit) critRate = 1;
		else critRate = getCritRateCalc(accPl);
		double netRawDmg = ((1-critRate)*rawBarrageNonCritDmg) + (critRate*rawBarrageCritDmg);
		//get eHitRate (physical and rng)
		double eHitRate = (thisBarrage.avgShellsHit/(double)thisBarrage.count) * rngHitRate;
		//get effective dmg (proc chance and eHitRate)
		double effectiveBarrageDmg = wholeBarrage.procChance * eHitRate * netRawDmg;
		//final edps (rld)
		double eDPS = effectiveBarrageDmg / wholeBarrage.rldDuration;
		barrageEDPS += eDPS;
	}
	//barrage skill edps
	double skillDmg = 0;
	if(ammoSkill.burn) skillDmg += getBurnDmgCalc(ammoSkill.burnPl);
	if(ammoSkill.flood) skillDmg += getFloodDmgCalc(ammoSkill.floodPl);
	skillEDPS = skillDmg / wholeBarrage.rldDuration;
	//final EDPS (barrage and barrage ammo skill together)
	finalEDPS = barrageEDPS + skillEDPS;
	return finalEDPS;
}