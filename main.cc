#include <iostream>
#include <vector>
#include <memory>
#include "Player.h"
#include "Game.h"
#include "Round.h"
#include "View.h"
#include "Card.h"
#include <string>
#include <random>
#include <chrono>

using namespace std;

int main(int argc, char** argv) {
  // handle cmd-line inputs and seed
  unsigned seed;
  bool stopEachRound = false;
  bool deckEachRound = false;
  if ( argc > 1 ) {
    seed = stoi(string{ argv[1] });
  } else {
    seed = chrono::system_clock::now().time_since_epoch().count();
  }

  auto theGame = make_unique<Game>(seed); //instantiate game with seed

  bool quit = false;
  
  while (!theGame->gameOver() && !quit) {

    theGame->shuffleDeck();

    auto theRound = make_unique<Round>(theGame->getDeck(), theGame->getPlayers());
    
    auto theView = make_unique<View>(&(*theRound));

    cout << "A new round begins. It's Player" << (theRound->getTurn(false) + 1) << "'s turn to play." << endl;
    
    while (!theRound->isRoundOver()) {
      theRound->notifyObservers();
      int turn = theRound->getTurn();
      quit = theView->controller(turn);
      if (quit) {
        break;
      }
    }

    if (!quit) {
      theRound->handleRoundEnd();
    }

  }


} 