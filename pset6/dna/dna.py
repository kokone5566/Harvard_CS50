from sys import argv, exit
import re

if len(argv) != 3:
    print("Invalid\n")
    exit(1)

#test list
target = []
database = {}
#open database
with open(argv[1], "r") as outfile:
    for line in outfile:
        if len(target) == 0:
            for t in line.strip().split(",")[1:]:
                target.append(t)
        else:
            database[line.split(",")[0]] = [int(t) for t in line.strip().split(",")[1:]]
#print(target)
#print(database)


#open customer
with open(argv[2], "r") as outfile:
    for line in outfile:
        dna = line.strip()
#print(dna)
cum = []
for tar in target:
    tmp = []
    counter = []
    for match in re.finditer(tar, dna):
        tmp.append(match.span())
    num = 1
    for i in range(len(tmp)):
        if i + 1 < len(tmp):
            if tmp[i][1] == tmp[i + 1][0]:
                num += 1
            else:
                counter.append(num)
                num = 1
        else:
            counter.append(num)
    try:
        cum.append(max(counter))
    except:
        cum.append(0)

#cum = "+".join([str(t) for t in cum])
flag = True
for key, val in database.items():
    flag = True
    for i in range(len(val)):
        if val[i] != cum[i]:
            flag = False
            continue
    if flag == True:
        print(key)
        exit(0)

print("No match")