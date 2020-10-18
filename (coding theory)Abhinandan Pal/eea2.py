from bitarray import bitarray
p = bitarray('111010')
a = bitarray('000101')
IP = bitarray('110111') # 1 + x + x2 + x4 + x5
#n = len(IP)

def leftshiftn(p,n): # left shift with extend 110 -> 1100 and n steps
	return p + bitarray('0'*n)

def addb(b,c):
	m = max(len(b),len(c))
	b = bitarray('0'*(m-len (b))) + b
	c = bitarray('0'*(m-len (c))) + c
	return b^c;

def multiLarger(p,a): # multiply without mod
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

def divide(p,a): # p/a
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
	return p,q # reminder,quotent

def multiGF(p,a,IP): # p*a mod IP
	mul = multiLarger(p,a)
	#print(mul)
	div,x = divide(mul,IP)
	ans = div[len(div)-len(IP):]
	return ans

#print(multiGF(bitarray('111'),bitarray('101'),bitarray('1011'))) 

def exdeu(a,IP):
	n = len(IP)
	s0 = bitarray('0'*(n-1)+'1')
	s1 = bitarray('0'*(n-1)+'0')
	t0 = bitarray('0'*(n-1)+'0')
	t1 = bitarray('0'*(n-1)+'1')
	r0 = IP
	r1 = a
	
	while(r1 != bitarray("000001")):
		r2,q1 = divide(r0,r1)

		s2 = s0 ^ multiGF(q1,s1,IP)
		t2 = t0 ^ multiGF(q1,t1,IP)
		s0 = s1
		s1 = s2
		t0 = t1
		t1 = t2
		r0 = r1
		r1 = r2
	return t1

x = bitarray('10100')
inv = exdeu(x,IP)
#print(multiGF(bitarray('1110'),bitarray('000000'),IP))

#print(divide(IP,bitarray('101')))
#r0 = q1*r1 + r2
#r2 = q1*r1 -r0
print("Input : "+str(x))
print("IP: "+str(IP))
print("Inverse : "+str(inv))
print("1 : "+str(multiGF(inv,x,IP)))

#x = bitarray('000001')
#for i in range(10):
#	print(' X = ' + str(x)+' INV = '+str(exdeu(x,IP))+' 1 = '+str(multiGF(inv,x,IP)))
#	x = addb(x,bitarray('1'))

#10101,10111 --> 000001
#print(exdeu(bitarray('10000000'), bitarray('100011011')))



