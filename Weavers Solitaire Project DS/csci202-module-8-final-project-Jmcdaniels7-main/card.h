#pragma once
#include <string>
#include <iostream>
#include "stack.h"
#include <vector>

class Cards
{
    public:
        enum suitType
        {
            HEART,
            SPADE,
            DIAMOND,
            CLUB,
            DEFAULTS
        };
        enum rankType
        {
            A,
            TWO,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            NINE,
            TEN,
            J,
            Q,
            K,
            DEFAULTR
        };

        stackType<Cards> kFHearts;
        stackType<Cards> kFDiamonds;
        stackType<Cards> kFSpades;
        stackType<Cards> kFClubs;
        stackType<Cards> aFHearts;
        stackType<Cards> aFDiamonds;
        stackType<Cards> aFSpades;
        stackType<Cards> aFClubs;

        static const rankType ranks[];
        static const suitType suits[];
        static const std::string rankStr[];
        static const std::string suitStr[];
        // we might need maps? but we definitely need symbols for ranks
        Cards(rankType, suitType);
        Cards();
        rankType getRank() const;
        suitType getSuit() const;
        //std::vector<Cards> setUpDeck(std::vector<Cards> &deck);

        //not sure if this is needed but we will see
        //void setRank(std::string);
        //void setColor(std::string);
        // needed for card rank comparison
        // we also need it for color but only with foundation piles, I wonder how we can do that
        bool operator>(const Cards &) const;
        bool operator<(const Cards &) const;
        bool operator==(const Cards &) const;
        bool operator!=(const Cards &) const;
        friend std::ostream& operator<<(std::ostream &, const Cards &);
    private:
        rankType rank;
        suitType suit;
};

/*class Weavers : public Cards
{
    public:
        void fillFoundations();
        void fillTableaus();

};*/