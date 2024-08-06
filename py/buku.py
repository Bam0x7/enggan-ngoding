class Buku:
    def __init__(self,judul,penulis,tahun_terbit):
        self.judul = judul
        self.penulis = penulis
        self.tahun_terbit = tahun_terbit

class ManajemenBuku:
    def __init__(self):
        self.daftar_buku = []
    
    def tambah_buku(self, buku):
        self.daftar_buku.append(buku)
    
    def lihat_buku(self):
        print("daftar buku")
        for buku in self.daftar_buku:
            print(f"{buku.judul} - {buku.penulis} - {buku.tahun_terbit}")
    
    def cari_buku(self,buku):
        for buku in self.daftar_buku:
            if buku.judul.lower() == buku.judul.lower():
                return buku
        return None
    
    def update_buku(self,judul,new_judul,new_penulis,new_tahun_terbit):
        buku = self.cari_buku(judul)
        if buku:
            buku.judul = new_judul
            buku.penulis = new_penulis
            buku.tahun_terbit = new_tahun_terbit
            print(f"data buku {judul} berhasil di perbarui")
        else:
            print(f"data buku {judul} gagal di perbarui")
    
    def hapus_buku(self,judul):
        buku = self.cari_buku(judul)
        if buku:
            self.daftar_buku.remove(buku)
            print(f"buku {judul} berhasil di hapus")
        else:
            print(f"buku {judul} gagal di hapus")

buku = Buku("The C programming language", "denish richie",1982)
manajemen_buku = ManajemenBuku()            

def lihat_buku():
    global manajemen_buku
    manajemen_buku.lihat_buku()
    menu()

def tambah_buku():
    judul_baru = input("judul ")
    penulis = input("penulis ")
    tahun_terbit = int(input("tahun terbit "))
    buku = Buku(judul_baru,penulis,tahun_terbit)
    global manajemen_buku
    manajemen_buku.tambah_buku(buku)
    menu()

def edit_buku():
    judul_buku = input("masukan judul buku yang ingin di update ")
    judul_baru = input("judul baru ")
    penulis_baru = input("penulis baru ")
    tahun_terbit_baru = int(input("tahun terbit baru "))
    global manajemen_buku
    manajemen_buku.update_buku(judul_buku,judul_baru,penulis_baru,tahun_terbit_baru)
    menu()

def hapus_buku():
    judul_buku = input("masukan judul buku yang ingin di hapus ")
    global manajemen_buku
    manajemen_buku.hapus_buku(judul_buku)
    menu()
    
def menu():
    
    while True:
        try:
            print("1. tampil buku")
            print("2. tambah buku")
            print("3. edit buku")
            print("4. hapus buku")
            print(" tekan 0 untuk keluar")
    
            choice = int(input("pilih "))
            if choice == 1:
                lihat_buku()
            elif choice == 2:
                tambah_buku()
            elif choice == 3:
                edit_buku()
            elif choice == 4:
                hapus_buku()
            elif choice == 0:
                print("anda keluar")
                exit()              
        except ValueError:
          print("pilihan tidak valid")
          continue                    
      
if __name__ == '__main__':
    menu()      