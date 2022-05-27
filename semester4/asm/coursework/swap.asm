global swap

swap:
    ; arg1 (void* mem1) - rdi
    ; arg2 (void* mem2) - rsi
    ; arg3 (long len)   - rdx

    mov rcx, rdx ; counter
    jecxz func_exit

    swap_loop:
        lodsb             ; si -> al
        mov rbx, [rdi]    ; tmp copy of [rdi]
        stosb             ; al -> di
        mov [rsi - 1], bl ; bl -> [rsi - 1]
    loop swap_loop

    func_exit:

