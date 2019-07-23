
;
; Sample XM2 Assembler program to increment a number by 1
; A. N. O'Nymous
; 7 May 2019
;
; Data space
org $80
Number word #0
;
; Code
org $1000
Start
;
; R0 = Address of Number
;
movlz Number,R0
;
; R1 = Value stored in Number [R0]
;
ld R0,R1
;
; Increment R1
;
add #1,R1
;
; Number [R0] = R1
;
st R1,R0
;
; End of program
; Specifying first executable location (Start)
;
end Start