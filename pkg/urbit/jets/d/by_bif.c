/* jets/d/by_bif.c
**
*/
#include "all.h"

/* internal functions
*/
static u3_noun
_b_bif_putroot(u3_noun a,
               u3_noun b)
{
  if ( u3_nul == a ) {
    return u3i_trel(u3a_gain(b), u3_nul, u3_nul);
  }
  else {
    u3_noun n_a, l_a, r_a;
    u3_noun p_n_a, q_n_a;
    u3_noun p_b, q_b;
    u3x_trel(a, &n_a, &l_a, &r_a);
    u3x_cell(b, &p_b, &q_b);
    u3x_cell(n_a, &p_n_a, &q_n_a);

    if ( c3y == u3r_sing(p_b, p_n_a) ) {
      return u3i_trel(u3a_gain(b), u3a_gain(l_a), u3a_gain(r_a));
    }
    else {
      u3_noun c, n_c, l_c, r_c;
      u3_noun d;

      if ( c3y == u3qc_gor(p_b, p_n_a) ) {
        c = _b_bif_putroot(l_a, b);
        u3r_trel(c, &n_c, &l_c, &r_c);
        d = u3i_trel(u3a_gain(n_c),
                 u3a_gain(l_c),
                 u3i_trel(u3a_gain(n_a), u3a_gain(r_c), u3a_gain(r_a))
                );
        u3a_lose(c);
        return d;
      }
      else {
        c = _b_bif_putroot(r_a, b);
        u3r_trel(c, &n_c, &l_c, &r_c);
        d = u3i_trel(u3a_gain(n_c),
                 u3i_trel(u3a_gain(n_a), u3a_gain(l_a), u3a_gain(l_c)),
                 u3a_gain(r_c)
                );
        u3a_lose(c);
        return d;
      }
    }
  }
}

/* functions
*/
u3_noun
u3wdb_bif(u3_noun cor)
{
  u3_noun a, b;
  u3x_mean(cor, u3x_sam, &b, u3x_con_sam, &a, 0);
  return u3qdb_bif(a, b);
}

u3_noun
u3qdb_bif(u3_noun a,
          u3_noun b)
{
  u3_noun c, n_c, l_c, r_c;
  u3_noun d;

  c = _b_bif_putroot(a, b);
  u3r_trel(c, &n_c, &l_c, &r_c);
  d = u3i_cell(u3a_gain(l_c), u3a_gain(r_c));
  u3a_lose(c);
  return d;
}
