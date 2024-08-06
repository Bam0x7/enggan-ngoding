class DaftarSiswa:
    def __init__(self,nama,jurusan,nik):
        self.nama = nama
        self.jurusan = jurusan
        self.nik = nik

class ManajemenSiswa:
    def __init__(self):
        self.data_siswa = []
    
    def tambah_data(self,data):
        self.data_siswa.append(data)
    
    def tampil_data(self):
        for data in self.data_siswa:
            print(f"nama: {data.nama}, Kelas: {data.jurusan}, Nik: {data.nik}")
    
    def cari_data(self,nama):
        for nama in self.data_siswa:
            if nama.nama.lower() == nama.nama.lower():
                return nama
        return None
    
    def update_data(self,nama,nm_baru,jr_baru,nk_baru):
        sw = self.cari_data(nama)
        if sw:
            sw.nama = nm_baru
            sw.jurusan = jr_baru
            sw.nik = nk_baru
        else:
            print("gagal memperbarui data")    
                            
    def hapus_data(self,nama):
        sw = self.cari_data(nama)
        if sw:
            self.data_siswa.remove(sw) 
            print("data berhasil di hapus")
        else:
            print("data gagal di hapus") 
            

siswa1 = DaftarSiswa("ibnu ruslan","Cyber Security",888120)
siswa2 = DaftarSiswa("Bam Mazino", "Multimedia", 888130)

manajemen_siswa = ManajemenSiswa()
manajemen_siswa.tambah_data(siswa1)
manajemen_siswa.tambah_data(siswa2)

manajemen_siswa.tampil_data()                                      
print("======================================")
manajemen_siswa.update_data("ibnu ruslan","muhamad ibnu ruslan","Vulnerability Research",888120)
manajemen_siswa.tampil_data()    
print("===============================")
manajemen_siswa.hapus_data("Bam Mazino")
manajemen_siswa.tampil_data()