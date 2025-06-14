#include "../../include/handler/loginHandler.hpp"

string LoginHandler::type() const {
    return "Login Handler";
}

json LoginHandler::process(const json& data){
    json processValue;
    processValue["type"] = "login";
    if (data.contains("username")){
        processValue["username"] = data["username"];
    } else {
        std::cerr << "Login handler fault: data not contain value username\n";
    }
    if (data.contains("pass")){
        string passWord = data["pass"];

        // xử lí lại phần truy vấn database từ mongoDB thì xử lí thêm
        processValue["value"] = "true";
    } else {
        std::cerr << "Login handler fault: data not contain value pass\n";
    }
    return processValue;
}