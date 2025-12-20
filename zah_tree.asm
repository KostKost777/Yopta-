PUSH 0

PUSH 2  ;ббнд гмювемхъ оепелеммни |x|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]

IN

PUSH 2  ;ббнд гмювемхъ оепелеммни |x|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 2  ;бшбнд гмювемхъ оепелеммни |x|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

CALL :func_0
PUSHREG AX
OUT
HLT

:func_0

PUSH 5     ;пюглеп ярейнбнцн тпеилю
PUSHREG HX
ADD
POPREG HX
PUSH 0  ;ббнд гмювемхъ оепелеммни |x|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 0  ;бшбнд гмювемхъ оепелеммни |x|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 1

JE :E_equal_0
PUSH 0
:E_equal_0


PUSH 0  ;бшбнд гмювемхъ оепелеммни |x|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 1

JNE :E_not_equal_0
PUSH 1
:E_not_equal_0


PUSH 0
JE :endif_0
PUSH 1


POPREG AX    ;вепег AX бнгбюпюыюел гмювемхъ
PUSHREG HX
PUSH 5     ;пюглеп ярейнбнцн тпеилю
SUB
POPREG HX
RET

:endif_0


PUSH 0  ;бшбнд гмювемхъ оепелеммни |x|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

PUSH 1
SUB
CALL :func_0
PUSHREG AX

PUSH 1  ;ббнд гмювемхъ оепелеммни |res|
PUSHREG HX 
ADD
POPREG GX
POPM [GX]


PUSH 1  ;бшбнд гмювемхъ оепелеммни |res|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]


PUSH 0  ;бшбнд гмювемхъ оепелеммни |x|
PUSHREG HX 
ADD
POPREG GX
PUSHM [GX]

MUL


POPREG AX    ;вепег AX бнгбюпюыюел гмювемхъ
PUSHREG HX
PUSH 5     ;пюглеп ярейнбнцн тпеилю
SUB
POPREG HX
RET

