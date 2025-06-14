#ifndef SESSION_HPP
#define SESSION_HPP
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>

#include "../handler/handler.hpp"

namespace beast = boost::beast;
namespace websocket = beast::websocket;
namespace net = boost::asio;
using tcp = net::ip::tcp;
using std::string;
using std::unordered_map;
using std::vector;
using std::shared_ptr;

class Session : public std::enable_shared_from_this<Session> {
private:
    websocket::stream<tcp::socket> ws_;
    beast::flat_buffer buffer_;
    unordered_map<string, std::shared_ptr<Session>>& sessions_lookup_;
    string username_;
    int cntMsg;
public:
    Session(tcp::socket socket, unordered_map<string, std::shared_ptr<Session>>& sessionLookup) 
    : ws_(std::move(socket)), sessions_lookup_(sessionLookup) {
        websocket::stream_base::timeout opt{
            std::chrono::seconds(30), // Time limit for handshaking
            std::chrono::seconds(60), // Thời gian idle
            true // Không dùng ping/pong tự động
        };
        ws_.set_option(opt);
        cntMsg = 0;
    }
    // Start of session to communicate to client
    void start();

    // Read data from client
    void do_read();

    //Function to deliver to client
    void deliver_msg(const json& message);

    //Process data and type of data
    void do_deliver(const string& type, const json& message, const json& j);

    // Close the sesison if not true
    void do_close();
};
#endif