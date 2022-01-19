::  takes in hoon files and builds a data structure with
::  lines tagged as either comments or code. doesn't work
::  with lines that have both just yet
::
|%
+$  tagl  [@tas tape]
::
++  eol  (just '\0a')  :: newline character
::  splits a tape into (list tape) separated by newlines
++  split  (star ;~(sfix (star prn) eol))
::  scans a comment line and outputs %comment
::  adds %comment label to commented line
++  coc   %+  stag  %comment
          ;~  plug
            col  col
            (star prn)
          ==
++  poc   (stag %code (star prn))
::
++  tag-line
  |=  line=tape  ^-  tagl
  ?:  =(-.line ':')
    ;;(tagl (scan line coc))
  ;;(tagl (scan line poc))
::
::  strip leading whitespace
++  strip  ;~(pfix (star ace) (star prn))
--
::
:-  %say
|=  [^ [arg=(list path) ~]]
:-  %noun
::  take in the file as a cord, convert to tape
=+  pax=-.arg
=/  raw=tape  (trip .^(@t %cx pax))
::  splits tape at newlines and strips whitespace
=/  clean-lines=(list tape)
  %+  turn
    (scan raw split)
  (curr scan strip)
=|  parsed-lines=(list tagl)
|-
?~  clean-lines
  parsed-lines
=+  parz=(tag-line -.clean-lines)
%=  $
  clean-lines  +.clean-lines
  parsed-lines  (weld parsed-lines (limo parz ~))
==
