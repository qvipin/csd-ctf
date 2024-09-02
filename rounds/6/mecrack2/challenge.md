# mecrack2

- Published: 08/26/2024 (#12/12 in round)
- Category: Reverse Engineering
- Points: 150
- Author: kolmus

The last one was a freebie, now it's time to get your hands dirty. Same old game, reverse the password -> get the flag.

## Attachments

- [mecrack2](mecrack2)

## Hint

This hint costed 20 points.

<details>
<summary>Reveal hint</summary>

dynamic analysis might be easier than static analysis for this one. try running the binary in a debugger and see what it does with your input. taking notes on the stack layout might be helpful too. reverse engineering is tedious ...
if you're having trouble debugging, that's because I stripped the binary. google ...

</details>

## Write-up

<details>
<summary>Reveal write-up</summary>

(Note: this challenge can be solved much more easily using angr or similar tools. At the time of writing, I was not familiar with angr ...)

Looking at some decompiled code while analyzing the binary dynamically with a debugger, here is how you could go about deconstructing what is happening in the binary:

```c
    rsp -= 0x100000 // allocates a big stack frame, this messes with some decompilers

    write(1, "Enter the password: ", 21)

    clear 16 bytes on the stack (this puts a null qword behind the input)

    read(0, rsp, 8) // read 8 bytes from stdin into rsp

    rsi = &"n\0u\0h\0 \0u\0h\0!\0!\0" // nuh uh!! with null bytes between each character (from .data section)
    
    // put those bytes into rax and rbx
    rax = *(uint64_t *)rsi // rax = 0x002000680075006e
    rbx = *(uint64_t *)(rsi + 8) // rbx = 0x0021002100680075

    input = *(uint64_t *)rsp

    // this behavior can be observed in gdb. essentially, it's interleaving the bytes of the input with the empty nuh uh!! bytes, one byte at a time in random order.
    rax = rax | (input[0] << 0x08) // rax = 0x002000680075 01 6e where 01 is the first byte of the input (input[0])
    rbx = rbx | (input[4] << 0x38) // rbx = 0x 05 21002100680075 where 05 is the fifth byte of the input (input[4])
    rax = rax | (input[2] << 0x28) // rax = 0x0020 03 680075016e
    rbx = rbx | (input[5] << 0x28) // rbx = 0x0521 06 2100680075
    rbx = rbx | (input[7] << 0x08) // rbx = 0x052100210668 08 75
    rax = rax | (input[3] << 0x38) // rax = 0x 04 2003680075016e
    rbx = rbx | (input[6] << 0x18) // rbx = 0x05210621 07 680875
    rax = rax | (input[1] << 0x18) // rax = 0x04200368 02 75016e
    
    // at this point, here is what rax and rbx look like:
    // rax = 0x04 20 03 68 02 75 01 6e
    // rbx = 0x05 21 06 21 07 68 08 75
    
    push rax and rbx
    clear rcx and rdx

    // here is how the data on the stack is laid out:
    /*
    rsp[0] = 0x75
    rsp[1] = input[7]
    rsp[2] = 0x68
    rsp[3] = input[6]
    rsp[4] = 0x21
    rsp[5] = input[5]
    rsp[6] = 0x21
    rsp[7] = input[4]
    rsp[8] = 0x6e
    rsp[9] = input[0]
    rsp[10] = 0x75
    rsp[11] = input[1]
    rsp[12] = 0x68
    rsp[13] = input[2]
    rsp[14] = 0x20
    rsp[15] = input[3]
    */

    // now follow some checks that are done on the input. if any of these fail, the program will print "Incorrect!" and exit.
    // using the information above, we can deduce the values of the input that will pass these checks.
    if ((*(uint8_t *))(rsp[2] - rsp[5]) != rsp[4]) goto FAILURE // 0x68 - input[5] != 0x21
    // so input[5] must be 0x47
    if ((*(uint8_t *))(rsp[8] + rsp[9]) != rsp[2]) goto FAILURE // 0x6e + input[0] != 0x68
    // so input[0] must be 0xfa (0x6e + 0xfa = 0x168, but only the lower byte is checked)
    if ((*(uint8_t *))(rsp[4] - rsp[11]) != rsp[0]) goto FAILURE // 0x21 - input[1] != 0x75
    // so input[1] must be 0xac
    if ((*(uint8_t *))(rsp[6] + rsp[3]) != rsp[12]) goto FAILURE // 0x21 + input[6] != 0x68
    // so input[6] must be 0x47
    if ((*(uint8_t *))(rsp[14] + rsp[13]) != rsp[6]) goto FAILURE // 0x20 + input[2] != 0x21
    // so input[2] must be 0x01
    if ((*(uint8_t *))(rsp[10] + rsp[15]) != rsp[14]) goto FAILURE // 0x75 + input[3] != 0x0d
    // so input[3] must be 0xab
    if ((*(uint8_t *))(rsp[12] + rsp[7]) != rsp[10]) goto FAILURE // 0x68 + input[4] != 0x75
    // so input[4] must be 0x0d
    if ((*(uint8_t *))(rsp[0] + rsp[1]) != rsp[8]) goto FAILURE // 0x75 + input[7] != 0x6e
    // so input[7] must be 0xf9

    // now in proper order:
    // password/input = \xfa\xac\x01\xab\x0d\x47\x47\xf9
    // inputting those bytes into the program will pass all the checks and print the flag.
    // echo -e -n "\xfa\xac\x01\xab\x0d\x47\x47\xf9" | ./mecrack2

    // now we have the following values in rax and rbx:
    // rax: 0x ab 20 01 68 ac 75 fa 6e
    // rbx: 0x 0d 21 47 21 47 68 f9 75

    xor rax, rbx // 0xa6014649eb1d031b
    mov rcx, 0x93320f22a8297158 // xor of rax, rbx and the flag
    xor rax, rcx // 0x3533496b43347243 (Cr4CkI35)
    push rax

    write(1, "Correct! The flag is: csd{", 27)
    write(1, rsp, 8)
    write(1, "}\n", 3)

    goto EXIT

    FAILURE:
        write(1, "Incorrect!\n", 12)

    EXIT:
        add rsp, 0x100000 // deallocate the stack frame
        exit(0)
```

now wasn't that fun? you're not ready for mecrack3 ...

Flag: ```csd{Cr4CkI35}```

</details>

Write-up by kolmus
