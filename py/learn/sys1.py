import os
import sys

def print_system_info():
    print("sistem informasi:")
    print(f"Nama OS: {os.name}")
    print(f"Platform: sys.platform")
    print(f"versi python: {sys.version}")

def create_file(file_name):
    with open(file_name,'w') as f:
        f.write("ini adalah contoh file")
    print(f"file {file_name} berhasil di buat")

def read_file(file_name):
    if os.path.exists(file_name):
        with open(file_name,'r') as f:
            print(f"konten: {file_name}")
            print(f.read())
    else:
        print(f"file {file_name} tidak ditemukan ")

def main():
    print_system_info()

    while True:

        file_name = input("nama file:")
        create_file(file_name)
