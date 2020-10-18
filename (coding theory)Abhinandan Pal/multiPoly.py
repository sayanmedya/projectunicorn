from bitarray import bitarray
p = bitarray('111010')
a = bitarray('000101')
IP = bitarray('110111') # 1 + x + x2 + x4 + x5
n = len(IP)
def leftshiftn(p,n): # left shift with extend 110 -> 1100 and n steps
	return p + bitarray('0'*n)

def addb(b,c):
	m = max(len(b),len(c))
	b = bitarray('0'*(m-len (b))) + b
	c = bitarray('0'*(m-len (c))) + c
	return b^c;

def multiLarger(p,a):
	m = bitarray('0')
	for i,x in enumerate(range(len(a)-1,-1,-1)):
		if(a[x] == 1):
			m = addb(leftshiftn(p,i),m)
	return m
#print(m)
def leftshift(c,q1):  # left shift without extend 110 -> 100 and n steps
	c.append(0)
	q1.append(0)
	c = c[1:]
	return c;
def divideToR(p,a): # p/a
	q = bitarray('0')
	m = max(len(p),len(a))
	p = bitarray('0'*(m-len (p))) + p
	a = bitarray('0'*(m-len (a))) + a
	n = len(a)
	temp  = a
	while(p>a):
		pos = -1
		for i in range(len(p)):
			if(p[i] == 1):
				pos = i
				break;
	
		q1=bitarray('1')
		while(p[i]!=a[i]):
			a = leftshift(a,q1)
		p = addb(p,a)
		q = addb(q,q1)
	
		a = temp[:n]
		#print(q1)

	return p
def multiGF(p,a,IP): # p*a mod IP
	mul = multiLarger(p,a)
	#print(mul)
	div = divideToR(mul,IP)
	ans = div[len(div)-len(IP):]
	return ans
print(multiGF(bitarray('111'),bitarray('101'),bitarray('1011')))