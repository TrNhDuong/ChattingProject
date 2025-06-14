#include "../../include/handler/registerHandler.hpp"

string RegisterHandler::type() const {
    return "Register Handler";
}

json RegisterHandler::process(const json& data){
    json processValue;
    string username, password;\

    processValue["type"] = "register";
    processValue["value"] = "true";

    if (data.contains("username")){
        username = data["username"];
    } else {
        std::cerr << "Login handler fault: data not contain value username\n";
    }
    if (data.contains("pass")){
        password = data["pass"];
    } else {
        std::cerr << "Login handler fault: data not contain value pass\n";
    }
    return processValue;
}