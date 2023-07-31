ciphered = list(map(int, open('./assets/p59.txt').read().split(',')))
charrange = range(ord('a'), ord('z')+1)
keys = [(i, j, k)\
            for i in charrange\
            for j in charrange\
            for k in charrange\
            if i != j and j != k]
is_ok = lambda value: value >= 32 and value <= 122
candidates = []
for (i, j, k) in keys:
    ok = True
    deciphered = ''
    for char in range(0, len(ciphered), 3):
        a, b, c, *_ = (ciphered[char:char+3])
        a, b, c = i ^ a, j ^ b, k ^ c
        if not is_ok(a) or not is_ok(b) or not is_ok(c):
            ok = False
            break
        da, db, dc = chr(a), chr(b), chr(c)
        deciphered += da + db + dc
    if ok:
        candidates.append(deciphered)
for c in candidates:
    if 'the' in c and 'to' in c and 'be' in c:
        print(c, end='\n\n')
        print('values sum =', sum(map(ord, c)))
