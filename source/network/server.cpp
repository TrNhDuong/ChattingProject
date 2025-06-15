#include "../../include/network/server.hpp"

void Server::do_accept() {
    acceptor_.async_accept(
        [this](beast::error_code ec, tcp::socket socket) {
            if (!ec) {
                std::make_shared<Session>(std::move(socket), sessions_lookup_)->start();
            } else {
                std::cerr << "Accept failed: " << ec.message() << "\n";
            }
            do_accept();
        }
    );
}

void Server::stop() {
    acceptor_.close();
}