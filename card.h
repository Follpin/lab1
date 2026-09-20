#pragma once

#include <compare>
#include <string>

struct Card {
    int rank;
    int suit;

    std::strong_ordering operator<=>(const Card& other) const;
    bool operator==(const Card& other) const;

    std::string toString() const;
};