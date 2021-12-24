from Crypto.Util.number import *
from params import *
import base64

flag = flag ^ key
flag = long_to_bytes(flag)
flag = base64.b64decode(flag)
print(flag)