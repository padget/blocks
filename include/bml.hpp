#ifndef __BLOCKS_BML_HPP__
#define __BLOCKS_BML_HPP__


#include <string>
#include <type_traits>


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


template<
    typename enum_t,
    typename str_t = std::string>
class token
{
    static_assert(std::is_enum_v<enum_t>);

private:
    enum_t __type;
    str_t __value;

public:
    explicit token (typename str_t::iterator begin,
                    typename str_t::iterator end,
                    enum_t type)
        : __type(type),
          __value(begin, end)
    {}


    explicit token (enum_t type)
        : __type(type)
    {}


    token (token &&other)
        : __type(std::move(other.__type)),
          __value(std::move(other.__value))
    {}


    bool operator== (const token &other) const
    {
        return this==&other or
               this->__type==other.__type;
    }


    bool operator!= (const token &other) const
    {
        return !this->operator==(other);
    }


public:
    const str_t &value () const
    {
        return __value;
    }


    str_t &value ()
    {
        return __value;
    }


public:
    const enum_t &type () const
    {
        return __type;
    }


    enum_t &type ()
    {
        return __type;
    }
};


template<typename str_t = std::string>
class lexer
{
public:
    enum class token_type : int
    {
        colon,
        label,
        number,
        string,
        indent,
        eof,
        eol,
        error
    };

    using tk = ::token<token_type, str_t>;

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
    tk token ()
    {

        iterator cursor = __cursor;

        if (__cursor==__end)
        {
            return tk(cursor, __cursor, token_type::eof);
        }
        else if (is_colon())
        {
            return tk(cursor, __cursor, token_type::colon);
        }
        else if (is_label())
        {
            return tk(cursor, __cursor, token_type::label);
        }
        else if (is_number())
        {
            return tk(cursor, __cursor, token_type::number);
        }
        else if (is_string())
        {
            return tk(cursor, __cursor, token_type::string);
        }
        else if (is_indent())
        {
            return tk(cursor, __cursor, token_type::indent);
        }
        else if (is_eol())
        {
            return tk(cursor, __cursor, token_type::eol);
        }
        else
        {
            __cursor++;
            return tk(token_type::error);
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