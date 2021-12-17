/* g/z.c
**
*/
#include "all.h"

/* u3z_key(): construct a memo cache-key.  Arguments retained.
*/
u3_noun
u3z_key(c3_m fun, u3_noun one)
{
  return u3i_cell(fun, u3a_gain(one));
}
u3_noun
u3z_key_2(c3_m fun, u3_noun one, u3_noun two)
{
  return u3i_trel(fun, u3a_gain(one), u3a_gain(two));
}
u3_noun
u3z_key_3(c3_m fun, u3_noun one, u3_noun two, u3_noun tri)
{
  return u3i_qual(fun, u3a_gain(one), u3a_gain(two), u3a_gain(tri));
}
u3_noun
u3z_key_4(c3_m fun, u3_noun one, u3_noun two, u3_noun tri, u3_noun qua)
{
  return u3i_cell(fun, u3i_qual(u3a_gain(one), u3a_gain(two), u3a_gain(tri), u3a_gain(qua)));
}
u3_noun
u3z_key_5(c3_m fun, u3_noun one, u3_noun two, u3_noun tri, u3_noun qua, u3_noun qin)
{
  return u3i_cell(fun, u3i_qual(u3a_gain(one), u3a_gain(two), u3a_gain(tri), u3i_cell(u3a_gain(qua), u3a_gain(qin))));
}

/* u3z_find(): find in memo cache.  Arguments retained.
*/
u3_weak
u3z_find(u3_noun key)
{
  return u3h_get(u3R->cax.har_p, key);
}
u3_weak
u3z_find_m(c3_m fun, u3_noun one)
{
  u3_noun key = u3i_cell(fun, u3a_gain(one));
  u3_weak val;

  val = u3h_get(u3R->cax.har_p, key);
  u3a_lose(key);
  return val;
}

/* u3z_save(): save in memo cache. TRANSFER key; RETAIN val
*/
u3_noun
u3z_save(u3_noun key, u3_noun val)
{
  u3h_put(u3R->cax.har_p, key, u3a_gain(val));
  u3a_lose(key);
  return val;
}

/* u3z_save_m(): save in memo cache. Arguments retained.
*/
u3_noun
u3z_save_m(c3_m fun, u3_noun one, u3_noun val)
{
  u3_noun key = u3i_cell(fun, u3a_gain(one));

  u3h_put(u3R->cax.har_p, key, u3a_gain(val));
  u3a_lose(key);
  return val;
}

/* u3z_uniq(): uniquify with memo cache.
*/
u3_noun
u3z_uniq(u3_noun som)
{
  u3_noun key = u3i_cell(c3__uniq, u3a_gain(som));
  u3_noun val = u3h_get(u3R->cax.har_p, key);

  if ( u3_none != val ) {
    u3a_lose(key); u3a_lose(som); return val;
  }
  else {
    u3h_put(u3R->cax.har_p, key, u3a_gain(som));
    return som;
  }
}
