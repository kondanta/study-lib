import main as base # Main lib for the code
import os # Needed lib. because of os.remove and os.system("pause")

try:
    os.remove("dencrypted.txt") 
except OSError:
    pass

# Definitions
dencArr = []
key = "0001100000011001"
fp = 0
lp = 10
cntr = 1

try:
    d_txtResults = base.revtxtReader("encrypted.txt")
except FileNotFoundError:
    print("Please run encrypyion first")
    os.system("pause")

while cntr*10 <= len(d_txtResults):
    arr = d_txtResults[fp:lp]
    dencArr = base.derun(arr,key)
    fp += 10
    lp += 10
    cntr += 1
    f = open('dencrypted .txt', 'a')
    for item in dencArr:
        f.write(item)
f.close()
