#include "minknap_private.h"

State *MinKnap::findState (long wSum, State *firstState, State *lastState) {
    State *midState;

    if (firstState > lastState) {
        panic ("findVect: a set should always have at least one vector");
    }
    if (firstState->weightSum > wSum) {
        return nullptr;
    }
    if (lastState->weightSum <= wSum) {
        return lastState;
    }
    while (lastState - firstState > SYNC) {
        midState = firstState + (lastState - firstState) / 2;
        if (midState->weightSum > wSum) {
            lastState = midState - 1;
        } else {
            firstState = midState;
        }
    }
    while (lastState->weightSum > wSum) {
        lastState--;
    }
    return lastState;
}

void MinKnap::improveSolution (State *state) {
    if (state->weightSum > m_capacity) {
        panic ("improveSolution: weight sum to high");
    }
    if (state->valueSum <= m_currentBestValSum) {
        panic ("improveSolution: not an improved solution");
    }
    m_currentBestValSum = state->valueSum;
    m_currentBestWeightSum = state->weightSum;
    m_currentBestSolVec = state->solVec;
}

int *median (int firstIndex, int lastIndex, long itemCount) {

}


