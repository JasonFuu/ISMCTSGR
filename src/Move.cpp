//
// Created by Jason Fu on 8/27/17.
//

#include "Move.h"

Move::Move() {}

Move::Move(TYPE move_type, card input) {
    type = move_type;
    stored_card = input;
}