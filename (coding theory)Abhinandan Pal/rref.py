import math
from bitarray import bitarray
a = [bitarray('011001'),
	 bitarray('101010'),
	 bitarray('010101'),
	 bitarray('111001'),
	 bitarray('110110')]
def makeZero(col):
	one_col =[]
	for i in range(col,len(a)):
		if(a[i][col]==True):
			one_col.append(i)
	if(len(one_col)== 0):
		return;
	for i in range(1,len(one_col)):
		addRow(one_col[i],one_col[0])  # ci = ci + c0
	swapRow(0+col,one_col[0])

def swapRow(i,j):
	temp = a[i]
	a[i]= a[j]
	a[j] = temp

def addRow(r1,r2):
	a[r1] = a[r1] ^ a[r2]
		
for i in range(min(len(a[0]),len(a))):
	makeZero(i)
for i in range(len(a)):
	print(a[i])

		



	