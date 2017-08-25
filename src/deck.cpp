//
// Created by Jason Fu on 7/22/17.
//

#include "deck.h"
#include "card.h"
#include <algorithm>
#include <random>
#include <iostream>
#include <chrono>

deck::deck() {
    size = 52;
    deckarray.reserve(size);

    int index = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 14; j++) {
            card newCard(static_cast<SUIT>(i), static_cast<VALUE>(j));
            deckarray.push_back(newCard);
        }
    }
}

deck::deck(std::vector<card> cards) {
    deckarray = cards;
    size = deckarray.size();
}

deck::deck(const deck &copy) {
    deckarray = copy.deckarray;
    size = copy.size;
}

card deck::draw() {
    card toDeal = deckarray[size];
    size--;
    return toDeal;
}


void deck::shuffle() {
    // seeding
    srand (time(0));

    for (int k = 0; k < 52; k++)
    {
        // Pick a random index from 0 to i
        int i = rand() % 52;
        int j = rand() % 52;

        // Swap arr[i] with the element at random index
        card temp = deckarray[i];
        deckarray[i] = deckarray[j];
        deckarray[j] = temp;
    }
}

int deck::remainingCards() {
    return size;
}

bool deck::isEmpty() {
    return size == 0;
}

std::vector<card> deck::allCards() {
    return deckarray;
}

void deck::print() {
    for (card draw : deckarray) {
        std::cout << draw << endl;
    }
}
