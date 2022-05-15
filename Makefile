#usage: "make windows", "mingw32-make windows" or "make linux".

linux:
	make -f Makefile.linux

windows:
	mingw32-make -f Makefile.windows