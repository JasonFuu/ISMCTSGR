//
// Created by Jason Fu on 8/23/17.
//

#ifndef UNTITLED_NODE_H
#define UNTITLED_NODE_H

#include <vector>
#include "card.h"

using namespace std;

class Node {
public:
    Node();

    std::vector<card> getUntriedMoves();

private:
    Node parentNode;
    std::vector<Node> children;
    int visits;
    int score;
};


#endif //UNTITLED_NODE_H
