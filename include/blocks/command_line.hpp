#ifndef __command_line_hpp__
#define __command_line_hpp__

#include <string>
#include <map>
#include <vector>
#include <any>

namespace blocks::cmdl
{
  template <typename from_t, typename type_t>
  type_t convert(const from_t &src);

  struct argument
  {
    std::string longname;
    std::string shortname;
    std::string documentation;

    bool required = false;
    bool valueable = true;

    std::string default_value;
  };

  template <typename type_t>
  class argument_builder;

  template <typename type_t>
  argument_builder<type_t> expect(
      const std::string &longname,
      const std::string &shortname)
  {
    cmdl::argument_builder<type_t> builder;

    builder.arg.longname = longname;
    builder.arg.shortname = shortname;
    builder.arg.valueable = true;

    return builder;
  }

  template <>
  cmdl::argument_builder<bool>
  cmdl::expect<bool>(
      const std::string &longname,
      const std::string &shortname);

  template <typename type_t>
  class argument_builder
  {
    argument arg;

  public:
    argument_builder<type_t> &
    default_value(type_t &&val)
    {
      arg.default_value = std::move(val);
      return *this;
    }

    argument_builder<type_t> &
    default_value(const type_t &val)
    {
      arg.default_value = convert<type_t, std::string>(val);
      return *this;
    }

    argument_builder<type_t> &
    required(bool req)
    {
      arg.required = req;
      return *this;
    }

    argument_builder<type_t> &
    documentation(const std::string &doc)
    {
      arg.documentation = doc;
      return *this;
    }

    argument build()
    {
      return arg;
    }

    friend argument_builder<type_t> expect<type_t>(
        const std::string &longname,
        const std::string &shortname);
  };

  struct specification
  {
    std::vector<argument> arguments;
  };

  class specification_builder
  {
    specification specs;

  public:
    specification_builder &arg(const argument &);
    specification build();
  };

  specification_builder specify();

  struct technical_parser_exception : public std::exception
  {
    const char *what() const throw();
  };

  struct parser_results
  {
    std::map<std::string, std::string> m;

    int count(std::string_view longname);

    template <typename type_t>
    type_t extract(const std::string &longname)
    {
      try
      {
        const std::string &value = m.at(longname);

        if (!value.empty())
          return convert<type_t>(value);
        else
          throw technical_parser_exception();
      }
      catch (std::exception &e)
      {
        throw technical_parser_exception();
      }
    }

    template <typename type_t>
    void fill(type_t &to_fill)
    {
    }
  };

  class parser;

  parser from(const specification &specs);

  class parser
  {
    specification specs;

  public:
    parser_results parse(int argc, char **argv);

    friend parser from(const specification &specs);

  private:
    parser_results init_default_results();
  };

} // namespace blocks::cmdl

namespace blocks::cmdl
{
  argument_builder<bool> abool(
      const std::string &longname,
      const std::string &shortname);

  argument_builder<int> aint(
      const std::string &longname,
      const std::string &shortname);

  argument_builder<long long> allint(
      const std::string &longname,
      const std::string &shortname);

  argument_builder<std::string> astring(
      const std::string &longname,
      const std::string &shortname);

} // namespace blocks::cmdl

namespace blocks::cmdl
{
  enum class verbosity
  {
    v,
    vv,
    vvv,
    vvvv
  };

  struct command_line_params
  {
    bool compile = false;
    bool execute = false;
    bool help = false;
    bool stats = false;
    bool version = false;

    verbosity verbose = verbosity::v;

    std::string file;
  };

  struct command_line
  {
    command_line_params params;
  };

} // namespace blocks::cmdl

#endif