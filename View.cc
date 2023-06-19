#include "View.h"
#include "iostream"
#include "Player.h"
#include "Card.h"
#include <algorithm>
#include <map>

using namespace std;

string format(const list<Card> &l, bool pile = true) {
    string s = " ";
    for (auto i: l) {
        if (pile) {
            s += i.getCard()[0];
        } else {
            s += i.getCard();
        }
        s += " ";
    }
    return s;
}

View::View(Round* round) : round{round} {
    round->attach(this);
}

bool View::controller(int turn) {
    bool quit = false;
    if (round->isBot(turn)) {
        round->botMove(turn);
    } else {
        string cmd;
        string inputCard;
        bool done = false;
        while(!done) {
            cout << ">";
            if (!(cin >> cmd)) {
                quit = true;
                break;
            }
            if (cmd == "play" || cmd == "discard") {
                cin >> inputCard;
                Card card = Card::stringToCard(inputCard);
                done = (cmd[0] == 'p') ? round->play(card, turn) : round->discard(card, turn);
            } else if (cmd == "deck") {
                round->deck();
            } else if (cmd == "ragequit") {
                round->ragequit(turn);
                done = true;
            } else if (cmd == "quit") {
                quit = true;
                done = true;
            } else {
                cout << "invalid command!" << endl;
            }
        }
    }
    return quit;   
}

void View::update() {
    turn = round->getTurn(false);
    //cout << "Turn " << turn << endl << endl;
    vector<list<Card>> piles = round->getState();
    list<Card> legalPlays = round->legalMoves(turn);
    cout << "Cards on the table:" << endl;
    cout << "Clubs:" << format(piles[1]) << endl;
    cout << "Diamonds:" << format(piles[0]) << endl;
    cout << "Hearts:" << format(piles[2]) << endl;
    cout << "Spades:" << format(piles[3]) << endl;
    cout << "Your Hand:" << format(round->getPlayer(turn)->getHand(), false) << endl;
    cout << "Legal Plays:" << format(legalPlays, false) << endl; 
}
