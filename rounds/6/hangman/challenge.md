# hangman

- Published: 08/15/2024 (#10/12 in round)
- Category: pwn
- Points: 100
- Author: kolmus

I was going through some of my old coding projects and I noticed that this hangman game was way too easy ...
All I changed is one line of code :) good **luck**!

## Attachments

- [hangman](./hangman)
- [hangman.c](./hangman.c)
- `nc 173.230.133.237 1024` (if the server is still up)

## Hint

This hint costed 15 points.

<details>
<summary>Reveal hint</summary>

look at the way the program determines which word is used. using a predictable seed is dangerous ...

</details>

## Write-up

<details>
<summary>Reveal write-up</summary>

There are multiple possible solutions for this challenge. Most people just ended up getting lucky by guessing (which was not intended). Instead, you were supposed to abuse the weak random word selection of the program.

```c
srand(time(NULL));
int i = rand() % (sizeof(words) / sizeof(words[0]));
// words[i] is the word that is used
```

This uses the current unix time (in seconds) as a seed for the random number generator. 2 possible ways to exploit this are:

- Connecting to the challenge twice within the same second. they will have the same seed -> you can fail one game on purpose to get the word and use it to beat the other one
- Writing a script that will use the same random number generator + seed and tells you the correct word before making the request (note that this requires a synchronized system with the same random number generator implementation)

Flag: ```csd{G3TT1n6_tHE_HaN6_0F_1T}```

</details>

Write-up by kolmus
