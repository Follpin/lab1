//MSBuild 17.14.19 (C++23)
#include "stack_analyzer.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>

using namespace std;

constexpr int MIN_CARDS_PER_SUIT = 2;
constexpr int MAX_CARDS_PER_SUIT = 1000;
constexpr int MIN_TOTAL_CARDS = 10;
constexpr int MAX_TOTAL_CARDS = 10000000;

constexpr int EXP_TOTAL_CARDS = 50000;
constexpr int EXP_MIN_K = 2;
constexpr int EXP_MAX_K = 24;
constexpr int EXP_STEP_K = 2;

int main() {
#ifdef _MSVC_LANG
    system("chcp 65001");
#endif

    int cardsPerSuit = 0;
    int totalCards = 0;

    while (true) {
        cout << "Enter number of cards per suit (k >= 2): ";
        if (cin >> cardsPerSuit && cardsPerSuit >= MIN_CARDS_PER_SUIT && cardsPerSuit <= MAX_CARDS_PER_SUIT) {
            break;
        }
        cout << "Invalid input. Please enter an integer between " 
             << MIN_CARDS_PER_SUIT << " and " << MAX_CARDS_PER_SUIT << "." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (true) {
        cout << "Enter total number of cards to deal (n >= 10): ";
        if (cin >> totalCards && totalCards >= MIN_TOTAL_CARDS && totalCards <= MAX_TOTAL_CARDS) {
            break;
        }
        cout << "Invalid input. Please enter an integer between " 
             << MIN_TOTAL_CARDS << " and " << MAX_TOTAL_CARDS << "." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    try {
        StackAnalyzer analyzer(cardsPerSuit, totalCards);
        SimulationResult res = analyzer.analyze();

        cout << "\nResult: " << endl;
        cout << "Total cards dealt: " << totalCards << endl;
        cout << "Total stacks formed: " << res.totalStackCnt << endl;
        cout << "Most frequent stack length: " << res.mostFreqLen << endl;
        cout << "Average stack length: " << fixed << setprecision(3) << res.avgLen << endl;
        cout << "Median stack length: " << fixed << setprecision(3) << res.medLen << endl;

        cout << "\nStack Length Distribution (%) " << endl;
        cout << setw(15) << "Length" << setw(20) << "Percentage (%)" << endl;
        for (const auto& [len, pct] : res.lenPctMap) {
            cout << setw(15) << len << setw(19) << fixed << setprecision(2) << pct << "%" << endl;
        }

        cout << "\nExperimental Study (Dependency on k): " << endl;
        cout << setw(15) << "Cards/Suit (k)" << setw(20) << "Average Length" << setw(20) << "Median Length" << endl;

        for (int testK = EXP_MIN_K; testK <= EXP_MAX_K; testK += EXP_STEP_K) {
            StackAnalyzer expAnalyzer(testK, EXP_TOTAL_CARDS);
            SimulationResult expRes = expAnalyzer.analyze();
            cout << setw(15) << testK 
                 << setw(20) << fixed << setprecision(3) << expRes.avgLen 
                 << setw(20) << fixed << setprecision(3) << expRes.medLen << endl;
        }

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}