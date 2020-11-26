SET true = 84
SET false = 70
DWORD dt = true
DWORD df = false
SET x = 1
SET y = 2
CHECK 2 x=y
PRINT dt -> STDOUT
PRINT df -> STDOUT
CHECK 2 x!=y
PRINT dt -> STDOUT
JMP 14
PRINT df -> STDOUT
CHECK 2 x<=y
PRINT dt -> STDOUT
JMP 18
PRINT df -> STDOUT