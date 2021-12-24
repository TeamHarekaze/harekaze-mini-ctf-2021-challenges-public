# この問題ではsagemath(https://www.sagemath.org/)を利用します。
# インストールして、 `sage problem.sage` コマンドを実行することで実行することができます。
# this problem requires `sagemath(https://www.sagemath.org/)`.
# you can run `sage problem.sage` after install this tool.

# *sagemathに* pycryptodomeを入れる必要があります。
# `sage --sh` コマンドでshellに入った後、`pip install pycryptodome` で Python の module をインストールすることが可能です。
# to solve this problem, you have to install `pycryptodome`.
# After entering the shell with the command `sage --sh`, you can use `pip install pycryptodome` to install the Python module.
from Crypto.Util.number import *
from flag import flag

# bytes <- str
flag = flag.encode('utf-8')
# long <- bytes
flag = bytes_to_long(flag)

p = getStrongPrime(512)
q = getStrongPrime(512)
n = p*q
e = 65537

# 計算するたびに mod n を取る 行列を生成します。
# generate matrix which calculate modulus n at every operation.
m = matrix(Zmod(n), [
    [p, 0],
    [0, flag]
])

# sagemathでは ^ は xor を表さずに、冪乗を表しています。
# in sagemath, ^ means exponentiation. not `xor`
m = m^e

# listで二次元配列に変換します。
# convert two-dimensional array by list() function
print("c =",list(m))
print("n =",n)
print("e =",e)

# hint 1
# c = [? 0] <= what's ?
#     [0 ?] <= what's ?
# hint 2
# JP: https://ja.wikipedia.org/wiki/%E6%9C%80%E5%A4%A7%E5%85%AC%E7%B4%84%E6%95%B0
# EN: https://en.wikipedia.org/wiki/Greatest_common_divisor