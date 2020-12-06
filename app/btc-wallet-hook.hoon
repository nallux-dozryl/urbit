::  btc-wallet-hook.hoon
::
::  Subscribes to:
::    btc-provider:
::      - connection status
::      - RPC call results/errors
::
::    btc-wallet-store
::      - requests for address info
::      - updates to existing address info
::
::  Sends updates to:
::    /sign-me
::
/-  *btc, *btc-wallet-hook, bws=btc-wallet-store
/+  dbug, default-agent, bwsl=btc-wallet-store, bp=btc-provider
|%
++  defaults
  |%
  ++  moon-limit  10
  --
+$  versioned-state
    $%  state-0
    ==
::  provider: maybe ship if provider is set
::  moon-limit: how many addresses a ship and its moons can request in piym
::  feybs: fee/byte in sats used for a given ship payee
::
+$  state-0
  $:  %0
      provider=(unit [host=ship connected=?])
      =btc-state
      def-wallet=(unit xpub)
      moon-limit=@ud
      feybs=(map ship sats)
      =reqs
      =piym
      =poym
      =piym-lock
  ==
::
+$  card  card:agent:gall
--
=|  state-0
=*  state  -
%-  agent:dbug
^-  agent:gall
=<
|_  =bowl:gall
+*  this      .
    def   ~(. (default-agent this %|) bowl)
    hc    ~(. +> bowl)
::
++  on-init
  ^-  (quip card _this)
  ~&  >  '%btc-wallet-hook initialized'
  :_  this(moon-limit.state moon-limit:defaults)
  :~  [%pass /r/[(scot %da now.bowl)] %agent [our.bowl %btc-wallet-store] %watch /requests]
      [%pass /u/[(scot %da now.bowl)] %agent [our.bowl %btc-wallet-store] %watch /updates]
  ==
++  on-save
  ^-  vase
  !>(state)
++  on-load
  |=  old-state=vase
  ^-  (quip card _this)
  ~&  >  '%btc-wallet-hook recompiled'
  `this(state !<(versioned-state old-state))
++  on-poke
  |=  [=mark =vase]
  ^-  (quip card _this)
  =^  cards  state
  ?+  mark  (on-poke:def mark vase)
      %btc-wallet-hook-action
    (handle-action:hc !<(action vase))
  ==
  [cards this]
::
++  on-watch
  |=  pax=path
  ^-  (quip card _this)
  ?+  pax  (on-watch:def pax)
      [%sign-me ~]
      `this
  ==
++  on-leave  on-leave:def
++  on-peek   on-peek:def
++  on-agent
  |=  [=wire =sign:agent:gall]
  ^-  (quip card _this)
  ?+  -.sign  (on-agent:def wire sign)
      %kick
    ~&  >>>  "kicked from provider {<src.bowl>}"
    ?~  provider  `this
    ?:  ?&  ?=(%set-provider -.wire)
            =(host.u.provider src.bowl)
        ==
      `this(provider ~)
    `this
    ::
      %fact
    =^  cards  state
      ?+  p.cage.sign  `state
          %btc-provider-status
        (handle-provider-status:hc !<(status:bp q.cage.sign))
        ::
          %btc-provider-update
        (handle-provider-update:hc !<(update:bp q.cage.sign))
        ::
          %btc-wallet-store-request
        (handle-wallet-store-request:hc !<(request:bws q.cage.sign))
        ::
          %btc-wallet-store-update
        (handle-wallet-store-update:hc wire !<(update:bws q.cage.sign))
      ==
    [cards this]
  ==
++  on-arvo  on-arvo:def
++  on-fail   on-fail:def
--
|_  =bowl:gall
++  handle-action
  |=  act=action
  ^-  (quip card _state)
  ?-  -.act
      %set-provider
    =*  sub-card
      [%pass /set-provider %agent [provider.act %btc-provider] %watch /clients]
    :_  state(provider [~ provider.act %.n])
    ?~  provider  ~[sub-card]
    :~  [%pass /set-provider %agent [host.u.provider %btc-provider] %leave ~]
        sub-card
    ==
    ::
      %set-default-wallet
    =/  xs=(list xpub)  scry-scanned
    ?.  (gth (lent xs) 0)  `state
    `state(def-wallet `(snag 0 xs))
    ::
      %req-pay-address
    ::  overwrites any payment being built currently
    ::  can't pay yourself; comets can't pay (could spam requests)
    ::  forwards poke to payee if payee isn't us
    ::  deletes poym since we'll be making a new outgoing payment
    ::  lets us set fee per byte and recall it once we get a payment address back
    ::  wire is /payer/value/timestamp
    ::
    ~|  "Can't pay ourselves; no comets"
    ?<  =(src.bowl payee.act)
    ?<  ?=(%pawn (clan:title payee.act))
    =+  feyb=?~(feyb.act fee.btc-state u.feyb.act)
    =>  .(poym ~, feybs (~(put by feybs) payee.act feyb))
    :_  state
    ~[(poke-wallet-hook payee.act [%gen-pay-address value.act])]
    ::
      %gen-pay-address
    :: TODO: only run this if the moon limit isn't passed
    ~|  "Can't pay ourselves; no comets"
    ?<  =(src.bowl our.bowl)
    ?<  ?=(%pawn (clan:title src.bowl))
    ?~  def-wallet  ~|("btc-wallet-hook: no def-wallet set" !!)
    =+  fam=(piym-key src.bowl)
    ?~  fam
      ~&  >>>  "not enough moon space or payer has an unconfirmed tx in to us"
      `state
    :_  state
    :~  %-  poke-wallet-store
        [%generate-address u.def-wallet %0 `[src.bowl value.act]]
    ==
    ::
      %ret-pay-address
    ?:  =(src.bowl our.bowl)  ~|("Can't pay ourselves" !!)
    ?~  def-wallet  ~|("btc-wallet-hook: no def-wallet set" !!)
    =+  feyb=(~(gut by feybs) src.bowl fee.btc-state)
    ?>  =(payer.act our.bowl)
    :_  state
    :~  %-  poke-wallet-store
        [%generate-txbu u.def-wallet `src.bowl feyb ~[[address.act value.act]]]
    ==
    ::
      %broadcast-tx
    `state
    ::
      %clear-poym
    `state(poym ~)
    ::
      %force-retry
    [(retry-reqs block.btc-state) state]
  ==
::  +handle-provider-status: handle connectivity updates from provider
::    - if status is %connected, retry all pending address lookups
::    - only retry all if previously disconnected
::    - if block is updated, retry all address reqs
::
++  handle-provider-status
  |=  s=status:bp
  ^-  (quip card _state)
  ?~  provider  `state
  ?.  =(host.u.provider src.bowl)  `state
  ?-  -.s
      %connected
    :_  %=  state
            provider  `[host.u.provider %.y]
            btc-state  [block.s fee.s now.bowl]
        ==
    ?:  ?!(connected.u.provider)
      (weld (retry-reqs block.s) retry-txbu)
    ?.  (lth block.btc-state block.s)  ~
    ~&  >  "got new block, retrying {<(lent (retry-reqs block.s))>} reqs "
    (retry-reqs block.s)
    ::
      %disconnected
    `state(provider `[host.u.provider %.n])
  ==
::
++  handle-provider-update
  |=  upd=update:bp
  ^-  (quip card _state)
  ?.  ?=(%.y -.upd)  `state
  ?-  -.body.p.upd
      %address-info
    =/  req=(unit request:bws)
      (~(get by reqs) req-id.p.upd)
    ?~  req  `state
    :_  state(reqs (~(del by reqs) req-id.p.upd))
    :~  %-  poke-wallet-store
        :*  %address-info  xpub.u.req  chyg.u.req  idx.u.req
            utxos.body.p.upd  used.body.p.upd  block.body.p.upd
        ==
    ==
    ::
      %raw-tx
    ?~  poym  `state
    =.  txis.u.poym  (update-poym-txis txis.u.poym +.body.p.upd)
    :_  state
    ?:(poym-ready ~[(send-sign-tx u.poym)] ~)
  ==
::  get address-info for the request if block in request is old
::
++  handle-wallet-store-request
  |=  req=request:bws
  ^-  (quip card _state)
  ?-  -.req
      %address-info
    =+  ri=(gen-req-id:bp eny.bowl)
    :_  state(reqs (~(put by reqs) ri req))
    ?~  provider  ~
    ?:  ?&  provider-connected
            (lth last-block.req block.btc-state)
        ==
      ~[(get-address-info ri host.u.provider a.req)]
    ~
  ==
::
++  handle-wallet-store-update
  |=  [=wire upd=update:bws]
  ^-  (quip card _state)
  ?-  -.upd
      %generate-address
    ::  if no peta (payer/value), just prints address
    ::
    ?~  peta.upd  ~&(> address.upd `state)
    =/  [payer=ship value=sats]  u.peta.upd
    :_  (update-piym address.upd payer value)
    :~  (poke-wallet-hook payer [%ret-pay-address address.upd payer value])
        (poke-wallet-store [%add-piym address.upd peta.upd])
    ==
    ::
      %generate-txbu
    ::  txbus can potentially use the same UTXO inputs, so if another payment
    ::   was in process of fetching raw-txs for a txbu, replace it
    ::
    :_  state(poym `txbu.upd)
    ?~  provider  ~&(>>> "provider not set" ~)
    %+  turn  txis.txbu.upd
    |=(=txi:bws (get-raw-tx host.u.provider txid.utxo.txi))
    ::
      %scan-done
    ?~  def-wallet
      `state(def-wallet `xpub.upd)
    `state
  ==
::  +piym-key: returns (unit ship), the sponsor of a ship
::  checks whether
::    - too many moons are already stored
::    - input ship is locked (i.e. broadcast a tx not in mempool yet)
::
++  piym-key
  |=  payer=ship
  ^-  (unit ship)
  ?:  (~(has by piym-lock) payer)
    ~
  =/  fam=ship
    ?:  =(%earl (clan:title payer))
      (sein:title our.bowl now.bowl payer)
    payer
  =+  ps=(~(get by piym) fam)
  ?~  ps  `fam
  ?:  (lte (lent u.ps) moon-limit.state)
    `fam
  ~
::  +update-piym: store an expected incoming payment by ship
::    moons are stored with their sponsor
::    if ship already has a payment for the payer ship, replace
::
++  update-piym
  |=  p=payment
  |^  ^-  _state
  =+  fam=(piym-key payer.p)
  ?~  fam  ~!("Too many moons or payer is locked" !!)
  =+  ps=(~(get by piym) u.fam)
  ?~  ps  (insert u.fam ~[p])
  =/  i=(unit @)
    (find ~[payer.p] (turn u.ps |=([* py=ship *] py)))
  ?~  i  (insert u.fam [p u.ps])
  (insert u.fam (snap u.ps u.i p))
  ++  insert
    |=  [u.fam=ship ps=(list payment)]
    state(piym (~(put by piym) u.fam ps))
  --
::  +update-poym-txis:
::    update outgoing payment with a rawtx, if the txid is in poym's txis
::
++  update-poym-txis
  |=  [txis=(list txi:bws) =txid rt=rawtx]
  ^-  (list txi:bws)
  =|  i=@
  |-  ?:  (gte i (lent txis))  txis
  =/  ith=txi:bws  (snag i txis)
  =?  txis  =(txid txid.utxo.ith)
   (snap txis i `txi:bws`ith(ur `rt))
  $(i +(i))
::  +poym-ready: whether all txis in poym have rawtxs
::
++  poym-ready
  ^-  ?
  ?~  poym  %.n
  %+  levy  txis.u.poym
  |=(t=txi:bws ?=(^ ur.t))
::  +retry-reqs: get-address-info for any reqs with old last-block
::
++  retry-reqs
  |=  [latest-block=@ud]
  ^-  (list card)
  ?~  provider  ~|("provider not set" !!)
  %+  murn  ~(tap by reqs)
  |=  [ri=req-id:bp req=request:bws]
  ?:  (gte last-block.req latest-block)  ~
  `(get-address-info ri host.u.provider a.req)
::
++  retry-txbu
  ^-  (list card)
  ?~  poym  ~
  ?~  provider  ~|("provider not set" !!)
  %+  turn  txis.u.poym
  |=  =txi:bws
  (get-raw-tx host.u.provider txid.utxo.txi)
::
++  get-address-info
  |=  [ri=req-id:bp host=ship a=address]
  ^-  card
  :*  %pass  /[(scot %da now.bowl)]  %agent  [host %btc-provider]
      %poke  %btc-provider-action  !>([ri %address-info a])
  ==
::
++  get-raw-tx
  |=  [host=ship =txid]
  ^-  card
  =/  ri=req-id:bp  (gen-req-id:bp eny.bowl)
  :*  %pass  /[(scot %da now.bowl)]  %agent  [host %btc-provider]
      %poke  %btc-provider-action  !>([ri %raw-tx txid])
  ==
::
++  provider-connected
  ^-  ?
  ?~  provider  %.n
  connected.u.provider
::
++  poke-wallet-hook
  |=  [target=ship act=action]
  ^-  card
  :*  %pass  /[(scot %da now.bowl)]  %agent
      [target %btc-wallet-hook]  %poke
      %btc-wallet-hook-action  !>(act)
  ==
::
++  send-sign-tx
  |=  =txbu:bws
  ^-  card
  [%give %fact ~[/sign-me] %btc-wallet-hook-request !>([%sign-tx txbu])]
::
++  poke-wallet-store
  |=  act=action:bws
  ^-  card
  :*  %pass  /[(scot %da now.bowl)]
      %agent  [our.bowl %btc-wallet-store]  %poke
      %btc-wallet-store-action  !>(act)
  ==
::
++  scry-scanned
  .^  (list xpub)
    %gx
    (scot %p our.bowl)
    %btc-wallet-store
    (scot %da now.bowl)
    %scanned
    %noun
  ==
--
