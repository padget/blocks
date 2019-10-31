#include "command.hpp"

blocks::command::command(const std::string &name,
                         const std::vector<std::string> args)
    : __name{name}, __args{args} {}

blocks::command::command(const std::string &name,
                         const std::initializer_list<std::string> args)
    : __name{name}, __args{args} {}

const std::string &blocks::command::name() const { return __name; }

const std::vector<std::string> &blocks::command::args() const { return __args; }