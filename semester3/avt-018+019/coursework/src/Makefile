all:
	cd client && make client && cd ..
	cd server && make server && cd ..
	cd processor && make processor && cd ..
	rm -f /etc/systemd/system/myserver.service
	cp ./server/myserver.service /etc/systemd/system/myserver.service
	clear