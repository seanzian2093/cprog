SRC_CLI = decode_value.c
OBJ_CLI = decode_value.o

all:lib_cil 4-4

lib_cil:
	gcc -c $(SRC_CLI)
	ar rcs c_in_linux.a $(OBJ_CLI)
	$(RM) *.o

4-4:
	gcc -o logic-4 ch4_3.c c_in_linux.a -lc
	cp logic-4 /usr/lib/cgi-bin/