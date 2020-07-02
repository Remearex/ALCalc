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
	double mgBaseDmg;
	double mgCoefficient;
	double mgSlotEff;
	int lvDifference;
	bool ammoBuffBit;
	double fp;
	double fpFromGear;
	double fpBonus;
	double formationBonusOnFp;
	
	bool hasBarrage;
	int barrageIDCount{};
	std::vector<double> barrageBaseDmgs;
	std::vector<double> barrageCoefficients;
	double barrageScalingStat;
	double barrageScalingStatFromGear;
	double formationBonusOnBarrageScalingStat;
	double barrageScalingStatBonus;

	double mgRldDuration;

	//init important parameters
	std::cout << "does the ship have a barrage? ('y' for yes any other key for no): ";
	std::getline(std::cin, input);
	if(input == "y") {
		hasBarrage = true;
		std::cout << "how many different barrage ammo IDs? Each ID needs to be calculated separately. Ex. monarch only has 1, which is just the AP, and Georgia has 2, SHS and HE";
		std::getline(std::cin, input);
		barrageIDCount = std::stoi(input);
		for (int i = 0; i < barrageIDCount; i++) {
			std::cout << "enter barrage ID number" << i+1 << "'s barrageBaseDmg, barrageCoefficient:";
			std::getline(std::cin, input);
			splittedInput = split(input, ' ');
			barrageBaseDmgs.push_back(std::stod(splittedInput.at(0)));
			barrageCoefficients.push_back(std::stod(splittedInput.at(1)));
		}
		std::cout << "enter: barrageScalingStat, barrageScalingStatFromGear, formationBonusOnBarrageScalingStat, barrageScalingStatBonus:";
		std::getline(std::cin, input);
		splittedInput = split(input, ' ');
		barrageScalingStat = std::stod(splittedInput.at(0));
		barrageScalingStatFromGear = std::stod(splittedInput.at(1));
		formationBonusOnBarrageScalingStat = std::stod(splittedInput.at(2));
		barrageScalingStatBonus = std::stod(splittedInput.at(3));
	} else {
		hasBarrage = false;
	}
	std::cout << "enter: mgBaseDmg, mgCoefficient, mgSlotEff, lvDifference, fp, fpFromGear, fpBonus, formationBonus on fp:";
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	mgBaseDmg = std::stod(splittedInput.at(0));
	mgCoefficient = std::stod(splittedInput.at(1));
	mgSlotEff = std::stod(splittedInput.at(2));
	lvDifference = std::stoi(splittedInput.at(3));
	fp = std::stod(splittedInput.at(4));
	fpFromGear = std::stod(splittedInput.at(5));
	fpBonus = std::stod(splittedInput.at(6));
	formationBonusOnFp = std::stod(splittedInput.at(7));
	std::cout << "is ammo buff activated? ('y' for yes, any other key for no): ";
	std::getline(std::cin, input);
	if (input == "y") ammoBuffBit = 1;
	else ammoBuffBit = 0;

	//get mgRldDuration
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
	mgRldDuration = getActualRldTime(rldPl);

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
	gunPl.baseDmg = mgBaseDmg;
	gunPl.coefficient = mgCoefficient;
	gunPl.slotEff = mgSlotEff;
	gunPl.lvDifference = lvDifference;
	gunPl.ammoBuffBit = ammoBuffBit;
	gunPl.fp = fp;
	gunPl.fpFromGear = fpFromGear;
	gunPl.formationBonus = formationBonusOnFp;
	gunPl.fpBonus = fpBonus;
	std::cout << "the following will be in regards to the main gun of the ship" << std::endl;
	std::cout << "enter: number of maingun mounts, number of shells per main gun mount, armorMod, " <<
		"dmgBonus, ammoTypeMod, enemyDebuff, hunterBonus, mgCritBonus" << std::endl;
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	gunPl.mgms = std::stoi(splittedInput.at(0));
	gunPl.count = std::stoi(splittedInput.at(1));
	gunPl.armorMod = std::stod(splittedInput.at(2));
	gunPl.dmgBonus = std::stod(splittedInput.at(3));
	gunPl.ammoTypeMod = std::stod(splittedInput.at(4));
	gunPl.enemyDebuff = std::stod(splittedInput.at(5));
	gunPl.hunterBonus = std::stod(splittedInput.at(6));
	gunPl.critBonus = std::stod(splittedInput.at(7));
	std::cout << "out of " << gunPl.mgms * gunPl.count << " shells, what is the effective average number of shells that physically hit the target: ";
	std::getline(std::cin, input);
	gunPl.avgShellsHit = std::stod(input);

	//mg ammo skill selection
	AmmoSkill mgAmmoSkill;
	mgAmmoSkill.burn = false;
	mgAmmoSkill.flood = false;
	mgAmmoSkill.pierce = false;
	mgAmmoSkill.armorBreak = false;
	std::cout << "will mg cause burn, flood, pierce, armorBreak ('y' for yes any other key for no):" << std::endl;
	std::getline(std::cin, input);
	splittedInput = split(input, ' ');
	if (splittedInput.at(0) == "y") mgAmmoSkill.burn = true;
	if (splittedInput.at(1) == "y") mgAmmoSkill.flood = true;
	if (splittedInput.at(2) == "y") mgAmmoSkill.pierce = true;
	if (splittedInput.at(3) == "y") mgAmmoSkill.armorBreak = true;

	if (mgAmmoSkill.burn) {
		mgAmmoSkill.burnPl.baseDmg = mgBaseDmg;
		mgAmmoSkill.burnPl.coefficient = mgCoefficient;
		mgAmmoSkill.burnPl.slotEff = mgSlotEff;
		mgAmmoSkill.burnPl.fp = fp;
		mgAmmoSkill.burnPl.fpFromGear = fpFromGear;
		mgAmmoSkill.burnPl.formationBonus = formationBonusOnFp;
		mgAmmoSkill.burnPl.fpBonus = fpBonus;
		std::cout << "burn coefficient and burnDmg bonus:" << std::endl;
		std::getline(std::cin, input);
		splittedInput = split(input, ' ');
		mgAmmoSkill.burnPl.burnCoef = std::stod(splittedInput.at(0));
		mgAmmoSkill.burnPl.burnDmgBonus = std::stod(splittedInput.at(1));
	}
	if (mgAmmoSkill.flood) {
		mgAmmoSkill.floodPl.baseDmg = mgBaseDmg;
		mgAmmoSkill.floodPl.coefficient = mgCoefficient;
		std::cout << "flood coefficient, scalingStat for flood, scalingStat from gear, scalingStatBonus, formationBonus on scalingStat:" << std::endl;
		std::getline(std::cin, input);
		splittedInput = split(input, ' ');
		mgAmmoSkill.floodPl.floodCoef = std::stod(splittedInput.at(0));
		mgAmmoSkill.floodPl.scalingStat = std::stod(splittedInput.at(1));
		mgAmmoSkill.floodPl.scalingStatFromGear = std::stod(splittedInput.at(2));
		mgAmmoSkill.floodPl.scalingStatBonus = std::stod(splittedInput.at(3));
		mgAmmoSkill.floodPl.formationBonus = std::stod(splittedInput.at(4));
	}
	mainGunEDps = getGunEDPS(gunPl, accPl, mgRldDuration, mgAmmoSkill);

//----------------------------------------------------------------------------------------------------------------barrage specific
	//init barrage (parameter list for an individual barrage ammo or type)
	if(hasBarrage) {
		std::vector<Barrage> indivBarrages;
		std::cout << "following will be barrage parameters" << std::endl;
		for (int i = 0; i < barrageIDCount; i++) {
			Barrage indivBarrage;
			indivBarrage.baseDmg = barrageBaseDmgs.at(i);
			indivBarrage.coefficient = barrageCoefficients.at(i);
			indivBarrage.lvDifference = lvDifference;
			indivBarrage.ammoBuffBit = ammoBuffBit;
			indivBarrage.scalingStat = barrageScalingStat;
			indivBarrage.scalingStatFromGear = barrageScalingStatFromGear;
			indivBarrage.formationBonus = formationBonusOnBarrageScalingStat;
			indivBarrage.scalingStatBonus = barrageScalingStatBonus;
			std::cout << "enter barrage ID number " << i+1 << "'s number of shells, armorMod, scaling coefficient, dmgBonus, enemyDebuff, " <<
				"hunterBonus, barrageCritBonus";
			std::getline(std::cin, input);
			splittedInput = split(input, ' ');
			indivBarrage.count = std::stoi(splittedInput.at(0));
			indivBarrage.armorMod = std::stod(splittedInput.at(1));
			indivBarrage.scaling = std::stod(splittedInput.at(2));
			indivBarrage.dmgBonus = std::stod(splittedInput.at(3));
			indivBarrage.enemyDebuff = std::stod(splittedInput.at(4));
			indivBarrage.hunterBonus = std::stod(splittedInput.at(5));
			indivBarrage.critBonus = std::stod(splittedInput.at(6));
		}
		//barrage ammo skill selection
		AmmoSkill barrageAmmoSkill;
		barrageAmmoSkill.burn = false;
		barrageAmmoSkill.flood = false;
		barrageAmmoSkill.pierce = false;
		barrageAmmoSkill.armorBreak = false;
		std::cout << "does barrage have any ammo skills: ";
		std::getline(std::cin, input);
		if(input == "y") {
			std::cout << "will barrage cause burn, flood, pierce, armorBreak ('y' for yes any other key for no):" << std::endl;
			std::getline(std::cin, input);
			splittedInput = split(input, ' ');
			if (splittedInput.at(0) == "y") barrageAmmoSkill.burn = true;
			if (splittedInput.at(1) == "y") barrageAmmoSkill.flood = true;
			if (splittedInput.at(2) == "y") barrageAmmoSkill.pierce = true;
			if (splittedInput.at(3) == "y") barrageAmmoSkill.armorBreak = true;

			if (barrageAmmoSkill.burn) {
				barrageAmmoSkill.burnPl.slotEff = 1;
				barrageAmmoSkill.burnPl.fp = fp;
				barrageAmmoSkill.burnPl.fpFromGear = fpFromGear;
				barrageAmmoSkill.burnPl.formationBonus = formationBonusOnFp;
				barrageAmmoSkill.burnPl.fpBonus = fpBonus;
				std::cout << "baseDmg, coefficient of barrage ammo, burn coefficient and burnDmg bonus:" << std::endl;
				std::getline(std::cin, input);
				splittedInput = split(input, ' ');
				barrageAmmoSkill.burnPl.baseDmg = std::stod(splittedInput.at(0));
				barrageAmmoSkill.burnPl.coefficient = std::stod(splittedInput.at(1));
				barrageAmmoSkill.burnPl.burnCoef = std::stod(splittedInput.at(2));
				barrageAmmoSkill.burnPl.burnDmgBonus = std::stod(splittedInput.at(3));
			}
			if (barrageAmmoSkill.flood) {
				std::cout << "baseDmg, coefficient of barrage ammo, flood coefficient, scalingStat for flood, scalingStat from gear, scalingStatBonus, formationBonus on scalingStat:" << std::endl;
				std::getline(std::cin, input);
				splittedInput = split(input, ' ');
				barrageAmmoSkill.floodPl.baseDmg = std::stod(splittedInput.at(0));
				barrageAmmoSkill.floodPl.coefficient = std::stod(splittedInput.at(1));
				barrageAmmoSkill.floodPl.floodCoef = std::stod(splittedInput.at(2));
				barrageAmmoSkill.floodPl.scalingStat = std::stod(splittedInput.at(3));
				barrageAmmoSkill.floodPl.scalingStatFromGear = std::stod(splittedInput.at(4));
				barrageAmmoSkill.floodPl.scalingStatBonus = std::stod(splittedInput.at(5));
				barrageAmmoSkill.floodPl.formationBonus = std::stod(splittedInput.at(6));
			}
		}
		//separate crit rate for barrage?
		std::cout << "separate critRateBonus for barrage?: ";
		std::getline(std::cin, input);
		if (input == "y") {
			std::cout << "critRateBonus for barrage: ";
			std::getline(std::cin, input);
			accPl.critRateBonus = std::stod(input);
		}
		barrageEDps = getBarrageEDPS(indivBarrages, accPl, mgRldDuration, barrageAmmoSkill);
	}
}

void getCVEDPSInit() {

}

void getOtherEDPSInit() {

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