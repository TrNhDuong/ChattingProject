#ifndef SEARCH_HANDLER_HPP
#define SEARCH_HANDLER_HPP
#include "handler.hpp"

class SearchHandler: public IHandler {
public:
    SearchHandler() = default;
    ~SearchHandler() = default;

    json process(const json& data) override;
    string type() const override;
};
#endif