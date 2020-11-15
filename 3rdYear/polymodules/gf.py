from polymodules.poly import poly

def inv(a, IP):
    r1 = a.copy().truncate_zeros()
    if len(r1) == 0:
        raise Exception('Inverse of zero polynomial does not exist')
    x1 = poly('1')
    y1 = poly()
    r2 = IP.copy()
    x2 = poly()
    y2 = poly('1')
    while len(r1) != 0:
        r = (r2 % r1).truncate_zeros()
        q = r2 // r1
        x = x2 - q * x1
        y = y2 - q * y1
        r2, x2, y2 = r1, x1, y1
        r1, x1, y1 = r, x, y
    return x2

def power(a, n, IP):
    p = poly('1')
    while n > 0:
        if n % 2 == 1:
            p = (p * a) % IP
        a = (a * a) % IP
        n = n >> 1
    return p
