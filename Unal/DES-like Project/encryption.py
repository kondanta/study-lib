import main as base # Main lib for the code
import os # Needed lib. because of os.remove and os.system("pause")

try:
    os.remove("encrypted.txt")
except OSError:
    pass

# Definitions
encArr = []
key = "0001100000011001"

try:
    txtResults = base.txtReader("input.txt")
except FileNotFoundError:
    print("Please run encrypyion first")
    os.system("pause")

for i in txtResults:
    encArr = base.run(i,key)
    f = open('encrypted.txt', 'a')
    for item in encArr:
        f.write(item)
f.close()
