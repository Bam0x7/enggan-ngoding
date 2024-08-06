import socket

def port_scan(target_host,target_ports):
    print(f"scanning target: {target_host}")
    for target_port in target_ports:
        client_sock = socket.socket(AF_INET,socket.SOCK_STREAM)
        client_sock.settimeout(1)

        if result == 0:
            print(f"port {target_port} is open")
        else:
            print(f"port {target_port} is closed")
        
        client_sock.close()

if __name__ == '__main__':
    target_host = input("nasukan host target: ")
    target_ports = range(1,1025)

    port_scan(target_host,target_ports)
