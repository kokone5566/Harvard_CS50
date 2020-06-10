text = input("Text: ")
text = [word for word in text.split(" ")]
W = len(text)
L = 0
S = 0
for word in text:
    for c in word:
        if c.isalpha():
            L += 1
        elif c in [".", "!", "?"]:
            S += 1

index = 5.88 * L / W - 29.6 * S / W - 15.8
if index >= 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade {int(round(index, 0))}")