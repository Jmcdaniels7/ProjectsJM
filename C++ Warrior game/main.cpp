#include "character.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <map>
#include <vector>

enum characterType {
  WARRIOR = 1,
  KNIGHT,
  THIEF,
  BEAUTY,
  JESTER,
  ORC,
  ROGUE,
  PRISONER
};

std::map<characterType, std::string> characterToString = {{WARRIOR, "Warrior"}, {KNIGHT, "Knight"}, {THIEF, "Thief"}, {BEAUTY, "Beauty"}, {JESTER, "Jester"}, {ORC, "Orc"}, {ROGUE, "Rogue"}, {PRISONER, "Prisoner"}};

void intro();
void resetStream();
int gameSelection();
int characterCreator();

int main() {
  std::string playerType1;
  std::string playerType2;
  std::string playerType3;
  std::string playerType4;
  int gameChoice;
  int characterChoice1;
  int characterChoice2;
  int characterChoice3;
  int characterChoice4;
  std::string name1;
  std::string name2;
  std::string name3;
  std::string name4;
  int teamChoice;
  int teamChoice2;
  int teamChoice3;
  int teamChoice4;
  int player1Turn = 0;
  int player2Turn = 0;
  //int player3Turn = 0;
  //int player4Turn = 0;
  //int playChoice1;
  //int playChoice2;
  //int playChoice3;
  //int playChoice4;
  std::vector<character> deathmatch;

  
  intro();
  // we need the press any key to continue thing we learned in lecture after the intro
  // we need to start implementing the turns

  gameChoice = gameSelection();
  std::cout << std::endl;

  

  if (gameChoice == 1)
  {
    // Player 1
    std::cout << "Player 1 please choose your character:" << std::endl;
    
    characterChoice1 = characterCreator();
    std::cout << std::endl;

    playerType1 = characterToString[characterType(characterChoice1)];
    
    std::cout << "What is the name of the " << playerType1 << "?" << std::endl;
    std::cin >> name1;
    std::cout << std::endl;

    if(characterChoice1 == 1)
    {
      warrior player1(name1, 0, 300, 0, 30, 28, 5, 15, 20, 5);

      std::cout << "You have chosen the Warrior!" << std::endl<< std::endl;

      player1.speak();

      deathmatch.push_back(player1);
      
      std::cout << player1.toString() << std::endl;
    }
    else if(characterChoice1 == 2)
    {
      knight player1(name1, player1Turn, 350, 0, 25, 25, 10, 5, 30, 10);

      std::cout << "You have chosen the Knight!" << std::endl<< std::endl;

      player1.speak();

      std::cout << player1.toString() << std::endl;

    }
    else if(characterChoice1 == 3)
    {
      thief player1(name1, player1Turn, 200, 0, 10, 30, 25, 30, 15, 5);

      std::cout << "You have chosen the Thief!" << std::endl<< std::endl;

      player1.speak();

      
      std::cout << player1.toString() << std::endl;

    }
    else if(characterChoice1 == 4)
    {
      beauty player1(name1, player1Turn, 200, 0, 5, 15, 30, 10, 20, 10);

      std::cout << "You have chosen the Beauty!" << std::endl<< std::endl;
      
      std::cout << player1.toString() << std::endl;

    }
    else if(characterChoice1 == 5)
      {
        jester player1(name1, player1Turn, 200, 0, 10, 20, 25, 25, 25, 5);

        std::cout << "You have chosen the Jester!" << std::endl<< std::endl;

        player1.speak();
        
        std::cout << player1.toString() << std::endl;

      }
    else if(characterChoice1 == 6)
      {
        orc player1(name1, player1Turn, 300, 0, 30, 28, 5, 5, 10, 5);

        std::cout << "You have chosen the Orc!" << std::endl<< std::endl;

        player1.speak();
        
        std::cout << player1.toString() << std::endl;

      }
    else if(characterChoice1 == 7)
      {
        rogue player1(name1, player1Turn, 300, 0, 15, 20, 15, 25, 30, 20);

        std::cout << "You have chosen the Rogue!" << std::endl<< std::endl;

        player1.speak();
        
        std::cout << player1.toString() << std::endl;

      }
    else if(characterChoice1 == 8)
      {
        prisoner player1(name1, player1Turn, 250, 0, 10, 15, 25, 10, 20, 30);

        std::cout << "You have chosen the Prisoner!" << std::endl<< std::endl;

        player1.speak();
        
        std::cout << player1.toString() << std::endl;

      }
    else if(characterChoice1 == 9)
      {
        sourcer player1(name1, player1Turn, 250, 200, 10, 15, 30, 5, 15, 20);

        std::cout << "You have chosen the Sourcer!" << std::endl<< std::endl;

        player1.speak();
        
        std::cout << player1.toString() << std::endl;

      }
    
   // Player 2
    std::cout << "Player 2 please choose your character:" << std::endl;

    characterChoice2 = characterCreator();
    std::cout << std::endl;
    
    playerType2 = characterToString[characterType(characterChoice2)];

    std::cout << "What is the name of the " << playerType2 << "?" << std::endl;
    std::cin >> name2;
    std::cout << std::endl;

    if(characterChoice2 == 1)
      {
        warrior player2(name2, player2Turn, 300, 0, 30, 28, 5, 15, 20, 5);
        
        std::cout << "You have chosen the Warrior!" << std::endl<< std::endl;

        player2.speak();
        
        std::cout << player2.toString() << std::endl;
      }
      else if(characterChoice2 == 2)
      {
        knight player2(name2, player2Turn, 350, 0, 25, 25, 10, 5, 30, 10);

        std::cout << "You have chosen the Knight!" << std::endl<< std::endl;

        player2.speak();
        
        std::cout << player2.toString() << std::endl;

      }
      else if(characterChoice2 == 3)
      {
        thief player2(name2, player2Turn, 200, 0, 10, 30, 25, 30, 15, 5);

        std::cout << "You have chosen the Thief!" << std::endl<< std::endl;

        player2.speak();
        
        std::cout << player2.toString() << std::endl;

      }
      else if(characterChoice2 == 4)
      {
        beauty player2(name2, player2Turn, 200, 0, 5, 15, 30, 10, 20, 10);

        std::cout << "You have chosen the Beauty!" << std::endl<< std::endl;

        player2.speak();
        
        std::cout << player2.toString() << std::endl;

      }
      else if(characterChoice2 == 5)
        {
          jester player2(name2, player2Turn, 200, 0, 10, 20, 25, 25, 25, 5);

          std::cout << "You have chosen the Jester!" << std::endl<< std::endl;

          player2.speak();
          
          std::cout << player2.toString() << std::endl;

        }
      else if(characterChoice2 == 6)
        {
          orc player2(name2, player2Turn, 300, 0, 30, 28, 5, 5, 10, 5);

          std::cout << "You have chosen the Orc!" << std::endl<< std::endl;

          player2.speak();
          
          std::cout << player2.toString() << std::endl;

        }
      else if(characterChoice2 == 7)
        {
          rogue player2(name2, player2Turn, 300, 0, 15, 20, 15, 25, 30, 20);

          std::cout << "You have chosen the Rogue!" << std::endl<< std::endl;

          player2.speak(); 
          
          std::cout << player2.toString() << std::endl;

        }
      else if(characterChoice2 == 8)
        {
          prisoner player2(name2, player2Turn, 250, 0, 10, 15, 25, 10, 20, 30);

          std::cout << "You have chosen the Prisoner!" << std::endl<< std::endl;

          player2.speak();
          
          std::cout << player2.toString() << std::endl;

        }
      else if(characterChoice2 == 9)
        {
          sourcer player2(name2, player2Turn, 250, 200, 10, 15, 30, 5, 15, 20);

          std::cout << "You have chosen the Sourcer!" << std::endl<< std::endl;

          player2.speak();
          
          std::cout << player2.toString() << std::endl;

        }

    std::cout << name1 << " the " << playerType1 << " vs. " << name2 << " the " << playerType2 << std::endl << std::endl;
    

    std::cout << "To the Death!!!" << std::endl << std::endl;
    // game begins
    // play until someone goes to 0 hp or quits
    
  }
  else if (gameChoice == 2)
  {
    // Player 1
    std::cout << "Player 1 please choose your character:" << std::endl;

    characterChoice1 = characterCreator();
    std::cout << std::endl;

    playerType1 = characterToString[characterType(characterChoice1)];

    std::cout << "What is the name of the " << playerType1 << "?" << std::endl;
    std::cin >> name1;
    std::cout << std::endl;

    if(characterChoice1 == 1)
      {
        warrior player1(name1, 0, 300, 0, 30, 28, 5, 15, 20, 5);

        std::cout << "You have chosen the Warrior!" << std::endl<< std::endl;

        player1.speak();

        std::cout << player1.toString() << std::endl;
      }
      else if(characterChoice1 == 2)
      {
        knight player1(name1, 0, 350, 0, 25, 25, 10, 5, 30, 10);

        std::cout << "You have chosen the Knight!" << std::endl<< std::endl;

        player1.speak();

        std::cout << player1.toString() << std::endl;

      }
      else if(characterChoice1 == 3)
      {
        thief player1(name1, 0, 200, 0, 10, 30, 25, 30, 15, 5);

        std::cout << "You have chosen the Thief!" << std::endl<< std::endl;

        player1.speak();

        std::cout << player1.toString() << std::endl;

      }
      else if(characterChoice1 == 4)
      {
        beauty player1(name1, 0, 200, 0, 5, 15, 30, 10, 20, 10);

        std::cout << "You have chosen the Beauty!" << std::endl<< std::endl;

        player1.speak();

        std::cout << player1.toString() << std::endl;

      }
      else if(characterChoice1 == 5)
        {
          jester player1(name1, 0, 200, 0, 10, 20, 25, 25, 25, 5);

          std::cout << "You have chosen the Jester!" << std::endl<< std::endl;

          player1.speak();

          std::cout << player1.toString() << std::endl;

        }
      else if(characterChoice1 == 6)
        {
          orc player1(name1, 0, 300, 0, 30, 28, 5, 5, 10, 5);

          std::cout << "You have chosen the Orc!" << std::endl<< std::endl;

          player1.speak();

          std::cout << player1.toString() << std::endl;

        }
      else if(characterChoice1 == 7)
        {
          rogue player1(name1, 0, 300, 0, 15, 20, 15, 25, 30, 20);

          std::cout << "You have chosen the Rogue!" << std::endl<< std::endl;

          player1.speak();

          std::cout << player1.toString() << std::endl;

        }
      else if(characterChoice1 == 8)
        {
          prisoner player1(name1, 0, 250, 0, 10, 15, 25, 10, 20, 30);

          std::cout << "You have chosen the Prisoner!" << std::endl<< std::endl;

          player1.speak();

          std::cout << player1.toString() << std::endl;

        }
      else if(characterChoice1 == 9)
        {
          sourcer player1(name1, 0, 250, 200, 10, 15, 30, 5, 15, 20);

          std::cout << "You have chosen the Sourcer!" << std::endl<< std::endl;

          player1.speak();

          std::cout << player1.toString() << std::endl;

        }

    // need some kind of collection to hold only two characters as a team and if a team is full then remaining players can only choose to be on the other team.
    std::cout << "Please Choose team 1 or 2" << std::endl;
    std::cin >> teamChoice;
    std::cout << std::endl;

   // Player 2
    std::cout << "Player 2 please choose your character:" << std::endl;

    characterChoice2 = characterCreator();
    std::cout << std::endl;

    playerType2 = characterToString[characterType(characterChoice2)];

    std::cout << "What is the name of the " << playerType2 << "?" << std::endl;
    std::cin >> name2;
    std::cout << std::endl;

    if(characterChoice2 == 1)
    {
      warrior player2(name2, 0, 300, 0, 30, 28, 5, 15, 20, 5);

      std::cout << "You have chosen the Warrior!" << std::endl<< std::endl;

      player2.speak();

      std::cout << player2.toString() << std::endl;
    }
    else if(characterChoice2 == 2)
    {
      knight player2(name2, 0, 350, 0, 25, 25, 10, 5, 30, 10);

      std::cout << "You have chosen the Knight!" << std::endl<< std::endl;

      player2.speak();

      std::cout << player2.toString() << std::endl;

    }
    else if(characterChoice2 == 3)
    {
      thief player2(name2, 0, 200, 0, 10, 30, 25, 30, 15, 5);

      std::cout << "You have chosen the Thief!" << std::endl<< std::endl;

      player2.speak();

      std::cout << player2.toString() << std::endl;

    }
    else if(characterChoice2 == 4)
    {
      beauty player2(name2, 0, 200, 0, 5, 15, 30, 10, 20, 10);

      std::cout << "You have chosen the Beauty!" << std::endl<< std::endl;

      player2.speak();

      std::cout << player2.toString() << std::endl;

    }
    else if(characterChoice2 == 5)
      {
        jester player2(name2, 0, 200, 0, 10, 20, 25, 25, 25, 5);

        std::cout << "You have chosen the Jester!" << std::endl<< std::endl;

        player2.speak();

        std::cout << player2.toString() << std::endl;

      }
    else if(characterChoice2 == 6)
      {
        orc player2(name2, 0, 300, 0, 30, 28, 5, 5, 10, 5);

        std::cout << "You have chosen the Orc!" << std::endl<< std::endl;

        player2.speak();

        std::cout << player2.toString() << std::endl;

      }
    else if(characterChoice2 == 7)
      {
        rogue player2(name2, 0, 300, 0, 15, 20, 15, 25, 30, 20);

        std::cout << "You have chosen the Rogue!" << std::endl<< std::endl;

        player2.speak(); 

        std::cout << player2.toString() << std::endl;

      }
    else if(characterChoice2 == 8)
      {
        prisoner player2(name2, 0, 250, 0, 10, 15, 25, 10, 20, 30);

        std::cout << "You have chosen the Prisoner!" << std::endl<< std::endl;

        player2.speak();

        std::cout << player2.toString() << std::endl;

      }
    else if(characterChoice2 == 9)
      {
        sourcer player2(name2, 0, 250, 200, 10, 15, 30, 5, 15, 20);

        std::cout << "You have chosen the Sourcer!" << std::endl<< std::endl;

        player2.speak();

        std::cout << player2.toString() << std::endl;

      }

    std::cout << "Please Choose team 1 or 2" << std::endl;
    std::cin >> teamChoice2;
    std::cout << std::endl;

  // Player 3
    std::cout << "Player 3 please choose your character:" << std::endl;

    characterChoice3 = characterCreator();
    std::cout << std::endl;

    playerType3 = characterToString[characterType(characterChoice3)];

    std::cout << "What is the name of the " << playerType3 << "?" << std::endl;
    std::cin >> name3;
    std::cout << std::endl;

    std::cout << "Please Choose team 1 or 2" << std::endl;
    std::cin >> teamChoice3;
    std::cout << std::endl;

   // Player 4
    std::cout << "Player 4 please choose your character:" << std::endl;

    characterChoice4 = characterCreator();
    std::cout << std::endl;

    playerType4 = characterToString[characterType(characterChoice4)];
    std::cout << std::endl;

    std::cout << "What is the name of the " << playerType4 << "?" << std::endl;
    std::cin >> name4;
    std::cout << std::endl;

    std::cout << "Please Choose team 1 or 2" << std::endl;
    std::cin >> teamChoice4;
    std::cout << std::endl;

    // game begins
    // if hp is at zero then a player will die, if both team members die then the opposing team wins.
  
  }
  
}
int gameSelection() {
  int gameChoice;
  std::cout << "WARRIOR" << std::endl << std::endl;

  std::cout << "Please choose a game mode: " << std::endl;

  std::cout << "Deathmatch(1)" << std::endl;
  std::cout << "Team Deathmatch(2)" << std::endl;

  std::cin >> gameChoice;

  while (!std::cin || gameChoice < 1 || gameChoice > 2)
    {
      if(!std::cin )
      {
        std::cout << "Please choose a valid game mode 1 for Deathmatch or 2 for Team Deathmatch." << std::endl;
        resetStream();
      }
      else if (gameChoice < 1 || gameChoice > 2)
      {
        std::cout << "Please choose a valid game mode 1 for Deathmatch or 2 for Team Deathmatch." << std::endl;
      }
      std::cin >> gameChoice;
    }
  return gameChoice;
}
void resetStream() {
  
}
int characterCreator() {
  int characterChoice;
  
  std::cout << "Warrior(1)" << std::endl;
  std::cout << "Knight(2)" << std::endl;
  std::cout << "Thief(3)" << std::endl;
  std::cout << "Beauty(4)" << std::endl;
  std::cout << "Jester(5)" << std::endl;
  std::cout << "Orc(6)" << std::endl;
  std::cout << "Rogue(7)" << std::endl;
  std::cout << "Prisoner(8)" << std::endl;
  std::cout << "Sourcer(9)" << std::endl;

  std::cin >> characterChoice;

  while (!std::cin || characterChoice < 1 || characterChoice > 8)
    {
      if(!std::cin )
      {
        std::cout << "Please choose a valid character 1-8." << std::endl;
        resetStream();
      }
      else if (characterChoice < 1 || characterChoice > 8)
      {
        std::cout << "Please choose a valid character 1-8." << std::endl;
      }
      std::cout << "Warrior(1)" << std::endl;
      std::cout << "Knight(2)" << std::endl;
      std::cout << "Thief(3)" << std::endl;
      std::cout << "Beauty(4)" << std::endl;
      std::cout << "Jester(5)" << std::endl;
      std::cout << "Orc(6)" << std::endl;
      std::cout << "Rogue(7)" << std::endl;
      std::cout << "Prisoner(8)" << std::endl;

      std::cin >> characterChoice;
    }

  return characterChoice;
}
void intro() {
  // need this line to be in the middle of the output terminal
  std::cout << "WARRIOR" << std::endl << std::endl;
  
  std::cout << "Welcome to the world of the Warrior! " << std::endl << std::endl;
  
  std::cout << "You can play as many different characters \nall with special abilities! " << std::endl << std::endl;
  
  std::cout << "Who will you choose to win the fight?" << std::endl << std::endl;
  
  std::cout << "Please press any key to start the game!" << std::endl << std::endl;

  std::cout << "Creator: Jacob McDaniels" << std::endl << std::endl;
  
  std::cout << "Developed by: Mango Tree Studios" << std::endl << std::endl;
  }