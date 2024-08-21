#include "character.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>

//constructor
character::character (std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith) {
this->name = name;
this->turnNumber = turnNumber;
this->hp = hp;
this->mp = mp;
this->strength = strength;
this->dexterity = dexterity;
this->intelligence = intelligence;
this->speed = speed;
this->endurance = endurance;
this->faith = faith;
}

//getters
double character::getHp() const {
    return hp;

}
double character::getMp() const {
    return mp;

}
int character::getDexterity() const {
    return dexterity;

}
int character::getEndurance() const {
    return endurance;

}
int character::getFaith() const {
    return faith;

}
int character::getIntelligence() const {
    return intelligence;
}
int character::getSpeed() const {
    return speed;

}
int character::getStrength() const {
    return strength;

}
std::string character::getName() const {
    return name;

}
std::string character::toString() {
    return " ";
}
//mutator methods
void character::increaseHP(int points) {
    hp += points;
}

void character::decreaseHP(int points) {
    hp -= points;
}

void character::skipTurn() {
    std::cout << "Your next turn will be skipped!" << std::endl;
}
void character::setDexterity(int dexterity)
{
    this->dexterity = dexterity;

}
void character::setSpeed(int speed)
{
    this->speed = speed;

}
void character::setStrength(int strength)
{
    this->strength = strength;

}
void character::setFaith(int faith)
{
     this->faith = faith;

}
void character::setIntelligence(int intelligence)
{
    this->intelligence = intelligence;

}
void character::setEndurance(int endurance)
{
     this->endurance = endurance;
}
void character::setMp(double mp)
{
    this->mp = mp;

}
void character::setHp(double hp)
{
     this->hp = hp;
}
void character::speak() {
    
    
}
double character::heal(character& other) {
    return 0;
    
}
double character::attack(character&other) {
    return 0;
    
}
int character::playTurn() {
    return 0;
}


beauty::beauty(std::string name,int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith) : character(name, turnNumber, hp, mp, strength, dexterity, intelligence, speed, endurance, faith) {
    
}
void beauty::speak() {
    std::cout << "Hello boys, whos going to help me win? \n" << std::endl;
    
}
int beauty::playTurn() {
    int playTurn;

    std::cout << "It is your turn to play!" << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Seduce" << std::endl;
    std::cout << "2. Heal" << std::endl;
    std::cout << "3. Skip Turn" << std::endl;
    std::cout << "4. Quit" << std::endl;

    std::cin >> playTurn;

    return playTurn;
    
}
double beauty::attack(character &other) {
    double seduce = 0;
    
    seduce = seduce + intelligence + endurance;
    
    std::cout << name << " Seduced " << other.getName() << std::endl;

    other.decreaseHP(seduce);
    
    return seduce;
}
double beauty::heal(character &other)
{
    double heal = 0;
    int charges = 3;

    heal = heal + hp / strength + faith;

    if (charges > 0)
    {
        std::cout << other.getName() << " was healed" << std::endl;
        other.increaseHP(heal);
        charges = charges - 1;
        
    }
    else
    {
        std::cout << "You have no charges left to perform heal" << std::endl;
    }

    return heal;
    
}
std::string beauty::toString() {
   std::stringstream outputStream;

	outputStream << name << " the Beauty's stats:" << std::endl;
	outputStream << "HP: " << std::setprecision(2) << std::fixed << hp << std::endl;
	outputStream << "MP: " << std::setprecision(2) << std::fixed << mp << std::endl;
	outputStream << "Strength: " << std::setprecision(0) << std::fixed << strength << std::endl;
	outputStream << "Dexterity: " << dexterity << std::endl;
	outputStream << "Intelligence: " << intelligence << std::endl;
	outputStream << "Speed: " << speed << std::endl;
	outputStream << "Endurance: " << endurance << std::endl;
	outputStream << "Faith: " << faith << std::endl;

	return outputStream.str(); 
    

}

warrior::warrior(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith) : character(name, turnNumber, hp, mp, strength, dexterity, intelligence, speed, endurance, faith) {
    
}
void warrior::speak() {
    std::cout << "I am the mightiest of the land no man shall escape my wraith \n" << std::endl;

}
int warrior::playTurn() {
    int playTurn;

    std::cout << "It is your turn to play!" << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Bash" << std::endl;
    std::cout << "2. Heal" << std::endl;
    std::cout << "3. Skip Turn" << std::endl;
    std::cout << "4. Quit" << std::endl;

    std::cin >> playTurn;

    return playTurn;

}
double warrior::attack(character &other) {
    double damage = 0;

    damage = strength + endurance + dexterity;
    if (endurance >= 5)
    {
        other.decreaseHP(damage);
        endurance = endurance - 5;
        
        std::cout << name << " bashed " << other.getName() << std::endl;
    }
    else {
        std::cout << "You do not have enough endurance to perform bash!" << std::endl;
    }

    return damage;
}

double warrior::heal(character &other) {
    double heal = 0;
    int charges = 2;

    heal = heal + hp / strength + faith;

    if (charges > 0)
    {
        std::cout << other.getName() << " was healed" << std::endl;
        other.increaseHP(heal);
        charges = charges - 1;

    }
    else
    {
        std::cout << "You have no charges left to perform heal" << std::endl;
    }

    return heal;
}
std::string warrior::toString() {
    std::stringstream outputStream;

	outputStream << name << " the Warrior's stats:" << std::endl;
	outputStream << "HP: " << std::setprecision(2) << std::fixed << hp << std::endl;
	outputStream << "MP: " << std::setprecision(2) << std::fixed << mp << std::endl;
	outputStream << "Strength: " << std::setprecision(0) << std::fixed << strength << std::endl;
	outputStream << "Dexterity: " << dexterity << std::endl;
	outputStream << "Intelligence: " << intelligence << std::endl;
	outputStream << "Speed: " << speed << std::endl;
	outputStream << "Endurance: " << endurance << std::endl;
	outputStream << "Faith: " << faith << std::endl;

	return outputStream.str();
}

sourcer::sourcer(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith) : character(name, turnNumber, hp, mp, strength, dexterity, intelligence, speed, endurance, faith) {
    
}
void sourcer::speak() {
    std::cout << "Beware for the most intelligent can see but can not for tell the future. \n" << std::endl;

}
int sourcer::playTurn() {
    int playTurn;
    
    std::cout << "It is your turn to play!" << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Cast" << std::endl;
    std::cout << "2. Heal" << std::endl;
    std::cout << "3. Skip Turn" << std::endl;
    std::cout << "4. Quit" << std::endl;

    std::cin >> playTurn;

    return playTurn;
    

}
double sourcer::attack(character &other) {
    double cast = 0;
    int charges = 5;

    cast = cast + intelligence + dexterity;

    if (charges > 0 && mp >= 32)
    {
        mp = mp - 32;
        other.decreaseHP(cast);
        std::cout << name << " Cast " << other.getName() << std::endl;
        charges = charges - 1;
    }
    else if (mp < 32)
    {
        std::cout << "You do not have enough mp to perform cast!" << std::endl;
    }
    else if (charges == 0)
    {
        std::cout << "You do not have any more charges to perform cast!" << std::endl;
    }
    
    return cast;
}

double sourcer::heal(character &other) {
    double heal = 0;
    int charges = 5;

    heal = heal + faith + intelligence;

    if (charges > 0 && mp >= 10)
    {
        mp = mp - 10;
        other.increaseHP(heal);
        std::cout << name << " healed " << other.getName() << std::endl;
        charges = charges -1;
    }
    else if (charges == 0)
    {
        std::cout << "You do not have any more charges to perform heal!" << std::endl;
    }
    else if (mp < 10)
    {
        std::cout << "You do not have enough mp to perform heal!" << std::endl;    }
    
    return heal;
}
std::string sourcer::toString() {

    std::stringstream outputStream;

	outputStream << name << " the Sourcer's stats:" << std::endl;
	outputStream << "HP: " << std::setprecision(2) << std::fixed << hp << std::endl;
	outputStream << "MP: " << std::setprecision(2) << std::fixed << mp << std::endl;
	outputStream << "Strength: " << std::setprecision(0) << std::fixed << strength << std::endl;
	outputStream << "Dexterity: " << dexterity << std::endl;
	outputStream << "Intelligence: " << intelligence << std::endl;
	outputStream << "Speed: " << speed << std::endl;
	outputStream << "Endurance: " << endurance << std::endl;
	outputStream << "Faith: " << faith << std::endl;

	return outputStream.str();


}

thief::thief(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith) : character(name, turnNumber, hp, mp, strength, dexterity, intelligence, speed, endurance, faith) {
    
}
void thief::speak() {
    std::cout << "Intelligence is a matter of how much money you have, whats in your pocket? \n" << std::endl;

}
int thief::playTurn() {
    int playTurn;
    
    std::cout << "It is your turn to play!" << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Steal" << std::endl;
    std::cout << "2. Heal" << std::endl;
    std::cout << "3. Skip Turn" << std::endl;
    std::cout << "4. Quit" << std::endl;

    std::cin >> playTurn;

    return playTurn;

}
double thief::attack(character &other) {
    double steal = 0;
    double damage = 0;

    steal = dexterity + speed + intelligence;
    damage = damage + speed + endurance + dexterity;

    int minimum = steal * 0.1; // 8.5
    int maximum = steal * 0.5; // 42.5

    steal = rand() % (maximum - minimum) + minimum;

    if (steal >= 20 )
    {
        other.decreaseHP(damage);
        hp += steal;
    }
    else
    {
        hp -= 10;
        other.decreaseHP(5);
    }
    

    std::cout << name << " Steal " << other.getName() << std::endl;
    
    return steal;
}

double thief::heal(character &other)
{
    double heal = 0;
    int charges = 3;

    heal = heal + hp / strength + faith;

    if (charges > 0)
    {
        std::cout << other.getName() << " was healed" << std::endl;
        other.increaseHP(heal);
        charges = charges -1;

    }
    else
    {
        std::cout << "You have no charges left to perform heal" << std::endl;
    }

    return heal;
}
std::string thief::toString() {
    std::stringstream outputStream;

	outputStream << name << " the Thief's stats:" << std::endl;
	outputStream << "HP: " << std::setprecision(2) << std::fixed << hp << std::endl;
	outputStream << "MP: " << std::setprecision(2) << std::fixed << mp << std::endl;
	outputStream << "Strength: " << std::setprecision(0) << std::fixed << strength << std::endl;
	outputStream << "Dexterity: " << dexterity << std::endl;
	outputStream << "Intelligence: " << intelligence << std::endl;
	outputStream << "Speed: " << speed << std::endl;
	outputStream << "Endurance: " << endurance << std::endl;
	outputStream << "Faith: " << faith << std::endl;

	return outputStream.str();
   
}
knight::knight(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith) : character(name, turnNumber, hp, mp, strength, dexterity, intelligence, speed, endurance, faith) {

}
void knight::speak() {
    std::cout << "I will protect the kings land until I die on my sword! \n" << std::endl;

}
int knight::playTurn() {
    int playTurn;
    
    std::cout << "It is your turn to play!" << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Slash" << std::endl;
    std::cout << "2. Heal" << std::endl;
    std::cout << "3. Skip Turn" << std::endl;
    std::cout << "4. Quit" << std::endl;

    std::cin >> playTurn;

    return playTurn;

}
double knight::attack(character &other) {
    double slash = 0;
    int charges = 3;
    double damage = 0;

    slash = slash + dexterity + strength + endurance;

    int minimum = slash * 0.1; // 8
    int maximum = slash * 0.5; // 40

    slash = rand() % (maximum - minimum) + minimum;

    if (charges == 0)
    {
        std::cout << "You do not have any more charges to perform slash!" << std::endl;
    }

    if (slash >= 24 && charges > 0)
    {
        other.decreaseHP(slash);
        charges = charges - 1;
    }
    else
    {
        damage = slash / 4;
        other.decreaseHP(damage);
        hp -= 10;
    }
    return slash;
    
}
double knight::heal(character &other) {
    double heal = 0;
    int charges = 5;

    heal = heal + hp / strength + faith;

    if (charges > 0)
    {
        std::cout << other.getName() << " was healed" << std::endl;
        other.increaseHP(heal);
        charges = charges -1;

    }
    else
    {
        std::cout << "You have no charges left to perform heal" << std::endl;
    }

    return heal;
    
}
std::string knight::toString() {
    std::stringstream outputStream;

    outputStream << name << " the Knight's stats:" << std::endl;
    outputStream << "HP: " << std::setprecision(2) << std::fixed << hp << std::endl;
    outputStream << "MP: " << std::setprecision(2) << std::fixed << mp << std::endl;
    outputStream << "Strength: " << std::setprecision(0) << std::fixed << strength << std::endl;
    outputStream << "Dexterity: " << dexterity << std::endl;
    outputStream << "Intelligence: " << intelligence << std::endl;
    outputStream << "Speed: " << speed << std::endl;
    outputStream << "Endurance: " << endurance << std::endl;
    outputStream << "Faith: " << faith << std::endl;

    return outputStream.str();
    
}
jester::jester(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith) : character(name, turnNumber, hp, mp, strength, dexterity, intelligence, speed, endurance, faith) {

}
void jester::speak() {
    std::cout << "Ha ha ha ha ha ha ha ha.....Whos going to win?...Me.. Ha ha ha ha ha ha ha ha \n" << std::endl;
    
}
int jester::playTurn() {
    int playTurn;
    
    std::cout << "It is your turn to play!" << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Trick" << std::endl;
    std::cout << "2. Heal" << std::endl;
    std::cout << "3. Skip Turn" << std::endl;
    std::cout << "4. Quit" << std::endl;
    std::cout << "5. Speak" << std::endl;

    std::cin >> playTurn;

    return playTurn;
    
}
double jester::attack(character &other) {
    double trick = 0;
    int charges = 3;

    trick = trick + intelligence + dexterity + endurance + speed + strength;
    // use a random number to determine whether or not the jester will trick the other character.
    int minimum = trick * 0.1; // 10.5
    int maximum = trick * 0.5; // 52.5

    trick = rand() % (maximum - minimum) + minimum;

    if (charges == 0)
    {
        std::cout << "You do not have any more charges to perform trick!" << std::endl;
    }

    else if (trick >= 45 && charges > 0)
    {
        other.decreaseHP(trick);
        charges = charges -1;
    }
    else
    {
        std::cout << "The jester failed to trick " << other.getName() << std::endl;
        hp -= 20;
        other.decreaseHP(25);
    }

    return trick;
    
}
double jester::heal(character &other) {
    double heal = 0;
    int charges = 5;

    heal = heal + hp / strength + faith + endurance;

    if (charges > 0)
    {
        std::cout << other.getName() << " was healed" << std::endl;
        other.increaseHP(heal);
        charges = charges -1;

    }
    else
    {
        std::cout << "You have no charges left to perform heal" << std::endl;
    }

    return heal;
    
    
}
std::string jester::toString() {
    std::stringstream outputStream;

    outputStream << name << " the Jester's stats:" << std::endl;
    outputStream << "HP: " << std::setprecision(2) << std::fixed << hp << std::endl;
    outputStream << "MP: " << std::setprecision(2) << std::fixed << mp << std::endl;
    outputStream << "Strength: " << std::setprecision(0) << std::fixed << strength << std::endl;
    outputStream << "Dexterity: " << dexterity << std::endl;
    outputStream << "Intelligence: " << intelligence << std::endl;
    outputStream << "Speed: " << speed << std::endl;
    outputStream << "Endurance: " << endurance << std::endl;
    outputStream << "Faith: " << faith << std::endl;

    return outputStream.str();
}

orc::orc(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith) : character(name, turnNumber, hp, mp, strength, dexterity, intelligence, speed, endurance, faith) {

}

void orc::speak() {
    std::cout << "Arggggg!!!! \n" << std::endl;
    
}
int orc::playTurn() {
    int playTurn;
    
    std::cout << "It is your turn to play!" << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Maul" << std::endl;
    std::cout << "2. Heal" << std::endl;
    std::cout << "3. Skip Turn" << std::endl;
    std::cout << "4. Quit" << std::endl;

    std::cin >> playTurn;

    return playTurn;
    
}
double orc::attack(character &other) {
    double maul = 0;
    int charges = 3;

    maul = maul + strength + dexterity + endurance + speed;

    if (endurance >=5 && charges > 0)
    {
        other.decreaseHP(maul);
    }
    else if (endurance < 5)
    {
        std::cout << "Your endurance is too low!" << std::endl;
        other.decreaseHP(20);
        hp -= 5;
        
        
    }
    else if (charges == 0)
    {
        std::cout << "You do not have any more charges to perform maul!" << std::endl;
    }
    

    return maul;
    
}
double orc::heal(character &other) {
    double heal = 0;
    int charges = 1;

    heal = heal + hp / strength + faith;

    if (charges > 0)
    {
        std::cout << other.getName() << " was healed" << std::endl;
        other.increaseHP(heal);
        charges = charges -1;

    }
    else
    {
        std::cout << "You have no charges left to perform heal" << std::endl;
    }

    return heal;
    
}
std::string orc::toString() {
    std::stringstream outputStream;

    outputStream << name << " the Orc's stats:" << std::endl;
    outputStream << "HP: " << std::setprecision(2) << std::fixed << hp << std::endl;
    outputStream << "MP: " << std::setprecision(2) << std::fixed << mp << std::endl;
    outputStream << "Strength: " << std::setprecision(0) << std::fixed << strength << std::endl;
    outputStream << "Dexterity: " << dexterity << std::endl;
    outputStream << "Intelligence: " << intelligence << std::endl;
    outputStream << "Speed: " << speed << std::endl;
    outputStream << "Endurance: " << endurance << std::endl;
    outputStream << "Faith: " << faith << std::endl;

    return outputStream.str();
    
}

prisoner::prisoner(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith) :  character(name, turnNumber, hp, mp, strength, dexterity, intelligence, speed, endurance, faith) {

}
void prisoner::speak() {
    std::cout << "God has forsaken me, for I am blessed with the power of our lord and savior! \n" << std::endl;
    
}
int prisoner::playTurn() {
    int playTurn;
    
    std::cout << "It is your turn to play!" << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Stab" << std::endl;
    std::cout << "2. Heal" << std::endl;
    std::cout << "3. Skip Turn" << std::endl;
    std::cout << "4. Quit" << std::endl;

    std::cin >> playTurn;

    return playTurn;
    
}
double prisoner::attack(character &other) {
    double stab = 0;

    stab = stab + strength + endurance + dexterity + faith + speed + intelligence;

    int minimum = stab * 0.1; // 11
    int maximum = stab * 0.5; // 55

    stab = rand() % (maximum - minimum) + minimum;

    if (stab >= 45)
    {
        other.decreaseHP(stab);
        std::cout << name << " stabbed " << other.getName() << std::endl;
    }
    else
    {
        std::cout << name << "barely missed " << other.getName() << std::endl;
        other.decreaseHP(25);
        hp -= 15;
    }

    return stab;
    
}
double prisoner::heal(character &other) {
    double heal = 0;
    int charges = 5;

    heal = heal + hp / strength + faith + endurance;

    if (charges > 0)
    {
        std::cout << other.getName() << " was healed" << std::endl;
        other.increaseHP(heal);
        charges = charges - 1;

    }
    else
    {
        std::cout << "You have no charges left to perform heal" << std::endl;
    }

    return heal;
    
    
}
std::string prisoner::toString() {
    std::stringstream outputStream;

    outputStream << name << " the Prisoner's stats:" << std::endl;
    outputStream << "HP: " << std::setprecision(2) << std::fixed << hp << std::endl;
    outputStream << "MP: " << std::setprecision(2) << std::fixed << mp << std::endl;
    outputStream << "Strength: " << std::setprecision(0) << std::fixed << strength << std::endl;
    outputStream << "Dexterity: " << dexterity << std::endl;
    outputStream << "Intelligence: " << intelligence << std::endl;
    outputStream << "Speed: " << speed << std::endl;
    outputStream << "Endurance: " << endurance << std::endl;
    outputStream << "Faith: " << faith << std::endl;

    return outputStream.str();
    
}

rogue::rogue(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith) : character(name, turnNumber, hp, mp, strength, dexterity, intelligence, speed, endurance, faith) {

}
void rogue::speak() {
    std::cout << "I will Survive! \n" << std::endl;
}
int rogue::playTurn() {
    int playTurn;
    
    std::cout << "It is your turn to play!" << std::endl;
    std::cout << "What would you like to do?" << std::endl;
    std::cout << "1. Bow" << std::endl;
    std::cout << "2. Heal" << std::endl;
    std::cout << "3. Skip Turn" << std::endl;
    std::cout << "4. Quit" << std::endl;

    std::cin >> playTurn;
    
    return playTurn;
    
}
double rogue::attack(character &other) {
    double bow = 0;
    double damage = 0;

    bow = bow + dexterity + strength + intelligence + faith;

    int minimum = bow * 0.1; // 7
    int maximum = bow * 0.5; // 35

    bow = rand() % (maximum - minimum) + minimum;

    if (bow >=25)
    {
        damage = damage + bow * 2;
        other.decreaseHP(damage); 
    }
    else
    {
        damage = damage + bow;
        other.decreaseHP(damage);
    }

    

    return bow;
}
double rogue::heal(character &other) {
    double heal = 0;
    int charges = 5;

    heal = heal + hp / strength + faith + endurance;

    if (charges > 0)
    {
        std::cout << other.getName() << " was healed" << std::endl;
        other.increaseHP(heal);
        charges = charges - 1;

    }
    else
    {
        std::cout << "You have no charges left to perform heal" << std::endl;
    }

    return heal;
}
std::string rogue::toString() {
    std::stringstream outputStream;

    outputStream << name << " the Rogue's stats:" << std::endl;
    outputStream << "HP: " << std::setprecision(2) << std::fixed << hp << std::endl;
    outputStream << "MP: " << std::setprecision(2) << std::fixed << mp << std::endl;
    outputStream << "Strength: " << std::setprecision(0) << std::fixed << strength << std::endl;
    outputStream << "Dexterity: " << dexterity << std::endl;
    outputStream << "Intelligence: " << intelligence << std::endl;
    outputStream << "Speed: " << speed << std::endl;
    outputStream << "Endurance: " << endurance << std::endl;
    outputStream << "Faith: " << faith << std::endl;

    return outputStream.str();
    
}