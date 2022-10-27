import math

slices = 10000000

l = 0

for i in range(slices):
    x = i/slices
    d = 1.0/slices
    l = l + math.sqrt(1 + (x/(math.sqrt(1 - x**2)))**2)*d

print(l*2)
