#include "utest.h"
#include "log.h"
#include "i18n.h"

bool utest_assert(bool expr, message err)
{
  if (!expr)
     log_warn(err);
  
  return expr;
}