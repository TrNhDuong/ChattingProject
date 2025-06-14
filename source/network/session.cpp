#include "../../include/network/session.hpp"

void Session::start() {
    auto self = shared_from_this();
    ws_.async_accept([self](beast::error_code ec){
        if (ec){
            std::cerr << "Websocket handshaking failed: " << ec.message() << "\n";
            return;
        } else {
            std::cout << "New Websocket connection established\n";
            self->do_read();
        }
    });
}

void Session::do_read(){
    auto self = shared_from_this();
    ws_.async_read(buffer_, [self](beast::error_code ec, std::size_t ){
        if (ec == websocket::error::closed) {
            std::cout << "Client disconnected\n";
            self->sessions_lookup_.erase(self->username_);
            return;
        }
        if (ec){
            std::cerr << "Read error " << ec.message() << "\n";
            self->do_close();
        }
        // Get message from client in string type
        string message = beast::buffers_to_string(self->buffer_.data());
        // Convert to json form
        json j = json::parse(message);

        // use Factory Designpattern to classify process data type
        shared_ptr<IHandler> requestMachine = HandlerFactory::getTypeRequest(j);

        string typeRequest = requestMachine->type();

        //Process data to appropriate form to deliver
        json  data = requestMachine->process(j);

        //Sender data to client
        self->do_deliver(typeRequest, data, j);
             
        std::cout << "Received: " << message << "\n";
        // self->do_write(message); // Gửi lại tin nhắn
        self->buffer_.consume(self->buffer_.size());
        self->do_read();
    });
}

void Session::deliver_msg(const json& message){
    auto self = shared_from_this();
    string msg = message.dump();
    ws_.async_write(
        net::buffer(msg),
        [self](beast::error_code ec, std::size_t){
            if (ec){
                std::cerr << "Send message error: " << ec.message() << "\n";
                self->do_close();
            }
        }
    );
}

void Session::do_deliver(const string& type, const json& message, const json& j) {
    auto self = shared_from_this();
    if ("Message Handler" == type){
        string receiver = message["receiver"];
        cntMsg++;
        if (sessions_lookup_.find(receiver) != sessions_lookup_.end()){
            sessions_lookup_[receiver]->deliver_msg(message);
        }
    } else if ("Login Handler" == type){
        if (message["value"] == "true"){
            string username = j["username"];
            username_ = username;
            sessions_lookup_.insert({username, self});
        }
        self->deliver_msg(message);
    } else if ("Register Handler" == type){
        //Nothing to do
    } else if ("Search Handler" == type){
        self->deliver_msg(message);
    }
}

void Session::do_close(){
    auto self = shared_from_this();
    ws_.async_close(websocket::close_code::normal,
        [self](beast::error_code ec) {
            if (ec) {
                std::cerr << "Close error: " << ec.message() << "\n";
            }
        });
}