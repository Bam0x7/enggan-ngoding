import socket

def start_server():
    server_socket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
    server_address = ('localhost',12345)
    
    server_socket.bind(server_address)
    server_socket.listen(5)
    
    print(f"server listening{server_address}")
    
    while True:
        print("menunggu koneksi client")
        client_socket,client_address = server_socket.accept()
        print(f"koneksi di terima: {client_address}")
        
        handle_client(client_socket)

def handle_client(client_socket):
    while True:
        data = client_socket.recv(1024).decode('utf-8')
        print(f"client: {data}")
    
        data = input("balas, (exit) untuk keluar: ")
        if data == "exit":
            client_socket.close()
            exit()
        else:
            client_socket.send(data.encode('utf-8'))

if __name__ == '__main__':
    start_server()              
                    

