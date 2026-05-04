// ioContext.h
#pragma once
#include <boost/asio/io_context.hpp>

namespace core {

class IoContext {
public:
    static boost::asio::io_context& main() {
        static boost::asio::io_context instance;
        return instance;
    }
};

}