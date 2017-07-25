//
// Created by Jason Fu on 7/22/17.
//

#include "DiscardPile.h"
#include "card.h"
#include <assert.h>

DiscardPile::DiscardPile() {
    size = 0;
}

card DiscardPile::draw() {
    assert(size > 0);
    size--;
    return discards[size];
}

void DiscardPile::discard(card input) {
    discards[size] = input;
    size++;
}

int DiscardPile::cardsInPile() {
    return size;
}

bool DiscardPile::isEmpty() {
    return size == 0;
}

card DiscardPile::cardOnTop() {
    assert(size > 0);
    return discards[size-1];
}