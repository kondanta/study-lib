# -*- coding: utf-8 -*-

# 
# __author__: Taylan Dogan
#   


# The dictionary that will be used for the encode and decode.
# For future additions, please add every charachters end of the dictionary.
myDict = {'A': '00000001', 'B':'00000010', ' ':'00000000', 'C':'00000011', 'Ç':'00000100', 'D':'00000101', 'E':'00000110', 'F':'00000111',
'G':'00001000', 'Ğ':'00001001', 'H': '00001010', 'I': '00001011', 'J': '0000110100', 'K':'00001110', 'L': '00001111', 'M':'00010000',
'N':'00010001', 'O':'00010010', 'Ö':'00010011', 'P':'00010100', 'R':'00010101', 'S':'00010110', 'Ş':'00010111', 'T':'00011000',
'U':'00011001', 'Ü':'00011010', 'V':'00011011', 'Y':'00011100', 'Z':'00011101', 'Q':'00011110', 'W':'00011111', 'X':'00100000',
'.':'00100001', ',':'00100010'}


# Initial Permutation table
IP = (10, 8, 6, 4, 2, 9, 7, 5, 3, 1)
# Inverse of the Initial Permutation table
IP_1 = (10, 5, 9, 4, 8, 3, 7, 2, 6, 1)


# Permutation tables for the Key 4 and Key 5
KEY1 = (8, 1, 3, 4, 6, 2, 5, 7) 
KEY2 = (7, 5, 2, 6, 4, 3, 1, 8) 


# Generic Permutation function
def Permutation(block, table):
    """
    @block: The elements of the list
    @table: Permutation table to be used. 
    """
    return [block[x-1] for x in table]


# Read 10 chars from txt file
def TxtReader(txtfile):
    text_file = ''
    with open(txtfile) as f:
        text_file = f.read()
    x = len(text_file) % 10
    den = []
    if x != 0:
        y = 10 - x
        text_file = text_file + " "*y
    den = [''.join(z) for z in zip(*[iter(text_file)]*10)]
    return den


# Read 8 bits from txt file
def DecryptReader(txtfile):
    text_file = ''
    with open(txtfile) as f:
        text_file = f.read()
    x = len(text_file) % 8
    den = []
    den = [''.join(x) for x in zip(*[iter(text_file)]*8)]
    return den    


def Encode(lst):
    """
    @lst: The block of the 10 bytes going to be encoded.
    """
    encode_list = []
    text_file = ''
    # Inıtial Permutation
    text_file = Permutation(lst, IP)
    for t in text_file:
        for keys,values in myDict.items():
            t = t.replace(keys, values)
        encode_list.append(t)
    return encode_list

def Decode(lst):
    """
    @lst: The block of the 8 bits going to be decoded
    """
    lst = Permutation(lst, IP_1)
    finarr = []
    for t in lst:
        for keys,values in myDict.items():
            t = t.replace(values, keys)
        finarr.append(t)
    return finarr


# Make every char of the element a list item
def Expand(lst):
    string=''
    lst2 = []
    for item in lst:
        for char in item:
            string = char
            lst2.append(string)
    return lst2


# Shift to the right for given value n
def rightShift(seq, n):
    """
    @seq: the list of the items that going to shifted
    @n: number of bytes to be shifted
    """
    shuffled_list = []
    a = n % len(seq)
    x = seq[-a:] + seq[:-a]
    shuffled_list.append(x)
    return x


# Shift to the left for given value n
def leftShift(seq, n):
    """
    @seq: the list of the items that going to shifted
    @n: number of bytes to be shifted
    """
    shuffled_list = []
    a = n % len(seq)
    x = seq[a:] + seq[:a]
    shuffled_list.append(x)
    return x


# Make the list one element list.
def ListGathering(lst, n=80, mode=0):
    if mode == 1: # This means we are doing decryption
        lst = [''.join(x) for x in zip(*[iter(lst)]*8)]
        return lst
    else:
        return [''.join(x) for x in zip(*[iter(lst)]*n)] # 80 total chars def.


# Creates left and right nibbles.
def RightLeftNibble(string):
    right_nibble = []
    left_nibble = []
    string = [string[i:i+8] for i in range(0, len(string), 8)]
    counter = 0
    for item in string:
        if counter % 2 == 0:
            right_nibble.append(item)
            counter += 1
        else:
            left_nibble.append(item)
            counter += 1
    return right_nibble, left_nibble


def ReverseRightLeftNibble(leftnibble, rightnibble):
    """
    When I was creating left and right nibbles, I seperate them by their index positions.
    So I need to fix them by their index positions again.
    """
    revArr = []
    counter = 0
    counterl = 0
    counterr = 0
    while counter < 10:
        if counter % 2 == 0:
            revArr.append(rightnibble[counterr])
            counter += 1
            counterr += 1
        else:
            revArr.append(leftnibble[counterl])
            counter += 1
            counterl += 1
    return revArr


# Compliment operation for the key. After that it splits the key into 2 equal pieces.
def compliment(key):
    complimented = ''
    for item in key:
        if item == '1':
            complimented += '0'
        elif item == '0':
            complimented += '1'
    return [complimented[i:i+8] for i in range(0, len(complimented), 8)]


# Exclusive or function for generating the sets
def XORFunction(lst, key):
    counter = 0
    xordlist = []
    while counter < len(lst):
        z = ''.join(format(int(a, 16) ^ int(b, 16), 'x') for a,b in zip(lst[counter], key))
        #print(z)
        xordlist.append(z)
        #print(xordlist)
        counter += 1
    return xordlist


# Generates K4, K5 with given CKEY elements
def GenNextKeys(right,left,mode=0):

    key45 = []
    right = Permutation(right, KEY1)
    left = Permutation(left, KEY2)

    re = Expand(right)
    le = Expand(left)

    rrs = rightShift(re, 5)
    ars = ListGathering(rrs, 8)
    key45 = key45 + ars

    lls = leftShift(le, 3)
    als = ListGathering(lls,8)
    key45 = key45 + als
    
    return key45


# Swapping two lists
def swap(lst,lst2):
    return lst2, lst


# Encryption Function
def Encrypt(param,key):
    encode_list = Encode(param)
    openList = Expand(encode_list)
    open_r_shifted_list = rightShift(openList, 4)
    r_shifted_list = ListGathering(open_r_shifted_list)
    r,l = RightLeftNibble(r_shifted_list[0])
    key_array = compliment(key)
    after_r_nibble = XORFunction(r,key_array[0])
    after_l_nibble = XORFunction(l,key_array[1])
    after_r_nibble,after_l_nibble = swap(after_r_nibble,after_l_nibble)
    key45 = GenNextKeys(key_array[0], key_array[1])
    xord_nibble_right = XORFunction(after_r_nibble, key45[0])
    xord_nibble_left = XORFunction(after_l_nibble, key45[1])
    xord_nibble_right, xord_nibble_left = swap(xord_nibble_right, xord_nibble_left)
    xord_nibbles = xord_nibble_left+xord_nibble_right
    cipher_text = Permutation(xord_nibbles, IP_1)
    print(cipher_text)
    return cipher_text


# Decryption Function
def Decrypt(param,key):
    key_array = compliment(key)
    key45 = GenNextKeys(key_array[0], key_array[1])
    dec_list = Permutation(param, IP)
    leftnib = dec_list[:5]
    rightnib = dec_list[5:10]
    rightnib, leftnib = swap(rightnib, leftnib)
    before_xor_rightnibble = XORFunction(rightnib, key45[0])
    before_xor_leftnibble = XORFunction(leftnib, key45[1])
    before_xor_rightnibble, before_xor_leftnibble = swap(before_xor_rightnibble, before_xor_leftnibble)
    rightnibbl = XORFunction(before_xor_rightnibble,key_array[0])
    leftnibbl = XORFunction(before_xor_leftnibble,key_array[1])
    fullLst = ReverseRightLeftNibble(leftnibbl,rightnibbl)
    gatheredListExpand = Expand(fullLst)
    ShGatheredList = leftShift(gatheredListExpand, 4)
    gatheredList = ListGathering(ShGatheredList,80,1)
    decoded = Decode(gatheredList)
    return decoded



# Testing the functions

b = []
key = "0001100000011001"
a = TxtReader("plain_text.txt")
print(a)
for item in a:
    print(item)
    b = Encrypt(item,key)
    f = open('cipher_text.txt', 'a')
    for item in b:
        f.write(item)
f.close()


c = []
key = "0001100000011001"
d = DecryptReader("cipher_text.txt")
print()
x = 0
y = 10
a = 1
while a*10 <= len(d):
    lst = d[x:y]
    c = Decrypt(lst,key)
    x += 10
    y += 10
    a += 1
    f = open('re_cipher_text.txt', 'a')
    for item in c:
        f.write(item)
f.close()