#ifndef LOGIN_HANDLER_HPP
#define LOGIN_HANDLER_HPP
#include "handler.hpp"

class LoginHandler: public IHandler {
public:
    LoginHandler() = default;
    ~LoginHandler() = default;

    json process(const json& data) override;
    string type() const override;
};
#endif
