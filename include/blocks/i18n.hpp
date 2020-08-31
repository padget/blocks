#ifndef __blocks_i18n_hpp__
#define __blocks_i18n_hpp__
#include <filesystem>
#include <iostream>
#include <string>
#include <map>

namespace blocks::i18n
{
  template <typename char_t>
  struct catalog
  {
    std::map<std::basic_string<char_t>, std::basic_string<char_t>> entries;
  };

  template <typename char_t>
  catalog<char_t> global()
  {
    // TODO faire la lecture du fs pour récupérer les catalogs et les mettres dans une variable "global".
    return {{{"hello", "bonjour"},
             {"world", "monde"}}};
  }
} // namespace blocks::i18n

namespace blocks::i18n
{
  template <typename char_t>
  struct lazy_translation
  {
    std::basic_string<char_t> key;
    blocks::i18n::catalog<char_t> catalog;
  };
} // namespace blocks::i18n

namespace blocks::i18n
{
  template <typename char_t>
  lazy_translation<char_t>
  translate(const std::basic_string<char_t> &key)
  {
    i18n::lazy_translation<char_t> tr;
    tr.key = key;
    tr.catalog = i18n::global<char_t>();
    return tr;
  }

  template <typename char_t>
  lazy_translation<char_t>
  translate(const char_t *key)
  {
    return translate(std::basic_string<char_t>(key));
  }
} // namespace blocks::i18n

namespace std
{
  template <typename char_t>
  ostream &operator<<(ostream &os, const blocks::i18n::lazy_translation<char_t> &translation)
  {
    auto it = translation.catalog.entries.find(translation.key);

    if (it != std::end(translation.catalog.entries))
      os << (*it).second;

    return os;
  }
} // namespace std

#endif