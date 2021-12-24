import base64
import random 

# flag.py から flag を読み込みます。flag.pyは非公開なので、手元でデバッグするときは自分でテスト用のファイルを生成してください。
# Load the flag from flag.py. Since flag.py is not public, you can generate your own test file for debugging at hand.
from flag import flag 

# pycryptodomeから(https://pycryptodome.readthedocs.io/en/latest/) import します。使えない場合は `pip3 install pycryptodome` をしてください
# import from pycryptodome (https://pycryptodome.readthedocs.io/en/latest/). If you can't run this problem, do `pip3 install pycryptodome`
from Crypto.Util.number import long_to_bytes, bytes_to_long

flag = base64.b64encode(flag)
flag = bytes_to_long(flag)
key = random.randrange(flag)
flag = flag ^ key
print(f"{key = }")
print(f"{flag = }")
