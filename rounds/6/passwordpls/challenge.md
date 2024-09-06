# passwordpls

- Published: 07/26/2024 (#4/12 in round)
- Category: Reverse Engineering
- Points: 50
- Author: kolmus

I don't think this needs a hint. the source code is enough...

## Attachments

- [passwordpls](./passwordpls)
- [passwordpls.c](./passwordpls.c)

## Write-up

<details>
<summary>Reveal write-up</summary>

Simply reverse the operations done to the input before it's checked.

- Xor the hardcoded value with the key
- Reverse
- Subtract 1 from each byte
- Enter the result as the password

Below are intended solve scripts (First one is by Kolmus; second one is by Vipin)

```python
value = "P8Va2Q04yV4SiW8l79fCg1i6"
key = "dvdYRiiR66r6X3XXSj03QQXy"

xored = []
for i in range(len(value)):
    xored.append(chr(ord(value[i]) ^ ord(key[i])))

reversed = xored[::-1]

decremented = []
for char in reversed:
    decremented.append(chr(ord(char) - 1))

print("Password:", ''.join(decremented))
```

```py
from pwn import xor
s1 = b'P8Va2Q04yV4SiW8l79fCg1i6';s2 = b'dvdYRiiR66r6X3XXSj03QQXy'
xored = xor(s1, s2) [::-1]
final = bytearray()
for x in xored:
    final.append(x - 1)

flag = f"csd{{{final.decode()}}}"
print(flag)
```

Flag: ```csd{N0_5oURc3_c0dE_NeX7_71M3}```

</details>

Write-up by kolmus
