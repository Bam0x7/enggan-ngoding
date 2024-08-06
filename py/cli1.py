import socket

def start_client():
    client_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    server_address = ('localhost',12345)
    
    client_socket.connect(server_address)
    print(f"koneksi terhubung ke: {server_address}")
    
    while True:
        print("(exit) untuk keluar")
        pesan = input("pesan: ")
        client_socket.send(pesan.encode('utf-8'))
        if pesan == "exit":
            client_socket.close()
            exit()
        
        pesan = client_socket.recv(1024).decode('utf-8')
        print(f"server: {pesan}")
        if pesan == "exit":
            client_socket.close()
            exit()

if __name__ == '__main__':
    start_client()        
    