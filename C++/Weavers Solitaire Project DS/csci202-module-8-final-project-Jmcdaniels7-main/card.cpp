#include "card.h"

const Cards::rankType Cards::ranks[] = {A, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, J, Q, K, DEFAULTR};
const Cards::suitType Cards::suits[] = {HEART, SPADE, DIAMOND, CLUB, DEFAULTS};
const std::string rankStr[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", " "};
const std::string suitStr[] = {"♥", "♠", "♦", "♣", " "};

Cards::Cards(rankType rank, suitType suit)
{
    this->rank = rank;
    this->suit = suit;

}
Cards::Cards()
{

}
Cards::rankType Cards::getRank() const
{
    return rank;

}

Cards::suitType Cards::getSuit() const
{
    return suit;
}

/*std::vector<Cards> Cards::setUpDeck(std::vector<Cards> &deck)
{
    while (deck.size() != 104)
    {
        for (int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 13; k++)
            {
                Cards *card = nullptr;
                card = new Cards(Cards::ranks[k], Cards::suits[j]);
                deck.push_back(*card);
            }
        }
    }
    return deck;
}*/

//not sure if this is needed but we will see
//void Cards::setRank(std::string)
//void Cards::setColor(std::string)

bool Cards::operator>(const Cards &otherCard) const
{
    return this->getRank() > otherCard.getRank();

}
bool Cards::operator<(const Cards &otherCard) const
{
    return this->getRank() < otherCard.getRank();
}
bool Cards::operator==(const Cards &otherCard) const
{
    return ((this->getRank() == otherCard.getRank()) && (this->getSuit() == otherCard.getSuit()));

}
bool Cards::operator!=(const Cards &otherCard) const
{
    return !((this->getRank() == otherCard.getRank()) && (this->getSuit() == otherCard.getSuit()));

}

std::ostream& operator<<(std::ostream & out, const Cards &topCard)
{
    out << suitStr[topCard.getSuit()] << " " << rankStr[topCard.getRank()];

    return out;
}

