global swap

swap:
    ; arg1 (void* mem1) - rdi
    ; arg2 (void* mem2) - rsi
    ; arg3 (long len)   - rdx

    mov rcx, rdx ; counter
    jrcxz func_exit

    cmp rcx, 8
    jl swap_byte

    swap_qword:
        xor rbx, rbx

        mov rbx, [rsi]
        fild qword [rdi]
        fistp qword [rsi]
        mov [rdi], rbx

        add rdi, 8
        add rsi, 8

        add rcx, -8
        cmp rcx, 8
    jge swap_qword

    jrcxz func_exit

    swap_byte:
        xor bl, bl

        lodsb             ; si -> al
        mov bl, [rdi]     ; tmp copy of [rdi]
        stosb             ; al -> di
        mov [rsi - 1], bl ; bl -> [rsi - 1]
    loop swap_byte

    func_exit:

