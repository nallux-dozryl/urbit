/+  *server
/=  tile-js
  /^  octs
  /;  as-octs:mimes:html
  /:  /===/app/weather/js/tile
  /|  /js/
      /~  ~
  ==
/=  weather-png
  /^  (map knot @)
  /:  /===/app/weather/img  /_  /png/
=,  format
::
|%
:: +move: output effect
::
+$  move  [bone card]
:: +card: output effect payload
::
+$  card
  $%  [%poke wire dock poke]
      [%http-response =http-event:http]
      [%diff %json json]
      [%connect wire binding:eyre term]
      [%request wire request:http outbound-config:iris]
      [%wait wire @da]
  ==
+$  poke
  $%  [%launch-action [@tas path @t]]
  ==
+$  state
  $%  [%0 data=json time=@da location=@t timer=(unit @da)]
  ==
--
::
|_  [bol=bowl:gall state]
::
++  this  .
::
++  bound
  |=  [wir=wire success=? binding=binding:eyre]
  ^-  (quip move _this)
  [~ this]
::
++  prep
  |=  old=(unit state)
  ^-  (quip move _this)
  =/  launcha
    [%launch-action [%weather /weathertile '/~weather/js/tile.js']]
  :-
  :~
    [ost.bol %connect / [~ /'~weather'] %weather]
    [ost.bol %poke /weather [our.bol %launch] launcha]
  ==
  ?~  old
    this
  %=  this
    data  data.u.old
    time  time.u.old
  ==
::
++  peer-weathertile
  |=  pax=path
  ^-  (quip move _this)
  [[ost.bol %diff %json data]~ this]
::
++  poke-json
  |=  jon=json
  ^-  (quip move _this)
  ?.  ?=(%s -.jon)
    [~ this]
  =/  str/@t  +.jon
  =/  req/request:http  (request-darksky str)
  =/  out  *outbound-config:iris
  ?~  timer
    :-  %+  weld
      `(list move)`[ost.bol %wait /timer (add now.bol ~d1)]~
      `(list move)`[ost.bol %request /[(scot %da now.bol)] req out]~
    %=  this
      location  str
      timer  `(add now.bol ~d1)
    ==
  :-  [ost.bol %request /[(scot %da now.bol)] req out]~
  %=  this
    location  str
  ==
::
++  request-darksky
  |=  location=@t
  ^-  request:http
  =/  url/@t
    %-  crip  %+  weld
    (trip 'https://api.darksky.net/forecast/634639c10670c7376dc66b6692fe57ca/')
    (trip location)
  =/  hed  [['Accept' 'application/json']]~
  [%'GET' url hed *(unit octs)]
::
++  send-tile-diff
  |=  jon=json
  ^-  (list move)
  %+  turn  (prey:pubsub:userlib /weathertile bol)
  |=  [=bone ^]
  [bone %diff %json jon]
::
++  http-response
  |=  [=wire response=client-response:iris]
  ^-  (quip move _this)
  ::  ignore all but %finished
  ?.  ?=(%finished -.response)
    [~ this]
  =/  data/(unit mime-data:iris)  full-file.response
  ?~  data
    :: data is null
    [~ this]
  =/  jon/(unit json)  (de-json:html q.data.u.data)
  ?~  jon
     [~ this]
  ?>  ?=(%o -.u.jon)
  =/  ayyy/json  %-  pairs:enjs:format  :~
    currently+(~(got by p.u.jon) 'currently')
    daily+(~(got by p.u.jon) 'daily')
  ==
  :-  (send-tile-diff ayyy)
  %=  this
    data  ayyy
    time  now.bol
  ==
::
++  poke-handle-http-request
  %-  (require-authorization:app ost.bol move this)
  |=  =inbound-request:eyre
  ^-  (quip move _this)
  =+  request-line=(parse-request-line url.request.inbound-request)
  =+  back-path=(flop site.request-line)
  =/  name=@t
    =+  back-path=(flop site.request-line)
    ?~  back-path
      ''
    i.back-path
  ::
  ?~  back-path
    :_  this  ~
  ?:  =(name 'tile')
    [[ost.bol %http-response (js-response:app tile-js)]~ this]
  ?:  (lte (lent back-path) 1)
    [[ost.bol %http-response not-found:app]~ this]
  ?:  =(&2:site.request-line 'img')
    =/  img  (as-octs:mimes:html (~(got by weather-png) `@ta`name))
    [[ost.bol %http-response (png-response:app img)]~ this]
  [~ this]
::
++  wake
  |=  [wir=wire err=(unit tang)]
  ^-  (quip move _this)
  =/  req/request:http  (request-darksky location)
  =/  lismov/(list move)
    `(list move)`[ost.bol %request /[(scot %da now.bol)] req *outbound-config:iris]~
  ?~  timer
    :-  (weld lismov `(list move)`[ost.bol %wait /timer (add now.bol ~h3)]~)
    this(timer `(add now.bol ~h3))
  [lismov this]
::
--
