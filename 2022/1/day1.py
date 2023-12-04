with open('input', 'r') as f:
    lines = f.readlines()

cals = [0]
print(lines)

for l in lines:
    if (l == '\n'):
        cals.append(0)
    else:
        try:
            cal = int(l.strip())
            cals[-1] += cal
        except:
            pass            

print(max(cals))
