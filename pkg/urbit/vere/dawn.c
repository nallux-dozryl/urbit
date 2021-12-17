/* vere/dawn.c
**
** ethereum-integrated pre-boot validation
*/
#include "all.h"
#include "vere/vere.h"
#include <curl/curl.h>
#include <uv.h>

/* _dawn_oct_to_buf(): +octs to uv_buf_t
*/
static uv_buf_t
_dawn_oct_to_buf(u3_noun oct)
{
  if ( c3n == u3a_is_cat(u3x_h(oct)) ) {
    exit(1);
  }

  c3_w len_w  = u3x_h(oct);
  c3_y* buf_y = c3_malloc(1 + len_w);
  buf_y[len_w] = 0;

  u3r_bytes(0, len_w, buf_y, u3x_t(oct));

  u3a_lose(oct);
  return uv_buf_init((void*)buf_y, len_w);
}

/* _dawn_buf_to_oct(): uv_buf_t to +octs
*/
static u3_noun
_dawn_buf_to_oct(uv_buf_t buf_u)
{
  u3_noun len = u3i_words(1, (c3_w*)&buf_u.len);

  if ( c3n == u3a_is_cat(len) ) {
    exit(1);
  }

  return u3i_cell(len, u3i_bytes(buf_u.len, (const c3_y*)buf_u.base));
}


/* _dawn_curl_alloc(): allocate a response buffer for curl
*/
static size_t
_dawn_curl_alloc(void* dat_v, size_t uni_t, size_t mem_t, void* buf_v)
{
  uv_buf_t* buf_u = buf_v;

  size_t siz_t = uni_t * mem_t;
  buf_u->base = c3_realloc(buf_u->base, 1 + siz_t + buf_u->len);

  memcpy(buf_u->base + buf_u->len, dat_v, siz_t);
  buf_u->len += siz_t;
  buf_u->base[buf_u->len] = 0;

  return siz_t;
}

/* _dawn_post_json(): POST JSON to url_c
*/
static uv_buf_t
_dawn_post_json(c3_c* url_c, uv_buf_t lod_u)
{
  CURL *curl;
  CURLcode result;
  long cod_l;
  struct curl_slist* hed_u = 0;

  uv_buf_t buf_u = uv_buf_init(c3_malloc(1), 0);

  if ( !(curl = curl_easy_init()) ) {
    u3l_log("failed to initialize libcurl\n");
    exit(1);
  }

  hed_u = curl_slist_append(hed_u, "Accept: application/json");
  hed_u = curl_slist_append(hed_u, "Content-Type: application/json");
  hed_u = curl_slist_append(hed_u, "charsets: utf-8");

  //  XX require TLS, pin default cert?
  //
  u3K.ssl_curl_f(curl);
  curl_easy_setopt(curl, CURLOPT_URL, url_c);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _dawn_curl_alloc);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&buf_u);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hed_u);

  // note: must be terminated!
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, lod_u.base);

  result = curl_easy_perform(curl);
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &cod_l);

  // XX retry?
  if ( CURLE_OK != result ) {
    u3l_log("failed to fetch %s: %s\n",
            url_c, curl_easy_strerror(result));
    exit(1);
  }
  if ( 300 <= cod_l ) {
    u3l_log("error fetching %s: HTTP %ld\n", url_c, cod_l);
    exit(1);
  }

  curl_easy_cleanup(curl);
  curl_slist_free_all(hed_u);

  return buf_u;
}

/* _dawn_get_jam(): GET a jammed noun from url_c
*/
static u3_noun
_dawn_get_jam(c3_c* url_c)
{
  CURL *curl;
  CURLcode result;
  long cod_l;

  uv_buf_t buf_u = uv_buf_init(c3_malloc(1), 0);

  if ( !(curl = curl_easy_init()) ) {
    u3l_log("failed to initialize libcurl\n");
    exit(1);
  }

  //  XX require TLS, pin default cert?
  //
  u3K.ssl_curl_f(curl);
  curl_easy_setopt(curl, CURLOPT_URL, url_c);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _dawn_curl_alloc);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&buf_u);

  result = curl_easy_perform(curl);
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &cod_l);

  // XX retry?
  if ( CURLE_OK != result ) {
    u3l_log("failed to fetch %s: %s\n",
            url_c, curl_easy_strerror(result));
    exit(1);
  }
  if ( 300 <= cod_l ) {
    u3l_log("error fetching %s: HTTP %ld\n", url_c, cod_l);
    exit(1);
  }

  curl_easy_cleanup(curl);

  //  throw away the length from the octs
  //
  u3_noun octs = _dawn_buf_to_oct(buf_u);
  u3_noun jammed = u3a_gain(u3x_t(octs));
  u3a_lose(octs);

  c3_free(buf_u.base);

  return u3ke_cue(jammed);
}

/* _dawn_eth_rpc(): ethereum JSON RPC with request/response as +octs
*/
static u3_noun
_dawn_eth_rpc(c3_c* url_c, u3_noun oct)
{
  uv_buf_t buf_u = _dawn_post_json(url_c, _dawn_oct_to_buf(oct));
  u3_noun    pro = _dawn_buf_to_oct(buf_u);

  c3_free(buf_u.base);

  return pro;
}

/* _dawn_fail(): pre-boot validation failed
*/
static void
_dawn_fail(u3_noun who, u3_noun rac, u3_noun sas)
{
  u3_noun how = u3v_dc("scot", 'p', u3a_gain(who));
  c3_c* how_c = u3r_string(u3a_gain(how));

  c3_c* rac_c;

  switch (rac) {
    default: c3_assert(0);
    case c3__czar: {
      rac_c = "galaxy";
      break;
    }
    case c3__king: {
      rac_c = "star";
      break;
    }
    case c3__duke: {
      rac_c = "planet";
      break;
    }
    case c3__earl: {
      rac_c = "moon";
      break;
    }
    case c3__pawn: {
      rac_c = "comet";
      break;
    }
  }

  u3l_log("boot: invalid keys for %s '%s'\r\n", rac_c, how_c);

  // XX deconstruct sas, print helpful error messages
  while ( u3_nul != sas ) {
    u3m_p("pre-boot error", u3x_h(sas));
    sas = u3x_t(sas);
  }

  u3a_lose(how);
  c3_free(how_c);
  exit(1);
}

/* _dawn_need_unit(): produce a value or print error and exit
*/
static u3_noun
_dawn_need_unit(u3_noun nit, c3_c* msg_c)
{
  if ( u3_nul == nit ) {
    u3l_log("%s\r\n", msg_c);
    exit(1);
  }
  else {
    u3_noun pro = u3a_gain(u3x_t(nit));
    u3a_lose(nit);
    return pro;
  }
}

/* _dawn_turf(): override contract domains with -H
*/
static u3_noun
_dawn_turf(c3_c* dns_c)
{
  u3_noun tuf;

  u3_noun par = u3v_wish("thos:de-purl:html");
  u3_noun dns = u3i_string(dns_c);
  u3_noun rul = u3v_dc("rush", u3a_gain(dns), u3a_gain(par));

  if ( (u3_nul == rul) || (c3n == u3x_h(u3x_t(rul))) ) {
    u3l_log("boot: invalid domain specified with -H %s\r\n", dns_c);
    exit(1);
  }
  else {
    u3l_log("boot: overriding network domains with %s\r\n", dns_c);
    u3_noun dom = u3x_t(u3x_t(rul));
    tuf = u3i_cell(u3a_gain(dom), u3_nul);
  }

  u3a_lose(par); u3a_lose(dns); u3a_lose(rul);

  return tuf;
}

/* _dawn_sponsor(): retrieve sponsor from point
*/
static u3_noun
_dawn_sponsor(u3_noun who, u3_noun rac, u3_noun pot)
{
  u3_noun uni = u3v_dc("sponsor:dawn", u3a_gain(who), u3a_gain(pot));

  if ( c3n == u3x_h(uni) ) {
    _dawn_fail(who, rac, u3i_cell(u3x_t(uni), u3_nul));
    return u3_none;
  }

  u3_noun pos = u3a_gain(u3x_t(uni));

  u3a_lose(who); u3a_lose(rac); u3a_lose(pot); u3a_lose(uni);

  return pos;
}

/* u3_dawn_vent(): validated boot event
*/
u3_noun
u3_dawn_vent(u3_noun ship, u3_noun feed)
{
  u3_noun sed, pos, pon, zar, tuf;

  u3_noun rank = u3v_do("clan:title", u3a_gain(ship));

  c3_c* url_c = ( 0 != u3_Host.ops_u.eth_c ) ?
    u3_Host.ops_u.eth_c :
    "https://roller.urbit.org/v1/azimuth";

  {
    //  +point:azimuth: on-chain state
    //
    u3_noun pot;

    if ( c3__pawn == rank ) {
      //  irrelevant, just bunt +point
      //
      pot = u3v_wish("*point:azimuth");
    }
    else  if ( c3__earl == rank ) {
      pot = u3v_wish("*point:azimuth");
    }
    else {
      u3l_log("boot: retrieving %s's public keys\r\n",
              u3_Host.ops_u.who_c);

      {
        u3_noun oct = u3v_do("point:give:dawn", u3a_gain(ship));
        u3_noun luh = _dawn_eth_rpc(url_c, u3a_gain(oct));

        pot = _dawn_need_unit(u3v_dc("point:take:dawn", u3a_gain(ship), u3a_gain(luh)),
                              "boot: failed to retrieve public keys");
        u3a_lose(oct); u3a_lose(luh);
      }
    }

    //  +live:dawn: network state
    //  XX actually make request
    //
    u3_noun liv = u3_nul;
    // u3_noun liv = _dawn_get_json(parent, /some/url)

    u3l_log("boot: verifying keys\r\n");

    //  (each seed (lest error=@tas))
    //
    sed = u3v_dq("veri:dawn", u3a_gain(ship), u3a_gain(feed), u3a_gain(pot), u3a_gain(liv));

    if ( c3n == u3x_h(sed) ) {
      // bails, won't return
      _dawn_fail(ship, rank, u3x_t(sed));
      return u3_none;
    }

    u3l_log("boot: getting sponsor\r\n");
    pos = _dawn_sponsor(u3a_gain(ship), u3a_gain(rank), u3a_gain(pot));
    u3a_lose(pot); u3a_lose(liv);
  }


  //  (map ship [=life =pass]): galaxy table
  //
  {
    u3l_log("boot: retrieving galaxy table\r\n");

    u3_noun oct = u3v_wish("czar:give:dawn");
    u3_noun raz = _dawn_eth_rpc(url_c, u3a_gain(oct));

    zar = _dawn_need_unit(u3v_do("czar:take:dawn", u3a_gain(raz)),
                          "boot: failed to retrieve galaxy table");
    u3a_lose(oct); u3a_lose(raz);
  }

  //  (list turf): ames domains
  //
  if ( 0 != u3_Host.ops_u.dns_c ) {
    tuf = _dawn_turf(u3_Host.ops_u.dns_c);
  }
  else {
    u3l_log("boot: retrieving network domains\r\n");

    u3_noun oct = u3v_wish("turf:give:dawn");
    u3_noun fut = _dawn_eth_rpc(url_c, u3a_gain(oct));

    tuf = _dawn_need_unit(u3v_do("turf:take:dawn", u3a_gain(fut)),
                          "boot: failed to retrieve network domains");
    u3a_lose(oct); u3a_lose(fut);
  }

  pon = u3_nul;
  while (c3__czar != rank) {
    u3_noun son;
    //  print message
    //
    {
      u3_noun who = u3v_dc("scot", 'p', u3a_gain(pos));
      c3_c* who_c = u3r_string(who);
      u3l_log("boot: retrieving keys for sponsor %s\r\n", who_c);
      u3a_lose(who);
      c3_free(who_c);
    }

    //  retrieve +point:azimuth of pos (sponsor of ship)
    //
    {
      u3_noun oct = u3v_do("point:give:dawn", u3a_gain(pos));
      u3_noun luh = _dawn_eth_rpc(url_c, u3a_gain(oct));

      son = _dawn_need_unit(u3v_dc("point:take:dawn", u3a_gain(pos), u3a_gain(luh)),
                            "boot: failed to retrieve sponsor keys");
      // append to sponsor chain list
      //
      pon = u3i_cell(u3i_cell(u3a_gain(pos), u3a_gain(son)), pon);
      u3a_lose(oct); u3a_lose(luh);
    }

    // find next sponsor
    //
    u3a_lose(ship); u3a_lose(rank);
    ship = pos;
    rank = u3v_do("clan:title", u3a_gain(ship));
    pos = _dawn_sponsor(u3a_gain(ship), u3a_gain(rank), u3a_gain(son));

    u3a_lose(son);
  }

  //  [%dawn seed sponsors galaxies domains block eth-url snap]
  //
  //NOTE  blocknum of 0 is fine because jael ignores it.
  //      should probably be removed from dawn event.
  u3_noun ven = u3i_cell(c3__dawn,
                     u3i_qual(u3a_gain(u3x_t(sed)), pon, zar, u3i_trel(tuf, 0, u3_nul)));

  u3a_lose(sed); u3a_lose(rank); u3a_lose(pos); u3a_lose(ship); u3a_lose(feed);

  return ven;
}

/* _dawn_come(): mine a comet under a list of stars
*/
static u3_noun
_dawn_come(u3_noun stars)
{
  u3_noun seed;
  {
    c3_w    eny_w[16];
    u3_noun eny;

    c3_rand(eny_w);
    eny = u3i_words(16, eny_w);

    u3l_log("boot: mining a comet. May take up to an hour.\r\n");
    u3l_log("If you want to boot faster, get an Urbit identity.\r\n");

    seed = u3v_dc("come:dawn", u3a_gain(stars), u3a_gain(eny));
    u3a_lose(eny);
  }

  {
    u3_noun who = u3v_dc("scot", 'p', u3a_gain(u3x_h(seed)));
    c3_c* who_c = u3r_string(who);

    u3l_log("boot: found comet %s\r\n", who_c);

  //  enable to print and save comet private key for future reuse
  //
#if 0
    {
      u3_noun key = u3v_dc("scot", c3__uw, u3qe_jam(seed));
      c3_c* key_c = u3r_string(key);

      u3l_log("boot: comet private key\n  %s\n", key_c);

      {
        c3_c  pat_c[64];
        snprintf(pat_c, 64, "%s.key", who_c + 1);

        FILE* fil_u = fopen(pat_c, "w");
        fprintf(fil_u, "%s\n", key_c);
        fclose(fil_u);
      }

      c3_free(key_c);
      u3a_lose(key);
    }
#endif

    c3_free(who_c);
    u3a_lose(who);
  }

  u3a_lose(stars);

  return seed;
}

/* u3_dawn_come(): mine a comet under a list of stars we download
*/
u3_noun
u3_dawn_come()
{
  return _dawn_come(
      _dawn_get_jam("https://bootstrap.urbit.org/comet-stars.jam"));
}
