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
    unknown, label, indent, space, number, colon, eol, eof, string /* TODO faire la fonction pour string */
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


template<typename iterator,
         typename starter>
auto start_with (iterator begin,
                 iterator end,
                 starter &&to_contains)
-> decltype(std::optional(begin))
{
    auto begin2 = std::begin(to_contains);
    auto end2 = std::end(to_contains);

    while (begin!=end&&
           begin2!=end2&&
           (*begin).type==*begin2)
    {
        begin++;
        begin2++;

        if (begin==end&&begin2!=end)
            return std::nullopt;
    }

    if (begin2==end2)
        return std::optional(begin);
    else
        return std::nullopt;
}


template<typename iterator>
auto parse_args (iterator begin,
                 iterator end)
{
    bool has_arg = true;

    while (has_arg)
    {
        auto arg = parse_arg(begin, end);
    }

    return 0; // return optional(begin);
}


template<typename iterator>
auto parse_eol (iterator begin,
                iterator end)
{
    return start_with(begin, end, {bml::eol});
}


template<typename iterator>
auto parse_label (iterator begin,
                  iterator end)
{
    return start_with(begin, end, {bml::label, bml::colon});
}


template<typename iterator>
auto parse_block (iterator begin,
                  iterator end)
{
    auto block_name = parse_label(begin, end);
    auto eol = parse_eol(block_name.value(), end);

    if (!eol.has_value())
    {
        auto cmd_arg = parse_args(block_name.value(), end);
        auto cmd_eol = parse_eol(cmd_arg.value(), end);
    }
    else
    {

    }
}
template <typename iterator>
void split_on_eol(iterator begin, iterator end) {
    constexpr auto is_eol = [] (const auto& tk) {return tk.type==bml::eol;};
    const size_t nbeol = std::count_if(begin, end, is_eol);
    std::vector<std::vector<std::decay_t<decltype(*begin)>>> lines(nbeol);

    while (begin != end) {
        begin = std::find_if(begin, end, is_eol);
    }

    std::find_if(begin, end, is_eol);
}

template <typename iterator>
void foreach_line(iterator begin, iterator end) {
    constexpr auto is_eol = [] (const auto& tk) {return tk.type==bml::eol;};
    const size_t nbeol = std::count_if(begin, end, is_eol);
    // pour chaque ligne on veut etablir si celui ci est conforme a une commande
    // ou bien si la ligne est malformée
}

template<typename str_t=std::string>
auto parse (const lexer<str_t> &lex)
{
    auto &&tokens = lex.tokens();
    return parse_block(std::begin(tokens), std::end(tokens));
}


#endif