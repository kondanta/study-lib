PAGE 55,132
.386
STACK_SEG SEGMENT STACK USE16
DB 100 DUP(?)
STACK_SEG ENDS
DATA_SEG SEGMENT 'DATA' USE16
MESSAGE DB 'Enter the msg: $',0DH,0AH
OUTMSG1 DB 0DH,0AH,'Lowercase $'
OUTMSG2 DB 0DH,0AH,'Uppercase $'
INSTRING DB 60, ?, 60 DUP('$')
NEWLINE DB 0DH,0AH,'$'
DATA_SEG ENDS
CODE_SEG SEGMENT PARA 'CODE' PUBLIC USE16
ASSUME CS:CODE_SEG, DS:DATA_SEG, SS:STACK_SEG
MAIN PROC FAR
PUSH DS ;INITIATE THE PROGRAM
XOR AX,AX
PUSH AX
MOV AX,DATA_SEG
MOV DS,AX

LEA DX,MESSAGE ;PRINT MESSAGE
MOV AH,9
INT 21H

MOV AH,0AH ;READ A string
LEA DX, INSTRING
INT 21H

mov cx,0 ;upc counter
mov bx,0 ;lwc counter

lea DI, INSTRING+2 ;Put the str to DI

loopp:
mov al, [DI]
cmp al, 'A'
jb lowercase ; Below A
cmp al, 'Z' 
ja lowercase ; Upper than Z

LEA DX,OUTMSG2 ;inc cx sim.
MOV AH,9
INT 21H

inc di
loop loopp
lowercase: ; Lowercase
cmp al, 'a'
jb spacecase ; Below a
cmp al, 'z'
ja spacecase ; Upper than A

LEA DX,OUTMSG1 ;inc bx sim.
MOV AH,9
INT 21H

inc di
loop loopp
spacecase: ; Case of having space " "
cmp al, ' '
jb ext ; if not space
cmp al, ' '
ja ext ; if not space
inc di
loop loopp
ext:
MOV DX,OFFSET NEWLINE
MOV AH,9 ;MOVE CURSOR TO NEXT LINE
INT 21H
RET
MAIN ENDP
CODE_SEG ENDS
END MAIN