a_addr = 0x104060
b_addr = 0x1040e0
a_lis = []
for i in range(32):
	a_lis.append(getInt(toAddr(a_addr + (4 * i))))

#a_lis = [122, 69, 62, 88, 61, 87, 53, 57, 108, 104, 95, 73, 58, 56, 84, 97, 52, 96, 56, 141, 86, 76, 133, 58, 64, 61, 59, 87, 115, 59, 48, 0]
b_lis = []
for i in range(32):
	b_lis.append(getInt(toAddr(b_addr + (4 * i))))

#b_lis = [-13968, -16102, -20064, -19089, -17976, -17848, -21350, -15958, -11725, -15792, -11550, -24108, -19323, -20241, -17557, -19700, -18924, -18721, -19952, -9310, -18315, -16245, -9384, -19323, -21177, -15326, -20300, -20160, -7824, -18590, -21625, 0]

import math
def solve(b,c):
	D = math.sqrt(b**2 - (4 * c))
	x1 = (-b + D) / 2
	x2 = (-b -D) /2
	return x1,x2

ans = []
for i in range(32):
	x1,x2 = solve(a_lis[i],b_lis[i])
	ans.append(int(x1))

print(''.join([chr(x) for x in ans]))
#'HarekazeCTF{quadrat1c_3quati0n}\x00'
