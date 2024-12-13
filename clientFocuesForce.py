import socket

# Defoult - Hello Admin
# stop 
# start
# status

def tcp_client(server_ip, server_port, command=""):
    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect((server_ip, server_port))
        message = f"NinjaTurtle7122 {command}"
        client_socket.sendall(message.encode('utf-8'))
        response = client_socket.recv(1024)
        #print(f"responce: {response.decode('utf-8')}")
        return response.decode('utf-8')

    except ConnectionRefusedError:
        print("Connection ERRO!")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        client_socket.close()

if __name__ == "__main__":
    ip="127.0.0.1"
    resp=tcp_client(ip, 80)
    if resp=='Hello Admin':
        print('FocuseForce founded!')
        inp=None
        while inp!='q':
            inp=input(f"FocuseForce@{ip}> ")
            print(tcp_client(ip, 80, inp))
