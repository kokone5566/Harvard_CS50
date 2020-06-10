def valid(num):
    #inverse
    num = [int(i) for i in num[::-1]]
    total = 0
    for i in range(len(num)):
        if ((i + 1) % 2 == 0):
            if num[i] * 2 >= 10:
                total += (1 + (num[i] * 2) % 10)
            else:
                total += (num[i] * 2)
        else:
            total += num[i]
        #print(total)
    if total % 10 == 0:
        return True
    else:
        return False
while True:
    credit = input("Number: ")
    if credit.isdigit():
        break
#American Express uses 15-digit  34 or 37
#MasterCard uses 16-digit numbers 51, 52, 53, 54, or 55
# Visa uses 13- and 16-digit 4
if len(credit) == 15 and int(credit[0:2]) in [34, 37]:
    if valid(credit) == True:
        print("AMEX\n")
    else:
        print("INVALID\n")
elif len(credit) == 16 and int(credit[0:2]) in [51, 52, 53, 54, 55]:
    if valid(credit) == True:
        print("MASTERCARD\n")
    else:
        print("INVALID\n")
elif len(credit) in [13, 16] and int(credit[0]) == 4:
    if valid(credit) == True:
        print("VISA\n")
    else:
        print("INVALID\n")
else:
    print("INVALID\n")