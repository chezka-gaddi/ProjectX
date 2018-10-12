all:
	g++ -c LeftDynamicTank.cpp -fPIC  -o ldt.o
	g++ -c RandomDynamicTank.cpp -fPIC -o rdt.o
	g++ -shared ldt.o -o ldt.so
	g++ -shared rdt.o -o rdt.so
