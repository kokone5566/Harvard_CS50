while True:
    try:
        cash = float(input("Change owed: "))
    except:
        continue
    if cash > 0:
            break

cash *= 100
counter = 0
for i in [25, 10, 5, 1]:
    while cash >= i:
        counter += int(cash / i)
        cash %= i
print(counter)