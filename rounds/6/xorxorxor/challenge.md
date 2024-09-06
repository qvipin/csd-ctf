# xorxorxor...

- Published: 08/12/2024 (#9/12 in round)
- Category: Cryptography/Programming
- Points: 50
- Author: kolmus

I <3 xor so much ... Can you reveal what's hidden behind this wall of text?

## Attachments

- [challenge](./challenge)

## Hint

This hint costed 5 points.

<details>
<summary>Reveal hint</summary>

I wonder what would happen if somebody were to xor all these random strings together ... hmm. automation is required for this one.

</details>

## Write-up

<details>
<summary>Reveal write-up</summary>

Xor all the lines together to get the flag.

Example solve script below:

```python
from pwn import *

with open('challenge', 'r') as f:
    lines = f.readlines()

result = lines[0].strip()
for i in range(1, len(lines)):
    result = xor(result, lines[i].strip())

print(result)
```

Flag: ```csd{K1n6_0F_X0R_a0eqjv1}```

</details>

Write-up by kolmus
