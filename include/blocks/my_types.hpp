#ifndef __cmdl_mytypes_hpp__
#define __cmdl_mytypes_hpp__

#include "std.hpp"
#include "basic_types.hpp"

namespace blocks::cmdl
{
    enum class verbosity
    {
        v,
        vv,
        vvv,
        vvvv
    };

    struct params
    {
        bool compile = false;
        bool execute = false;
        bool help = false;
        bool stats = false;
        bool version = false;

        verbosity verbose = verbosity::v;

        str_t file;
    };
} // namespace blocks::cmdl

namespace blocks::cmdl::specification
{
    inline str_t to_string(const verbosity &t)
    {
        switch (t)
        {
        case verbosity::v:
            return "v";
        case verbosity::vv:
            return "vv";
        case verbosity::vvv:
            return "vvv";
        case verbosity::vvvv:
            return "vvvv";
        }

        return "";
    }

    template <>
    inline bool str_convertible<verbosity>(const str_t &s)
    {
        return s == "v" or s == "vv" or s == "vvv" or s == "vvvv";
    }
} // namespace blocks::cmdl::specification

#endif