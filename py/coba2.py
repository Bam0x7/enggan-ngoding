def func_generator(num):
    for i in range(num):
        yield i

for i in func_generator(10):
    print(i)   
    

def func_fibo(limit):
    a,b = 0,1
    
    while a < limit:
        yield a
        a = b
        b = a + b

for inc in func_fibo(20):
    print(inc)                 