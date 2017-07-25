//
// Created by Jason Fu on 7/22/17.
//

#include "deck.h"
#include "card.h"
#include <algorithm>
#include <iostream>

deck::deck() {
    size = 52;
    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 14; j++) {
            card newCard(static_cast<SUIT>(i), static_cast<VALUE>(j));
            deckarray[index++] = newCard;
        }
    }
}

card deck::draw() {
    card toDeal = deckarray[size];
    size--;
    return toDeal;
}

void deck::shuffle() {
    random_shuffle(std::begin(deckarray), std::end(deckarray));
}

int deck::remainingCards() {
    return size;
}

bool deck::isEmpty() {
    return size == 0;
}

void deck::print() {
    for (card draw : deckarray) {
        std::cout << draw << endl;
    }
}
