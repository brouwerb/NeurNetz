import math
slices = 100000000
au = 0
ai = 0
for i in range(slices):
    x = i/slices
    au = au + math.sqrt(1-x**2)/slices
    x = (i+1)/slices
    ai = ai + math.sqrt(1-x**2)/slices

print("Obersumme:    ", 4*au)
print("Untersumme:   ", 4*ai)
print("Literaturwert:", math.pi)