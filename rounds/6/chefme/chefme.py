import base64
import random

f = open("flag.txt", "r")
fb = f.read().encode("utf-8")
jeepers = base64.b16encode(fb)
test = random.randint(1, 50)
nb = bytes([byte ^ test for byte in jeepers])
f = base64.b85encode(nb)
f2 = str(f,"utf-8")
print(f2)
