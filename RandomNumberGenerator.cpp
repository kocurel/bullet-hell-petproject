#pragma once
#include "RandomNumberGenerator.h"
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <mutex>

RandomNumberGenerator& RandomNumberGenerator::getInstance() {
    static RandomNumberGenerator instance;
    return instance;
}

int RandomNumberGenerator::uniformRange(const int lower_bound, const int upper_bound) {
    if (lower_bound > upper_bound) {
        throw std::runtime_error("Error: lower_bound cannot be greater than upper_bound.");
    }
    std::lock_guard<std::mutex> lock(mtx_);
    std::uniform_int_distribution<int> dist(lower_bound, upper_bound);
    return dist(engine_);
}

float RandomNumberGenerator::uniformRange(const float lower_bound, const float upper_bound) {
    if (lower_bound > upper_bound) {
        throw std::runtime_error("Error: lower_bound cannot be greater than upper_bound.");
    }
    std::lock_guard<std::mutex> lock(mtx_);
    std::uniform_real_distribution<float> dist(lower_bound, upper_bound);
    return dist(engine_);
}

RandomNumberGenerator::RandomNumberGenerator() {
    engine_.seed((unsigned)std::chrono::system_clock::now().time_since_epoch().count());
}