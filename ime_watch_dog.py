import socket
import os

path = ""

UDP_IP = "127.0.0.1"
UDP_PORT = 54000

sock = socket.socket(socket.AF_INET,socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))
sock.settimeout(5.0)

def main():
	while True:

		try :
			data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
			print("received message: %s" % data)

		except socket.timeout as err:
			# print("hi")
			print("WatchDog Timeout!!")
			os.system(path)


if __name__ == '__main__':


	try:
		main()
	except KeyboardInterrupt:
		sock.close()
		print("Watch Dog goodbye.")