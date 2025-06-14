#include "../include/network/server.hpp"

int main(int argc, char* argv[]) {
    try {
        short port = (argc > 1) ? std::stoi(argv[1]) : 1234;
        net::io_context ioc;
        std::shared_ptr<Server> server = std::make_shared<Server>(ioc, port);
        std::cout << "Server is running on port " << port << "\n";

        // Xử lý tín hiệu để dừng server
        net::signal_set signals(ioc, SIGINT, SIGTERM);
        signals.async_wait([&](beast::error_code, int) {
            server->stop();
            ioc.stop();
        });

        ioc.run();
    } catch (std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
    }
    return 0;
}