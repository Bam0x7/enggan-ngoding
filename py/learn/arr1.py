import sys

def check(arr):
    min = sys.maxsize

    for i in arr:
        if i < min:
            min = i
    for i in arr:
        if not i % min == 0:
            return False
    return True

arr = [20,25,30,100,200,201]
print(check(arr))            