/* j/6/ap.c
**
*/
#include "all.h"


/** forward declares
**/
    u3_noun u3wfp_rake(u3_noun);
    u3_noun u3wfp_open(u3_noun);
    u3_noun u3wfp_hack(u3_noun);

    static u3_noun
    _ap_open_l(u3_noun, u3_noun, u3_noun);

    // make sure these match the array below!
    //
#   define _ap_jet_open  0
#   define _ap_jet_rake  1
#   define _ap_jet_hack  2

#if 0
    static u3_noun
    _open_in(u3_noun ter, u3_noun gen);
    /* ~(. al gen)
    */
    static u3_noun
    _al_bore(u3_noun ter,
             u3_noun gen)
    {
      u3_noun gat = u3j_hook(u3a_gain(ter), "al");

      return u3i_molt(gat, u3x_sam, u3i_cell(c3__herb, u3a_gain(gen)), 0);
    }
    /* ~(. al gen)
    */
    static u3_noun
    _al_core(u3_noun ter,
             u3_noun gen)
    {
      u3_noun gat = u3j_hook(u3a_gain(ter), "al");

      return u3i_molt(gat, u3x_sam, u3a_gain(gen), 0);
    }

    /* van is transferred, gen is retained
    */
    static u3_noun
    _ap_bunt(u3_noun van,
             u3_noun gen)
    {
      u3_noun pro = u3qfl_bunt(van, gen);

      u3a_lose(van);
      return pro;
    }

/** open cases
**/

#define _open_do_p(stem)  \
  static u3_noun _open_in_##stem \
    ( u3_noun ter, u3_noun p_gen)

#define _open_do_pq(stem)  \
  static u3_noun _open_in_##stem \
    ( u3_noun ter, u3_noun p_gen, u3_noun q_gen)

#define _open_do_pqr(stem)  \
  static u3_noun _open_in_##stem \
    ( u3_noun ter, u3_noun p_gen, u3_noun q_gen, u3_noun r_gen)

#define _open_do_pqrs(stem)  \
  static u3_noun _open_in_##stem \
    (  u3_noun ter, u3_noun p_gen, u3_noun q_gen, u3_noun r_gen, \
     u3_noun s_gen)

/***
****
***/
  _open_do_pq(tsbr)   //  =:
  {
    return u3i_trel(c3__tsls,
	            _ap_bunt(_al_core(ter, p_gen), p_gen),
	            u3a_gain(q_gen));
  }
  _open_do_pq(tscl)   //  =:
  {
    return u3i_trel(c3__tsgr,
		        u3i_trel(c3__cncb,
                     u3i_cell(u3i_cell(u3_nul, 1),
                          u3_nul),
                          u3a_gain(p_gen)),
		             u3a_gain(q_gen));
  }
  _open_do_pqr(tsdt)   //  =.
  {
    return u3i_trel(c3__tsgr,
	            u3i_trel(c3__cncb,
			         u3i_cell(u3i_cell(u3_nul, 1),
				          u3_nul),
                     u3i_cell(u3i_cell(u3a_gain(p_gen),
					           u3a_gain(q_gen)),
				          u3_nul)),
	            u3a_gain(r_gen));
  }
  _open_do_pq(tsgl)   //  =<
  {
    return u3i_trel(c3__tsgr,
                u3a_gain(q_gen),
                u3a_gain(p_gen));
  }
  _open_do_pq(tshp)   //  =-
  {
    return u3i_trel(c3__tsls,
                u3a_gain(q_gen),
                u3a_gain(p_gen));
  }
  _open_do_pq(tsls)   //  =+
  {
    return u3i_trel(c3__tsgr,
                u3i_cell(u3a_gain(p_gen),
                     u3i_cell(u3_nul, 1)),
                u3a_gain(q_gen));
  }
  _open_do_p(tssg)   //  =~
  {
    if ( !_(u3a_is_cell(p_gen)) ) {
      return u3i_cell(0, 1);
    } else {
      u3_noun tp_gen = u3x_t(p_gen);
      u3_noun ip_gen = u3x_h(p_gen);

      if ( (u3_nul == p_gen) ) {
        return u3i_cell(u3_blip, 1);
      }
      else if ( (u3_nul == tp_gen) ) {
        return u3a_gain(ip_gen);
      }
      else {
        return u3i_trel(c3__tsgr,
                    u3a_gain(ip_gen),
                    _open_in_tssg(ter, tp_gen));
      }
    }
  }
/***
****
***/
  _open_do_p(bccb)    //  $_
  {
    return _ap_bunt(_al_core(ter, p_gen), p_gen);
  }
  _open_do_p(bctr)    //  $*
  {
    return
      u3i_cell(c3__ktsg,
	       _ap_bunt(_al_core(ter, p_gen),
					p_gen));
  }
  _open_do_p(bczp)    //  $!
  {
    return u3i_trel(c3__bccb,
                c3__axil,
                u3a_gain(p_gen));
  }
/***
****
***/
  _open_do_p(brhp)    //  |-
  {
    return u3i_trel(c3__tsgl,
                u3i_cell(c3__cnzy, u3_blip),
                u3i_cell(c3__brdt, u3a_gain(p_gen)));
  }
  _open_do_p(brdt)   //  |.
  {
    return u3i_cell(c3__brcn,
                u3i_trel(u3i_trel(u3_blip, c3__ash, u3a_gain(p_gen)),
                     u3_nul,
                     u3_nul));
  }

/***
****
***/
  _open_do_p(wtbr)    //  ?|
  {
    if ( (u3_nul == p_gen) ) {
      return u3i_trel(c3__dtzz, 'f', c3n);
    }
    else {
      u3_noun ip_gen = u3x_h(p_gen);
      u3_noun tp_gen = u3x_t(p_gen);

      return u3i_qual(c3__wtcl,
                  u3a_gain(ip_gen),
                  u3i_trel(c3__dtzz, 'f', c3y),
	              _open_in_wtbr(ter, tp_gen));
    }
  }
  _open_do_pqr(wtkt)   //  ?^
  {
    return u3i_qual(c3__wtcl,
                u3i_trel(c3__wtts,
		             u3i_trel(c3__axil, c3__atom, u3_blip),
	                 u3a_gain(p_gen)),
                u3a_gain(r_gen),
                u3a_gain(q_gen));
  }
  _open_do_pq(wtgl)   //  ?<
  {
    return u3i_qual(c3__wtcl,
                u3a_gain(p_gen),
                u3i_cell(c3__zpzp, u3_nul),
                u3a_gain(q_gen));
  }
  _open_do_pqr(wtdt)  //  ?.
  {
    return u3i_qual(c3__wtcl,
                u3a_gain(p_gen),
                u3a_gain(r_gen),
                u3a_gain(q_gen));
  }
  _open_do_pq(wtgr)   //  ?>
  {
    return u3i_qual(c3__wtcl,
                u3a_gain(p_gen),
                u3a_gain(q_gen),
                u3i_cell(c3__zpzp, u3_nul));
  }
  _open_do_pq(wthp)  //  ?-
  {
    if ( (u3_nul == q_gen) ) {
      return u3i_cell(c3__zpfs,
                  u3i_cell(c3__cnzz,
                       u3a_gain(p_gen)));
    }
    else {
      u3_noun iq_gen = u3x_h(q_gen);
      u3_noun tq_gen = u3x_t(q_gen);
      u3_noun piq_gen = u3x_h(iq_gen);
      u3_noun qiq_gen = u3x_t(iq_gen);

      return u3i_qual(c3__wtcl,
                  u3i_trel(c3__wtts,
                       u3a_gain(piq_gen),
                       u3a_gain(p_gen)),
                  u3a_gain(qiq_gen),
                  _open_in_wthp(ter, p_gen, tq_gen));
    }
  }
  _open_do_p(wtpm)    //  ?&
  {
    if ( (u3_nul == p_gen) ) {
      return u3i_trel(c3__dtzz, 'f', c3y);
    }
    else {
      u3_noun ip_gen = u3x_h(p_gen);
      u3_noun tp_gen = u3x_t(p_gen);

      return u3i_qual(c3__wtcl,
                  u3a_gain(ip_gen),
	              _open_in_wtpm(ter, tp_gen),
                  u3i_trel(c3__dtzz, 'f', c3n));
    }
  }
  _open_do_pqr(wtls)  //  ?+
  {    u3_noun tul = u3i_cell(u3i_cell(u3i_cell(c3__axil, c3__noun),
                               u3a_gain(q_gen)),
                          u3_nul);
    u3_noun zal = u3qb_weld(r_gen, tul);
    u3_noun ret = u3i_trel(c3__wthp, u3a_gain(p_gen), zal);

    u3a_lose(tul);
    return ret;

  }
  _open_do_pqr(wtpt)  //  ?@
  {
    return u3i_qual(c3__wtcl,
                u3i_trel(c3__wtts,
                     u3i_trel(c3__axil,
                          c3__atom,
                          u3_blip),
                     u3a_gain(p_gen)),
		        u3a_gain(q_gen),
                u3a_gain(r_gen));
  }
  _open_do_pqr(wtsg)    //  ?~
  {
    return u3i_qual(c3__wtcl,
                u3i_trel(c3__wtts,
                     u3i_cell(c3__axil, c3__null),
                     u3a_gain(p_gen)),
                u3a_gain(q_gen),
                u3a_gain(r_gen));
  }
  _open_do_p(wtzp)    //  ?!
  {
    return u3i_qual(c3__wtcl,
                u3a_gain(p_gen),
                u3i_trel(c3__dtzz, 'f', c3n),
                u3i_trel(c3__dtzz, 'f', c3y));
  }
/***
****
***/
  _open_do_pq(zpcb)    //  !_
  {
    return u3a_gain(q_gen);
  }
  _open_do_p(zpgr)    //  !>
  {
    return u3i_qual(c3__cnhp,
                u3i_cell(c3__cnzy, c3__onan),
                u3i_trel(c3__zpsm,
	                 u3i_cell(c3__bctr,
		                  u3i_cell(c3__herb,
			                   u3i_cell(c3__cnzy,
					     	   c3__abel))),
		             u3a_gain(p_gen)),
                u3_nul);
  }
/***
****
***/
  _open_do_pq(clhp) //  :-
  {
    return u3i_cell(u3a_gain(p_gen),
                u3a_gain(q_gen));
  }
  _open_do_pq(clcb) //  :_
  {
    return u3i_cell(u3a_gain(q_gen),
                u3a_gain(p_gen));
  }
  _open_do_p(clcn) //  :%
  {
    return u3i_cell(u3i_cell(c3__clsg,
                     u3a_gain(p_gen)),
                u3i_cell(c3__bczp, c3__null));
  }
  _open_do_pqrs(clkt) //  :^
  {
    return u3i_qual(u3a_gain(p_gen),
                u3a_gain(q_gen),
                u3a_gain(r_gen),
                u3a_gain(s_gen));
  }
  _open_do_pqr(clls)  //  :+
  {
    return u3i_trel(u3a_gain(p_gen),
                u3a_gain(q_gen),
                u3a_gain(r_gen));
  }
  _open_do_p(clsg)    //  :~
  {
    if ( (u3_nul == p_gen) ) {
      return u3i_trel(c3__dtzz, 'n', u3_nul);
    }
    else {
      u3_noun ip_gen = u3x_h(p_gen);
      u3_noun tp_gen = u3x_t(p_gen);

      return u3i_cell(u3a_gain(ip_gen),
		          _open_in_clsg(ter, tp_gen));
    }
  }
  _open_do_p(cltr)    //  :*
  {
    if ( (u3_nul == p_gen) ) {
      return u3i_cell(c3__zpzp, u3_nul);
    }
    else {
      u3_noun ip_gen = u3x_h(p_gen);
      u3_noun tp_gen = u3x_t(p_gen);

      if ( (u3_nul == tp_gen) ) {
        return u3a_gain(ip_gen);
      } else {
        return u3i_cell(u3a_gain(ip_gen),
                    _open_in_cltr(ter, tp_gen));
      }
    }
  }
/***
****
***/
  _open_do_pq(cncb)   //  %_
  {
    return u3i_cell(c3__ktls,
                u3i_qual(u3i_cell(c3__cnzz, u3a_gain(p_gen)),
	                 c3__cnts,
                     u3a_gain(p_gen),
                     u3a_gain(q_gen)));
  }
#if 0
  _open_do_pq(cncl)   //  %:
  {
    return u3nq
      (c3__cnsg,
            u3i_cell(u3_blip, u3_nul),
            u3a_gain(p_gen),
            u3a_gain(q_gen));
  }
#endif
  _open_do_pq(cndt)   //  %.
  {
    return u3i_trel(c3__cnhp,
                u3a_gain(q_gen),
                u3i_cell(u3a_gain(p_gen), u3_nul));
  }
  _open_do_pqrs(cnkt) //  %^
  {
    return u3i_qual(c3__cnhp,
                u3a_gain(p_gen),
                u3a_gain(q_gen),
                u3i_trel(u3a_gain(r_gen),
                     u3a_gain(s_gen),
                     u3_nul));
  }
  _open_do_pq(cnhp)   //  %-
  {
    if ( (u3_nul == q_gen) ) {
      return u3i_trel(c3__tsgr,
                  u3a_gain(p_gen),
                  u3i_cell(c3__cnzy, u3_blip));
    } else {
      return u3i_qual(c3__cncl,
                  u3a_gain(p_gen),
                  c3__cltr,
                  u3a_gain(q_gen));
    }
  }
  _open_do_pqr(cnls)  //  %+
  {
    return u3i_cell(c3__cnhp,
                u3i_qual(u3a_gain(p_gen),
                     u3a_gain(q_gen),
                     u3a_gain(r_gen),
                     u3_nul));
  }
  _open_do_pqr(cnsg)  //  %~
  {
    return u3i_qual(c3__cntr,
                u3a_gain(p_gen),
                u3a_gain(q_gen),
                u3i_cell(u3i_cell(u3i_cell(u3i_cell(u3_nul, 6), 0), u3a_gain(r_gen)), 0));
  }
  _open_do_p(cnzy)  //  %cnzy
  {
    return u3i_trel(c3__cnts,
                u3i_cell(u3a_gain(p_gen), u3_nul),
                u3_nul);
  }
  _open_do_p(cnzz)  //  %cnzz
  {
    return u3i_trel(c3__cnts, u3a_gain(p_gen), u3_nul);
  }
/***
****
***/
  _open_do_p(hxgl)  //  #<
  {
    return u3i_qual(c3__cnhp,
                u3i_cell(c3__cnzy, c3__noah),
                u3i_cell(c3__zpgr,
		             u3i_cell(c3__cltr, u3a_gain(p_gen))),
                u3_nul);
  }
  _open_do_p(hxgr)  //  #>
  {
    return u3i_qual(c3__cnhp,
                u3i_cell(c3__cnzy, c3__cain),
                u3i_cell(c3__zpgr,
		             u3i_cell(c3__cltr, u3a_gain(p_gen))),
                u3_nul);
  }
/***
****
***/
   _open_do_pq(ktdt)   //  ^.
  {
    return u3i_trel(c3__ktls,
                u3i_qual(c3__cnhp, u3a_gain(p_gen), u3a_gain(q_gen), u3_nul),
                u3a_gain(q_gen));
  }
#if 0
   _open_do_pq(kthp)   //  ^-
  {
    return u3i_trel(c3__ktls,
                _ap_bunt(_al_bore(ter, p_gen), p_gen),
                u3a_gain(q_gen));
  }
#endif
/***
****
***/
  _open_do_pq(brcb)   //  |_
  {
    return u3i_trel(c3__tsls,
		        u3i_cell(c3__bctr, u3a_gain(p_gen)),
		        u3i_cell(c3__brcn, u3a_gain(q_gen)));
  }
  _open_do_pq(brkt)   //  |^
  {
    u3_noun diz = u3i_cell(c3__ash, u3a_gain(p_gen));
    u3_noun ret = u3i_trel(c3__tsgr,
                       u3i_cell(c3__brcn,
                            u3qdb_put(q_gen, u3_blip, diz)),
                       u3i_cell(c3__cnzy, u3_blip));

    c3_assert(0);
    u3a_lose(diz);
    return ret;
  }
  _open_do_pq(brls)   //  |+
  {
    return u3i_cell(c3__ktbr,
                u3i_trel(c3__brts,
                     u3a_gain(p_gen),
                     u3a_gain(q_gen)));
  }
  _open_do_p(brwt)   //  |?
  {
    return u3i_trel(c3__ktwt,
                c3__brdt,
                u3a_gain(p_gen));
  }
/***
****
***/
  _open_do_pq(sgts)   //  ~=
  {
    return u3i_trel(c3__sggr,
                u3i_cell(c3__germ, u3a_gain(p_gen)),
                u3a_gain(q_gen));
  }
#if 0
  _open_do_pq(sgbr)   //  ~|
  {
    return u3nt
      (c3__sggr,
              u3i_cell(c3__mean, u3a_gain(p_gen)),
              u3a_gain(q_gen));
  }
#endif
  _open_do_pq(sggl)   //  ~>
  {
    return u3i_trel(c3__tsgl,
                u3i_qual(c3__sggr, u3a_gain(p_gen), u3_nul, 1),
                u3a_gain(q_gen));
  }
  _open_do_pq(sgbc)    //  ~$
  {
    return u3i_trel(c3__sggr,
                u3i_qual(c3__live,
                     c3__dtzz,
                     u3_blip,
                     u3a_gain(p_gen)),
                u3a_gain(q_gen));
  }
  _open_do_pq(sgcb)    //  ~_
  {
    return u3i_trel(c3__sggr,
                u3i_cell(c3__mean,
	                 u3i_cell(c3__brdt,
		                  u3a_gain(p_gen))),
                u3a_gain(q_gen));
  }
    static u3_noun
    _sgcn_a(u3_noun r_gen,
            u3_noun nob)
    {
      if ( c3n == u3a_is_cell(r_gen) ) {
        return u3a_gain(nob);
      } else {
        u3_noun ir_gen = u3x_h(r_gen);
        u3_noun tr_gen = u3x_t(r_gen);
        u3_noun pir_gen, qir_gen;

        u3x_cell(ir_gen, &pir_gen, &qir_gen);

        return u3i_cell(u3i_cell(u3i_trel(c3__dtzz, u3_blip, u3a_gain(pir_gen)),
                         u3i_cell(c3__zpts, u3a_gain(qir_gen))),
                    _sgcn_a(tr_gen, nob));
      }
    }
  _open_do_pqrs(sgcn) //  ~%
  {
    return u3i_trel(c3__sggl,
                u3i_qual(c3__sgcn,
                     c3__clls,
                     u3i_trel(c3__dtzz, u3_blip, u3a_gain(p_gen)),
                     u3i_trel(u3i_cell(c3__zpts, u3a_gain(q_gen)),
                     c3__clsg,
                     _sgcn_a(r_gen, u3_nul))),
                u3a_gain(s_gen));
  }
  _open_do_pq(sgfs) //  ~/
  {
     return u3i_cell(c3__sgcn,
                 u3i_qual(u3a_gain(p_gen),
                      u3i_cell(u3_nul, 7),
                      u3_nul,
                      u3a_gain(q_gen)));
  }
  _open_do_pq(sgls)   //  ~+
  {
    return u3i_trel(c3__sggr,
                u3i_qual(c3__sgls, c3__dtzz, u3_blip, u3a_gain(p_gen)),
                u3a_gain(q_gen));
  }
  _open_do_pqr(sgpm)   //  ~&
  {
    return u3i_trel(c3__sggr,
                u3i_trel(c3__slog,
	                 u3i_trel(c3__dtzy, u3_blip, u3a_gain(p_gen)),
	                 u3i_qual(c3__cnhp, u3i_cell(c3__cnzy, c3__cain),
		             u3i_cell(c3__zpgr, u3a_gain(q_gen)), u3_nul)),
                u3a_gain(r_gen));
  }
  _open_do_pqrs(sgwt)   //  ~?
  {
    return u3i_trel(c3__tsls,
                u3i_qual(c3__wtdt,
                     u3a_gain(q_gen),
                     u3i_cell(c3__bczp, c3__null),
                     u3i_cell(u3i_cell(c3__bczp, c3__null), u3a_gain(r_gen))),
                u3i_qual(c3__wtsg,
                     u3i_cell(u3i_cell(u3_nul, 2),u3_nul),
                     u3i_trel(c3__tsgr,
                          u3i_cell(u3_nul, 3),
                          u3a_gain(s_gen)),
                          u3i_qual(c3__sgpm,
                               u3a_gain(p_gen),
                               u3i_cell(u3_nul, 5),
                               u3i_trel(c3__tsgr,
                                    u3i_cell(u3_nul, 3),
                                    u3a_gain(s_gen)))));
  }
/***
****
***/
    static u3_noun
    _smcl_in(u3_noun q_gen)
    {
      u3_noun hq_gen = u3x_h(q_gen);
      u3_noun tq_gen = u3x_t(q_gen);

      if ( c3n == u3a_is_cell(tq_gen) ) {
        return u3i_trel(c3__tsgr,
                    u3i_cell(u3_nul, 3),
                    u3a_gain(hq_gen));
      } else {
        return u3i_cell(c3__cnhp,
                    u3i_qual(u3i_cell(u3_nul, 2),
                         u3i_trel(c3__tsgr,
                              u3i_cell(u3_nul, 3),
                              u3a_gain(hq_gen)),
                         _smcl_in(tq_gen),
                         u3_nul));
      }
    }
  _open_do_pq(smcl)
  {
    if ( c3n == u3a_is_cell(q_gen) ) {
      return u3i_cell(c3__zpzp, u3_nul);
    }
    else if ( u3_nul == u3x_t(q_gen) ) {
      return u3a_gain(u3x_h(q_gen));
    }
    else {
      return u3i_trel(c3__tsls,
                  u3a_gain(p_gen),
                  _smcl_in(q_gen));
    }
  }
#if 0
  _open_do_pq(smsm)
  {
    return
      u3i_trel(c3__tsgr, u3i_qual(c3__ktts, c3__v, u3_nul, 1),
	    u3i_trel(c3__tsls,
		  u3i_trel(c3__ktts, c3__a,
			u3i_trel(c3__tsgr, u3i_cell(c3__cnzy, c3__v),
			      u3a_gain(p_gen))),
		  u3i_trel(c3__tsls,
			u3i_trel(c3__ktts, c3__b,
			      u3i_trel(c3__tsgr,
				    u3i_cell(c3__cnzy, c3__v),
				    u3a_gain(q_gen))),
			u3i_trel(c3__tsls,
			      u3i_trel(c3__ktts, c3__c,
				    u3i_qual(c3__cnhp,
					  u3i_cell(c3__cnzy, c3__a),
					  u3i_cell(c3__cnzy, c3__b),
					  u3_nul)),
			      u3i_trel(c3__wtgr,
				    u3i_trel(c3__dtts,
					  u3i_cell(c3__cnzy, c3__c),
					  u3i_cell(c3__cnzy, c3__b)),
				    u3i_cell(c3__cnzy, c3__c))))));
  }
#endif

/* functions
*/
  /** open
  **/
    static u3_noun
    _open_in(u3_noun ter,
             u3_noun gen)
    {
      u3_noun p_gen, q_gen, r_gen, s_gen;

      return u3_none;

      if ( c3y == u3a_is_atom(gen) ) {
        // printf("studly\n");
        // u3_err("stud m", gen);
        return u3m_bail(c3__exit);

        return u3i_trel(c3__cnts,
                    u3i_cell(u3a_gain(gen), u3_nul),
                    u3_nul);
      }
      else switch ( u3x_h(gen) ) {
        default: return u3_none;

        case u3_nul: {
          return u3i_trel(c3__cnts,
                      u3i_cell(u3a_gain(gen), u3_nul),
                      u3_nul);
        }

#     define _open_p(stem) \
          case c3__##stem: \
            return _open_in_##stem(ter, u3x_t(gen));  \

#     define _open_pq(stem) \
          case c3__##stem: \
            if ( c3n == u3r_cell(u3x_t(gen), &p_gen, &q_gen) ) { \
              return u3m_bail(c3__fail); \
            } else return _open_in_##stem(ter, p_gen, q_gen);

#     define _open_pqr(stem) \
          case c3__##stem: \
            if ( c3n == u3r_trel(u3x_t(gen), &p_gen, &q_gen, &r_gen) ) { \
              return u3m_bail(c3__fail); \
            } else return _open_in_##stem(ter, p_gen, q_gen, r_gen);

#     define _open_pqrs(stem) \
          case c3__##stem: \
            if ( c3n == u3r_qual\
                          (u3x_t(gen), &p_gen, &q_gen, &r_gen, &s_gen) )\
            { \
              return u3m_bail(c3__fail); \
            } else return _open_in_##stem(ter, p_gen, q_gen, r_gen, s_gen);

	_open_p   (bccb);
	_open_p   (bctr);
	_open_p   (bczp);

        _open_p   (brdt);
        _open_pq  (brcb);
        _open_p   (brhp);
        _open_pq  (brkt);
        _open_pq  (brls);
	_open_p   (brwt);

	_open_pq  (clcb);
	_open_p   (clcn);
	_open_pq  (clhp);
        _open_pqrs(clkt);
        _open_pqr (clls);
        _open_p   (cltr);
        _open_p   (clsg);
        _open_pq  (cncb);
        //  _open_pq  (cncl);
        _open_pq  (cndt);
        _open_pqrs(cnkt);
        _open_pq  (cnhp);
        _open_pqr (cnls);
        _open_pqr (cnsg);
        _open_p   (cnzy);
        _open_p   (cnzz);

	_open_p   (hxgl);
	_open_p   (hxgr);

	_open_pq  (ktdt);
//  _open_pq  (kthp);

	_open_pq  (sgts);
//	_open_pq  (sgbr);
	_open_pq  (sggl);
	_open_pq  (sgbc);
	_open_pq  (sgcb);
	_open_pqrs(sgcn);
	_open_pq  (sgfs);
	_open_pq  (sgls);
	_open_pqr (sgpm);
	_open_pqrs(sgwt);

        _open_pq  (smcl);
	//	_open_pq  (smsm);

	_open_pq  (tsbr);
	_open_pq  (tscl);
	_open_pqr (tsdt);
        _open_pq  (tsgl);
        _open_pq  (tshp);
        _open_pq  (tsls);
	_open_p   (tssg);

        _open_pqr (wtdt);
        _open_pq  (wtgl);
	_open_pqr (wtpt);
	_open_pqr (wtsg);
        _open_p   (wtzp);
        _open_p   (wtbr);
	_open_pq  (wthp);
        _open_pq  (wtgr);
        _open_pqr (wtls);
        _open_pqr (wtkt);
        _open_p   (wtpm);

	_open_pq  (zpcb);
	_open_p   (zpgr);
      }
    }

  /** rake
  **/
    u3_noun
    u3qfp_rake(u3_noun gen)
    {
      u3_noun p_gen, q_gen;

      if ( c3y == u3a_is_atom(gen) ) {
        return u3i_cell(u3a_gain(gen), u3_nul);
      }
      else switch ( u3x_h(gen) ) {
        default: return u3m_error("rake-twig");

        case u3_nul:  return u3i_cell(u3a_gain(gen), u3_nul);

        case c3__cnzy: {
          return u3i_cell(u3a_gain(u3x_t(gen)), u3_nul);
        }
        case c3__cnzz: {
          return u3a_gain(u3x_t(gen));
        }
        case c3__cnts: {
          if ( c3n == u3r_cell(u3x_t(gen), &p_gen, &q_gen) ) {
            return u3m_bail(c3__fail);
          }
          else {
            if ( u3_nul != q_gen ) {
              return u3m_bail(c3__fail);
            }
            else {
              return u3a_gain(p_gen);
            }
          }
        }
        case c3__zpcb: {
          if ( c3n == u3r_cell(u3x_t(gen), &p_gen, &q_gen) ) {
            return u3m_bail(c3__fail);
          }
          else return u3qfp_rake(q_gen);
        }
      }
    }
    u3_noun
    u3wfp_rake(u3_noun cor)
    {
      u3_noun gen;

      if ( u3_none == (gen = u3r_at(u3x_sam, cor)) ) {
        return u3m_bail(c3__fail);
      } else {
        return u3qfp_rake(gen);
      }
    }

  /** hack
  **/
    u3_noun
    u3qfp_hack(u3_noun ter,
               u3_noun gen)
    {
      u3_noun p_gen, q_gen;
      u3_noun ret;

      if ( c3y == u3a_is_cell(u3x_h(gen)) ) {
        return u3i_trel(c3y,
                    u3a_gain(u3x_h(gen)),
                    u3a_gain(u3x_t(gen)));
      }
      else switch ( u3x_h(gen) ) {
        case c3__tsgr: u3x_cell(u3x_t(gen), &p_gen, &q_gen);
        {
          if ( (c3n == u3a_is_cell(p_gen)) || (u3_nul != u3x_h(p_gen)) ) {
            return u3i_cell(c3n, u3a_gain(gen));
          }
          else {
            u3_noun pyr = u3qfp_hack(ter, q_gen);

            if ( c3y == u3x_h(pyr) ) {
              ret = u3i_trel(c3y,
                         u3i_trel(c3__tsgr,
                              u3a_gain(p_gen),
                              u3a_gain(u3x_h(u3x_t(pyr)))),
                         u3i_trel(c3__tsgr,
                              u3a_gain(p_gen),
                              u3a_gain(u3x_t(u3x_t(pyr)))));
            }
            else {
              ret = u3i_cell(c3n,
                         u3i_trel(c3__tsgr,
                              u3a_gain(p_gen),
                              u3a_gain(u3x_t(pyr))));
            }
            u3a_lose(pyr);
            return ret;
          }
        }
        case c3__zpcb: u3x_cell(u3x_t(gen), &p_gen, &q_gen);
        {
          u3_noun pyr = u3qfp_hack(ter, q_gen);

          if ( c3y == u3x_h(pyr) ) {
            ret = u3i_trel(c3y,
                       u3i_trel(c3__zpcb,
                            u3a_gain(p_gen),
                            u3a_gain(u3x_h(u3x_t(pyr)))),
                       u3i_trel(c3__zpcb,
                            u3a_gain(p_gen),
                            u3a_gain(u3x_t(u3x_t(pyr)))));
          }
          else {
            ret = u3i_cell(c3n,
                       u3i_trel(c3__zpcb,
                            u3a_gain(p_gen),
                            u3a_gain(u3x_t(pyr))));
          }
          u3a_lose(pyr);
          return ret;
        }
        default: break;
      }

      {
        u3_noun voq = _ap_open_l(ter, gen);

        if ( u3_none == voq ) {
          return u3i_cell(c3n, u3a_gain(gen));
        }
        else if ( c3y == u3r_sing(voq, gen) ) {
          return u3i_cell(c3n, voq);
        }
        else {
          ret = u3qfp_hack(ter, voq);

          u3a_lose(voq);
          return ret;
        }
      }
    }

    u3_noun
    u3wfp_hack(u3_noun cor)
    {
      u3_noun gen;

      if ( u3_none == (gen = u3r_at(u3x_sam, cor)) ) {
        return u3m_bail(c3__fail);
      } else {
        u3_noun ter = u3r_at(u3x_con, cor);

        return u3qfp_hack(ter, gen);
      }
    }
#endif

/* boilerplate
*/
  static u3_noun
  _ap_core(u3_noun ter,
           u3_noun gen)
  {
    u3_noun gat = u3j_cook("_ap_core-ap", u3a_gain(ter), "ap");

    return u3i_molt(gat, u3x_sam, u3a_gain(gen), 0);
  }

  static u3_noun
  _ar_core(u3_noun van,
           u3_noun ref,
           u3_noun syn)
  {
    u3_noun gat = u3j_hook(u3a_gain(van), "ar");

    return u3i_molt(gat, u3x_sam, u3i_cell(u3a_gain(ref), u3a_gain(syn)), 0);
  }

/* fish
*/
  u3_noun
  u3qfr_fish(u3_noun van,
             u3_noun ref,
             u3_noun syn,
             u3_noun axe)
  {
    u3_noun gat = u3j_soft(_ar_core(van, ref, syn), "fish");

    return u3n_kick_on(u3i_molt(gat,
                                u3x_sam,
                                u3a_gain(axe),
                                0));
  }

/* open
*/
  static u3_noun
  _ap_open_n(u3_noun ter,
             u3_noun fab,
             u3_noun gen)
  {
    u3_noun cor = _ap_core(ter, gen);

#if 1
    if ( c3n == fab ) {
      cor = u3i_molt(cor, 14, c3n, 0);
    }
#endif
    return u3j_soft(cor, "open");
  }
  static u3_noun
  _ap_open_l(u3_noun ter,
             u3_noun fab,
             u3_noun gen)
  {
#if 0
    u3_noun pro = _open_in(ter, gen);

    if ( u3_none != pro ) {
      return pro;
    } else {
      return _ap_open_n(ter, gen);
    }
#else
    return _ap_open_n(ter, fab, gen);
#endif
  }

  u3_noun
  u3qfp_open(u3_noun ter,
             u3_noun fab,
             u3_noun gen)
  {
    return _ap_open_l(ter, fab, gen);
  }

  u3_noun
  u3wfp_open(u3_noun cor)
  {
    u3_noun gen;

    if ( u3_none == (gen = u3r_at(u3x_sam, cor)) ) {
      return u3m_bail(c3__fail);
    } else {
      u3_noun ter = u3r_at(u3x_con, cor);

      return u3qfp_open(ter, c3y, gen);
    }
  }

