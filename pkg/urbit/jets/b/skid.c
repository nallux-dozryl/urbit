/* j/2/skid.c
**
*/
#include "all.h"

u3_noun
u3qb_skid(u3_noun a, u3_noun b)
{
  u3_noun l, r;
  u3_noun* lef = &l;
  u3_noun* rig = &r;

  if ( u3_nul != a) {
    u3_noun   i, t = a;
    u3_noun*   hed;
    u3_noun*   tel;
    u3j_site sit_u;
    u3j_gate_prep(&sit_u, u3a_gain(b));

    do {
      u3x_cell(t, &i, &t);

      switch ( u3j_gate_slam(&sit_u, u3a_gain(i)) ) {
        case c3y: {
          *lef = u3i_defcons(&hed, &tel);
          *hed = u3a_gain(i);
          lef  = tel;
        } break;

        case c3n: {
          *rig = u3i_defcons(&hed, &tel);
          *hed = u3a_gain(i);
          rig  = tel;
        } break;

        default: u3m_bail(c3__exit);
      }
    }
    while ( u3_nul != t );

    u3j_gate_lose(&sit_u);
  }

  *lef = u3_nul;
  *rig = u3_nul;

  return u3i_cell(l, r);
}

u3_noun
u3wb_skid(u3_noun cor)
{
  u3_noun a, b;
  u3x_mean(cor, u3x_sam_2, &a, u3x_sam_3, &b, 0);
  return u3qb_skid(a, b);
}
