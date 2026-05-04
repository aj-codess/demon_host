#include <iostream>
#include <string>
#include <env.h>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>

#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>

namespace Env {

    static bool loaded = false;

    // Trim helper
    static std::string trim(std::string s) {
        s.erase(0, s.find_first_not_of(" \t\n\r"));
        s.erase(s.find_last_not_of(" \t\n\r") + 1);
        return s;
    }

    // Read .env file
    void loadEnvFile(const std::string& path) {
        if (loaded) return;

        std::ifstream file(path);
        if (!file.is_open()) return;

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;

            auto eqPos = line.find('=');
            if (eqPos == std::string::npos) continue;

            std::string key = trim(line.substr(0, eqPos));
            std::string value = trim(line.substr(eqPos + 1));

            setenv(key.c_str(), value.c_str(), 1);
        }

        loaded = true;
    }

    // Read environment variable OR default
    std::string get(const std::string& key, const std::string& def) {
        const char* val = std::getenv(key.c_str());
        return val ? std::string(val) : def;
    }

}