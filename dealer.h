#pragma once

#include "card.h"
#include <vector>
#include <random>
#include <cstddef>

class Dealer {
private:
    int cardsPerSuit;
    std::vector<Card> deck;
    std::size_t currentIdx;
    std::mt19937 rng;

    void shuffleDeck();

public:
    explicit Dealer(int cardsPerSuit);
    Card operator()();
};