//
// Created by Jason Fu on 7/22/17.
//

#include "Hand.h"
#include <assert.h>

using namespace std;

Hand::Hand() {
    cards.reserve(11);

    size_index = 0;
}

Hand::Hand(std::vector<card> input) {
    assert(input.size() == 10);
    cards.reserve(11);

    for (int i = 0; i < 10; i++) {
        cards[i] = input[i];
    }
    size_index = 10;
}

Hand::Hand(const Hand &copy) {
    cards = copy.cards;
    size_index = copy.size_index;
}

void Hand::addToHand(card input) {
    cards[size_index] = input;
    size_index++;
}

// returns true if card was discarded, false otherwise
bool Hand::discard(card input) {
    assert(size_index == 11);
    bool match = false;

    // if match found, remove card from hand by moving all cards ahead of it down one slot
    for (int i = 0; i < 11; i++) {
        if (cards[i].sameSuit(input) && cards[i].sameValue(input)) {
            match = true;
            for (int j = i; j < 10; j++) {
                cards[j] = cards[j+1];
            }
        }

    }
    size_index--;
    return match;
}

// const functions dont modify the object on which they are called
std::vector<card> Hand::cardsInHand() const {
    return cards;
}

// returns number of cards in hand
int Hand::cardNumber() const {
    return size_index;
}

std::ostream& operator<< (std::ostream &out, Hand const &hand) {
    for (card input : hand.cardsInHand()) {
        out << input;
    }
    return out;
}
