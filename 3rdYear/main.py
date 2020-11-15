from polymodules.poly import poly
from polymodules.gf import inv
from polymodules.gf import power


a = poly(input())
IP = poly('11001')
b = inv(a, IP)
print('a = ' + a.to_exp())
print('IP = ' + IP.to_exp())
print('inv(a) = ' + b.to_exp())
