/* j/4/put.c
**
*/
#include "all.h"

/* functions
*/
u3_noun
u3qdb_put(u3_noun a,
          u3_noun b,
          u3_noun c)
{
  if ( u3_nul == a ) {
    return u3i_trel(u3i_cell(u3a_gain(b), u3a_gain(c)),
                u3_nul,
                u3_nul);
  }
  else {
    u3_noun n_a, l_a, r_a;
    u3_noun pn_a, qn_a;
    u3x_trel(a, &n_a, &l_a, &r_a);
    u3x_cell(n_a, &pn_a, &qn_a);

    if ( c3y == u3r_sing(pn_a, b) ) {
      if ( c3y == u3r_sing(qn_a, c) ) {
        return u3a_gain(a);
      }
      else {
        return u3i_trel(u3i_cell(u3a_gain(b), u3a_gain(c)),
                    u3a_gain(l_a),
                    u3a_gain(r_a));
      }
    }
    else {
      u3_noun d, n_d, l_d, r_d;

      if ( c3y == u3qc_gor(b, pn_a) ) {
        d = u3qdb_put(l_a, b, c);

        if ( c3y == u3qc_mor(pn_a, u3x_h(u3x_h(d))) ) {
          return u3i_trel(u3a_gain(n_a),
                      d,
                      u3a_gain(r_a));
        }
        else {
          u3r_trel(d, &n_d, &l_d, &r_d);

          u3_noun e = u3i_trel(u3a_gain(n_d),
                           u3a_gain(l_d),
                           u3i_trel(u3a_gain(n_a),
                                u3a_gain(r_d),
                                u3a_gain(r_a)));

          u3a_lose(d);
          return e;
        }
      }
      else {
        d = u3qdb_put(r_a, b, c);

        if ( c3y == u3qc_mor(pn_a, u3x_h(u3x_h(d))) ) {
          return u3i_trel(u3a_gain(n_a),
                      u3a_gain(l_a),
                      d);
        }
        else {
          u3r_trel(d, &n_d, &l_d, &r_d);

          u3_noun e = u3i_trel(u3a_gain(n_d),
                           u3i_trel(u3a_gain(n_a),
                                u3a_gain(l_a),
                                u3a_gain(l_d)),
                            u3a_gain(r_d));

          u3a_lose(d);
          return e;
        }
      }
    }
  }
}

u3_noun
u3wdb_put(u3_noun cor)
{
  u3_noun a, b, c;
  u3x_mean(cor, u3x_sam_2,   &b,
                u3x_sam_3,   &c,
                u3x_con_sam, &a, 0);
  return u3qdb_put(a, b, c);
}

u3_noun
u3kdb_put(u3_noun a,
          u3_noun b,
          u3_noun c)
{
  u3_noun pro = u3qdb_put(a, b, c);
  u3a_lose(a); u3a_lose(b); u3a_lose(c);
  return pro;
}
