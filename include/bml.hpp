#ifndef __BLOCKS_BML_HPP__
#define __BLOCKS_BML_HPP__


#include <string>
#include <type_traits>
#include <variant>
#include <optional>

template<typename char_t>
class char_wrapper
{
private:
    char_t c;

public:
    explicit char_wrapper (char_t c)
        : c(c)
    {}


public:
    bool in (char_t first, char_t end) const
    {
        return first<=c and c<=end;
    }


    bool is (char_t o) const
    {
        return c==o;
    }


    char_wrapper &reset (char_t c)
    {
        this->c = c;
        return *this;
    }
};


template<typename str_t = std::string>
struct token_error
{
    str_t value;
};


template<typename str_t = std::string>
struct token_number
{
    str_t value;
};


template<typename str_t = std::string>
struct token_label
{
    str_t value;
};


template<typename str_t = std::string>
struct token_string
{
    str_t value;
};


template<typename str_t = std::string>
struct token_eol
{
    str_t value;
};


template<typename str_t = std::string>
struct token_eof
{
    str_t value;
};


template<typename str_t = std::string>
struct token_indent
{
    str_t value;
};


template<typename str_t = std::string>
struct token_colon
{
    str_t value;
};


template<typename ... type_t>
struct pack
{
};


template<typename pack_t>
struct __variant_of
{
};


template<
    template<typename ...> typename pack_t,
                           typename ... type_t>
struct __variant_of<pack_t<type_t...>>
{
    using type = std::variant<type_t...>;
};


template<typename pack_t>
using variant_of = typename __variant_of<pack_t>::type;


template<typename str_t>
using tokens = pack<token_error<str_t>,
    token_label<str_t>,
    token_number<str_t>,
    token_colon<str_t>,
    token_eof<str_t>,
    token_eol<str_t>,
    token_indent<str_t>,
    token_string<str_t>>;


template<typename str_t>
using bml_token = variant_of<tokens<str_t>>;


template<
    template<typename ...> typename pack_t,
                           typename ... type_t>
constexpr size_t pack_size (pack_t<type_t...> const &)
{
    return sizeof...(type_t);
}


template<typename pack_t>
struct first
{
};

template<
    template<
    typename,
    typename ...>
    typename pack_t,
    typename first_t,
    typename ... next_t>
struct first<pack_t<first_t, next_t...>>
{
    using type = first_t;
};


template<typename pack_t>
struct tail
{
};


template<
    template<
    typename,
    typename ...>
    typename pack_t,
    typename first_t,
    typename ... next_t>
struct tail<pack_t<first_t, next_t...>>
{
    using type = pack_t<next_t...>;
};


template<
    typename str_t,
    typename pack_t,
    typename iterator>
std::optional<bml_token<str_t>> for_each_token_type (iterator begin, iterator end)
{
    constexpr auto size = pack_size(std::declval<pack_t>());
    if constexpr (size>1)
    {
        using first_t = typename first<pack_t>::type;
        constexpr auto detector = first_t();
        std::optional<bml_token<str_t>> detected = detector.try_detect(begin, end);

        if (detected.has_value())
        {
            return detected;
        }
        else
        {
            return for_each_token_type<tail<pack_t>>(begin, end);
        }
    }
    else if constexpr (size==1)
    {
        constexpr auto token_type = typename first<pack_t>::type();
        return token_type.try_detect(begin, end);
    }
}


template<typename str_t = std::string>
class lexer
{
private:
    using iterator = typename str_t::iterator;

    iterator __cursor;
    iterator __end;

public:
    explicit lexer (iterator cursor, iterator end)
        : __cursor{cursor},
          __end{end}
    {}


public:
    bml_token<str_t> token ()
    {

        iterator cursor = __cursor;

        if (__cursor==__end)
        {
            return token_eof<str_t>{{__cursor, __end}};
        }
        else if (is_colon())
        {
            return token_colon<str_t>{{cursor, __cursor}};
        }
        else if (is_label())
        {
            return token_label<str_t>{{cursor, __cursor}};
        }
        else if (is_number())
        {
            return token_number<str_t>{{cursor, __cursor}};
        }
        else if (is_string())
        {
            return token_string<str_t>{{cursor, __cursor}};
        }
        else if (is_indent())
        {
            return token_indent<str_t>{{cursor, __cursor}};
        }
        else if (is_eol())
        {
            return token_eol<str_t>{{cursor, __cursor}};
        }
        else
        {
            __cursor++;
            return token_error<str_t>{{cursor, __cursor}};
        }
    }


public:
    bool has_next () const
    {
        return __cursor not_eq __end;
    }


private:
    bool is_label ()
    {

        auto cursor = __cursor;
        char_wrapper<char> c(*cursor);

        while (cursor not_eq __end and
               c.reset(*cursor).in('a', 'z'))
        {
            cursor++;
        }

        if (cursor not_eq __cursor)
        {
            __cursor = cursor;
            return true;
        }
        else
        {
            return false;
        }
    }


    bool is_colon ()
    {
        auto res = char_wrapper<char>(*__cursor).is(':');

        if (res)
        {
            __cursor++;
            return true;
        }
        else
        {
            return false;
        }
    }


    bool is_number ()
    {

        auto cursor = __cursor;
        char_wrapper<char> c(*cursor);

        while (cursor not_eq __end and
               c.reset(*cursor).in('0', '9'))
        {
            cursor++;
        }

        if (cursor not_eq __cursor)
        {
            __cursor = cursor;
            return true;
        }
        else
        {
            return false;
        }
    }


    bool is_string ()
    {
        iterator cursor = __cursor;
        auto c = char_wrapper<char>(*cursor);

        if (c.is('"'))
        {
            cursor++;

            while (not c.reset(*cursor).is('"'))
            {
                cursor++;
            }

            if (c.reset(*cursor).is('"'))
            {
                cursor++;
                __cursor = cursor;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }


    bool is_indent ()
    {
        auto res = char_wrapper<char>(*__cursor).is(' ');

        if (res)
        {
            __cursor++;
            return true;
        }
        else
        {
            return false;
        }
    }


    bool is_eol ()
    {
        auto res = char_wrapper<char>(*__cursor).is('\n');

        if (res)
        {
            __cursor++;
            return true;
        }
        else
        {
            return false;
        }
    }
};


class parser
{

};

#endif