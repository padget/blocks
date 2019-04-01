#ifndef __BLOCKS_BML_HPP__
#define __BLOCKS_BML_HPP__


#include <string>
#include <type_traits>
#include <variant>
#include <optional>
#include <algorithm>
#include <vector>
#include <list>

namespace mystd
{
    template<class InputIt,
             class UnaryPredicate>
    constexpr InputIt find_if (InputIt first, InputIt last, UnaryPredicate p)
    {
        for (; first!=last; ++first)
        {
            if (p(*first))
            {
                return first;
            }
        }
        return last;
    }
}


template<typename iterator, auto type>
std::optional<std::pair<iterator, decltype(type)>>
detect_colon (iterator begin,
              iterator end)
{
    return (begin!=end&&*begin==':') ?
           std::optional(std::pair(std::next(begin), type)) :
           std::nullopt;
}


template<typename iterator, auto type>
std::optional<std::pair<iterator, decltype(type)>>
detect_indent (iterator begin,
               iterator end)
{
    return (begin!=end&&*begin=='\t') ?
           std::optional(std::pair(std::next(begin), type)) :
           std::nullopt;
}


template<typename iterator, auto type>
std::optional<std::pair<iterator, decltype(type)>>
detect_space (iterator begin,
              iterator end)
{
    return (begin!=end&&*begin==' ') ?
           std::optional(std::pair(std::next(begin), type)) :
           std::nullopt;
}


template<typename iterator, auto type>
std::optional<std::pair<iterator, decltype(type)>>
detect_eol (iterator begin,
            iterator end)
{
    return (begin!=end&&*begin=='\n') ?
           std::optional(std::pair(std::next(begin), type)) :
           std::nullopt;
}


template<typename iterator, auto type>
std::optional<std::pair<iterator, decltype(type)>>
detect_eof (iterator begin,
            iterator end)
{
    return (begin==end) ?
           std::optional(std::pair(std::next(begin), type)) :
           std::nullopt;
}


template<typename iterator, auto type>
std::optional<std::pair<iterator, decltype(type)>>
detect_label (iterator begin,
              iterator end)
{
    auto cursor = begin;

    while (cursor!=end&&
           'a'<=*cursor&&
           *cursor<='z')
    {
        ++cursor;
    }

    return (cursor!=begin) ?
           std::optional(std::pair(cursor, type)) :
           std::nullopt;
}


template<typename iterator, auto type>
std::optional<std::pair<iterator, decltype(type)>>
detect_tabitem (iterator begin,
                iterator end)
{
    return (begin!=end&&*begin=='[') ?
           std::optional(std::pair(std::next(begin), type)) :
           std::nullopt;
}


template<typename iterator, auto type>
std::optional<std::pair<iterator, decltype(type)>>
detect_number (iterator begin,
               iterator end)
{
    auto cursor = begin;

    while (cursor!=end&&
           '0'<=*cursor&&
           *cursor<='9')
    {
        ++cursor;
    }

    return (cursor!=begin) ?
           std::optional(std::pair(cursor, type)) :
           std::nullopt;
}


template<typename iterator,
         typename detector,
         typename ... detectors>
auto detect (iterator begin, iterator end,
             detector d, detectors ... ds)
-> decltype(d(begin, end))
{
    auto results = std::array{d(begin, end), ds(begin, end)...};
    auto has_value = [] (auto const &opt)
    { return opt.has_value(); };
    auto found = mystd::find_if(std::begin(results),
                                std::end(results),
                                has_value);

    if (found!=std::end(results))
        return *found;
    else
        return std::nullopt;
}


enum class bml : int
{
    unknown, label, indent, space, number, colon, eol, eof, tabitem, string /* TODO faire la fonction pour string */
};


template<typename str_t = std::string>
class lexer
{
private:
    using iterator = typename str_t::const_iterator;

    iterator __cursor;
    iterator __end;

public:
    explicit lexer (const str_t &input)
        : __cursor(std::begin(input)),
          __end(std::end(input))
    {}


    struct token
    {
        bml type;
        str_t value;
    };


public:
    token next ()
    {
        auto res = detect(
            __cursor, __end,
            &detect_tabitem<iterator, bml::tabitem>,
            &detect_colon<iterator, bml::colon>,
            &detect_eof<iterator, bml::eof>,
            &detect_eol<iterator, bml::eol>,
            &detect_number<iterator, bml::number>,
            &detect_label<iterator, bml::label>,
            &detect_indent<iterator, bml::indent>,
            &detect_space<iterator, bml::space>);

        bool valued = res.has_value();

        auto &&type = valued ? std::get<1>(res.value()) : bml::unknown;
        auto &&iter = valued ? std::get<0>(res.value()) : std::next(__cursor);
        auto &&value = str_t(__cursor, iter);

        auto tk = token{type, value};
        __cursor = valued ? std::get<0>(res.value()) : std::next(__cursor);
        return tk;
    }


    bool has_next () const
    {
        return __cursor not_eq __end;
    }


    std::vector<token> tokens ()
    {
        std::list<token> tks;

        while (has_next())
            tks.push_back(next());

        auto begin = std::begin(tks);
        auto end = std::end(tks);

        std::list<token> tks2;
        auto end2 = std::remove_if(
            std::begin(tks), std::end(tks),
            [] (const auto &tk)
            { return tk.type==bml::space; });

        std::vector<token> res(
            std::make_move_iterator(std::begin(tks)),
            std::make_move_iterator(end2));
        return res;
    }
};


template<typename iterator>
bool is_not_end (const iterator &begin,
                 const iterator &end)
{
    return begin!=end;
}


template<typename iterator>
bool is_not_eol (const iterator &begin)
{
    return (*begin).type!=bml::eol;
}


template<typename iterator>
bool is_indent (const iterator &begin)
{
    return (*begin).type==bml::indent;
}


template<typename iterator>
bool is_arg (const iterator &begin)
{
    const auto &type = (*begin).type;
    return type==bml::label||
           type==bml::number||
           type==bml::tabitem||
           type==bml::string;
}


template<typename iterator>
bool is_command_name (const iterator &begin)
{
    return (*begin).type==bml::label;
}


struct command
{
    unsigned context;
    std::string name;
    std::vector<std::string> args;
};


template<typename iterator>
std::optional<command>
parse_line (iterator begin, iterator end)
{
    if (is_not_end(begin, end)&&
        is_not_eol(begin))
    {
        unsigned context = 0;
        while (is_not_end(begin, end)&&
               is_indent(begin))
        {
            begin++;
            context++;
        }

        std::string name;

        if (is_not_end(begin, end)&&
            is_command_name(begin))
        {
            name = (*begin).value;
            begin++;
            begin++;
        }

        std::vector<std::string> args;

        while (is_not_end(begin, end)&&
               is_arg(begin))
        {
            args.push_back((*begin).value);
            begin++;
        }

        return {command{
            .context=context,
            .name=name,
            .args=args
        }};
    }
    else
    {
        return std::nullopt;
    }
}


command command_in_error ()
{
    return command{ // todo faire une meilleure gestion des erreurs de syntaxe...
        .name="command in error"
    };
}


template<typename str_t=std::string>
std::vector<command>
parse (lexer<str_t> &lex)
{
    auto &&tokens = lex.tokens();
    auto begin = std::begin(tokens), eol = begin;
    auto end = std::end(tokens);
    std::vector<command> commands;
    const command error = command_in_error();

    while (is_not_end(begin, end))
    {
        while (is_not_end(eol, end)&&
               is_not_eol(eol))
        {
            eol++;
        }

        // between begin and eol we have a line
        auto &&cmd = parse_line(begin, eol);

        commands.push_back(cmd.value_or(error));
        if (is_not_end(eol, end))
            eol++;
        begin = eol;
    }

    return commands;
}


#endif