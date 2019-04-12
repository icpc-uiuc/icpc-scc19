NMAX = 101

b = {}
c = {}
for i in range(NMAX):
  c[(i,0)] = 1
for j in range(1,NMAX):
  c[(0,j)] = 0
for i in range(1,NMAX):
  for j in range(1,NMAX):
    c[(i,j)] = c[(i-1,j)] + c[(i-1,j-1)]
b[0] = 1;
for i in range(1,NMAX):
  b[i] = sum([c[(i-1,j)] * b[j] for j in range(i)])

t = int(input())
for tt in range(t):
  n = int(input())
  print(b[n] % 1000000007)

