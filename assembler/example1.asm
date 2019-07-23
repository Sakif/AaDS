SIZE equ $26
CAP_A equ 'A'

org #80
BASE bss SIZE
org $1000

Start movlz CAP_A,R0

