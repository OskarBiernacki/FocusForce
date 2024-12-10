import socket

def tcp_client(server_ip, server_port):
    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print(f"Łączenie z serwerem {server_ip}:{server_port}...")
        client_socket.connect((server_ip, server_port))
        print("Połączono z serwerem.")
        message = "NinjaTurtle7122 stop"
        client_socket.sendall(message.encode('utf-8'))
        response = client_socket.recv(1024)
        print(f"responce: {response.decode('utf-8')}")

    except ConnectionRefusedError:
        print("Connection ERRO!")
    except Exception as e:
        print(f"Error: {e}")
    finally:
        # Zamknięcie połączenia
        client_socket.close()
        print("Połączenie zamknięte.")

# Przykład użycia klienta
if __name__ == "__main__":
    tcp_client("127.0.0.1", 80)
