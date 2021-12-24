from Crypto.Util.number import *
from flag import flag

assert flag.startswith('HarekazeCTF{')

p = getStrongPrime(512)
q = getStrongPrime(512)
e = 65537
n = p*q

print("e =", e)

out = []
for char in flag:
    out.append(pow(ord(char), e, n))

print("cs =", out)
