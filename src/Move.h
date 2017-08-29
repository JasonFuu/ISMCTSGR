//
// Created by Jason Fu on 8/27/17.
//

#ifndef UNTITLED_MOVE_H
#define UNTITLED_MOVE_H

#include "card.h"

// delineates type of move
enum TYPE {CARD, DECK_DRAW, DISCARD_DRAW, KNOCK, NOKNOCK};

struct Move {
    Move();

    Move(TYPE move_type, card input = NULL);

    card stored_card;
    TYPE type;
};


#endif //UNTITLED_MOVE_H
