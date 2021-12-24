from sympy.ntheory.modular import crt
from Crypto.Util.number import *
from Crypto.Random.random import *
from params import *

values = []
primes = []
for p in range(2, 1000):
    if N % p == 0:
        primes.append(p)
        for i in range(p):
            if c%p == pow(i, e, p):
                values.append(i)

print(long_to_bytes(crt(primes, values)[0]))