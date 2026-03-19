.model tiny
.code
org 100h

Start:
            jmp Main

Main:

            xor ax, ax
			mov es, ax

 ;_____________________________________________
            mov bx, 4 * 08h            

            mov ax, es:[bx]
            mov word ptr cs:old_MeM[0], ax

            mov ax, es:[bx + 2]
            mov word ptr cs:old_MeM[2], ax
            
            mov es:[bx], offset new_08h       ; mine offset
            mov es:[bx + 2], cs               ; start of mine segment
 ;_____________________________________________

            mov dx, offset Fin          ; smeschenie 
            add dx, 4                   ; size of double buff
            shr dx, 4                   ; byte -> paragraph
            inc dx                      ; +1 for not zero div

            mov ax, 3100h               ; interrpt for save in memory code // unlimited use 
            int 21h 
;_____________________________________________________



;===============new_08h============================

;   Entry:      void
;   Exit:       vid mem for check
;   Expected:   void
;   Destr:      di

;=====================================================

new_08h     proc
;{
    push ax
    push dx
    push es
    push bx

   ;_________deystvie
    mov di, 1
    ; xor cx, cx

;    ;_________chage_fraze
;     mov ax, 52D0h
;     mov es, ax

;     mov bx, 1ACh

;         mov al, 's'
;         mov es:[bx],   al

;         mov al, 'u'
;         mov es:[bx+1], al

;         mov al, 'c'
;         mov es:[bx+2], al

;         mov al, 'c'
;         mov es:[bx+3], al

;         mov al, 'e'
;         mov es:[bx+4], al

;         mov al, 's'
;         mov es:[bx+5], al

;         mov al, 's'
;         mov es:[bx+6], al

;         mov al, '$'
;         mov es:[bx+7], al
;    ;;;;;;;;;;;;;;;;;;;;

   ;______report of working 
    mov ax, 0b800h
    mov es, ax

    mov byte ptr es:[1000], 03Ah
    mov byte ptr es:[1001], 03Ah
   ;_____________________

    pop bx
    pop es
    pop dx
    pop ax

   ;__________retern_domination
    jmp dword ptr cs:old_MeM[0]

    new_08h     endp
;}
;_____________________________________________________

old_MeM    DB 4 DUP(0)

Fin:

end			Start