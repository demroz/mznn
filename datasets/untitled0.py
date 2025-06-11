
def product_value(n):
    s = 1
    ndigits = len(str(n))
    for index in range(1,ndigits+1):
        digit = (n%(10**index))//(10**(index-1))
        if digit == 0 :
            digit = 1
        s*=digit
    return s
        
n = 3
s = 0
for i in range(10**n):
    print(s,product_value(i))
    s += product_value(i)
print(s)