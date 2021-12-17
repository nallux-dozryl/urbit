/* j/6/help.c
**
*/
#include "all.h"


/* functions
*/
  u3_noun
  u3qf_help(u3_noun sag,
            u3_noun tip)
  {
    if ( c3__void == tip ) {
      return c3__void;
    }
    else return u3i_trel(c3__help,
                     u3a_gain(sag),
                     u3a_gain(tip));
  }
  u3_noun
  u3wf_help(u3_noun cor)
  {
    u3_noun sag, tip;

    if ( c3n == u3r_mean(cor, u3x_sam_2, &sag, u3x_sam_3, &tip, 0) ) {
      return u3m_bail(c3__fail);
    } else {
      return u3qf_help(sag, tip);
    }
  }

