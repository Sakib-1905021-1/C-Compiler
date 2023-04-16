.MODEL SMALL
.STACK 1000H
.DATA
	FIXED_POINT_MULTIPLIER DW 64H
	CR EQU 0Dh
	LF EQU 0Ah
	NEWLINEM DB CR,LF,'$'
	TEN DW 10



NEWLINE PROC 
	
	PUSH AX
	PUSH DX
	
	LEA DX, NEWLINEM
	MOV AH,9
	INT 21h
	
	POP DX
	POP AX 
	RET
   
NEWLINE ENDP

PRINTNUMBER PROC
	PUSH CX
	MOV CX,0   
	
	CMP AX,0			 
	JG PRINTNUMBER_START 
	
	CMP AX,0
	JNE NOT_ZERO
	MOV DX,0
	ADD DL,'0'
	MOV AH, 02H
	INT 21H
CALL NEWLINE 
	POP CX  
	RET
	
	
	NOT_ZERO:
	PUSH AX
	MOV DX,'-'
	MOV AH, 02H
	INT 21H 
	POP AX  
	NEG AX
	
	PRINTNUMBER_START:
	CMP AX,0
	JE PRINTNUMBER_END 
	
	XOR DX, DX
	DIV TEN
	ADD DL, '0'
	PUSH DX
	INC CX
	JMP PRINTNUMBER_START
	
	PRINTNUMBER_END:
	
	PRINTNUMBER_LOOP:
		
		POP DX
		MOV AH, 02H
		INT 21H
	
	LOOP PRINTNUMBER_LOOP
CALL NEWLINE 
	POP CX
	RET
	
PRINTNUMBER ENDP



f PROC
	PUSH BP
	MOV BP,SP

; int k; 
	SUB SP,2

; k=5; 
	MOV CX,5
	MOV -2[BP],CX

; while (k>0){ a++; k--; }  
label3:
	MOV CX,-2[BP]
	PUSH CX
	MOV CX,0
	POP AX
	CMP AX,CX
	JG label1
	MOV CX,0
	JMP label2
label1:
	MOV CX,1
label2:
	JCXZ label4
; a++; 
	MOV CX,4[BP]
	INC 4[BP]

; k--; 
	MOV CX,-2[BP]
	 MOV AX,CX
	SUB AX,1
	MOV -2[BP],AX
	JMP label3
label4:

; return 3*a-7; 
	MOV CX,3
	PUSH CX
	MOV CX,4[BP]
	POP AX
IMUL CX
	MOV CX,AX
	PUSH CX
	MOV CX,7
	POP AX
	SUB AX,CX
	MOV CX,AX
	MOV DX,CX
	JMP f_exit

; a=9; 
	MOV CX,9
	MOV 4[BP],CX

f_exit:
	ADD SP,2
	POP BP
	RET
	f ENDP


g PROC
	PUSH BP
	MOV BP,SP

; int x,i; 
	SUB SP,2
	SUB SP,2

; x=f(a)+a+b; 
	MOV CX,6[BP]
	PUSH CX
	CALL f
	MOV CX,DX
	ADD SP,2
	PUSH CX
	MOV CX,6[BP]
	POP AX
	ADD AX,CX
	MOV CX,AX
	PUSH CX
	MOV CX,4[BP]
	POP AX
	ADD AX,CX
	MOV CX,AX
	MOV -2[BP],CX

; for (i=0; i<7; i++){ if (i%3==0){ x=x+5; }  else { x=x-1; }  }  
	MOV CX,0
	MOV -4[BP],CX
label11:
	MOV CX,-4[BP]
	PUSH CX
	MOV CX,7
	POP AX
	CMP AX,CX
	JL label5
	MOV CX,0
	JMP label6
label5:
	MOV CX,1
label6:
	JCXZ label12
; if (i%3==0){ x=x+5; }  else { x=x-1; }  
	MOV CX,-4[BP]
	PUSH CX
	MOV CX,3
	POP AX
CWD
IDIV CX
	MOV CX,DX
	PUSH CX
	MOV CX,0
	POP AX
	CMP AX,CX
	JE label7
	MOV CX,0
	JMP label8
label7:
	MOV CX,1
label8:

	JCXZ label9
; x=x+5; 
	MOV CX,-2[BP]
	PUSH CX
	MOV CX,5
	POP AX
	ADD AX,CX
	MOV CX,AX
	MOV -2[BP],CX

	JMP label10
label9:
; x=x-1; 
	MOV CX,-2[BP]
	PUSH CX
	MOV CX,1
	POP AX
	SUB AX,CX
	MOV CX,AX
	MOV -2[BP],CX

label10:
	MOV CX,-4[BP]
	INC -4[BP]
	JMP label11
label12:

; return x; 
	MOV CX,-2[BP]
	MOV DX,CX
	JMP g_exit

g_exit:
	ADD SP,4
	POP BP
	RET
	g ENDP


main PROC
	PUSH BP
	MOV BP,SP
	MOV AX,@DATA
	MOV DS,AX

; int a,b,i; 
	SUB SP,2
	SUB SP,2
	SUB SP,2

; a=1; 
	MOV CX,1
	MOV -2[BP],CX

; b=2; 
	MOV CX,2
	MOV -4[BP],CX

; a=g(a,b); 
	MOV CX,-2[BP]
	PUSH CX
	MOV CX,-4[BP]
	PUSH CX
	CALL g
	MOV CX,DX
	ADD SP,4
	MOV -2[BP],CX

; println (a); 
	MOV AX,-2[BP]
	CALL PRINTNUMBER

; for (i=0; i<4; i++){ a=3; while (a>0){ b++; a--; }  }  
	MOV CX,0
	MOV -6[BP],CX
label19:
	MOV CX,-6[BP]
	PUSH CX
	MOV CX,4
	POP AX
	CMP AX,CX
	JL label13
	MOV CX,0
	JMP label14
label13:
	MOV CX,1
label14:
	JCXZ label20
; a=3; 
	MOV CX,3
	MOV -2[BP],CX

; while (a>0){ b++; a--; }  
label17:
	MOV CX,-2[BP]
	PUSH CX
	MOV CX,0
	POP AX
	CMP AX,CX
	JG label15
	MOV CX,0
	JMP label16
label15:
	MOV CX,1
label16:
	JCXZ label18
; b++; 
	MOV CX,-4[BP]
	INC -4[BP]

; a--; 
	MOV CX,-2[BP]
	 MOV AX,CX
	SUB AX,1
	MOV -2[BP],AX
	JMP label17
label18:
	MOV CX,-6[BP]
	INC -6[BP]
	JMP label19
label20:

; println (a); 
	MOV AX,-2[BP]
	CALL PRINTNUMBER

; println (b); 
	MOV AX,-4[BP]
	CALL PRINTNUMBER

; println (i); 
	MOV AX,-6[BP]
	CALL PRINTNUMBER

; return 0; 
	MOV CX,0
	MOV DX,CX
	JMP main_exit

main_exit:
	ADD SP,6
	POP BP
	MOV AH,4ch
INT 21h

main ENDP


END Main
