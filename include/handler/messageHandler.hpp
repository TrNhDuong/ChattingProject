#ifndef MESSAGE_HANDLER_HPP
#define MESSAGE_HANDLER_HPP
#include "handler.hpp"

class MessageHandler: public IHandler {
public:
    MessageHandler() = default;
    ~MessageHandler() = default;

    json process(const json& data) override;
    string type() const override;
};
#endif