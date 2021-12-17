/* j/6/flip.c
**
*/
#include "all.h"


/* functions
*/
  u3_noun
  u3qf_flip(u3_noun hel)
  {
    if ( c3y == u3r_sing(1, u3x_h(hel)) ) {
      if ( (c3y == u3x_t(hel)) ) {
        return u3i_cell(1, c3n);
      }
      else {
        c3_assert((c3n == u3x_t(hel)));

        return u3i_cell(1, c3y);
      }
    }
    else {
      return u3i_qual(6,
                  u3a_gain(hel),
                  u3i_cell(1, c3n),
                  u3i_cell(1, c3y));
    }
  }
  u3_noun
  u3wf_flip(u3_noun cor)
  {
    u3_noun hel;

    if ( u3_none == (hel = u3r_at(u3x_sam, cor)) ) {
      return u3m_bail(c3__fail);
    } else {
      return u3qf_flip(hel);
    }
  }
