# -*- coding: utf-8 -*-

""" Starter """

# Encode Table
myDict = { 'A': '00000001', 'a':'00000002', 'B':'00000010', 'b':'00000020', 'C':'00000011', 'c':'00000022', 'Ç':'00000100', 'ç':'00000200', 'D':'00000101', 'd':'00000202', 'E':'00000110', 'e':'00000220', 'F':'00000111', 'f':'00000222', 'G':'00001000', 'g':'00002000', 'Ğ':'00001001', 'ğ':'00002002', 'H': '00001010', 'h':'00002020', 'I': '00001011', 'i':'00002022', 'J': '00001101', 'j':'00002202', 'K':'00001110', 'k':'00002220', 'L': '00001111', 'l':'00002222', 'M':'00010000', 'm':'00020000', 'N':'00010001', 'n':'00020002', 'O':'00010010', 'o':'00020020', 'Ö':'00010011', 'ö':'00020022', 'P':'00010100', 'p':'00020200', 'R':'00010101', 'r':'00020202', 'S':'00010110', 's':'00020220', 'Ş':'00010111', 'ş':'00020222', 'T':'00011000', 't':'00022000', 'U':'00011001', 
'u':'00022002', 'Ü':'00011010', 'ü':'00022020', 'V':'00011011', 'v':'00022022', 'Y':'00011100', 'y':'00022200', 'Z':'00011101', 'z':'00022202', ' ':'00000000', 'X':'00000003', 'x':'00000030', 'W':'00000033', 'w':'00000303', '.':'00000333',}

# Permutation tables for the code
IP = (10, 8, 6, 4, 2, 9, 7, 5, 3, 1) # Init. Perm.
REV_IP = (10, 5, 9, 4, 8, 3, 7, 2, 6, 1) # Rev. Inıt. Perm.

# Keys permutation tables 
KEY1 = (8, 1, 3, 4, 6, 2, 5, 7) # Will be used for K4 
KEY2 = (7, 5, 2, 6, 4, 3, 1, 8) # Will be used for K5

# Read 10 text from a txt file // Also adds padding if last block < 10 // Ads " " as padding
def txtReader(txtfile):
    text_file = ''
    with open(txtfile) as f:
        text_file = f.read()
    mod = len(text_file) % 10
    arr = []
    if mod != 0: #Padding part
        rMod = 10 - mod
        text_file = text_file + " "*rMod
    arr = [''.join(z) for z in zip(*[iter(text_file)]*10)]
    return arr

# Txt reader for denc.
def revtxtReader(txtfile):
    text_file = ''
    with open(txtfile) as f:
        text_file = f.read()
    arr = []
    arr = [''.join(z) for z in zip(*[iter(text_file)]*8)]
    return arr    

# Permutation func.
def permutation(array, pTable):
    return [array[x-1] for x in pTable]

""" Encode funcs. """
# Func for enc.
def enc(strr):
    encode_list = []
    text_file = ''
    text_file = permutation(strr, IP) # Inıtial permutation here
    for t in text_file: # Encoding part starts here
        for keys,values in myDict.items():
            t = t.replace(keys, values)
        encode_list.append(t)
    return encode_list

# Func for denc.
def revEnc(arr):
    arr = permutation(arr, REV_IP) # Last permutation here
    finarr = []
    for t in arr:
        for keys,values in myDict.items():
            t = t.replace(values, keys)
        finarr.append(t)
    return finarr

""" Shifting """

# Shift to right for given value n
def rightShift(items, sValue): # Items are in an array
    shuffled_list = []
    mod = sValue % len(items)
    x = items[-mod:] + items[:-mod]
    shuffled_list.append(x)
    return x

# Shift to left for given value n
def leftShift(items, sValue):
    shuffled_list = []
    mod = sValue % len(items)
    arr = items[mod:] + items[:mod]
    shuffled_list.append(arr)
    return arr

# Makes every number an array item
def expand(lst):
    string=''
    lst2 = []
    for item in lst:
        for char in item:
            string = char
            lst2.append(string)
    return lst2

# Sums the whole array items into one single item // n = 80 def.
def ESummer(lst, n=80):
    return [''.join(x) for x in zip(*[iter(lst)]*n)]

""" Nibble Creation """

# Creates left and right nibbles. Before that creates an array item for each 8 number.
def rlNibble(string):
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

# Reverses the nibble effect
def revrlNibble(lnibble,rnibble): #As arrays
    revArr = []
    counter = 0
    counterl = 0
    counterr = 0
    while counter < 10:
        if counter % 2 == 0:
            revArr.append(rnibble[counterr])
            counter += 1
            counterr += 1
        else:
            revArr.append(lnibble[counterl])
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
        xordlist.append(z)
        counter += 1
    return xordlist

# Generates K4, K5 with given CKEY elements
def GenNextKeys(right,left):
    key45 = []
    right = permutation(right, KEY1)
    left = permutation(left, KEY2)

    re = expand(right)
    le = expand(left)

    rrs = rightShift(re, 5)
    ars = ESummer(rrs, 8)
    key45 = key45 + ars

    lls = leftShift(le, 3)
    als = ESummer(lls,8)
    key45 = key45 + als
    
    return key45

# Swapping two lists
def swap(lst,lst2):
    return lst2, lst

""" Function Calls """

# Func. call for enc.
def run(param,key):
    encode_list = enc(param)
    openList = expand(encode_list)
    open_r_shifted_list = rightShift(openList, 4)
    r_shifted_list = ESummer(open_r_shifted_list)
    r,l = rlNibble(r_shifted_list[0])
    key_array = compliment(key)
    after_r_nibble = XORFunction(r,key_array[0])
    after_l_nibble = XORFunction(l,key_array[1])
    after_r_nibble,after_l_nibble = swap(after_r_nibble,after_l_nibble)
    key45 = GenNextKeys(key_array[0], key_array[1])
    xord_nibble_right = XORFunction(after_r_nibble, key45[0])
    xord_nibble_left = XORFunction(after_l_nibble, key45[1])
    xord_nibble_right, xord_nibble_left = swap(xord_nibble_right, xord_nibble_left)
    xord_nibbles = xord_nibble_left+xord_nibble_right
    cipher_text = permutation(xord_nibbles, REV_IP)
    return cipher_text

# Func. call for denc.
def derun(param,key):
    key_array = compliment(key)
    key45 = GenNextKeys(key_array[0], key_array[1])
    b = permutation(param, IP)
    leftnib = b[:5]
    rightnib = b[5:10]
    rightnib, leftnib = swap(rightnib, leftnib)
    before_xor_rnib = XORFunction(rightnib, key45[0])
    before_xor_lnib = XORFunction(leftnib, key45[1])
    before_xor_rnib, before_xor_lnib = swap(before_xor_rnib, before_xor_lnib)
    sec_r_nibble = XORFunction(before_xor_rnib,key_array[0])
    sec_l_nibble = XORFunction(before_xor_lnib,key_array[1])
    fullArr = revrlNibble(sec_l_nibble,sec_r_nibble)
    fullArr_open = expand(fullArr)
    sf_fullArr_open = leftShift(fullArr_open, 4)
    summed_fullarr = ESummer(sf_fullArr_open,8)
    normArr = revEnc(summed_fullarr)
    return normArr