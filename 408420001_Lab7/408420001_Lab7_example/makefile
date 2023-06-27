TARGET=lab7_stu

$(TARGET): lab7_stu.o error.o
	$(CC) -o $@ $^ 

lab7_stu.o: lab7_stu.c
error.o: error.c

clean:
	rm -f lab7_stu.o error.o $(TARGET)
