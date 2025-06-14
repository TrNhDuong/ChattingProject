#ifndef HANDLER_HPP
#define HANDLER_HPP
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <memory>
#include <nlohmann/json.hpp>
using std::string;
using std::vector;
using std::shared_ptr;
using json = nlohmann::json;

class IHandler{
public:
    IHandler() = default;
    virtual ~IHandler() = default;

    virtual json process(const json& data) = 0;
    virtual string type() const = 0;
};

class HandlerFactory {
public:
    static shared_ptr<IHandler> getTypeRequest(const json& data);
};
#endif