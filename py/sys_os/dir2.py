import os

def current_path():
    print("direktori saat ini")
    print(os.getcwd())

current_path()
os.chdir('../')
current_path()