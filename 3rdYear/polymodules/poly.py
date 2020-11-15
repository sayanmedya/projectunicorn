from bitarray import bitarray

class poly(bitarray):
    def to_exp(self):
        s = ''
        for i in range(len(self) - 1, -1, -1):
            if self[i]:
                if len(s) != 0:
                    s += ' + '
                if i == 0:
                    s += '1'
                elif i == 1:
                    s += 'x'
                else:
                    s += 'x^' + str(i)
        if len(s) == 0:
            s = '0'
        return s
    
    def calc_deg(self):
        n = len(self)
        for i in range(n - 1, -1, -1):
            if self[i]:
                return i
        return 0

    def __xor__(self, b):
        x = bitarray(self)
        y = bitarray(b)
        if len(x) < len(y):
            x = x + bitarray('0'*(len(y) - len(x)))
        elif len(y) < len(x):
            y = y + bitarray('0'*(len(x) - len(y)))
        return poly(x ^ y)

    def __add__(self, b):
        return self.__xor__(b)

    def __sub__(self, b):
        return self.__xor__(b)

    def __mul__(self, b):
        p = poly()
        for bit in self:
            if bit:
                p = p + b
            b = b>>1
        return p

    def __lshift__(self, n):
        return self[n:]

    def __rshift__(self, n):
        return poly(bitarray('0'*n).__add__(self))

    def __repr__(self):
        return "{}('{}')".format(type(self).__name__, self.to01())

    def truncate_zeros(self): # 10110000 -> 1011
        n = len(self)
        for i in range(n - 1, -1, -1):
            if self[i]:
                return self[:i+1]
        return poly()

    def __floordiv__(self, b): # return quotient(self, b)
        b = b.truncate_zeros()
        if len(b) == 0:
            raise Exception('Divition by zero polynomial')
        p = self.copy()
        q = poly('0' * max((len(p) - len(b) + 1), 0))
        for i in range(len(p) - 1, len(b) - 2, -1):
            if p[i]:
                p = p + (b>>(i - len(b) + 1))
                q[i - len(b) + 1] = True
        return q

    def __mod__(self, b): # return remainder(self, b)
        return self - b * (self // b)
