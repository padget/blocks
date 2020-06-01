#include "utest.h"
#include "log.h"
#include "i18n.h"



bool utest_assert(bool expr, message err, utest_report *report)
{
  if (!expr)
  {   
    log_warn(err);
    report->nb_errors++;
  }
  else
  {
    report->nb_passed++;
  } 

  report->nb_tests++;

  return expr;
}