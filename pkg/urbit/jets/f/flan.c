/* j/6/flan.c
**
*/
#include "all.h"


/* functions
*/
  u3_noun
  u3qf_flan(u3_noun bos,
            u3_noun nif)
  {
    if ( c3y == u3r_sing(bos, nif) ) {
      return u3a_gain(bos);
    }
    if ( c3y == u3r_sing(1, u3x_h(bos)) ) {
      if ( (u3_nul == u3x_t(bos)) ) {
        return u3a_gain(nif);
      }
      else return u3a_gain(bos);
    }
    else {
      if ( c3y == u3r_sing(1, u3x_h(nif)) ) {
        if ( (u3_nul == u3x_t(nif)) ) {
          return u3a_gain(bos);
        }
        else return u3a_gain(nif);
      }
      else {
        return u3i_qual(6,
                    u3a_gain(bos),
                    u3a_gain(nif),
                    u3i_cell(1, c3n));
      }
    }
  }
  u3_noun
  u3wf_flan(u3_noun cor)
  {
    u3_noun bos, nif;

    if ( c3n == u3r_mean(cor, u3x_sam_2, &bos, u3x_sam_3, &nif, 0) ) {
      return u3m_bail(c3__fail);
    } else {
      return u3qf_flan(bos, nif);
    }
  }
