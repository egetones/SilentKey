all:
	g++ -o silentkey silentkey.cpp

clean:
	rm -f silentkey keylog.txt
