class Buku:
    def set_info(self, judul, penulis, tahun_terbit):
        self.judul = judul
        self.penulis = penulis
        self.tahun_terbit = tahun_terbit

class ManajemenBuku:
    def __init__(self):
        self.daftar_buku = []

    def tambah_buku(self, buku):
        self.daftar_buku.append(buku)
        print(f"Buku '{buku.judul}' berhasil ditambahkan.")

    def lihat_semua_buku(self):
        print("Daftar Buku:")
        for buku in self.daftar_buku:
            print(f"{buku.judul} - {buku.penulis} ({buku.tahun_terbit})")

# Membuat objek ManajemenBuku
manajemen_buku = ManajemenBuku()

# Membuat objek Buku dan menetapkan informasinya tanpa __init__
buku1 = Buku()
buku1.set_info("Python Programming", "John Doe", 2020)

buku2 = Buku()
buku2.set_info("Data Science Handbook", "Jane Smith", 2019)

# Menambahkan buku ke manajemen buku
manajemen_buku.tambah_buku(buku1)
manajemen_buku.tambah_buku(buku2)

# Melihat semua buku
manajemen_buku.lihat_semua_buku()


