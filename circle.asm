PUSH 100

PUSH 0  ;ббнд гмювемхъ оепелеммни |еБЦЕМ_ьОЮКЮ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

PUSH 100

PUSH 1  ;ббнд гмювемхъ оепелеммни |еПФЮМ_цМНЛ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

PUSH 20

PUSH 2  ;ббнд гмювемхъ оепелеммни |яЕПЕЦЮ_пЮДХСЯ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 0  ;бшбнд гмювемхъ оепелеммни |еБЦЕМ_ьОЮКЮ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 2
DIV

PUSH 3  ;ббнд гмювемхъ оепелеммни |жЕМРП_юПЙЮДХВ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 1  ;бшбнд гмювемхъ оепелеммни |еПФЮМ_цМНЛ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 2
DIV

PUSH 4  ;ббнд гмювемхъ оепелеммни |жЕМРП_нКЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

PUSH 0

PUSH 5  ;ббнд гмювемхъ оепелеммни |яВЕРВХЙ_лЮЙЮПШВ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

PUSH 0

PUSH 6  ;ббнд гмювемхъ оепелеммни |яВЕРВХЙ_еБЦЕМ_ьОЮКЮ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

PUSH 0

PUSH 7  ;ббнд гмювемхъ оепелеммни |яВЕРВХЙ_еПФЮМ_цМНЛ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


:begin_while_0

PUSH 5  ;бшбнд гмювемхъ оепелеммни |яВЕРВХЙ_лЮЙЮПШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 0  ;бшбнд гмювемхъ оепелеммни |еБЦЕМ_ьОЮКЮ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 1  ;бшбнд гмювемхъ оепелеммни |еПФЮМ_цМНЛ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL

JB :L_less_0
PUSH 0
:L_less_0


PUSH 5  ;бшбнд гмювемхъ оепелеммни |яВЕРВХЙ_лЮЙЮПШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 0  ;бшбнд гмювемхъ оепелеммни |еБЦЕМ_ьОЮКЮ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 1  ;бшбнд гмювемхъ оепелеммни |еПФЮМ_цМНЛ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL

JA :L_bigger_0
PUSH 1
:L_bigger_0


PUSH 0
JE :endwhile_0


PUSH 3  ;бшбнд гмювемхъ оепелеммни |жЕМРП_юПЙЮДХВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 6  ;бшбнд гмювемхъ оепелеммни |яВЕРВХЙ_еБЦЕМ_ьОЮКЮ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

SUB

PUSH 3  ;бшбнд гмювемхъ оепелеммни |жЕМРП_юПЙЮДХВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 6  ;бшбнд гмювемхъ оепелеммни |яВЕРВХЙ_еБЦЕМ_ьОЮКЮ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

SUB
MUL

PUSH 4  ;бшбнд гмювемхъ оепелеммни |жЕМРП_нКЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 7  ;бшбнд гмювемхъ оепелеммни |яВЕРВХЙ_еПФЮМ_цМНЛ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

SUB

PUSH 4  ;бшбнд гмювемхъ оепелеммни |жЕМРП_нКЕЦШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 7  ;бшбнд гмювемхъ оепелеммни |яВЕРВХЙ_еПФЮМ_цМНЛ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

SUB
MUL
ADD

PUSH 8  ;ббнд гмювемхъ оепелеммни |юМДПЧУЮ_пЮЯЯРНЪМХЕ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 8  ;бшбнд гмювемхъ оепелеммни |юМДПЧУЮ_пЮЯЯРНЪМХЕ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦЮ_пЮДХСЯ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦЮ_пЮДХСЯ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL

JB :L_less_1
PUSH 0
:L_less_1


PUSH 8  ;бшбнд гмювемхъ оепелеммни |юМДПЧУЮ_пЮЯЯРНЪМХЕ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦЮ_пЮДХСЯ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 2  ;бшбнд гмювемхъ оепелеммни |яЕПЕЦЮ_пЮДХСЯ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL

JA :L_bigger_1
PUSH 1
:L_bigger_1


PUSH 0
JE :endif_0

PUSH 7  ;бшбнд гмювемхъ оепелеммни |яВЕРВХЙ_еПФЮМ_цМНЛ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 1  ;бшбнд гмювемхъ оепелеммни |еПФЮМ_цМНЛ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL

PUSH 6  ;бшбнд гмювемхъ оепелеммни |яВЕРВХЙ_еБЦЕМ_ьОЮКЮ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

ADD
PUSH 3
MUL

PUSH 9  ;ббнд гмювемхъ оепелеммни |лЮЙЯНМ_йННПДХМЮРШ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 9  ;бшбнд гмювемхъ оепелеммни |лЮЙЯНМ_йННПДХМЮРШ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


POPREG BX
PUSH 255
POPM [BX]
PUSH 1
PUSHREG BX
ADD
POPREG BX
PUSH 128
POPM [BX]
PUSH 1
PUSHREG BX
ADD
POPREG BX
PUSH 255
POPM [BX]
:endif_0


PUSH 5  ;бшбнд гмювемхъ оепелеммни |яВЕРВХЙ_лЮЙЮПШВ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 1
ADD

PUSH 5  ;ббнд гмювемхъ оепелеммни |яВЕРВХЙ_лЮЙЮПШВ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 6  ;бшбнд гмювемхъ оепелеммни |яВЕРВХЙ_еБЦЕМ_ьОЮКЮ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 0  ;бшбнд гмювемхъ оепелеммни |еБЦЕМ_ьОЮКЮ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


JE :E_equal_0
PUSH 0
:E_equal_0


PUSH 6  ;бшбнд гмювемхъ оепелеммни |яВЕРВХЙ_еБЦЕМ_ьОЮКЮ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 0  ;бшбнд гмювемхъ оепелеммни |еБЦЕМ_ьОЮКЮ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


JNE :E_not_equal_0
PUSH 1
:E_not_equal_0


PUSH 0
JE :endif_with_else_0

PUSH 0

PUSH 6  ;ббнд гмювемхъ оепелеммни |яВЕРВХЙ_еБЦЕМ_ьОЮКЮ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 7  ;бшбнд гмювемхъ оепелеммни |яВЕРВХЙ_еПФЮМ_цМНЛ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 1
ADD

PUSH 7  ;ббнд гмювемхъ оепелеммни |яВЕРВХЙ_еПФЮМ_цМНЛ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


:endif_with_else_0

PUSH 6  ;бшбнд гмювемхъ оепелеммни |яВЕРВХЙ_еБЦЕМ_ьОЮКЮ|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 1
ADD

PUSH 6  ;ббнд гмювемхъ оепелеммни |яВЕРВХЙ_еБЦЕМ_ьОЮКЮ|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]




JMP :begin_while_0

:endwhile_0

DRAW
HLT

