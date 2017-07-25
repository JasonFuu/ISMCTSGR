//
// Created by Jason Fu on 7/20/17.
//

#include "card.h"
#include <iostream>
using namespace std;

// default constructor
card::card() {
}

// parameter constructor
card::card(SUIT s, VALUE v) {
    suit = s;
    value = v;
}

// checks two cards for suit equality
bool card::sameSuit(const card &that) {
    return (suit == that.suit);
}

// checks two cards for value equality
bool card::sameValue(const card &that) {
    return(value == that.value);
}

const string card::toString() const {
    string valuestr;
    switch(value) {
        case TWO:
            valuestr =  "TWO";
            break;
        case THREE:
            valuestr = "THREE";
            break;
        case FOUR:
            valuestr = "FOUR";
            break;
        case FIVE:
            valuestr = "FIVE";
            break;
        case SIX:
            valuestr = "SIX";
            break;
        case SEVEN:
            valuestr = "SEVEN";
            break;
        case EIGHT:
            valuestr = "EIGHT";
            break;
        case NINE:
            valuestr = "NINE";
            break;
        case TEN:
            valuestr = "TEN";
            break;
        case JACK:
            valuestr = "JACK";
            break;
        case QUEEN:
            valuestr = "QUEEN";
            break;
        case KING:
            valuestr = "KING";
            break;
        case ACE:
            valuestr = "ACE";
            break;
    }

    string suitstr;

    switch(suit) {
        case HEARTS:
            suitstr = "HEARTS";
            break;
        case SPADES:
            suitstr = "SPADES";
            break;
        case CLUBS:
            suitstr = "CLUBS";
            break;
        case DIAMONDS:
            suitstr = "DIAMONDS";
            break;
    }
    return valuestr + " of " + suitstr;
}

std::ostream& operator<< (std::ostream &out, card const &card) {
    return out << card.toString();
}