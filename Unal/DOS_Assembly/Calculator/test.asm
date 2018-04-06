PAGE 55,132
.386
STACK_SEG SEGMENT STACK USE16
DB 100 DUP(?)
STACK_SEG ENDS
DATA_SEG SEGMENT 'DATA' USE16

err0 db 0Dh,0Ah ,'Not a number. $'
msg0 db "Calculator",0Dh,0Ah, '$'
msg1 db 'Enter the first number: $'
msg2 db "Enter the operator: $"
msg3 db "Enter second number: $"
msg4 db  0dh,0ah , 'Result : $' 

opr db '?'
num1 dw ?
num2 dw ?
ten dw 10

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

mov dx, offset msg0 ; start
mov ah, 9
int 21h


lea dx, msg1 ; Take the first number
mov ah, 09h   
int 21h  

call Scan_Num

mov num1, cx ; first number

lea dx, NEWLINE ; Newline
mov ah, 9
int 21h

lea dx, msg2 ; Take the operator
mov ah, 09h 
int 21h  

mov ah, 1 
int 21h
mov opr, al

lea dx, NEWLINE ; Newline
mov ah, 9
int 21h

lea dx, msg3 ; Take the second number
mov ah, 09h
int 21h  

call Scan_Num ; Do work with he number

mov num2, cx ; Second number

lea dx, msg4 ; Result
mov ah, 09h
int 21h 

cmp opr, '+'
je doplus

cmp opr, '-'
je dominus

cmp opr, '*'
je domult

cmp opr, '/'
je dodiv

doplus:
mov ax, num1
add ax, num2
call Print_Number
jmp ext

dominus:
mov ax, num1
sub ax, num2
call Print_Number 
jmp ext

domult:
mov ax, num1
imul num2 
;call Print_Number
jmp ext

dodiv: 
mov dx, 0
mov ax, num1
idiv num2
;call Print_Number
jmp ext

Scan_Num PROC NEAR

PUSH    DX
PUSH    AX
PUSH    SI

mov     CX, 0

mainn:
mov ah, 00h ; get the number
int 16h

mov ah, 0Eh ; print the number
int 10h

cmp al, 0Dh  ; Check for enter press
jne docheck ; if not
jmp stop_input ; if enter

docheck:
cmp al, '0'
jae docheck2
jmp not_number ; No need???

docheck2:
cmp al, '9'
jbe dowork
jmp not_number ; No need???

dowork:
PUSH AX
mov AX, CX
mul CS:ten  
mov CX, AX
pop AX

sub AL, 30h

mov AH, 0
mov DX, CX ; backup, in case the result will be too big.
add CX, AX

jmp mainn  

not_number:
mov dx, offset err0 ; error
mov ah, 9
int 21h
jmp stop_input
        
stop_input: ; stop the work
POP SI
POP AX
POP DX
RET

Scan_Num ENDP

Print_Number PROC NEAR

mov cx, 0 ; counter
mov bx, 10 ; will be used as 10

loopp:
mov dx, 0
div bx

push ax
add dl, '0' ;convert dl to ascii

pop ax
push dx
inc cx ; loop inc
cmp ax, 0
jnz loopp
mov ah, 2

loopp2:
pop dx                          
int 21h                         
loop loopp2
ret

Print_Number ENDP

ext:
MOV DX,OFFSET NEWLINE
MOV AH,9 ;MOVE CURSOR TO NEXT LINE
INT 21H
RET
MAIN ENDP
CODE_SEG ENDS
END MAIN