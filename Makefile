CC=g++-9
CFLAGS=-fopenmp -lgomp -lpthread

Lab2Main: Lab2Main.cpp matrixBlockTransposeOpenMp.cpp matrixTransposeNaive.cpp OpenMPDiagonalThreading.cpp PThreadBlockOrientedThreading.cpp PThreadDiagonalThreading.cpp
	$(CC) $(CFLAGS) Lab2Main.cpp -o Lab2Main

clean:
	$(RM) Lab2Main