from random import *
import os
import filecmp


def dec_to_base(num,base):
    base_num = ""
    while num>0:
        dig = int(num%base)
        base_num += str(dig)
        num //= base
    base_num = base_num[::-1]
    return base_num

def base_to_dec(num_str,base):
    num_str = num_str[::-1]
    num = 0
    for k in range(len(num_str)):
        dig = num_str[k]
        dig = int(dig)
        num += dig*(base**k)
    return num


def solve(n, k, string):
    num = base_to_dec(string[::-1], k)
    inf = open("output2", "w")
    for i in range(n):
        print(i % 2 + 1, dec_to_base(num, k)[::-1], file = inf)
        num += 1
    print("Done", file = inf)
    inf.close()


# Compile main.c
solution_name = "sm21-3.c"

os.system("gcc -m32 -Wall -std=gnu11 -Wextra -fsanitize=address -fsanitize=leak -std=gnu11 {} -o main".format(solution_name))

# Run 1000 tests
for test in range(1):
    # Random arguments: n, k, length of string
    n = randrange(10) 
    k = randrange(2, 11)
    leng = randrange(1, 4000)

    string = "".join(choice("0123456789"[:k]) for i in range(leng - 1)) + choice("0123456789"[1:k])

    os.system("rm output*")
    os.system("./main {} {} {} > output1".format(n, k, string))    
    solve(n, k, string)

    FLAG = (filecmp.cmp('output1', 'output2', shallow=False))
    if (FLAG):
        print("Ok", test)
    else:
        print("Wa", test)
        print(n, k, string)
        break
