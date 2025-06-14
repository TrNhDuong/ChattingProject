#include "../../include/handler/messageHandler.hpp"

string MessageHandler::type() const {
    return "Message Handler";
}

json MessageHandler::process(const json& data){
    json processValue;
    processValue["type"] = "message";
    if (data.contains("sender")){
        processValue["sender"] = data["sender"];
    } else {
        std::cerr << "Message handler fault: data not contain value sender\n";
    }
    if (data.contains("receiver")){
        processValue["receiver"] = data["receiver"];
    } else {
        std::cerr << "Message handler fault: data not contain value receiver\n";
    }
    if (data.contains("content")){
        processValue["content"] = data["content"];
    } else {
        std::cerr << "Message handler fault: data not contain value content\n";
    }
    if (data.contains("time")){
        processValue["time"] = data["time"];
    } else {
        std::cerr << "Message handler fault: data not contain value time\n";
    }
    return processValue;
}