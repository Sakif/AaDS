org $80
Label01 word #0
org $FF00
Label02 word #1
org $100
Label03 MOVLZ Label01,R0
MOVLS Label02,R1
LD R0,R0
LD R1,R2
Label04 ADD R0,R2
CMP #16,R2
BNE Label04
ST R2,R1
Done BRA Done
END Label03
