/* j/4/by_get.c
**
*/
#include "all.h"

/* functions
*/
u3_noun
u3qdb_get(u3_noun a,
          u3_noun b)
{
  if ( u3_nul == a ) {
    return u3_nul;
  }
  else {
    u3_noun n_a, lr_a;
    u3_noun pn_a, qn_a;
    u3x_cell(a, &n_a, &lr_a);
    u3x_cell(n_a, &pn_a, &qn_a);

    if ( (c3y == u3r_sing(b, pn_a)) ) {
      return u3i_cell(u3_nul, u3a_gain(qn_a));
    }
    else {
      return ( c3y == u3qc_gor(b, pn_a) ) ? u3qdb_get(u3x_h(lr_a), b)
                                          : u3qdb_get(u3x_t(lr_a), b);
    }
  }
}

u3_noun
u3wdb_get(u3_noun cor)
{
  u3_noun a, b;
  u3x_mean(cor, u3x_sam, &b, u3x_con_sam, &a, 0);
  return u3qdb_get(a, b);
}

u3_weak
u3kdb_get(u3_noun a,
          u3_noun b)
{
  u3_noun c = u3qdb_get(a, b);
  u3a_lose(a); u3a_lose(b);

  if ( c3n == u3a_is_cell(c) ) {
    u3a_lose(c);
    return u3_none;
  }
  else {
    u3_noun pro = u3a_gain(u3x_t(c));
    u3a_lose(c);
    return pro;
  }
}

u3_noun
u3kdb_got(u3_noun a,
          u3_noun b)
{
  return u3x_good(u3kdb_get(a, b));
}
