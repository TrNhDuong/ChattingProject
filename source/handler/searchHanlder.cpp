#include "../../include/handler/searchHandler.hpp"

string SearchHandler::type() const {
    return "Search Handler";
}

json SearchHandler::process(const json& data){
    json processValue;
    processValue["type"] = "search";
    if (data.contains("username")){
        processValue["username"] = data["username"];
    } else {
        std::cerr << "Login handler fault: data not contain value username\n";
    }
    // Process query data
    // ...
    processValue["value"] = "true";
    return processValue;
}