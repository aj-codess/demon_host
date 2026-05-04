#pragma once

#include <string>
#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>

namespace Env {
    void loadEnvFile(const std::string& path);
    std::string get(const std::string& key, const std::string& def = "");
}