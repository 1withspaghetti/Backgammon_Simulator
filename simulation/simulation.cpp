#include <stdio.h>
#include <iostream>
#include <cmath>
#include <stdint.h>
#include <unordered_map>
using namespace std;

//#define DEBUG

#define BOARD_SIZE 6
#define MAX_TURNS 24

struct Board {

    uint8_t arr[BOARD_SIZE];
    uint8_t size;

    Board(uint8_t input_arr[BOARD_SIZE]) {
        for (uint8_t i = 0; i < BOARD_SIZE; i++) arr[i] = input_arr[i];
        #ifdef DEBUG
            cout << "Initialized board: " << this << endl;
        #endif
        size = 6;
        shrink();
    }

    Board(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t f) {
        arr[0] = a;
        arr[1] = b;
        arr[2] = c;
        arr[3] = d;
        arr[4] = e;
        arr[5] = f;
        size = 6;
        shrink();
    }

    Board(Board *board) {
        size = board->size;
        for (uint8_t i = 0; i < BOARD_SIZE; i++) arr[i] = board->arr[i];
    }

    void shrink() {
        while (size > 0 && arr[size-1] == 0) size--;
    }

    bool emulate_roll(uint8_t d) {
        if (size == 0) return true;
        if (d >= size) {
            arr[size - 1]--;
            shrink();
            return false;
        } else if (arr[d] > 0) {
            arr[d]--;
            shrink();
            return false;
        } else {
            arr[size-1]--;
            arr[size - 1 - (d + 1)]++;
            shrink();
            return false;
        }
        cerr << "No action could be taken. Roll: " << (int)d << " Board: " << (int)arr[0] << " " << (int)arr[1] << " " << (int)arr[2] << " " << (int)arr[3] << " " << (int)arr[4] << " " << (int)arr[5] << endl;
        return true;
    }

    uint32_t toInt() {
        uint32_t result = 0;
        for (uint8_t i = 0; i < 6; i++) {
            result |= (arr[i] & 0xF) << (i * 4);
        }
        return result;
    }

    friend ostream& operator << (ostream &os, const Board &b) {
        return (os << (int)b.arr[0] << " " << (int)b.arr[1] << " " << (int)b.arr[2] << " " << (int)b.arr[3] << " " << (int)b.arr[4] << " " << (int)b.arr[5] << " (" << (int)b.size << ")");
    }
};

struct ResultsProbability {
    double average;
    double perTurn[MAX_TURNS];
};

struct Results {
    uint64_t turnWins[MAX_TURNS] = {};

    Results() {}

    Results(Results *results) {
        for (uint8_t i = 0; i < MAX_TURNS; i++) turnWins[i] = results->turnWins[i];
    }

    Results(uint64_t initial) {
        turnWins[0] = initial;
    }

    void add(Results *other) {
        for (uint8_t i = 0; i < MAX_TURNS; i++) {
            turnWins[i] += other->turnWins[i];
        }
    }

    void shift(uint64_t wins) {
        for (uint8_t i = MAX_TURNS - 1; i > 0; i--) turnWins[i] = turnWins[i-1];
        turnWins[0] = wins;
    }

    ResultsProbability probPerTurn() {
        ResultsProbability prob;

        double possibilities = 1;
        double prob_acc = 0;
        for (int i = 0; i < MAX_TURNS; i++) {
            if (possibilities > 0) {
                prob.perTurn[i] = (turnWins[i] / possibilities) * (1 - prob_acc);
                prob_acc += prob.perTurn[i];
                possibilities -= turnWins[i];
                possibilities *= 36;
            } else prob.perTurn[i] = 0;
        }

        double avg_total_acc = 0;
        double avg_weight_acc = 0;
        for (int i = 1; i < MAX_TURNS; i++) {
            avg_total_acc += i * prob.perTurn[i];
            avg_weight_acc += prob.perTurn[i];
        }

        prob.average = avg_total_acc / avg_weight_acc;

        return prob;
    }

    double chanceWinAgainst(Results *oppResults) {
        ResultsProbability us = probPerTurn();
        ResultsProbability opp = oppResults->probPerTurn();

        double chance = 0;
        double chanceOpp = 0;
        for (int i = 0; i < MAX_TURNS; i++) {
            chance += us.perTurn[i] * (1 - chanceOpp);
            chanceOpp += opp.perTurn[i];
        };
        return chance;
    }

    uint64_t sum() {
        uint64_t sum = 0;
        for (int i = 0; i < MAX_TURNS; i++) sum += turnWins[i];
        return sum;
    }

    void printProbPerTurn() {
        ResultsProbability us = probPerTurn();
        for (int i = 0; i < MAX_TURNS; i++) {
            cout << "[" << i << "]: " << (us.perTurn[i] * 100) << "% " << endl;
        }
        cout << "Average Turns: " << us.average << endl;
    }

    friend ostream& operator << (ostream &os, const Results &s) {
        return (os << "[" << s.turnWins[0] << " " << s.turnWins[1] << " " << s.turnWins[2] << " " << s.turnWins[3] << " " << s.turnWins[4] << " " << s.turnWins[5] << " " << s.turnWins[6] << " " << s.turnWins[7] << " " << s.turnWins[8] << " " << s.turnWins[9] << " " << s.turnWins[10] << " " << s.turnWins[11] << "]");
    }
};

Board* next_board_state(Board *old, uint8_t roll[2]) {
    Board *board = new Board(old);
    
    if (roll[0] >= roll[1]) {
        if (board->emulate_roll(roll[0])) return board;
        if (board->emulate_roll(roll[1])) return board;
    }
    if (roll[1] >= roll[0]) {
        if (board->emulate_roll(roll[1])) return board;
        if (board->emulate_roll(roll[0])) return board;
    }

    return board;
}

int simulations = 0;
int maxed_out = 0;

unordered_map<uint32_t, Results> cache;

Results *simulate(Board *board, int turns) {

    if (board->size == 0) {
        delete board;
        return new Results(1);
    }

    if (turns >= MAX_TURNS) {
        maxed_out++;
        delete board;
        return new Results();
    }

    
    unordered_map<uint32_t, Results>::iterator result = cache.find(board->toInt());
    if (result != cache.end()) {
        #ifdef DEBUG
        cout << "Found cached value for board: " << *board << " with results: " << result->second << endl;
        #endif
        delete board;
        return new Results(result->second);
    }
    
    simulations++;
    
    Results *simResults = new Results();

    for (uint8_t i = 0; i < 6; i++) {
        for (uint8_t j = 0; j < 6; j++) {
            uint8_t roll[2] = {i, j};

            #ifdef DEBUG
                cout << "Rolling " << (int)roll[0] << " " << (int)roll[1] << " for board " << *board << endl;
            #endif

            Results *results = simulate(next_board_state(board, roll), turns + 1);
            simResults->add(results);
            delete results;
        }
    }

    simResults->shift(0);

    cache.emplace(make_pair(board->toInt(), Results(simResults)));

    #ifdef DEBUG
        cout << "Reached end of rolls for board: " << *board << " results: " << *simResults << " turn: " << turns << endl;
    #endif

    delete board;
    return simResults;
}
