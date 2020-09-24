#ifndef __libs_log_hpp__
#define __libs_log_hpp__

#include "string.hpp"
#include "algorithm.hpp"
#include <iostream>

#define ENUM_TO_STRING(enum) "enum"

namespace libs::log
{
  enum class logger_level
  {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    FATAL
  };

  template <
      logger_level lvl>
  struct logger
  {
  };

  template <
      logger_level lvl,
      typename char_t>
  void log(
    const basic_string<char_t> &);

  template <typename char_t>
  void trace(
    const basic_string<char_t> &);

  template <typename char_t>
  void debug(
    const basic_string<char_t> &);

  template <typename char_t>
  void info(
    const basic_string<char_t> &);

  template <typename char_t>
  void warn(
    const basic_string<char_t> &);

  template <typename char_t>
  void error(
    const basic_string<char_t> &);

  template <typename char_t>
  void fatal(
    const basic_string<char_t> &);

} // namespace libs::log


template <
    typename char_t>
void libs::log::log(
    const char* lvl,
    const libs::basic_string<char_t> &s)
{
  std::cout << "[" << lvl << "] ";

  libs::foreach (
      libs::begin(s),
      libs::end(s),
      [](const char_t &c) {
        std::cout << c;
      });

  std::cout << "\n";
}

template <typename char_t>
void libs::log::trace(
    const libs::basic_string<char_t> &s)
{
  log("trace", s);
}

template <typename char_t>
void libs::log::debug(
    const libs::basic_string<char_t> &s)
{
  log("debug", s);
}

template <typename char_t>
void libs::log::info(
    const libs::basic_string<char_t> &s)
{
  log("info", s);
}

template <typename char_t>
void libs::log::warn(
    const libs::basic_string<char_t> &s)
{
  log("warn", s);
}

template <typename char_t>
void libs::log::error(
    const libs::basic_string<char_t> &s)
{
  log("error", s);
}

template <typename char_t>
void libs::log::fatal(
    const libs::basic_string<char_t> &s)
{
  log("fatal", s);
}

#endif