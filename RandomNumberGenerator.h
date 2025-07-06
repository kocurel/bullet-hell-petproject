/// @file RandomNumberGenerator.h
/// @brief declares the RandomNumberGenerator singleton class
#include <random>
#include <mutex>

/// @brief Generates random numbers.
/// Designed as a thread safe Singleton to ensure only
/// instance of it exists globally.
/// RandomNumberGenerator uses default_random_engine
/// seeded with current time.
class RandomNumberGenerator {
public:
    /// @brief Singleton instance.
    /// @return Returns the single instance of the RandomNumberGenerator
    static RandomNumberGenerator& getInstance();

    /// @brief Generates a random int bounded by two integer values (inclusive).
    /// @details Method is made thread-safe with the use of mtx_
    /// @param lower_bound The lower bound for generated number.
    /// @param upper_bound The upper bound for generated number.
    /// @return Returns the newly generated int.
    /// @sa RandomNumberGenerator::mtx_
    int uniformRange(const int lower_bound, const int upper_bound);

    /// @brief Generates a random float bounded by two floating point values (inclusive).
    /// @details Method is made thread-safe with the use of mtx_
    /// @param lower_bound The lower bound for generated number.
    /// @param upper_bound The upper bound for generated number.
    /// @return Returns the newly generated float.
    /// @sa RandomNumberGenerator::mtx_
    float uniformRange(const float lower_bound, const float upper_bound);

    /// @brief Prevents copying of the Singleton instance. 
    RandomNumberGenerator(const RandomNumberGenerator&) = delete;
    
    /// @brief Prevents assignment of the Singleton instance. 
    RandomNumberGenerator& operator=(const RandomNumberGenerator&) = delete;
private:
    /// @brief The default constructor.
    /// Initializes default_random_engine with the time.
    RandomNumberGenerator();
    /// @brief The default_random_engine.
    std::default_random_engine engine_;
    /// @brief Mutex to protect access to engine_
    std::mutex mtx_;
};

