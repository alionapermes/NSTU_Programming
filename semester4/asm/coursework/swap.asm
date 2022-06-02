global swap

swap:
    ; arg1 (void* mem1) - rdi
    ; arg2 (void* mem2) - rsi
    ; arg3 (long len)   - rdx

    mov rcx, rdx

    swap_qword:
        jrcxz func_exit

        cmp rcx, 8
        jl swap_byte

        xor rbx, rbx

        mov rbx, [rsi]
        fild qword [rdi]
        fistp qword [rsi]
        mov [rdi], rbx

        add rdi, 8
        add rsi, 8
        add rcx, -8
    jmp swap_qword

    swap_byte:
        xor bl, bl
        xor al, al

        mov bl, [rdi]
        movsb
        mov [rsi - 1], bl
    loop swap_byte

    func_exit:

