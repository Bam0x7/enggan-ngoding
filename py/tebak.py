import random

def tebak_angka():
    angka_random = random.randint(1,100)
    attemp = 0
   
    
    while True:
        try:
            print("pilih 0 untuk keluar")
            tebak = int(input("masukan angka "))
            if tebak == 0:
                exit()
            if tebak == angka_random:
                print("benar")
            elif tebak <= angka_random:
                print("angka terlalu kecil dari angka random")
            elif tebak >= angka_random:
                print("angka terlalu besar dari angka random")
        except ValueError:
            print("masukan angka, bukan huruf")
            continue

if __name__ ==  "__main__":
    tebak_angka()                           