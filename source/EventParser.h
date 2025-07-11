/// @file EventParser.h
/// @brief declares the EventParser class responsible for reading stage files.
#pragma once
#include <filesystem>
#include <vector>
#include "EventFactory.h"

// forward declarations
class IProjectileManager;
class IEventManager;

/// @brief Parses event definition files and creates corresponding game events.
/// This class is responsible for reading structured event data from files,
/// interpreting it, and using an EventFactory to instantiate and enqueue
/// these events into the game's event system.
class EventParser {
private:
    /// @brief The path the last file parsed.
    std::filesystem::path current_file_;

    /// @brief Internal structure to hold parsed data for a single event entry from a file.
    /// Represents one line/entry in an event definition file.
    struct WaveEntry;

    /// @brief An instance of EventFactory used to create game events based on parsed data.
    EventFactory event_factory_;
    
    /// @brief A collection of file paths found in the event directory, representing different levels.
    std::vector<std::filesystem::path> files_;

    /// @brief Parses a single event definition file and creates events from its content.
    /// Reads lines from the specified file, applies a regex pattern to extract event parameters
    /// (wait, id, countdown), and then uses the internal EventFactory to create and enqueue
    /// these events.
    /// @param path - the path to the event definition file to parse.
    void parse(const std::filesystem::path path);
public:
    /// @brief Constructs an EventParser.
    /// This constructor initializes the internal EventFactory and populates the list of event files
    /// by iterating through a predefined directory (e.g., "./event_dir").
    /// @param projectiles - a reference to the IProjectileManager interface of the ProjectileManager class, passed to the EventFactory.
    /// @param event_manager - a reference to the IAddEvent interface of the EventManager class, passed to the EventFactory and used to enqueue events.
    EventParser(IProjectileManager& projectiles, IEventManager& event_manager);

    /// @brief Loads events from a specific event definition file by its index.
    /// This method retrieves a file path from the internally stored list of event files
    /// based on the given index, and then calls parse() to process its contents.
    /// If the file_number is out of bounds, no action is taken.
    /// @param file_number - the zero-based index of the event file to load from the discovered files.
    void load(unsigned int file_number);

    /// @brief The getter of current_file_.
    /// @return Returns a const reference to current_file_ path.
    const std::filesystem::path& getPath();
};