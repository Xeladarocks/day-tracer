#pragma once
#ifndef UTIL_H
#define UTIL_H

using namespace std;

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <string>
#include <random>
#include <memory>

struct xorshift_engine {
    using result_type = uint32_t;

    uint32_t state;

    xorshift_engine() {
        state = 0x1234567;
    }

    xorshift_engine(uint32_t seed) {
        if (seed == 0)
            seed++;
        state = seed;
    }

    const uint32_t min() {
        return 1;
    }

    const uint32_t max() {
        return 0xffffffff;
    }

    uint32_t operator()() {
        state ^= state << 13;
        state ^= state >> 17;
        state ^= state << 5;
        return state;
    }
};

static thread_local std::uniform_real_distribution<double> dist(0.0f, 1.0f);
static thread_local std::random_device rd;
static thread_local xorshift_engine eng(rd());

static double randomDouble() {
    return dist(eng);
}

#endif