#include "EventParser.h"

#include <regex>
#include <fstream>
#include <string>
#include <iostream>
#include "EventFactory.h"

class IAddProjectile;

struct EventParser::WaveEntry {
    bool wait;
    int id;
    int countdown;
};

void EventParser::parse(const std::filesystem::path path) {
    current_file_ = path;
    std::cout << current_file_;
    std::regex pattern(R"(^wait=(0|1),\s*id=([0-9a-fA-F]+?),\s*cd=(\d+)\s*$)");
    std::smatch matches;
    std::vector<WaveEntry> parsed_data;
    std::string line;
    std::ifstream infile(path);
    while (std::getline(infile, line)) {
        if (line.empty() || line.find_first_not_of(" \t\n\r") == std::string::npos) {
            continue;
        }

        std::smatch matches;

        if (std::regex_search(line, matches, pattern)) {
            if (matches.size() == 4) {
                WaveEntry entry;
                entry.wait = std::stoi(matches[1].str());
                entry.id = std::stoul(matches[2].str(), nullptr, 16);
                entry.countdown = std::stoi(matches[3].str());
                parsed_data.push_back(entry);
            }
        }
        else {
            std::cerr << "Warning: Line did not match expected format: '" << line << "'" << std::endl;
        }
    }

    for (const auto& entry : parsed_data) {
        event_factory_.createEvent(entry.id, entry.wait, entry.countdown);
    }

    return;
}

EventParser::EventParser(IProjectileManager& projectiles, IEventManager& event_manager) : event_factory_(projectiles, event_manager) {
    auto directory_path = std::filesystem::path("./event_dir");
    if (std::filesystem::is_directory(directory_path)) {
        for (auto file : std::filesystem::directory_iterator(directory_path)) {
            files_.push_back(file.path());
        }
        std::sort(files_.begin(), files_.end(), [](std::filesystem::path& file1, std::filesystem::path& file2) {
            int i = 0;
            while (file1.c_str()[0] != 0 and file2.c_str()[i] != 0) {
                if (file1.c_str()[i] > file2.c_str()[i])
                    return false;
                i++;
            }
            return true;
            });
    };

}

void EventParser::load(unsigned int file_number){
    if (file_number >= files_.size()) {
        return;
    }
    parse(files_[file_number]);
}

const std::filesystem::path& EventParser::getPath() {
    return current_file_;
}