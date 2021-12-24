from Crypto.Util.number import *
from params import *

p = GCD(c[0][0], n)
assert n % p == 0
q = n // p

d = pow(e, -1, (p-1)*(q-1))

print(long_to_bytes(pow(int(c[1][1]), int(d), int(n))).decode('utf-8'))