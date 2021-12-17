/* jets/d/in_bif.c
**
*/
#include "all.h"

/* internal functions
*/
static u3_noun
_i_bif_putroot(u3_noun a,
               u3_noun b)
{
  if ( u3_nul == a) {
    return u3i_trel(u3a_gain(b), u3_nul, u3_nul);
  }
  else {
    u3_noun n_a, lr_a;
    u3x_cell(a, &n_a, &lr_a);

    if ( c3y == u3r_sing(b, n_a) ) {
      return u3a_gain(a);
    }
    else {
      u3_noun c, n_c, l_c, r_c;
      u3_noun d;
      u3_noun l_a, r_a;
      u3x_cell(lr_a, &l_a, &r_a);

      if ( c3y == u3qc_gor(b, n_a) ) {
        c = _i_bif_putroot(l_a, b);
        u3r_trel(c, &n_c, &l_c, &r_c);
        d = u3i_trel(u3a_gain(n_c),
                 u3a_gain(l_c),
                 u3i_trel(u3a_gain(n_a), u3a_gain(r_c), u3a_gain(r_a)));
        u3a_lose(c);
        return d;
      }
      else {
        c = _i_bif_putroot(r_a, b);
        u3r_trel(c, &n_c, &l_c, &r_c);
        d = u3i_trel(u3a_gain(n_c),
                 u3i_trel(u3a_gain(n_a), u3a_gain(l_a), u3a_gain(l_c)),
                 u3a_gain(r_c));
        u3a_lose(c);
        return d;
      }
    }
  }
}

/* functions
*/
u3_noun
u3wdi_bif(u3_noun cor)
{
  u3_noun a, b;
  u3x_mean(cor, u3x_sam, &b, u3x_con_sam, &a, 0);
  return u3qdi_bif(a, b);
}

u3_noun
u3qdi_bif(u3_noun a,
          u3_noun b)
{
  u3_noun c, n_c, l_c, r_c;
  u3_noun d;

  c = _i_bif_putroot(a, b);
  u3r_trel(c, &n_c, &l_c, &r_c);
  d = u3i_cell(u3a_gain(l_c), u3a_gain(r_c));
  u3a_lose(c);
  return d;
}
