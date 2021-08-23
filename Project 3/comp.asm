;; =============================================================
;; CS 2110 - Fall 2020
;; Project 3 - Compare
;; =============================================================
;; Name: Swapnil Lad
;; =============================================================

.orig x3000
LD R1, A
LD R2, B
LD R3, C
LD R4, D
LD R5, E
NOT R2, R2
ADD R2, R2, 1
ADD R1, R1, R2
BRp POS
BRn NEG
ST R5, RESULT
BR END
POS
ST R3, RESULT
BR END
NEG
ST R4, RESULT
BR END
END
HALT

A       .fill 5
B       .fill 7
C       .fill 1
D       .fill -1
E       .fill 0

RESULT  .blkw 1
.end
