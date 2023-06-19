#include "Game.h"
#include "Card.h"
#include "Observer.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
#include <random>

Game::Game(int seed) : seed{seed} {
    fillPlayers();
    fillDeck();
}

Game::Game(vector<Card>& deck, vector<shared_ptr<Player>>& players, int seed): deck{deck}, players{players}, seed{seed} {};

Game::~Game(){};

void Game::fillPlayers() {
    for (int i = 0; i < 4; i++) {
        char c;
        cout << "Is Player" << i+1 << " a human (h) or a computer (c)?" << endl;
        cout << ">";
        cin >> c;
        auto it = make_shared<Player>(c=='c');
        players.push_back(it);
    }
}

void Game::fillDeck() {
    vector<char> suites{'D', 'C', 'H', 'S'};
    for (int i = 0; i < suites.size(); i++) {
        for (int j = 1; j < 14; j++) {
            deck.push_back(Card(j,suites[i]));
        }
    }
}

void Game::attach(Observer* o) {
  observers.emplace_back(o);
}

void Game::notifyObservers() {
  for (auto &ob : observers) ob->update();
}


vector<Card>& Game::getDeck() {
    return deck;
}

vector<shared_ptr<Player>>& Game::getPlayers() {
    return players;
}

void Game::shuffleDeck() {
    shuffle(deck.begin(), deck.end(), default_random_engine(seed));
}

bool Game::gameOver() {
   bool gameOver = false;
   
   for (int i = 0; i < players.size(); i++) {
       if (players[i]->getGamePoints() >= 80) {
        cout << "Player" << i+1 << " wins!" << endl;
        gameOver = true;
       }
   }
   return gameOver;
}

Card Game::deckAt(int index) {
    return deck.at(index);
}