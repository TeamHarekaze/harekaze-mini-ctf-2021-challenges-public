from params import *
import math

i = 0
ns = []
for c in 'HarekazeCTF{':
    ns.append(pow(ord(c), e) - cs[i])
    i += 1

n = ns[0]
for nn in ns:
    n = math.gcd(n, nn)

res = ""
for c in cs:
    for i in range(256):
        if pow(i, e, n) == c:
            res += chr(i)

print(res)
