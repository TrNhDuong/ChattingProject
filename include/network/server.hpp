#ifndef SERVER_HPP
#define SERVER_HPP
#include "session.hpp"

class Server : public std::enable_shared_from_this<Server> {
private:
    tcp::acceptor acceptor_;
    unordered_map<string, std::shared_ptr<Session>> sessions_lookup_;
public:
    Server(net::io_context& ioc, short port)
        : acceptor_(ioc, tcp::endpoint(tcp::v4(), port)) {
        do_accept();
    }

    void do_accept();

    void stop();
};
#endif