import random, string

w = 1000
n = 1000
m = 100
q = 10000

words = []
weights = []
for i in range(w):
  word = ''.join(random.choices(string.ascii_lowercase, k=random.randint(1,10)))
  words.append(word)
  weights.append(random.random())
print(n)
for i in range(n):
  print(str(m) + ' ' + ' '.join(random.choices(words, weights=weights, k=m)))
print(q)
for i in range(q):
  print(' '.join(random.choices(words, weights=weights, k=2)))

