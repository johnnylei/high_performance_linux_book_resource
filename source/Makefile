C_FILE_LIST=$(wildcard *.c)
D_FILE_LIST=$(patsubst %.c, %.d, C_FILE_LIST)

%.o:%.c
	gcc -MMD $< -o $@

%.debug:%.c
	gcc -g -MMD $< -o $@

-include $(D_FILE_LIST)

clean:
	rm -f *.o *.d *.debug
