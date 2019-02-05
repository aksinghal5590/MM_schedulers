CC=g++
CFLAGS=-std=c++11 -O2 -Iinclude -pthread

.PHONY: all clean

all: clean cshare drsteal drshare drsteal_mod drshare_mod

cshare:
	$(CC) $(CFLAGS) -o bin/cshare src/CSchedulerMain.cpp -ltbb

drsteal:
	$(CC) $(CFLAGS) -o bin/drsteal src/DRStealSchedulerMain.cpp -ltbb

drshare:
	$(CC) $(CFLAGS) -o bin/drshare src/DRShareSchedulerMain.cpp -ltbb

drsteal_mod:
	$(CC) $(CFLAGS) -o bin/drsteal_mod src/DRStealModSchedulerMain.cpp -ltbb

drshare_mod:
	$(CC) $(CFLAGS) -o bin/drshare_mod src/DRShareModSchedulerMain.cpp -ltbb

clean:
	rm -rf bin/
	mkdir -p bin


