;; =============================================================
;; CS 2110 - Fall 2020
;; Project 3 - To Uppercase
;; =============================================================
;; Name: Swapnil Lad
;; =============================================================

.orig x3000

LD R4, STRING ;string start address loaded
AND R1, R1, 0
LD R2, CONVERM
LD R3, LOWER_A
LD R5, LOWER_Z

LOOP
LDR R0, R4, 0 ;character at index of string loaded into R0
BRz ENDREACHED ;if value at index is 0 and the string is over

ADD R6, R0, 0
ADD R6, R6, R3
BRn LOOPR
ADD R6, R0, 0
ADD R6, R6, R5
BRp LOOPR
ADD R0, R0, R2 ;add to make it uppercase

LOOPR
ADD R0, R0, 0
OUT

ADD R4, R4, 1
BR LOOP

ENDREACHED

;LEA R0, STRING
;PUTS

HALT

TOUPPER     .fill xdf
LOWER_A     .fill -97
LOWER_Z     .fill -122

CONVERM     .fill -32

STRING      .fill x4000
RESULT      .blkw 1
.end

.orig x4000
.stringz "hAhA"
.end
