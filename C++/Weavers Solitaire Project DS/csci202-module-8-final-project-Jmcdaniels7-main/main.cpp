#include <string>
#include <iostream>
#include <iomanip>
#include "card.h"
#include "linkedQueue.h"
#include "unorderedLinkedList.h"
#include "stack.h"
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
#include <set>

/* Program name: Final Project
* Author: Jacob McDaniels
* Date last updated: 12/12/2024
* Purpose: Weavers Card Game that implements Data Structures, OOP, and Procedural Programming concepts
*/
const int tsize = 12;
const int kingPile = 13;
const int EXILE = 14;

int welcome();
void rules();
void resetStream();
bool playAgain();
bool emptyTableaus(stackType<Cards> arr[]);
bool emptyExile(stackType<Cards> &e);
bool emptyKingPile(std::vector<Cards> &k);
void fillFoundations(int &countkH, int &countkD, int &countkS, int &countkC, int &countaH, int &countaD, int &countaS, int &countaC,std::vector<Cards> &deck, stackType<Cards> &aH, stackType<Cards> &aS, stackType<Cards> &aD, stackType<Cards> &aC, stackType<Cards> &kH, stackType<Cards> &kS, stackType<Cards> &kD, stackType<Cards> &kC);
void fillTableaus(std::vector<Cards> &deck, std::vector<Cards> &k, stackType<Cards> arr[], stackType<Cards> &e);
void gather(stackType<Cards> arr[], std::vector<Cards> &k, stackType<Cards> &e, std::vector<Cards> &newDeck);
int cChoice(stackType<Cards> &e, int &pc, int &rd, stackType<Cards> arr[], std::vector<Cards> &v, stackType<Cards> &aH, stackType<Cards> &aS, stackType<Cards> &aD, stackType<Cards> &aC, stackType<Cards> &kH, stackType<Cards> &kS, stackType<Cards> &kD, stackType<Cards> &kC);
int placement(int &pc, stackType<Cards> arr[], std::vector<Cards> &v, stackType<Cards> &aH, stackType<Cards> &aS, stackType<Cards> &aD, stackType<Cards> &aC, stackType<Cards> &kH, stackType<Cards> &kS, stackType<Cards> &kD, stackType<Cards> &kC);
bool won(stackType<Cards> kFHearts, stackType<Cards> kFDiamonds, stackType<Cards> kFSpades, stackType<Cards> kFClubs, stackType<Cards> aFHearts, stackType<Cards> aFDiamonds, stackType<Cards> aFSpades, stackType<Cards> aFClubs);

int main()
{
    // phase 1 setup intial frame of starting game
    // phase 2 create weavers game setup
    // phase 3 implement game operation and test

   while(true)
   {
        int choice = welcome();


        if(choice == 1)
        {
            while(true)
            {
                Cards card;
                stackType<Cards> tableaus[tsize];
                linkedQueueType<Cards> qTableaus[tsize];

                //foundations
                stackType<Cards> kFHearts;
                stackType<Cards> kFDiamonds;
                stackType<Cards> kFSpades;
                stackType<Cards> kFClubs;
                stackType<Cards> aFHearts;
                stackType<Cards> aFDiamonds;
                stackType<Cards> aFSpades;
                stackType<Cards> aFClubs;

                //exile
                stackType<Cards> exile;

                // fanned 13th pile/king pile
                std::vector<Cards> t13;

                // here we will insert 2 decks of cards into a vector
                std::vector<Cards> deck;

                //this is for if the cards are redealt
                std::vector<Cards> newDeck;

                //std::set<Cards> deckOne;
                //std::set<Cards> deckTwo;

                //card and play choice
                int cardChoice;
                int pChoice;
            
                int playCount = 0;

                // these are to keep track of the last card inserted into the foundations
                int countkH = 12;
                int countkS = 12;
                int countkD = 12;
                int countkC = 12;
                int countaH = 0;
                int countaS = 0;
                int countaD = 0;
                int countaC = 0;
                
                // this fills the deck
                while (deck.size() != 104 )
                {
                    for (int j = 0; j < 4; j++)
                    {
                        for(int k = 0; k < 13; k++)
                        {
                            Cards card (Cards::ranks[k], Cards::suits[j]);
                            deck.push_back(card);

                        }
                    }
                }

                // shuffles the deck
                std::random_shuffle ( deck.begin(), deck.end() );

                //filling foundations and setting last card initializing lastCard inserted at foundations
                fillFoundations(countkH, countkD, countkS, countkC, countaH, countaD, countaS, countaC, deck, aFHearts, aFSpades, aFDiamonds, aFClubs, kFHearts, kFSpades, kFDiamonds, kFClubs);
            
                fillTableaus(deck, t13, tableaus, exile);
                // dealing out rest of cards into tableaus and piles

                while(!won(kFHearts, kFDiamonds, kFSpades, kFClubs, aFHearts, aFDiamonds, aFSpades, aFClubs))
                {
                    int redeal = 0;
                    //present the board and return a choice of the card to take to play
                    // we can only pick from tableau top, exile, and 13th pile
                    cardChoice = cChoice(exile, playCount, redeal, tableaus, t13, aFHearts, aFDiamonds, aFSpades, aFClubs, kFHearts, kFDiamonds, kFSpades, kFClubs);
                    
                    // card picked to play
                    Cards cardPick;

                    if (cardChoice == 15 && redeal < 3)
                    {
                        // here we need to make a choice to play a card or redeal(gather)
                        gather(tableaus, t13, exile, newDeck);
                        fillTableaus(newDeck, t13, tableaus, exile);
                        redeal++;
                    }
                    // initializing the picked card and choosing a place to play it
                    else if(cardChoice >= 1 && cardChoice <= 14)
                    {
                        if (cardChoice >= 1 && cardChoice <= 12)
                        {
                            if(tableaus[cardChoice - 1].isEmptyStack())
                            {
                                std::cout << "This Tableau is empty!" << std::endl;
                            }
                            else
                            {
                                cardPick = tableaus[cardChoice - 1].top();
                                tableaus[cardChoice - 1].pop();

                            }
                        }


                        else if(cardChoice == 13)
                        {
                            int kingPile;
                            std::cout << "Please choose a card from the King Pile:" << std::endl;
                            for(int i = 0; i < t13.size(); i++)
                            {
                                std::cout << i + 1 << ". " << t13[i] << "  ";

                            }

                            std::cin >> kingPile;

                            while(!std::cin || (kingPile < 1 || kingPile > t13.size()))
                            {
                                std::cout << "Please choose a valid option from the King Pile." << std::endl;
                                resetStream();
                                std::cin >> kingPile;
                            }

                            if(t13.empty())
                            {
                                std::cout << "King Pile is Empty!" << std::endl;
                                break;
                            }
                            else
                            {
                                cardPick = t13[kingPile - 1];
                                t13.erase(t13.begin() + (kingPile - 1));

                            }

                            
                        }
                        else if (cardChoice == 14)
                        {
                            if(emptyExile(exile))
                            {
                                std::cout << "Exile Pile is Empty!!!!" << std::endl;
                            }
                            else
                            {
                                cardPick = exile.top();
                                std::cout << "You draw from the exile pile and find..." << std::endl;
                                std::cout << std::endl;
                                std::cout << cardPick << std::endl;
                                exile.pop();

                            }
                            
                            
                        }

                        // menu for choosing card placement
                        pChoice = placement(playCount, tableaus, t13, aFHearts, aFSpades, aFDiamonds, aFClubs, kFHearts, kFSpades, kFDiamonds, kFClubs);

                        //plays on tableaus
                        if(pChoice >= 1 && pChoice <= 13)
                        {
                            // this is to validate tableau plays
                            bool foundMatch = false;

                            //this is for calling invalid play on kingpile
                            bool foundMatch13 = false;

                            // validates plays on king pile
                            if (pChoice == 13 && cardPick.getRank() == Cards::ranks[12])
                            {
                                foundMatch13 = true;
                                t13.push_back(cardPick);
                            }
                            else
                            {
                                //searching for a match if we haven't broken from the loop already
                                for(int i = 0; i < tsize; i++)
                                {
                                    if((pChoice - 1) == i && cardPick.getRank() == i)
                                    {
                                        // this is the weaving process for tableaus 1-12
                                        foundMatch = true;
                                        //stack top = first in queue
                                        while(!tableaus[i].isEmptyStack())
                                        {
                                            qTableaus[i].enqueue(tableaus[i].top());
                                            tableaus[i].pop();
                                        }

                                        //cardPick is at back of Queue
                                        qTableaus[i].enqueue(cardPick);
                                        
                                        //cardPick now equals first in queue
                                        qTableaus[i].revQueue(qTableaus[i]);

                                        // first in queue goes to the bottom of the stack
                                        while(!qTableaus[i].isEmptyQueue())
                                        {
                                            tableaus[i].push(qTableaus[i].dequeue());
                                        }
                                        break;
                                    }
                                }
                            }

                            if(!foundMatch && !foundMatch13)
                            {
                                // technical else based on not breaking from loop
                                std::cout << "                  ******************Invalid play******************" << std::endl;

                                //puts back the card
                                for(int i = 0; i <= tsize; i++)
                                {
                                    if((cardChoice - 1) == i)
                                    {
                                        tableaus[i].push(cardPick);
                                        break;
                                    }
                                }
                                break;

                            }

                        }
                        // plays on foundations
                        else if (pChoice > 13 && pChoice <= 21)
                        {
                            //14-21 for foundation placements

                            //kings 14-17
                            if(pChoice == 14 && cardPick.getRank() == Cards::ranks[countkH] && cardPick.getSuit() == Cards::suits[0])
                            {
                                //validates the play
                                kFHearts.push(cardPick);
                                countkH--;
                            }
                            else if(pChoice == 15 && cardPick.getRank() == Cards::ranks[countkS] && cardPick.getSuit() == Cards::suits[1])
                            {
                                
                                kFSpades.push(cardPick);
                                countkS--;
                                
                            }
                            else if(pChoice == 16 && cardPick.getRank() == Cards::ranks[countkD] && cardPick.getSuit() == Cards::suits[2])
                            {
                                kFDiamonds.push(cardPick);
                                countkD--;
                                
                            }
                            else if(pChoice == 17 && cardPick.getRank() == Cards::ranks[countkC] && cardPick.getSuit() == Cards::suits[3])
                            {
                                kFClubs.push(cardPick);
                                countkC--;
                            }
                            
                            //aces 18-21
                            else if(pChoice == 18 && cardPick.getRank() == Cards::ranks[countaH] && cardPick.getSuit() == Cards::suits[0])
                            {
                                aFHearts.push(cardPick);
                                countaH++;
                                
                            }
                            else if(pChoice == 19 && cardPick.getRank() == Cards::ranks[countaS] && cardPick.getSuit() == Cards::suits[1])
                            {
                                aFSpades.push(cardPick);
                                countaS++;

                            }
                            else if(pChoice == 20 && cardPick.getRank() == Cards::ranks[countaD] && cardPick.getSuit() == Cards::suits[2])
                            {
                                aFDiamonds.push(cardPick);
                                
                                countaD++;
                                
                            }
                            else if(pChoice == 21 && cardPick.getRank() == Cards::ranks[countaC] && cardPick.getSuit() == Cards::suits[3])
                            {
                                aFClubs.push(cardPick);
                                
                                countaC++;
                            }
                            else
                            {
                                std::cout << "Invalid play " << std::endl;

                                //puts back the card
                                if(cardChoice >= 1 && cardChoice <= 12)
                                {
                                    for(int i = 0; i <= tsize; i++)
                                    {
                                        tableaus[cardChoice - 1].push(cardPick);
                                    }
                                }
                                else if(cardChoice == kingPile || cardChoice == EXILE)
                                {
                                    if(cardChoice == kingPile)
                                    {
                                        t13.push_back(cardPick);
                                    }
                                    else if(cardChoice == EXILE)
                                    {
                                        exile.push(cardPick);
                                    }
                                }
                            }
                        }
                    
                        // to keep track of plays
                        playCount++;
                    }

                }

                if (won(kFHearts, kFDiamonds, kFSpades, kFClubs, aFHearts, aFDiamonds, aFSpades, aFClubs))
                {
                    std::cout << "Congratulations, You Won!!!!!" << std::endl;
                }
                else
                {
                    std::cout << "Better Luck Next Time." << std::endl;
                }

                if(!playAgain())
                {
                    exit(0);
                }

            }

        }
        else if(choice == 2)
        {
            rules();

        }
        else if (choice == 3)
        {
            exit(0);
            
        }
    }

}

int welcome()
{
    int choice;

    std::cout << "Welcome to Weavers Solitare!\nSelect From the options below:\n"; 
    std::cout << "1. Start Game\n2. Rules\n3. Exit\n";

    std::cin >> choice;

    while(!std::cin || choice < 1 || choice > 3)
    {
        std::cout << "Please select a option 1-3." << std::endl;
        std::cout << "1. Start Game\n2. Rules\n3. Exit\n";

        std::cin >> choice;
    }
    
    return choice;
}

void rules()
{
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Weavers Solitare Game Rules" << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << std::endl;

    std::cout << "General" << std::endl;
    std::cout << "-------" << std::endl;
    std::cout << "1. A standard deck of cards has 52 cards, 4 suits, and 2 colors." << std::endl;
    std::cout << "2. Weavers Solitare is played with 2 standard decks of cards." << std::endl;
    std::cout << "3. Weavers Solitare will be played generally like Solitare with a few new features." << std::endl;
    std::cout << std::endl;

    std::cout << "Foundations" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "1. There are 8 Foundations, 4 Ace Foundations and 4 King Foundations." << std::endl;
    std::cout << "2. The 4 King Foundations will build down to an Ace." << std::endl;
    std::cout << "3. The 4 Ace Foundations will build up to a King." << std::endl;
    std::cout << std::endl;

    // We will do Tableau next then talk about Valid plays, 
    // their specifications, and the gather option specifications
    std::cout << "Tableau" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "1. There are 12 tableaus marked as 1-12 with 6 cards in each tableau." << std::endl;
    std::cout << "2. The top card on each tableau is playable." << std::endl;
    // this will happen when dealing as well so we will need to code this behind the scenes
    // if a card is dealt in a pile that matches the cards number, it goes into the exile pile.
    std::cout << "3. If you choose to play a card from a tableau that matches the number of a tableau 1-12,\n   you can weave that card to the bottom of the tableau with the cooresponding cards number." << std::endl;
    std::cout << std::endl;

    std::cout << "Stock" << std::endl;
    std::cout << "-----------" << std::endl;
    std::cout << "1. Draw a card from the exile pile and you can choose a valid play. Kings go to 13th pile,\n   Queens to 12th and Jacks to 11th." << std::endl;
    std::cout << "2. Draw a card from the 13th pile to make a valid play." << std::endl;
    //option for even more challenging version
    //std::cout << "3. Drawing a King stops the play and a exile card is drawn." << std::endl;
    //this will be a feature where we start with the 13th pile and stack them in reverse order, then turn them over and redeal
    std::cout << "3. If you run out of plays or wish to redeal, you can choose to gather the cards and redeal." << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;


    


}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void fillFoundations(int &countkH, int &countkD, int &countkS, int &countkC, int &countaH, int &countaD, int &countaS, int &countaC, std::vector<Cards> &deck, stackType<Cards> &aH, stackType<Cards> &aS, stackType<Cards> &aD, stackType<Cards> &aC, stackType<Cards> &kH, stackType<Cards> &kS, stackType<Cards> &kD, stackType<Cards> &kC)
{
    for (int i = 0; i < deck.size(); i++)
    {
        // search for king foundations
        if(deck[i].getRank() == Cards::ranks[12])
        {
            if(deck[i].getSuit() == Cards::suits[0] && countkH == 12)
            {
                kH.push(deck[i]);
                deck.erase(deck.begin() + i);
                countkH--;
            }
            else if(deck[i].getSuit() == Cards::suits[1] && countkS == 12)
            {
                kS.push(deck[i]);
                deck.erase(deck.begin() + i);
                countkS--;
                
            }
            else if(deck[i].getSuit() == Cards::suits[2] && countkD == 12)
            {
                kD.push(deck[i]);
                deck.erase(deck.begin() + i);
                countkD--;
            }
            else if(deck[i].getSuit() == Cards::suits[3] && countkC == 12)
            {
                kC.push(deck[i]);
                deck.erase(deck.begin() + i);
                countkC--;
            }
        }

        // search for ace foundations
        else if(deck[i].getRank() == Cards::ranks[0])
        {
            if(deck[i].getSuit() == Cards::suits[0] && countaH == 0)
            {
                aH.push(deck[i]);
                deck.erase(deck.begin() + i);
                countaH++;
            }
            else if(deck[i].getSuit() == Cards::suits[1] && countaS == 0)
            {
                aS.push(deck[i]);
                deck.erase(deck.begin() + i);
                countaS++;
            }
            else if(deck[i].getSuit() == Cards::suits[2] && countaD == 0)
            {
                aD.push(deck[i]);
                deck.erase(deck.begin() + i);
                countaD++;
            }
            else if(deck[i].getSuit() == Cards::suits[3] && countaC == 0)
            {
                aC.push(deck[i]);
                deck.erase(deck.begin() + i);
                countaC++;
            }
        }
        else if(countaC == 1 && countaH == 1 && countaD == 1 && countaS == 1 && countkH == 11 && countkS == 11 && countkD == 11 && countkC == 11)
        {
            break;
        }
    }
}

void fillTableaus(std::vector<Cards> &deck, std::vector<Cards> &k, stackType<Cards> arr[], stackType<Cards> &e)
{
    int tabs = 0;
    
    for(int i = 0; i < deck.size(); i++)
    {
        for (int j = 0; j <= 12; j++)
        {
            //if card rank matches tableau it goes in the exile
            if(deck[i].getRank() == j)
            {
                e.push(deck[i]);
                deck.erase(deck.begin());
            }
            else 
            {
                if(j >=0 && j <= 11)
                {
                    arr[j].push(deck[i]);

                    deck.erase(deck.begin());
                }
                else if (j == 12)
                {
                    k.push_back(deck[0]);
                    deck.erase(deck.begin());
                }
            }
        }
    }
    

}

int cChoice(stackType<Cards> &e, int &pc, int &rd, stackType<Cards> arr[], std::vector<Cards> &v, stackType<Cards> &aH, stackType<Cards> &aS, stackType<Cards> &aD, stackType<Cards> &aC, stackType<Cards> &kH, stackType<Cards> &kS, stackType<Cards> &kD, stackType<Cards> &kC)
{
    int cardChoice;

    std::cout << "Ace Foundations" << std::endl;
    std::cout << std::endl;
    std::cout << aH.top() << "     " << aS.top() << "     " << aD.top() << "     " << aC.top() << "\n\n";
    
    std::cout << "King Foundations" << std::endl;
    std::cout << std::endl;
    std::cout << kH.top() << "     " << kS.top() << "     " << kD.top() << "     " << kC.top() << "\n\n";

    std::cout << "Tableaus" << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < tsize; i++)
    {
        if(arr[i].isEmptyStack())
        {
            std::cout << i + 1 << ": " << "  " << "      " << std::endl;
        }
        else
        {
            std::cout << i + 1 << ": " << arr[i].top() << "      ";
            if(i % 6 == 0 && i > 0)
            {
                std::cout << std::endl;
            }
        }
        
    }

    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "13. Fanned out King pile" << std::endl;
    if(v.empty())
    {
        std::cout << "Empty King Pile" << std::endl;
    }
    else
    {
        for(int i = 0; i < v.size(); i++)
        {
            std::cout << v[i] << "  ";

        }
    }
    
    std::cout << std::endl;
    std::cout << std::endl;

    
    if(emptyExile(e))
    {
        std::cout << "Empty Exile Pile" << std::endl;
    }
    else
    {
        std::cout << "14. Draw from exile" << std::endl;

    }
    std::cout << std::endl;

    if(e.isEmptyStack() && pc > 0 && rd < 3)
    {
        std::cout << "15. Redeal" << std::endl;
    }

    std::cout << "Play Count: " << pc << std::endl;
    std::cout << std::endl;

    std::cout << "Pick a card from a pile to play:" << std::endl;
    
    std::cin >> cardChoice;

    

    while(!std::cin || (cardChoice < 1 || cardChoice > 15) || (!emptyExile(e) && pc >= 0 && cardChoice == 15) || (emptyExile(e) && pc >= 0 && rd == 3 && cardChoice == 15) || ((emptyExile(e) && cardChoice == 14) || (emptyKingPile(v) && cardChoice == 13)))
    {
        if(!std::cin || (cardChoice < 1 || cardChoice > 15) || (!emptyExile(e) && pc >= 0 && cardChoice == 15))
        {
            std::cout << "Please choose a card from the given options of piles." << std::endl;

        }
        else if(emptyExile(e) && pc >= 0 && rd == 3 && cardChoice == 15)
        {
            std::cout << "Invalid Choice" << std::endl;
            std::cout << "You have reached the maximum number of redeals: " << rd << std::endl;
            

        }
        else if(emptyExile(e) || emptyKingPile(v))
        {
            std::cout << "Invalid Choice" << std::endl;
            std::cout << "There are no more cards in that pile to pick from!" << std::endl;

        }
        
        resetStream();
        std::cin >> cardChoice;

    }
    
    //handles trying to pick a card from an empty tableau or king pile
    while(((cardChoice >= 1 && cardChoice <= 12) && arr[cardChoice - 1].isEmptyStack()) || (cardChoice == 13 && v.empty()))
    {
        std::cout << "This pile is empty, please choose a different pile to pick from." << std::endl;
        resetStream();
        std::cin >> cardChoice;
    }
    std::cout << std::endl;
    std::cout << std::endl;

    return cardChoice;

}

int placement(int &pc, stackType<Cards> arr[], std::vector<Cards> &v, stackType<Cards> &aH, stackType<Cards> &aS, stackType<Cards> &aD, stackType<Cards> &aC, stackType<Cards> &kH, stackType<Cards> &kS, stackType<Cards> &kD, stackType<Cards> &kC)
{
    int pChoice;
    

    std::cout << "Where would you like to place your card?" << std::endl;
    std::cout << std::endl;

    std::cout << "Tableaus" << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < tsize; i++)
    {
        if (arr[i].isEmptyStack())
        {
            std::cout << i + 1 << ": " << " " << "     ";
        }
        else
        {
            std::cout << i + 1 << ": " << arr[i].top() << "     ";
        
            if(i % 4 == 0 && i > 0)
            {
                std::cout << std::endl;
            }
        }
    }

    std::cout << std::endl;
    std::cout << std::endl;
    
    std::cout << "13. King Pile" << std::endl;
    if(v.empty())
    {
        std::cout << "Empty King Pile" << std::endl;
    }
    else
    {
        for(int i = 0; i < v.size(); i++)
        {
            std::cout <<  v[i] << "  ";
        }
    }
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "King Foundations" << std::endl;
    std::cout << std::endl;

    std::cout << "14." << kH.top() << "  15." << kS.top() << "  16." << kD.top() << "  17." << kC.top() << std::endl;
    
    std::cout << "Ace Foundations" << std::endl;
    std::cout << std::endl;

    std::cout << "18." << aH.top() << "  19." << aS.top() << "  20." << aD.top() << "  21." << aC.top() << std::endl;
    std::cout << std::endl;

    std::cout << "Play Count: " << pc << std::endl;
    std::cout << std::endl;

    std::cin >> pChoice;

    while(!std::cin || (pChoice < 1 || pChoice > 21))
    {
        std::cout << "Please choose a valid play 1-21." << std::endl;
        resetStream();
        std::cin >> pChoice;
    }

    std::cout << std::endl;
    std::cout << std::endl;

    return pChoice;

}

void gather(stackType<Cards> arr[], std::vector<Cards> &k, stackType<Cards> &e, std::vector<Cards> &newDeck)
{
    stackType<Cards> gather;
    linkedQueueType<Cards> helpG;
    Cards card;

    //we want the stacks to be added as they are in reverse order 13 at bottom

    //we take king pile contents first
    while(!k.empty())
    {
        card = k[0];
        k.erase(k.begin());

        gather.push(card);
    }

    // each stack has its top card put first into the queue
    // stack[11] top is first in queue, in this loop
    for(int i = 11; i > 0; i--)
    {
        while(!arr[i].isEmptyStack())
        {
            gather.push(arr[i].top());
            arr[i].pop();
        }
    }

    while(!gather.isEmptyStack())
    {
        newDeck.push_back(gather.top());
        gather.pop();
    }
}

bool playAgain()
{
    int plChoice;
    bool playAgain = true;
    std::cout << "Do you want to play again?" << std::endl;
    std::cout << "1. Yes" << std::endl;
    std::cout << "2. No" << std::endl;

    std::cin >> plChoice;

    while(!std::cin || (plChoice != 1 && plChoice != 2))
    {
        std::cout << "Please choose a valid option: \n1. Play Again\n 2. Exit Game" <<std::endl;
        std::cin >> plChoice;
    }

    if (plChoice == 2)
    {
        playAgain = false;
    }

    return playAgain;

}

bool emptyTableaus(stackType<Cards> arr[])
{
    bool empty = false;

    for(int i = 0; i < 12; i++)
    {
        if(arr[i].isEmptyStack())
        {
            return true;
            break;
        }

    }

    return empty;
}

bool emptyKingPile(std::vector<Cards> &k)
{
    bool empty = false;

    if(k.size() == 0)
    {
        empty = true;
    }

    return empty;
}

bool emptyExile(stackType<Cards> &e)
{
    bool empty = false;

    if(e.isEmptyStack())
    {
        empty = true;
    }

    return empty;
}

bool won(stackType<Cards> kFHearts, stackType<Cards> kFDiamonds, stackType<Cards> kFSpades, stackType<Cards> kFClubs, stackType<Cards> aFHearts, stackType<Cards> aFDiamonds, stackType<Cards> aFSpades, stackType<Cards> aFClubs)
{
    Cards hAce(Cards::ranks[0], Cards::suits[0]);
    Cards hKing(Cards::ranks[12], Cards::suits[0]);

    Cards dAce(Cards::ranks[0], Cards::suits[2]);
    Cards dKing(Cards::ranks[12], Cards::suits[2]);

    Cards sAce(Cards::ranks[0], Cards::suits[1]);
    Cards sKing(Cards::ranks[12], Cards::suits[1]);

    Cards cAce(Cards::ranks[0], Cards::suits[3]);
    Cards cKing(Cards::ranks[12], Cards::suits[3]);

    bool won = false;
    //foundations not being found?

    if ((kFHearts.top() == hAce) && (aFHearts.top() == hKing) && (kFDiamonds.top() == dAce) && (aFDiamonds.top() == dKing) && (kFSpades.top() == sAce) && (aFSpades.top() == sKing) && (kFClubs.top() == cAce) && (aFClubs.top() == cKing))
    {
        won = true;

    } 
    return won;
}