# rsabasics

- Published: 07/31/2024 (#6/12 in round)
- Category: Cryptography
- Points: 65
- Author: kolmus

A classic RSA challenge. Decrypt the cipher to get the flag.

## Attachments

- [rsabasics.txt](./rsabasics.txt)

## Hint

<details>
<summary>Reveal hint</summary>

the flag has 34 characters.
[https://en.wikipedia.org/wiki/RSA_(cryptosystem)](https://en.wikipedia.org/wiki/RSA_(cryptosystem))

python code that was used to encrypt the flag:

```python
flag = b'csd{this_is_not_the_real_flag}'
m = int.from_bytes(flag, 'little')
cipher = base64.b64encode(pow(m, e, n).to_bytes(256, 'little'))
```

#### Later in the round this hint was added due to lack of solutions:

This line of python code was used in the process of encrypting the flag
```py
cipher = base64.b64encode(pow(m, e, n).to_bytes(256, 'little'))
```

Also take a look at [what is rsa](https://ctf101.org/cryptography/what-is-rsa/) and [these ctf notes on rsa](https://book.jorianwoltjer.com/cryptography/asymmetric-encryption/rsa).

Lastly I want to mention this section of the pycryptodome (Crypto library) docs:

## Crypto.Util.number.bytes_to_long(s)
Convert a byte string to a long integer (**big endian**).

In Python 3.2+, use the native method instead:

int.from_bytes(s, 'big')
For instance:

> int.from_bytes(b'P', 'big')
> 80
> This is (essentially) the inverse of long_to_bytes().

-# (Note the difference in endianess here compared to what is used for the cipher.)

</details>

## Write-up

<details>
<summary>Reveal write-up</summary>

This is standard key generation starting from 2 primes.

- Compute private key ***d*** using the modular inverse
- Decode the Base64 encoded ciphertext -> Int
- Compute the message

Intended solve script:

```python
import base64

e = 0x10001
p = 0xcadccc461e3a64390fc41cf843e1562577f6f1f4a9513009e852edebb3ffae4a30bb604740e42aaadc042cfec430a72823f05b42f199676899b97c0de0113e14486fef5dcf9f4078afb7354ff80fdf8762db2c3826e28fd8a691f51f03873005e31b02c703cd63d7e11872e0155225c60f17c99776cb02ea435fab4535a1c3c9
q = 0xd207fbe478b5c12befd76b625d86774f61d7463484f46ba8a0ca68378abe5fea4320fbee426a4cfae984509e0dea0fcdce39f40d117c21e84eb882d77be7f124f5c1fe0319d99963be51d0414753d0b2d84899e3322a68b538ada947fce5d1d87862e6adf0183e8a6477dc30140382dbb5978d4cfa7685e65f1c604dbf57614b
cipher = '5q6f1mO/ONBSDLix2fgEkp3NHOV0XPMn9937w40SKf2aIzAGI2zZED6gWqdEzKkUd8MSNPApOwc1xzBl7LlK20TXaMaB8w6N7SflnmjY6l8QDDUJpQM858Lsu8SYPdg2fm9tAoXKVFOKRN5y98HpYYWdEcvBo3h5xbkDOquYnXsXF2qOOSZnu0jJ5BSEcwjYhTLKy7E4ATZeapi9be+KD2wX+aarpiQY6PewXTxExzi+MUS7yauVxiHe8+cLAgWWc8JJfxlV1+/CM+apOccTkgw6vhV4ptj82DhbdQoT2gwTcnzwg3d2rmiOHXebR69FaulMyCxhR3d0v7ksiZUuLg=='

n = p * q
phi = (p-1) * (q-1)
d = pow(e, -1, phi)
c = int.from_bytes(base64.b64decode(cipher), 'little')
m = pow(c, d, n).to_bytes(256, 'little') # where 256 just needs to be >= 34
print(m.decode())
```

Flag: ```csd{RSA_M34N5_R34D_5M4R7_4R71CL35}```

</details>

Write-up by kolmus
