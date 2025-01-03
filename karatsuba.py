
# Online Python - IDE, Editor, Compiler, Interpreter

import math

def size_base10(x):
    return math.floor(math.log10(x)) + 1


def split_at(num, m2):
    high = num // pow(10, m2)
    low = num - high * pow(10, m2)
    return high, low


def rec_multiply(x, y):
    
    if (x < 10) or (y < 10): # base case
        return x * y
        
   # Calculates the size of the numbers.
    m = max(size_base10(x), size_base10(y))
    m2 = math.floor(m // 2)
    
    # Split the digit sequences in the middle.
    high1, low1 = split_at(x, m2)
    high2, low2 = split_at(y, m2)
    
    # 3 recursive calls made to numbers approximately half the size. */
    z0 = rec_multiply(low1, low2)
    z1 = rec_multiply(low1 + high1, low2 + high2)
    z2 = rec_multiply(high1, high2)
    
    return z2 * pow(10, m2 * 2) + (z1 - z2 - z0) * pow(10, m2) + z0

x = 3141592653589793238462643383279502884197169399375105820974944592
y = 2718281828459045235360287471352662497757247093699959574966967627

print(int(rec_multiply(int(x), int(y))))
