#include <iostream>
#include <string>

#include <env.h>
#include <ioContext.h>

using namespace std;

int main(){

    Env::loadEnvFile(ENV_PATH);

    auto& io_context = core::ioContext::main();

    boost::asio::signal_set signals(io, SIGINT, SIGTERM);
    signals.async_wait([&](auto, auto) {
        io.stop();
    });


    io_context.run()

    return 0;
}