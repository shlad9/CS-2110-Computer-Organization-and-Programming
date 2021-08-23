;; =============================================================
;; CS 2110 - Fall 2020
;; Project 3 - RPN Calculator
;; =============================================================
;; Name: Swapnil Lad
;; =============================================================


.orig x3000
HALT

;; DO NOT add anything before this line

;; !!!! PLEASE READ !!!!!
;; - The specification for each subroutine can be found before the corresponding
;;   label for the subroutine. It contains information about the input register(s),
;;   output register(s), and the operation that needs to be carried out
;;
;; - For some subroutines, we ask that you follow the pseudocode provided in the pdf.
;;   You are welcome to deviate from it, but we won't be able to help you in case you
;;   run into issues with the autograder
;;
;; - To test your subroutines, we highly recommend that you to use complx before
;;	 running the autograder. Details on how to run subroutines in complx can be found
;;   in the project pdf. We have covered this in lab too, so feel free to rewatch one
;;   of the lab recordings on this. Doing it this way will save you a TON of time.


;; Performs addition between two integers `a` and `b`
;;
;; input:		R0 = a, R1 = b
;; output:		R2 = a + b
my_add


	ADD R2, R0, R1

	RET


;; Performs subtraction between two integers `a` and `b`
;;
;; input:		R0 = a, R1 = b
;; output:		R2 = a - b
my_sub
	NOT R1, R1
	ADD R1, R1, 1
	ADD R2, R0, R1
	RET


;; Performs multiplication between two integers `a` and `b`
;;
;; input:		R0 = a, R1 = b
;; output:		R2 = a * b
;;
;; !!!!! IMPORTANT !!!!!
;; FOLLOW THE PSEDUOCODE PROVIDED IN THE PROJECT PDF
my_mul

	AND R3, R3, 0 ;RESULT
	; R1 is B
	AND R4, R4, 0 ;NEGATE

	ADD R1, R1, 0
	BRp MOVEON
	BRz MOVEON
	NOT R1, R1
	ADD R1, R1, 1
	ADD R4, R4, 1
	BR MOVEON

	MOVEON

	WHILE
	ADD R1, R1, 0
	BRnz OUTWHILE
	ADD R3, R3, R0
	ADD R1, R1, -1
	BR WHILE

	OUTWHILE

	ADD R4, R4, 0
	BRn DONE
	BRz DONE
	NOT R3, R3
	ADD R3, R3, 1

	DONE

	ADD R2, R3, 0
	RET



;; Performs **integer** division between two integers `a` and `b`
;;
;; input:		R0 = a, R1 = b
;; output:		R2 = a / b
;; examples:
;;				 4   /   2	=  2
;;				 16  /	 4	=  4
;;				 95  /	 5	=  19
;;
;;				 8  /   3	=  2	(not 2.6667)
;;				-8  /   3	= -2	(not -2.6667)
;;				 8  /  -3	= -2	(not -2.6667)
;;
;;				 5  /  10	=  0	(not 0.5)
;;				 5  / -10	=  0	(not -0.5)
;;				-5  / -10	=  0	(not -0.5)
;;
;; !!!!! IMPORTANT !!!!!
;; FOLLOW THE PSEDUOCODE PROVIDED IN THE PROJECT PDF
my_div
	;; YOUR IMPLEMENTATION HERE

AND R3, R3, 0 ;RESULT
;R0 is A
AND R4, R4, 0 ;negate

ADD R0, R0, 0
BRp ELSE
BRz ELSE
ADD R4, R4, -1
NOT R0, R0
ADD R0, R0, 1
BR ELSE

ELSE
;R1 is B
ADD R1, R1, 0
BRp ELER
BRz ELER
ADD R4, R4, 1
NOT R1, R1
ADD R1, R1, 1
BR ELER

ELER

WHILEM
NOT R5, R1
ADD R5, R5, 1
ADD R5, R0, R5
BRn BREAKWHILEL
NOT R5, R1
ADD R5, R5, 1
ADD R3, R3, 1
ADD R0, R0, R5
BR WHILEM

BREAKWHILEL

ADD R4, R4, 0
BRz ELSET
NOT R3, R3
ADD R3, R3, 1
BR ELSET

ELSET
ADD R2, R3, 0

RET

;; Evaluates an arithmetic expression that is in RPN form
;;
;; ## inputs
;; R0 = Base address of a string that contains an arithmetic
;; 	 expression in postfix notation
;;
;; ## outputs
;; R1 = The result of computing the arithmetic expression
;;
;; ## input constraints
;;
;; - Your postfix expression will only consist of **postive single digit** integers
;;   and operators. It won't contain illegal characters, parentheses, negative
;;   numbers, multiple-digit numbers, floating point numbers, or heck, even complex
;;   numbers. Just pure good old **positive single digit** integers!
;;
;; - You will always get a valid postix expression.
;;
;; ## implementation details
;;
;; Let's say we want to calculate (1-(5*8+2)). Since our calculator works on
;; postfix notation, we will need to convert this infix expression to postfix.
;; Doing this will give us (1 5 8 * 2 + -). The string version of this expression
;; is "158*2+-". Note that there are no spaces between the digits. Remember, your
;; expression will only consist of **postive single digit** integers, so you don't
;; have to worry about supporting negative integers, or multiple-digit integers.
;;
;; The subroutine `rpn` will receive the base address of the string "158*2+-".
;; For example, if your string is stored starting at memory location 0x4000, `rpn`
;; will receive 0x4000 through the R0 register.
;;
;; You will now need to evaluate this expression by iterating over the string, and
;; carrying out the operations outlined in the "Background" section of the project
;; pdf
;;
;; Finally, once you are done, you will need to save the final result in the
;; register R0.
;;
;; ## hints
;; - There are some useful labels at the bottom of this file. For example, we have
;;   given you a label that refers to the ASCII value of '+'. You will find this
;;   useful when trying to determine which operation to carry out. We have also
;;   provided you the ASCII value of the character '0'.
;; - There are some test postfix strings starting at x4000. You can access these via
;;	 EXP_LOC, and can use these strings when trying to develop the calculator initially
;; - Figure out how to run subroutines in complx. It will save you a TON of time
;;   during debugging!

rpn
	;; YOUR IMPLEMENTATION HERE


ADD R5, R0, 0
;string of expression loaded


LD R3, STACK
LD R6, STACKT
;if int push to stack
;if one of the special characters, pop from stack


LOOPOL
LDR R4, R5, 0
LD R1, ZERO
NOT R1, R1
ADD R1, R1, 1
ADD R1, R4, R1
BRz ENDREACHED

ADD R4, R4, 0
BRz ENDREACHED


LD R1, PLUS
NOT R1, R1
ADD R1, R1, 1

ADD R1, R4, R1
BRz PLUSP
LD R1, MINUS
NOT R1, R1
ADD R1, R1, 1

ADD R1, R4, R1
BRz MINUSP
LD R1, MULT
NOT R1, R1
ADD R1, R1, 1


ADD R1, R4, R1
BRz MULTP
LD R1, DIVIDE
NOT R1, R1
ADD R1, R1, 1

ADD R1, R4, R1
BRz DIVIDEP


LD R1, TOASCII
ADD R4, R4, R1

ADD R3, R3, #-1
STR R4, R3, #0

ADD R5, R5, 1
BR LOOPOL


PLUSP

ADD R6, R6, #-1
STR R0, R6, #0
ADD R6, R6, #-1
STR R1, R6, #0
ADD R6, R6, #-1
STR R2, R6, #0
ADD R6, R6, #-1
STR R7, R6, #0

LDR R1, R3, #0
ADD R3, R3, #1

LDR R0, R3, #0
ADD R3, R3, #1

JSR my_add

ADD R3, R3, #-1
STR R2, R3, #0

LDR R7, R6, #0
ADD R6, R6, #1
LDR R2, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1

LDR R0, R6, #0
ADD R6, R6, #1

BR OUTTAOP


MINUSP
ADD R6, R6, #-1
STR R0, R6, #0
ADD R6, R6, #-1
STR R1, R6, #0
ADD R6, R6, #-1
STR R2, R6, #0
ADD R6, R6, #-1
STR R7, R6, #0

LDR R1, R3, #0
ADD R3, R3, #1

LDR R0, R3, #0
ADD R3, R3, #1

JSR my_sub

ADD R3, R3, #-1
STR R2, R3, #0

LDR R7, R6, #0
ADD R6, R6, #1
LDR R2, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1

LDR R0, R6, #0
ADD R6, R6, #1

BR OUTTAOP


MULTP
ADD R6, R6, #-1
STR R0, R6, #0
ADD R6, R6, #-1
STR R1, R6, #0
ADD R6, R6, #-1
STR R2, R6, #0
ADD R6, R6, #-1
STR R3, R6, #0
ADD R6, R6, #-1
STR R4, R6, #0
ADD R6, R6, #-1
STR R5, R6, #0
ADD R6, R6, #-1
STR R7, R6, #0

LDR R1, R3, #0
ADD R3, R3, #1

LDR R0, R3, #0
ADD R3, R3, #1


JSR my_mul

ADD R0, R2, 0

LDR R7, R6, #0
ADD R6, R6, #1
LDR R5, R6, #0
ADD R6, R6, #1
LDR R4, R6, #0
ADD R6, R6, #1
LDR R3, R6, #0
ADD R6, R6, #1
LDR R2, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1

ADD R3, R3, #-1
STR R0, R3, #0

LDR R0, R6, #0
ADD R6, R6, #1

BR OUTTAOP


DIVIDEP
ADD R6, R6, #-1
STR R0, R6, #0
ADD R6, R6, #-1
STR R1, R6, #0
ADD R6, R6, #-1
STR R2, R6, #0
ADD R6, R6, #-1
STR R3, R6, #0
ADD R6, R6, #-1
STR R4, R6, #0
ADD R6, R6, #-1
STR R5, R6, #0
ADD R6, R6, #-1
STR R7, R6, #0

LDR R1, R3, #0
ADD R3, R3, #1

LDR R0, R3, #0
ADD R3, R3, #1

JSR my_div

ADD R0, R2, 0


LDR R7, R6, #0
ADD R6, R6, #1
LDR R5, R6, #0
ADD R6, R6, #1
LDR R4, R6, #0
ADD R6, R6, #1
LDR R3, R6, #0
ADD R6, R6, #1
LDR R2, R6, #0
ADD R6, R6, #1
LDR R1, R6, #0
ADD R6, R6, #1

ADD R3, R3, #-1
STR R0, R3, #0

LDR R0, R6, #0
ADD R6, R6, #1

BR OUTTAOP

OUTTAOP

ADD R5, R5, 1

BR LOOPOL

ENDREACHED

LDR R1, R3, #0


RET

;; some useful labels

;; ASCII value for important characters
PLUS	.fill x2B	;; +
MINUS	.fill x2D	;; -
MULT	.fill x2A	;; *
DIVIDE	.fill x2F	;; /
ZERO	.fill x30	;; 0
TOASCII  .fill -48
TOASCIIBA  .fill 48

;; initial stack pointer
STACK	.fill xf000
STACKT	.fill xf100
EXP_LOC .fill x4000
.end

.orig x4000
.stringz "34+"		;; expected output => R1 = 7
;; EXP	.stringz "54-3+"	;; expected output => R1 = 2
;; EXP	.stringz "58*42/-"	;; expected output => R1 = 38
.end
