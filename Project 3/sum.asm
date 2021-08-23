;; =============================================================
;; CS 2110 - Fall 2020
;; Project 3 - Alternating Sum
;; =============================================================
;; Name: Swapnil Lad
;; =============================================================

.orig x3000

LD R4, ARRAY
AND R1, R1, 0
LD R1, LENGTH

LD R6, LENGTH

AND R5, R5, 0

LOOP
ADD R1, R1, -1
BRn STOPIT
LDR R0, R4, 0

AND R2, R1, 1
BRp ODD
ADD R5, R5, R0
BR MOVEON

ODD
NOT R0, R0
ADD R0, R0, 1
ADD R5, R5, R0
BR MOVEON

MOVEON
ADD R4, R4, 1
BR LOOP

STOPIT

AND R6, R6, 1
BRp CALLIT
NOT R5, R5
ADD R5, R5, 1
BR CALLIT

CALLIT
ST R5, RESULT
HALT

LENGTH      .fill 4
ARRAY       .fill x7000
RESULT      .blkw 1

.end


.orig x7000
    .fill 1
    .fill 2
    .fill 3
    .fill 4
.end
