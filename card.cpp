#include "card.h"
#include <format>

// Compares cards by rank using three-way comparison
std::strong_ordering Card::operator<=>(const Card& other) const {
    return rank <=> other.rank;
}

bool Card::operator==(const Card& other) const {
    return rank == other.rank;
}

// Returns formatted string (rank and suit)
std::string Card::toString() const {
    const char* suitNames[] = {"Hearts", "Diamonds", "Spades", "Clubs"};
    std::string suitStr = (suit >= 0 && suit < 4) ? suitNames[suit] : "Unknown";
    return std::format("[Rank: {}, Suit: {}]", rank, suitStr);
}