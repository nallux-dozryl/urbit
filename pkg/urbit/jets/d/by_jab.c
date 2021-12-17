/* j/4/by_jab.c
**
*/
#include "all.h"

/* functions
*/
u3_noun
u3qdb_jab(u3_noun a,
          u3_noun key,
          u3_noun fun)
{
  if ( u3_nul == a ) {
    return u3m_bail(c3__exit);
  }
  else {
    u3_noun n_a, lr_a;
    u3_noun pn_a, qn_a;
    u3x_cell(a, &n_a, &lr_a);
    u3x_cell(n_a, &pn_a, &qn_a);

    if ( (c3y == u3r_sing(key, pn_a)) ) {
      u3_noun value = u3n_slam_on(u3a_gain(fun), u3a_gain(qn_a));
      return u3i_cell(u3i_cell(u3a_gain(pn_a), value), u3a_gain(u3x_t(a)));
    }
    else {
      u3_noun l_a, r_a;
      u3x_cell(lr_a, &l_a, &r_a);

      return ( c3y == u3qc_gor(key, pn_a) )
             ? u3i_trel(u3a_gain(n_a), u3qdb_jab(l_a, key, fun), u3a_gain(r_a))
             : u3i_trel(u3a_gain(n_a), u3a_gain(l_a), u3qdb_jab(r_a, key, fun));
    }
  }
}

u3_noun
u3wdb_jab(u3_noun cor)
{
  u3_noun a, key, fun;
  u3x_mean(cor, u3x_sam_2,   &key,
                u3x_sam_3,   &fun,
                u3x_con_sam, &a, 0);

  return u3qdb_jab(a, key, fun);
}
