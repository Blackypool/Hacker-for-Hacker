.model tiny
.code
org 100h

;            0      2        4          6            8        10        12     14          32-33                     34 - byte
; save_er [off09, seg09, psw_sucss? num_of_let    true_psw                          kanareyka in the end    1/0 = true or no flag
;                           PPPPLL                                                                                     1 = true

Start:

            jmp Main

Main:

;_______________________save & replace old int09h seg & offs
            xor ax, ax
			mov es, ax

            ; offs segm
            ; 0000 0000
            mov bx, 4 * 09h             ; sdvig 09h^ inter = 4b

 ;          save old interrupt in save_er
            xor si, si

            mov ax, es:[bx]
            mov word ptr cs:save_er[si], ax

            mov ax, es:[bx + 2]
            mov word ptr cs:save_er[si + 2], ax
 ;

            ; replace int09h to func irritator9 <=> its change offset ot new segment                        

            mov es:[bx], offset irritator9    ; mine offset
            mov es:[bx + 2], cs               ; start of mine segment
;_______________________


            mov si, 6                            ; here save num of where save new let
            mov word ptr cs:save_er[si], 10      ; start posi of where save scan codes // need_swap_for_new_offset

            add si, 2 ; = 8
            mov bx, 176                          ; true psw = summ
            mov word ptr cs:save_er[si], bx


            mov si, 32
            mov bx, 9111h                        ;   letter, which press + unpress = kanareyka // value of Kana
            mov word ptr cs:save_er[si], bx

;;;;

            mov dx, offset Fin          ; smeschenie 
            add dx, 34                  ; sizof(buf)
            shr dx, 4                   ; byte -> paragraph
            inc dx                      ; +1 for not zero div

            mov ax, 3100h               ; interrpt for save in memory code // unlimited use 
            int 21h                     ; need sixe of programm in dx in paragraph

;_____________________________________________________



;===============irritator9============================

;   func:       hook S = first letter of password // enter = enter password
;   Entry:      void
;   Exit:       vid mem
;   Expected:   void
;   Destr:      nothing, all save, but in use  //ax, bx, dx, es//

;=====================================================

    irritator9      proc
;{
    cli     ; protect from int08h

            push ax                     ; save regs for use
            push bx
            push dx
            push si
            push es


            mov si, 32                          ; sizof(buf) - 2
            mov ax, word ptr cs:save_er[si]     ; check Kana
            mov dx, 9111h                       ; value of Kana

            cmp dx, ax
            jne bad_psw

            xor ax, ax
            in al, 60h                  ; al = scan from klava

            mov si, 1Ch                 ; si = enter or if unEntern ->

            cmp si, ax 
            je  enter_password          ; if press ___enter___ clear

            jmp func_for_eat_symb


    enter_password:
    ;{
        call check_passw

            xor bx, bx
            xor ax, ax

            mov si, 34                  ; check flag
            mov bl, byte ptr cs:save_er[si]

            mov al, 1

            cmp bl, al

        je psw_is_true        
        ;{  ; printf(unluck);
         bad_psw:
            mov ax, 0b800h
            mov es, ax

            mov bx, 1000
            mov word ptr es:[bx], 4768h
            mov word ptr es:[bx + 2], 4761h
            mov word ptr es:[bx + 6], 476Ch
            mov word ptr es:[bx + 8], 476Fh
            mov word ptr es:[bx + 10], 4768h  
            
            jmp end_psw___        
        ;}

        psw_is_true:
        ;{  ; printf(luck);
            mov ax, 0b800h
            mov es, ax

            mov bx, 1000
            mov word ptr es:[bx], 2773h
            mov word ptr es:[bx + 2], 2775h
            mov word ptr es:[bx + 4], 2763h
            mov word ptr es:[bx + 6], 2763h
            mov word ptr es:[bx + 8], 2765h
            mov word ptr es:[bx +10], 2773h
            mov word ptr es:[bx +12], 2773h

            jmp end_psw___
        ;}
    ;}

    end_psw___:
    ;{
        in al, 61h
        or al, 80h                  ; 10000000b
        out 61h, al
        and al, not 80h
        out 61h, al

        mov al, 20h                 ; End Of Interrpt
        out 20h, al

        pop es
        pop si
        pop dx
        pop bx
        pop ax

        sti
        iret
    ;}

    func_for_eat_symb:
    ;{
        mov bx, 6                           ; here save num of where save new let
        mov si, word ptr cs:save_er[bx]

        mov byte ptr cs:save_er[si], al     ; save sc-c

        add si , 1                          ; update value
        mov word ptr cs:save_er[bx], si

        jmp retern_dominion_int9
    ;}

    retern_dominion_int9:
    ;{
            in al, 61h
            or al, 80h                  ; 10000000b
            out 61h, al
            and al, not 80h
            out 61h, al


            mov al, 20h                 ; End Of Interrpt
            out 20h, al

            pop es
            pop si
            pop dx
            pop bx
            pop ax

        ;
            push si

            xor si, si

            mov bx, word ptr cs:save_er[si]             ; offset = bx
            mov dx, word ptr cs:save_er[si + 2]         ; segment = dx

            pop si

            push dx
            push bx
            
            sti

            retf                        ; jmp to real int9
    ;}


    irritator9      endp    
;}
;_____________________________________________________



;===============check_passw============================

;   func:       doing flag
;   Entry:      void
;   Exit:       vid mem
;   Expected:   void
;   Destr:      void

;=====================================================

    check_passw      proc
;{
    push ax
    push si
    push bx
    push dx
    push di
    push es

    mov bx, 6                           ; here save num of where save new let
    mov si, word ptr cs:save_er[bx]     ; si = num of let*2 = end of sch

    mov bx, 10          ; bx = posi of now symb        need_swap_for_new_offset
    xor dx, dx          ; final formul
    xor ax, ax
    
   ;_______________________
    while_ch_psw:
    ;{
        mov al, byte ptr cs:save_er[bx]

        add dx, ax          ; defolt summ of symb for eaysy find collisium

        add bx, 2

        cmp bx, si
        jb while_ch_psw     ; if bx < si
    ;}


    mov bx, 8               ; here save true psw
    mov ax, word ptr cs:save_er[bx]
    cmp dx, ax

    jne passwa_unluck

        ;success
     ;{
        mov bx, 34

        xor ax, ax
        mov al, 1
        mov byte ptr cs:save_er[bx], al

        jmp endi__kk
     ;}
    
    passwa_unluck:
        jmp endi__kk        ; nothing change
   ;_______________________

 endi__kk:
    pop es
    pop di
    pop dx
    pop bx
    pop si
    pop ax
    
    ret

    check_passw      endp    
;}
;_____________________________________________________


save_er     DB 48 DUP(0)

Fin:

end			Start