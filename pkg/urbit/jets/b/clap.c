/* j/2/clap.c
**
*/
#include "all.h"


/* functions
*/
  u3_noun
  u3qb_clap(u3_noun a,
            u3_noun b,
            u3_noun c)
  {
    if ( 0 == a ) {
      return u3a_gain(b);
    }
    else if ( 0 == b ) {
      return u3a_gain(a);
    }
    else {
      return u3i_cell(0, u3n_slam_on(u3a_gain(c), u3i_cell(u3a_gain(u3x_t(a)), u3a_gain(u3x_t(b)))));
    }
  }
  u3_noun
  u3wb_clap(u3_noun cor)
  {
    u3_noun a, b, c;

    if ( c3n == u3r_mean(cor, u3x_sam_2, &a,
                              u3x_sam_6, &b,
                              u3x_sam_7, &c, 0) ) {
      return u3m_bail(c3__exit);
    } else {
      return u3qb_clap(a, b, c);
    }
  }
