import threading
import time

def threading_1():
    for i in range(5):
        print(f"fungsi 1: {i}")
        time.sleep(1)

def threading_2():
    for i in range(5):
        print(f"fungsi 2: {i}")
        time.sleep(1)
        
if __name__ == '__main__':
    thread_1 = threading.Thread(target=threading_1)
    thread_2 = threading.Thread(target=threading_2)
    
    thread_1.start()
    thread_2.start()
    
    thread_1.join()
    thread_2.join()
    
    print("program selesai")                
        