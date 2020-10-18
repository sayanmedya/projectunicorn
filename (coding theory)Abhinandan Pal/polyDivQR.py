from bitarray import bitarray
p = bitarray('111010')
a = bitarray('000101')
n = len(a)
q = bitarray('0')
def leftshift(c,q1):
	c.append(0)
	q1.append(0)
	c = c[1:]
	return c;

def add(b,c):
	d = bitarray()
	for i in range (len(b)):
		d.append((b[i]+c[i])%2)
	return d;
def addb(b,c):
	b = bitarray('0'*(n-len (b))) + b
	c = bitarray('0'*(n-len (c))) + c
	return b^c;
print("Solve = "+str(p)+" / "+str(a))

temp  = a
while(p>a):
	pos = -1
	for i in range(len(p)):
		if(p[i] == 1):
			pos = i
			break;

	q1=bitarray('1')
	#print(p)
	while(p[i]!=a[i]):
		a = leftshift(a,q1)
	#print(a)
	p = addb(p,a)
	q = addb(q,q1)

	a = temp[:n]
	#print(q1)

print("Remainder = "+str(p))
print("Quotent = "+str(q))