;; =============================================================
;; CS 2110 - Fall 2020
;; Project 3 - Modulus
;; =============================================================
;; Name: Swapnil Lad
;; =============================================================

.orig x3000
LD R1, A
BRp APOS
NOT R1, R1
ADD R1, R1, 1
APOS
ADD R1, R1, 0


LD R2, B
BRp BPOS
NOT R2, R2
ADD R2, R2, 1
BPOS
ADD R2, R2, 0

ADD R3, R2, 0

NOT R2, R2
ADD R2, R2, 1

ADD R1, R1, 0
WHILE
BRn END
BRz SEND
ADD R1, R1, R2
BR WHILE
END
ADD R1, R1, R3
BR COMPL
SEND
AND R1, R1, 0

COMPL
ST R1, RESULT
HALT

A       .fill 5
B       .fill 7
RESULT  .blkw 1
.end
