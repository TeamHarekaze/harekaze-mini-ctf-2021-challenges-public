

flag ="HarekazeCTF{quadrat1c_3quati0n}"

import random

a = []
b = []
for i in flag:
    tmp = random.randrange(150,200)
    x = ord(i)
    a.append(tmp-x)
    b.append(-x * tmp)

print(a)
print(b)
    
#a = [122, 69, 62, 88, 61, 87, 53, 57, 108, 104, 95, 73, 58, 56, 84, 97, 52, 96, 56, 141, 86, 76, 133, 58, 64, 61, 59, 87, 115, 59, 48]
#b = [-13968, -16102, -20064, -19089, -17976, -17848, -21350, -15958, -11725, -15792, -11550, -24108, -19323, -20241, -17557, -19700, -18924, -18721, -19952, -9310, -18315, -16245, -9384, -19323, -21177, -15326, -20300, -20160, -7824, -18590, -21625]
