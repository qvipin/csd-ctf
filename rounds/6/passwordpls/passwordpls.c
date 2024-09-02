// gcc passwordpls.c -o passwordpls
// running: ./passwordpls anexamplepassword

#include<stdio.h>
#include<string.h>

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Usage: %s <password>\n", argv[0]);
        return 1;
    }

    printf("This challenge will modify the provided argument through a series of operations and compare it to a hardcoded value.\n");
    // to pass the check, you will need to reverse the operations so that the input matches the value by the end of the program.

    printf("Checking password...\n");

    // check if the password has the correct length
    int len = strlen(argv[1]);

    if (len != 0x18) {
        printf("Invalid password length!\n");
        return 1;
    }

    // copy the input to a buffer (to avoid modifying the original input)
    char input[0x19] = {0};
    strncpy(input, argv[1], 0x18);

    // add 1 to each character in the input
    for (int i = 0; i < len; i++) {
        input[i] += 1;
    }

    // reverse the input
    for (int i = 0; i < len / 2; i++) {
        char tmp = input[i];
        input[i] = input[len - i - 1];
        input[len - i - 1] = tmp;
    }

    // xor with a key
    char key[] = "dvdYRiiR66r6X3XXSj03QQXy";
    for (int i = 0; i < len; i++) {
        input[i] ^= key[i];
    }

    // make sure the result matches the hardcoded value: P8Va2Q04yV4SiW8l79fCg1i6
    if (strcmp(input, "P8Va2Q04yV4SiW8l79fCg1i6") == 0) {

        printf("Correct!\n");
        printf("The flag is: csd{%s}\n", argv[1]);

    } else {
        printf("Wrong password!\n");
    }

    return 0;
}