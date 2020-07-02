#include "../HeaderFiles/CalcFunctions.h"
#include "../HeaderFiles//ParameterClasses.h"
#include <iostream>
#include <string>

void commandList();
void getRldInit();
void getCVLaunchCdInit();
void getAirResistanceInit();
void getRammingDmgInit();
void getPullRateInit();
void getHitRateInit();
void getCritRateInit();
void getBBEDPSInit();
void getCVEDPSInit();
void getOtherEDPSInit();
double getGunEDPS(AmmoSkill ammoSkill, GunPL gunPl, RldPL rldPl, AccPL accPl, BurnPL burnPl, FloodPL floodPl, double shellsHit, int totShells);
double getTorpEDPS();
double getAirStrikeEDPS();
double getBarrageEDPS();
void getFloodInit();
void getBurnInit();

enum class Command {
	commandList,
	terminate,
	getRldDuration,
	getCVLaunchCd,
	getAirResistance,
	getRammingDmg,
	getPullRate,
	getHitRate,
	getCritRate,
	getBBEDPS,
	getCVEDPS,
	getOtherEDPS,
	getFlood,
	getBurn,
	unknownCommand,
};
Command getCommand(std::string input) {
	if(input == "commandlist") return Command::commandList;
	if(input == "terminate") return Command::terminate;
	if(input == "getRldDuration") return Command::getRldDuration;
	if(input == "getCVLaunchCd") return Command::getCVLaunchCd;
	if(input == "getAirResistance") return Command::getAirResistance;
	if(input == "getRammingDmg") return Command::getRammingDmg;
	if(input == "getPullRate") return Command::getPullRate;
	if(input == "getHitRate") return Command::getHitRate;
	if(input == "getCritRate") return Command::getCritRate;
	if(input == "getBBEDPS") return Command::getBBEDPS;
	if(input == "getCVEDPS") return Command::getCVEDPS;
	if(input == "getOtherEDPS") return Command::getOtherEDPS;
	if(input == "getFlood") return Command::getFlood;
	if(input == "getBurn") return Command::getBurn;
	else return Command::unknownCommand;
}

int main() {
	bool running = true;
	while (running) {
		std::cout << "(enter 'commandlist' for list of commands) command: ";
		std::string input;
		std::getline(std::cin, input);
		switch (getCommand(input)) {
			case Command::commandList:
				commandList();
				break;
			case Command::terminate:
				running = false;
				break;
			case Command::getRldDuration:
				getRldInit();
				break;
			case Command::getCVLaunchCd:
				getCVLaunchCdInit();
				break;
			case Command::getAirResistance:
				getAirResistanceInit();
				break;
			case Command::getRammingDmg:
				getRammingDmgInit();
				break;
			case Command::getPullRate:
				getPullRateInit();
				break;
			case Command::getHitRate:
				getHitRateInit();
				break;
			case Command::getCritRate:
				getCritRateInit();
				break;
			case Command::getBBEDPS:
				getBBEDPSInit();
				break;
			case Command::getCVEDPS:
				getCVEDPSInit();
				break;
			case Command::getOtherEDPS:
				getOtherEDPSInit();
				break;
			case Command::getFlood:
				getFloodInit();
				break;
			case Command::getBurn:
				getBurnInit();
				break;
			case Command::unknownCommand:
				std::cout << input << " is not a valid command, for a list of commands, type 'commandlist' ";
				break;
			default:
				std::cout << input << " what happened lol";
		}
	}
}

void commandList() {
	std::cout << "in progress";
}

void getRldInit() {
	RldPL pl;
	
	std::cout << "enter the following on one line separated by a space: weapon's reload duration, " << 
		"reload stat, reloat stat bonus,: ";
	std::string input;
	std::vector<std::string> splittedInput;
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	
	pl.weaponRldDuration = std::stod(splittedInput.at(0));
	pl.rld = std::stod(splittedInput.at(1));
	pl.rldBonus = std::stod(splittedInput.at(2));

	std::cout << "do you have a temporary reload stat bonus? (enter 'y' for yes, any other key for no): ";
	std::getline(std::cin, input);
	if(input == "y") {
		pl.tempRldBonus = true;
		std::cout << "enter reload stat bonus duration: ";
		std::cin >> pl.rldBonusDuration;
	} else {
		pl.tempRldBonus = false;
		pl.rldBonusDuration = NULL;
	}
	std::cout << "\n\nyou entered:" << std::endl;
	std::cout << "weapon reload duration: " << pl.weaponRldDuration << ", reload stat: " << pl.rld << ", reload stat bonus: " << pl.rldBonus
		<< ", temporary reload stat bonus: " << std::boolalpha << pl.tempRldBonus << ", temporary reload stat bonus duration: " << pl.rldBonusDuration
		<< "\nfinal reload duration: " << getActualRldTime(pl) << std::endl;
}

void getCVLaunchCdInit() {
	std::vector<double> planeCds;
	std::vector<int> planeCounts;
	LaunchCdPL pl;
	std::string input;
	std::vector<std::string> splittedInput;
	std::cout << "enter the cooldowns of the planes in one line separated by a space. For example if using vf-17 in first slot and " << 
		"helldiver in second and third slot, enter '10.2 11.88 11.88' or '10.2 11.88' this will affect what you enter next for plane counts: ";
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	for (int i = 0; i < splittedInput.size(); i++) {
		pl.planeCds.push_back(std::stod(splittedInput.at(i)));
	}
	std::cout << "enter the plane counts of the planes in one line separated by a space. For example if there are 2 vf-17s in first slot, " <<
		"3 helldivers in second and third slot, enter '2 3 3' IF you entered '10.2 11.88 11.88' for the cooldown input. If you entered '10.2 11.88' " <<
		"for cooldown input, enter '2 6'. Basically each number in planecount input must correspond to each number in the cooldown input: ";
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	for (int i = 0; i < splittedInput.size(); i++) {
		pl.planeCounts.push_back(std::stoi(splittedInput.at(i)));
	}
	std::cout << "enter the ship's reload, reload bonus, and cooldown reduction on one line separated by a space: ";
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	pl.rld = std::stod(splittedInput.at(0));
	pl.rldBonus = std::stod(splittedInput.at(1));
	pl.cdReduction = std::stod(splittedInput.at(2));
	std::cout << "are you equipping a homing beacon? (type 'y' for yes and any other key for no): ";
	std::getline(std::cin, input);
	if(input == "y") pl.withHomingBeacon = true;
	else pl.withHomingBeacon = false;

	std::cout << "\n\nyou entered:" << std::endl;
	for (int i = 0; i < planeCds.size(); i++) {
		std::cout << "slot: " << i << " with cd " << planeCds.at(i) << " and planecount " << planeCounts.at(i) << ", ";
	}
	std::cout << "\nrld: " << pl.rld << ", rld stat bonus: " << pl.rldBonus << ", cooldown reduction: " << pl.cdReduction << std::endl;
	std::cout << "with homing beacon: " << std::boolalpha << pl.withHomingBeacon << "\nfinal launch cooldown is: " <<
		getLaunchCdCalc(pl) << std::endl <<std::endl;
}

void getAirResistanceInit() {
	double aa, aaBonus;
	std::string input;
	std::cout << "ship AA: ";
	std::getline(std::cin, input);
	aa = std::stod(input);
	std::cout << "AA stat bonus: ";
	std::getline(std::cin, input);
	aaBonus = std::stod(input);

	std::cout << "\n\nyou entered:" << std::endl;
	std::cout << "AA: " << aa << ", AA stat bonus: " << aaBonus << std::endl;
	std::cout << "final air resistance: " << getAirResistance(aa, aaBonus) << std::endl << std::endl;
}

void getRammingDmgInit() {
	int ownShipMaxHp, otherShipMaxHp;
	double ownShipRamDefBonus, otherShipRamAtkBonus;
	std::string input;
	std::vector<std::string> splittedInput;
	std::cout << "enter own ship's max hp, and other ship's max hp on one line separated by a space: ";
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	ownShipMaxHp = std::stoi(splittedInput.at(0));
	otherShipMaxHp = std::stoi(splittedInput.at(1));
	std::cout << "enter own ship's ram defense bonus, and other ship's ram attack bonus on one line separated by a space: ";
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	ownShipRamDefBonus = std::stod(splittedInput.at(0));
	otherShipRamAtkBonus = std::stod(splittedInput.at(1));

	std::cout << "\n\nyou entered:" << std::endl;
	std::cout << "ownShipMaxHp: " << ownShipMaxHp << ", otherShipMaxHp: " << otherShipMaxHp <<
		", ownShipRamDefBonus: " << ownShipRamDefBonus << ", otherShipRamAtkBonus: " << otherShipRamAtkBonus << std::endl;
	std::cout << "final ramming damage taken: " << getRammingDmg(ownShipMaxHp, otherShipMaxHp, otherShipRamAtkBonus, ownShipRamDefBonus) << std::endl << std::endl;
}

void getPullRateInit() {
	double rateOfShip;
	int pulls;
	std::string input;
	std::cout << "rate of the ship: ";
	std::getline(std::cin, input);
	rateOfShip = std::stod(input);
	std::cout << "number of pulls: ";
	std::getline(std::cin, input);
	pulls = std::stoi(input);
	std::cout << "for shipRate: " << rateOfShip << ", number of pulls: " << pulls << "\nchance at getting the ship: " << getPullRate(rateOfShip, pulls) << std::endl << std::endl;
}

void getHitRateInit() {
	std::string input;
	std::vector<std::string> splittedInput;
	std::cout << "enter the following parameters on one line separated by a space:" << std::endl;
	std::cout << "attackerHit, attackerHitBonus, attackerLuck, attackerLuckBonus, defenderEva, defenderEvaBonus, " <<
		"defenderLuck, defenderLuckBonus, lvDifference, attackerHitRateBonus, and enemyEvaRateBonus:" << std::endl;
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	AccPL accPL;
	accPL.attackerHit = std::stoi(splittedInput.at(0));
	accPL.attackerHitBonus = std::stod(splittedInput.at(1));
	accPL.attackerLuck = std::stoi(splittedInput.at(2));
	accPL.attackerLuckBonus = std::stod(splittedInput.at(3));
	accPL.defenderEva = std::stoi(splittedInput.at(4));
	accPL.defenderEvaBonus = std::stod(splittedInput.at(5));
	accPL.defenderLuck = std::stoi(splittedInput.at(6));
	accPL.defenderLuckBonus = std::stod(splittedInput.at(7));
	accPL.lvDifference = std::stoi(splittedInput.at(8));
	accPL.attackerAccBonus = std::stod(splittedInput.at(9));
	accPL.defenderEvaRateBonus = std::stod(splittedInput.at(10));
	std::cout << "final hit rate: " << getAccCalc(accPL) << std::endl << std::endl;
}

void getCritRateInit() {
	std::string input;
	std::vector<std::string> splittedInput;
	std::cout << "enter the following parameters on one line separated by a space:" << std::endl;
	std::cout << "attackerHit, attackerHitBonus, attackerLuck, attackerLuckBonus, defenderEva, defenderEvaBonus, " <<
		"defenderLuck, defenderLuckBonus, lvDifference, critRateBonus:" << std::endl;
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	AccPL accPL;
	accPL.attackerHit = std::stoi(splittedInput.at(0));
	accPL.attackerHitBonus = std::stod(splittedInput.at(1));
	accPL.attackerLuck = std::stoi(splittedInput.at(2));
	accPL.attackerLuckBonus = std::stod(splittedInput.at(3));
	accPL.defenderEva = std::stoi(splittedInput.at(4));
	accPL.defenderEvaBonus = std::stod(splittedInput.at(5));
	accPL.defenderLuck = std::stoi(splittedInput.at(6));
	accPL.defenderLuckBonus = std::stod(splittedInput.at(7));
	accPL.lvDifference = std::stoi(splittedInput.at(8));
	accPL.critRateBonus = std::stod(splittedInput.at(9));
	std::cout << "final crit rate: " << getCritRateCalc(accPL) << std::endl << std::endl;
}

void getFloodInit() {
	double finalFloodDmg;
	FloodPL pl;
	std::string input;
	std::vector<std::string> splittedInput;
	std::cout << "enter the following parameters on one line separated by a space:" << std::endl;
	std::cout << "baseDamage, coefficient, scalingStat, scalingStatFromGear, formationBonus, scalingStatBonus, floodCoefficient:" << std::endl;
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	pl.baseDmg = std::stod(splittedInput.at(0));
	pl.coefficient = std::stod(splittedInput.at(1));
	pl.scalingStat = std::stod(splittedInput.at(2));
	pl.scalingStatFromGear = std::stod(splittedInput.at(3));
	pl.formationBonus = std::stod(splittedInput.at(4));
	pl.scalingStatBonus = std::stod(splittedInput.at(5));
	pl.floodCoef = std::stod(splittedInput.at(6));
	finalFloodDmg = getFloodDmgCalc(pl);
	std::cout << "final flood damage: " << finalFloodDmg << std::endl << std::endl;
}

void getBurnInit() {
	double finalBurnDmg;
	BurnPL pl;
	std::string input;
	std::vector<std::string> splittedInput;
	std::cout << "enter the following parameters on one line separated by a space:" << std::endl;
	std::cout << "burnDmgbonus, baseDmg, coefficient, slotEff, fp, fpFromGear, formationBonus, fpBonus, burnCoefficient:" << std::endl;
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	pl.burnDmgBonus = std::stod(splittedInput.at(0));
	pl.baseDmg = std::stod(splittedInput.at(1));
	pl.coefficient = std::stod(splittedInput.at(2));
	pl.slotEff = std::stod(splittedInput.at(3));
	pl.fp = std::stod(splittedInput.at(4));
	pl.fpFromGear = std::stod(splittedInput.at(5));
	pl.formationBonus = std::stod(splittedInput.at(6));
	pl.fpBonus = std::stod(splittedInput.at(7));
	pl.burnCoef = std::stod(splittedInput.at(8));
	finalBurnDmg = getBurnDmgCalc(pl);
	std::cout << "final burn damage: " << finalBurnDmg << std::endl << std::endl;
}

void getBBEDPSInit() {
//---------------------------------------------------------------------------------------------------------------general parameters
	double totEDPS;
	double mainGunEDps;
	double barrageEDps;
	double otherEDps;

	std::string input;
	std::vector<std::string> splittedInput;

	//important stats and parameters, often reused
	double baseDmg;
	double coefficient;
	double slotEff;
	double fp;
	double fpFromGear;
	double fpBonus;
	double formationBonus;
	double shellsHit;
	int totShells;

	//ammo skill initialization
	AmmoSkill ammoSkill;
	ammoSkill.burn = false;
	ammoSkill.flood = false;
	ammoSkill.pierce = false;
	ammoSkill.armorBreak = false;

	//init RldPL
	RldPL rldPl;
	std::cout << "the following will be in regards to the reload parameters" << std::endl;
	std::cout << "enter: weaponRldDuration, rld, rldBonus" << std::endl;
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	rldPl.weaponRldDuration = std::stod(splittedInput.at(0));
	rldPl.rld = std::stod(splittedInput.at(1));
	rldPl.rldBonus = std::stod(splittedInput.at(2));
	std::cout << "temporary rldStatBonus? 'y' for yes anything else for no: ";
	std::getline(std::cin, input);
	if(input == "y") {
		rldPl.tempRldBonus = true;
		std::cout << "rldBonusDuration:" << std::endl;
		std::getline(std::cin, input);
		rldPl.rldBonusDuration = std::stod(input);
	}
	else rldPl.tempRldBonus = false;

	//init AccPL
	AccPL accPl;
	std::cout << "the following will be in regards to the accuracies" << std::endl;
	std::cout << "enter: attackerHit, attackerHitBonus, attackerLuck, attackerLuckBonus, defenderEva, defenderEvaBonus, " <<
		"defenderLuck, defenderLuckBonus, lvDifference, attackerHitRateBonus, defenderEvaRateBonus, critRateBonus" << std::endl;
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	accPl.attackerHit = std::stoi(splittedInput.at(0));
	accPl.attackerHitBonus = std::stod(splittedInput.at(1));
	accPl.attackerLuck = std::stoi(splittedInput.at(2));
	accPl.attackerLuckBonus = std::stod(splittedInput.at(3));
	accPl.defenderEva = std::stoi(splittedInput.at(4));
	accPl.defenderEvaBonus = std::stod(splittedInput.at(5));
	accPl.defenderLuck = std::stoi(splittedInput.at(6));
	accPl.defenderLuckBonus = std::stod(splittedInput.at(7));
	accPl.lvDifference = std::stoi(splittedInput.at(8));
	accPl.attackerAccBonus = std::stod(splittedInput.at(9));
	accPl.defenderEvaRateBonus = std::stod(splittedInput.at(10));
	accPl.critRateBonus = std::stod(splittedInput.at(11));

//--------------------------------------------------------------------------------------------------------------------main gun specific	
	//init GunPL
	GunPL gunPl;
	std::cout << "the following will be in regards to the main gun of the ship" << std::endl;
	std::cout << "enter: number of maingun mounts, baseDmg, coefficient, number of shells per main gun mount, slotEff, armorMod, lvDifference, " <<
		"dmgBonus, ammoTypeMod, enemyDebuff, hunterBonus, fp, fpFromGear, formationBonus on fp, fpBonus, critBonus" << std::endl;
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	gunPl.mgms = std::stoi(splittedInput.at(0));
	gunPl.baseDmg = std::stod(splittedInput.at(1));
	baseDmg = std::stod(splittedInput.at(1));
	gunPl.coefficient = std::stod(splittedInput.at(2));
	coefficient = std::stod(splittedInput.at(2));
	gunPl.count = std::stoi(splittedInput.at(3));
	gunPl.slotEff = std::stod(splittedInput.at(4));
	slotEff = std::stod(splittedInput.at(4));
	gunPl.armorMod = std::stod(splittedInput.at(5));
	gunPl.lvDifference = std::stoi(splittedInput.at(6));
	gunPl.dmgBonus = std::stod(splittedInput.at(7));
	gunPl.ammoTypeMod = std::stod(splittedInput.at(8));
	gunPl.enemyDebuff = std::stod(splittedInput.at(9));
	gunPl.hunterBonus = std::stod(splittedInput.at(10));
	gunPl.fp = std::stod(splittedInput.at(11));
	fp = std::stod(splittedInput.at(11));
	gunPl.fpFromGear = std::stod(splittedInput.at(12));
	fpFromGear = std::stod(splittedInput.at(12));
	gunPl.formationBonus = std::stod(splittedInput.at(13));
	formationBonus = std::stod(splittedInput.at(13));
	gunPl.fpBonus = std::stod(splittedInput.at(14));
	fpBonus = std::stod(splittedInput.at(14));
	gunPl.critBonus = std::stod(splittedInput.at(15));
	std::cout << "is ammo buff activated? ('y' for yes, any other key for no): ";
	std::getline(std::cin, input);
	if (input == "y") gunPl.ammoBuffBit = 1;
	else gunPl.ammoBuffBit = 0;

	std::cout << "out of " << gunPl.mgms * gunPl.count << " shells, what is the effective average number of shells that physically hit the target: ";
	std::getline(std::cin, input);
	shellsHit = std::stod(input);
	totShells = gunPl.mgms * gunPl.count;

	//mg ammo skill selection
	std::cout << "will mg cause burn, flood, pierce, armorBreak ('y' for yes any other key for no):" << std::endl;
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	if (splittedInput.at(0) == "y") ammoSkill.burn = true;
	if (splittedInput.at(1) == "y") ammoSkill.flood = true;
	if (splittedInput.at(2) == "y") ammoSkill.pierce = true;
	if (splittedInput.at(3) == "y") ammoSkill.armorBreak = true;

	//init mg ammo skill ParameterLists
	BurnPL burnPl{};
	FloodPL floodPl{};

	if (ammoSkill.burn) {
		burnPl.baseDmg = baseDmg;
		burnPl.coefficient = coefficient;
		burnPl.slotEff = slotEff;
		burnPl.fp = fp;
		burnPl.fpFromGear = fpFromGear;
		burnPl.formationBonus = formationBonus;
		burnPl.fpBonus = fpBonus;
		std::cout << "burn coefficient and burnDmg bonus:" << std::endl;
		std::getline(std::cin, input);
		splittedInput = split(input, ' ');
		burnPl.burnCoef = std::stod(splittedInput.at(0));
		burnPl.burnDmgBonus = std::stod(splittedInput.at(1));
	}
	if (ammoSkill.flood) {
		floodPl.baseDmg = baseDmg;
		floodPl.coefficient = coefficient;
		std::cout << "flood coefficient, scalingStat for flood, scalingStat from gear, scalingStatBonus, formationBonus on scalingStat:" << std::endl;
		std::getline(std::cin, input);
		splittedInput = split(input, ' ');
		floodPl.floodCoef = std::stod(splittedInput.at(0));
		floodPl.scalingStat = std::stod(splittedInput.at(1));
		floodPl.scalingStatFromGear = std::stod(splittedInput.at(2));
		floodPl.scalingStatBonus = std::stod(splittedInput.at(3));
		floodPl.formationBonus = std::stod(splittedInput.at(4));
	} 
	mainGunEDps = getGunEDPS(ammoSkill, gunPl, rldPl, accPl, burnPl, floodPl, shellsHit, totShells);

	std::cout << "mg dps: " << mainGunEDps << std::endl;

	//barrage

	//burn, armorbreak, or flood from barrage

}

void getCVEDPSInit() {

}

void getOtherEDPSInit() {

}

double getGunEDPS(AmmoSkill ammoSkill, GunPL gunPl, RldPL rldPl, AccPL accPl, BurnPL burnPl, FloodPL floodPl, double shellsHit, int totShells) {
	double nonCritDmg;
	double critDmg;
	double critRate;
	double avgDmg;
	double skillDmg = 0; //dmg from main gun skill(s)
	double netDmg;
	double eHitRate;
	double rldDuration;
	double EDPS;
	
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
	//skillDmg
	if(ammoSkill.burn) skillDmg += getBurnDmgCalc(burnPl);
	if(ammoSkill.flood) skillDmg += getFloodDmgCalc(floodPl);
	//netDmg
	netDmg = avgDmg + skillDmg;
	//effectiveHitRate
	eHitRate = (shellsHit/totShells) * getAccCalc(accPl);
	//rldDuration
	rldDuration = getActualRldTime(rldPl);
	//EDPS
	EDPS = (netDmg*eHitRate) / rldDuration;
	return EDPS;
}

double getTorpEDPS() {
	return 0;
}

double getAirStrikeEDPS() {
	return 0;
}

double getBarrageEDPS() {
	return 0;
}

std::vector<std::string> split(std::string s, char c) {
	std::string buff{""};
	std::vector<std::string> resultVector;

	for (char n : s) {
		if(n != c) buff += n;
		else if(n == c && buff != "") {resultVector.push_back(buff); buff = "";}
	}
	if(buff != "") resultVector.push_back(buff);
	return resultVector;
}