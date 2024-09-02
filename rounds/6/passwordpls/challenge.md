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

- xor the hardcoded value with the key
- reverse
- subtract 1 from each byte
- enter the result as the password

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

Flag: ```csd{N0_5oURc3_c0dE_NeX7_71M3}```

</details>

Write-up by kolmus
