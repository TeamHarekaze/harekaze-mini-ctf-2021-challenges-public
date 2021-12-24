from sympy.ntheory.modular import crt
from Crypto.Util.number import *
from Crypto.Random.random import *
from flag import flag

flag = bytes_to_long(flag)

N = 1
num = 2
while N < flag:
    if isPrime(num):
        N *= num
    num += 1

p = getStrongPrime(512)
q = getStrongPrime(512)
N = N * p * q
e = 65537
c = pow(flag, e, N)

print("bit_length =", flag.bit_length())
print("c =", c)
print("e =", e)
print("N =", N)
