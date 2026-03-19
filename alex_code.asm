.model tiny
.code
org 100h

Start:
            jmp Main


eater_psw          proc
;{
        push    bx
        push    cx
        push    di
    ;_____________save_regs

        mov     bx, 180h          ; here start writing psw
        xor     di, di            ; schetchik

    whilele:
        cmp     di, 8               ; can write 9symb withe 8 buffer => 9is flag => need ASCII = 1
        jg      end_of_first        ; jmp if first > second 

       ;_______eat ascii
        mov     ah, 1
        int     21h             ; AL = ASCIII read

       ;_______back_space?
        cmp     al, 8
        jne     enter_li

        cmp     di, 0           ; can skip and infinity swap in anything BX
        je      whilele         ; cant <0/?

        dec     di      
        dec     bx              ; sweety

        jmp     whilele
       ;_______

    ;_______enter press??
    enter_li:
        cmp     al, 0Dh
        je      end_of_first

    ;_______add in mem
        mov     [bx], al
        inc     di
        inc     bx

        jmp     whilele

    ;_______
    end_of_first:

    pop     di
    pop     cx
    pop     bx
    
    ret

    eater_psw      endp
;}
;_____________________________________________________



check_psw           proc
;{
    push    ax
    push    bx
    push    cx
    push    di

    mov     bx, 180h
    mov     di, 189h
    mov     cx, 8

    whilehile:
        cmp cx, 0               ; do cx = 0 in start?// rewrite true psw? // rewrite unluck??
        je  success_granded

        mov     al, [bx]
        xor     al, 3Fh         ; hash input

        ;_______cmp with true HASH
        cmp     al, [di]
        jne     end_of_check

        ;_______next symb
        inc di
        inc bx
        dec cx

        jmp whilehile

    success_granded:
        mov     bx, 188h
        mov     byte ptr [bx], 1


    end_of_check:
        pop     di
        pop     cx
        pop     bx
        pop     ax
        ret
    
    check_psw      endp
;}
;_____________________________________________________


Main:

            mov     dx, 191h            ; printf("Hello");
            mov     ah, 9
            int     21h   


            call eater_psw
            call check_psw


            mov     bx, 188h            ; !!!! go here and change flag ???? 
            cmp     byte ptr [bx], 1    ; 1 = success
            je      true_psw

            mov     dx, 1ACh    ; printf(incorrect psw);
            jmp     return_0
    

        true_psw:
            mov     dx, 1A2h    ; success

        return_0:
            mov     ah, 9
            int     21h            
                                
            mov     ax, 4C00h
            int     21h            
;_____________________________________________________


save_input_psw               db 9 dup(0)

random_true_hashed_psw       db 0Eh, 5Eh, 0Dh, 5Dh, 0Ch, 5Ch, 0Bh, 5Bh

prompt       db 'enter password: $'                   
success      db 0Dh, 0Ah, 'success$'                    
unluck       db 0Dh, 0Ah, 'incorrect password$'


;_____________________________________________________

end			Start