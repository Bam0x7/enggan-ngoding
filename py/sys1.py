import sys
import os
from bs4 import BeautifulSoup

print("Argumen baris perintah")

def perfom_cleanup():
    print("melakukan pembersihan")

try:
    raise Exception("contoh kesalahan")
except Exception as e:
    print("terjadi kesalahan",e)
    sys.exit(1)

perfom_cleanup()

sys.stdout.write("versi python3 :",sys.version)
