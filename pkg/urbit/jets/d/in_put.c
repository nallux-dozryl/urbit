/* j/4/in_put.c
**
*/
#include "all.h"

/* functions
*/
u3_noun
u3qdi_put(u3_noun a,
          u3_noun b)
{
  if ( u3_nul == a ) {
    return u3i_trel(u3a_gain(b), u3_nul, u3_nul);
  }
  else {
    u3_noun n_a, lr_a;
    u3x_cell(a, &n_a, &lr_a);

    if ( c3y == u3r_sing(n_a, b) ) {
      return u3a_gain(a);
    }
    else {
      u3_noun c, n_c, l_c, r_c;
      u3_noun l_a, r_a;
      u3x_cell(lr_a, &l_a, &r_a);

      if ( c3y == u3qc_gor(b, n_a) ) {
        c = u3qdi_put(l_a, b);

        if ( c3y == u3qc_mor(n_a, u3x_h(c)) ) {
          return u3i_trel(u3a_gain(n_a),
                      c,
                      u3a_gain(r_a));
        }
        else {
          u3r_trel(c, &n_c, &l_c, &r_c);
          {
            u3_noun d = u3i_trel(u3a_gain(n_c),
                             u3a_gain(l_c),
                             u3i_trel(u3a_gain(n_a), u3a_gain(r_c), u3a_gain(r_a)));

            u3a_lose(c);
            return d;
          }
        }
      }
      else {
        c = u3qdi_put(r_a, b);

        if ( c3y == u3qc_mor(n_a, u3x_h(c)) ) {
          return u3i_trel(u3a_gain(n_a),
                      u3a_gain(l_a),
                      c);
        }
        else {
          u3r_trel(c, &n_c, &l_c, &r_c);
          {
            u3_noun d = u3i_trel(u3a_gain(n_c),
                             u3i_trel(u3a_gain(n_a), u3a_gain(l_a), u3a_gain(l_c)),
                             u3a_gain(r_c));

            u3a_lose(c);
            return d;
          }
        }
      }
    }
  }
}

u3_noun
u3wdi_put(u3_noun cor)
{
  u3_noun a, b;
  u3x_mean(cor, u3x_sam, &b, u3x_con_sam, &a, 0);
  return u3qdi_put(a, b);
}

u3_noun
u3kdi_put(u3_noun a,
          u3_noun b)
{
  u3_noun pro = u3qdi_put(a, b);
  u3a_lose(a); u3a_lose(b);
  return pro;
}
