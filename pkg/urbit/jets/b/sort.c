/* j/2/sort.c
**
*/
#include "all.h"


/* functions
*/
  // like skid, except its callback is $-([* *] ?) and it takes the second
  // argument so that it calls its callback with [i.list, second]
  //
  // all args are RETAINED
  static u3_noun
  _split_in(u3j_site* sit_u,
            u3_noun a,
            u3_noun second)
  {
    if ( 0 == a ) {
      return u3i_cell(u3_nul, u3_nul);
    }
    else if ( c3n == u3a_is_cell(a) ) {
      return u3m_bail(c3__exit);
    } else {
      u3_noun acc = _split_in(sit_u, u3x_t(a), second);
      u3_noun hoz = u3j_gate_slam(sit_u, u3i_cell(u3a_gain(u3x_h(a)), u3a_gain(second)));
      u3_noun nex;

      if ( c3y == hoz ) {
        nex = u3i_cell(u3i_cell(u3a_gain(u3x_h(a)), u3a_gain(u3x_h(acc))), u3a_gain(u3x_t(acc)));
      }
      else {
        nex = u3i_cell(u3a_gain(u3x_h(acc)), u3i_cell(u3a_gain(u3x_h(a)), u3a_gain(u3x_t(acc))));
      }
      u3a_lose(hoz);
      u3a_lose(acc);

      return nex;
    }
  }

  static u3_noun
  _sort_in(u3j_site* sit_u, u3_noun list)
  {
    if ( 0 == list ) {
      return u3_nul;
    }
    else if ( c3n == u3a_is_cell(list) ) {
      return u3m_bail(c3__exit);
    } else {
      u3_noun hed, tal;
      u3x_cell(list, &hed, &tal);

      u3_noun split = _split_in(sit_u, tal, hed);
      u3_noun lhs = _sort_in(sit_u, u3x_h(split));
      u3_noun rhs = u3i_cell(u3a_gain(hed), _sort_in(sit_u, u3x_t(split)));

      u3_noun ret = u3qb_weld(lhs, rhs);
      u3a_lose(lhs);
      u3a_lose(rhs);
      u3a_lose(split);

      return ret;
    }
  }

  u3_noun
  u3qb_sort(u3_noun a,
            u3_noun b)
  {
    u3_noun  pro;
    u3j_site sit_u;
    u3j_gate_prep(&sit_u, u3a_gain(b));
    pro = _sort_in(&sit_u, a);
    u3j_gate_lose(&sit_u);
    return pro;
  }
  u3_noun
  u3wb_sort(u3_noun cor)
  {
    u3_noun a, b;

    if ( c3n == u3r_mean(cor, u3x_sam_2, &a, u3x_sam_3, &b, 0) ) {
      return u3m_bail(c3__exit);
    } else {
      return u3qb_sort(a, b);
    }
  }

