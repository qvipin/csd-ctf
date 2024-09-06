# chefme

- Published: 07/25/2024 (#3/12 in round)
- Category: Cryptography
- Points: 40
- Author: Vipin

try not to chatgpt if u want to practice your python skills!

## Attachments

- [enc](enc)
- [chefme.py](chefme.py)

## Hint

This hint costed 15 points.

<details>
<summary>Reveal hint</summary>

Analyze how the challenge is encrypting the text, you can use CyberChef or Python to decrypt it.

ModMail if you need more assistance.

</details>

## Write-up

<details>
<summary>Reveal write-up</summary>

The text is encoded in a simple way. Flag > encode in UTF-8 (to bytes) > Base16 encode (Hex) > Xored with random number between 1-50 > Base85 encode > *enc*

Below is a simple solve script where the whole process is reversed.
```python
import base64
import binascii

flagenc = input("enter enc text: ") 

flag_bytes = flagenc.encode("utf-8") # To bytes
    
jeepers = base64.b85decode(flag_bytes) # Decoding from base85

for test in range(1, 50):
    nb = bytes([byte ^ test for byte in jeepers]) # Bruteforcing the key used to xor
    try:
        decoded = nb.decode("utf-8") # decode from bytes
        if decoded.isprintable(): # check if it is printable text or text that isn't broken
            new = binascii.unhexlify(decoded) # decodes from hex
        print(new, test) # print flag and xor key
    except UnicodeDecodeError and binascii.Error:
        continue
```

Flag: `csd{H0ly_j33p3Rs_W4T_15_H4pP3ning_726f756e6436}`

</details>

Write-up by [Vipin](https://vipin.xyz)