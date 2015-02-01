# Sheng Xia 73387315 and Zixun Ai 63572173.  ICS 31 Lab sec 11.  Lab asst 1d.

################
# Assignment D #
################

def factorial (n: int) -> int:
    ''' Compute n! (n factorial) '''
    if n <= 0:
        return 1
    else:
        return n * factorial(n - 1)
assert factorial(0) == 1
assert factorial(5) == 120

print("10! is", factorial(10))
print("100! is", factorial(100))
print("120! is", factorial(120))
print("(50 * 10)! is", factorial(50 * 10))
print("5!! is", factorial(factorial(5)))
# print("50!! is", factorial(factorial(50)))
