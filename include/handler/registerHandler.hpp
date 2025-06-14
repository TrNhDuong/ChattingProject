#ifndef REGISTER_HANDLER_HPP
#define REGISTER_HANDLER_HPP
#include "handler.hpp"

class RegisterHandler: public IHandler {
public:
    RegisterHandler() = default;
    ~RegisterHandler() = default;

    json process(const json& data) override;
    string type() const override;
};
#endif
