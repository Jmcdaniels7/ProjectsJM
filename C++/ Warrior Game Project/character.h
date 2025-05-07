#pragma once
#include <string>
#include <cstdlib>
#include <sstream>
#include <iomanip>

class character {
    //attributes
    protected:
        double hp;
        double mp;
        int dexterity;
        int intelligence;
        int endurance;
        int speed;
        int strength;
        int faith;
        std::string name;
    public:
        int turnNumber;

    //constructor
    public:
    character (std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith);

    //getters
    double getHp() const;
    double getMp() const;
    int getDexterity() const;
    int getEndurance() const;
    int getFaith() const;
    int getIntelligence() const;
    int getSpeed() const;
    int getStrength() const;
    std::string getName() const;
    virtual std::string toString();
    virtual void speak();
    virtual int playTurn();

    //mutator methods
    void increaseHP(int points);
    void decreaseHP(int points);
    virtual void skipTurn();
    virtual double heal(character& other);
    virtual double attack(character&other);
    void setDexterity(int dexterity);
    void setSpeed(int speed);
    void setStrength(int strength);
    void setFaith(int faith);
    void setIntelligence(int intelligence);
    void setEndurance(int endurance);
    void setMp(double mp);
    void setHp(double hp);
};

class beauty : public character {
public:
    beauty(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith);
    double attack(character &other);
    double heal(character &other);
    virtual std::string toString();
    virtual void speak();
    virtual int playTurn();
};

class warrior : public character {
public:
    warrior(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith);
    double attack(character &other);
    double heal(character &other);
    virtual std::string toString();
    virtual void speak();
    virtual int playTurn();
};

class sourcer : public character {
public:
    sourcer(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith);
    double attack(character &other);
    double heal(character &other);
    virtual std::string toString();
    virtual void speak();
    virtual int playTurn();
};

class thief : public character {
public:
    thief(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith); 
    double attack(character &other);
    double heal(character &other);
    virtual std::string toString();
    virtual void speak();
    virtual int playTurn();
};

class knight : public character {
public:
    knight(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith);
    double attack(character &other);
    double heal(character &other);
    virtual std::string toString();
    virtual void speak();
    virtual int playTurn();
};

class jester : public character {
public:
    jester(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith);
    double attack(character &other);
    double heal(character &other);
    virtual std::string toString();
    virtual void speak();
    virtual int playTurn();
};

class orc : public character {
public:
    orc(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith);
    double attack(character &other);
    double heal(character &other);
    virtual std::string toString();
    virtual void speak();
    virtual int playTurn();
};

class prisoner : public character {
public:
    prisoner(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith);
    double attack(character &other);
    double heal(character &other);
    virtual std::string toString();
    virtual void speak();
    virtual int playTurn();
};

class rogue : public character {
public:
    rogue(std::string name, int turnNumber, double hp, double mp, int strength, int dexterity, int intelligence, int speed, int endurance, int faith);
    double attack(character &other);
    double heal(character &other);
    virtual std::string toString();
    virtual void speak();
    virtual int playTurn();
};