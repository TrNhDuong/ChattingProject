#include "../../include/handler/handler.hpp"
#include "../../include/handler/loginHandler.hpp"
#include "../../include/handler/messageHandler.hpp"
#include "../../include/handler/registerHandler.hpp"
#include "../../include/handler/searchHandler.hpp"

shared_ptr<IHandler> HandlerFactory::getTypeRequest(const json& data){
    string type = data["type"];
    if ("login" == type)        return std::make_shared<LoginHandler>();
    else if ("message" == type)   return std::make_shared<MessageHandler>();
    else if ("register" == type) return std::make_shared<RegisterHandler>();
    else if ("search" == type) return std::make_shared<SearchHandler>();
    return nullptr;
};