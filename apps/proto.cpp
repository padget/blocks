#include <iostream>
#include <string>

template <typename type_t, typename... skills_t>
class named_type : public skills_t...
{
  type_t t;

public:
  named_type(type_t &_t) : skills_t(t)..., t(_t) {}

public:
  type_t &get()
  {
    return t;
  }

  const type_t &get() const
  {
    return t;
  }
};

template <typename type_t>
class skill
{
  type_t &t;

public:
  skill(type_t &_t) : t(_t) {}

  type_t &get2()
  {
    return t;
  }

  const type_t &get2() const
  {
    return t;
  }
};

using str_t = named_type<std::string, skill<std::string>>;

int main(int argc, char **argv)
{
  std::string s = "coucou";
  str_t str(s);
  str.get();
  std::cout << str.get2() << std::endl;

  return EXIT_SUCCESS;
}