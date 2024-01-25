JSON = "../../game_data/map2.json"
IP = "127.0.0.1"
PORT = "9990"
LIBS = `pkg-config --libs --cflags gtk+-2.0`
CC = gcc
FCC = ~/AFLplusplus/afl-gcc
CFLAGS = -g -fprofile-arcs -ftest-coverage

test_client : cJSON_object test_client_object

#cJSON
cJSON_object: cJSON.c 
	$(CC) -c $^

#Test version
test_client_object: pushpush_client.c
	$(CC) $(CFLAGS) -c $^ $(LIBS) -D TEST
test_connect:
	$(CC) $(CFLAGS) -o test_client cJSON.o pushpush_client.o unit_test.c $(LIBS) -D CONNECT
test_start_gamae: 
	$(CC) $(CFLAGS) -o test_client cJSON.o pushpush_client.o unit_test.c $(LIBS) -D START_GAME
test_read_write: 
	$(CC) $(CFLAGS) -o test_client cJSON.o pushpush_client.o unit_test.c $(LIBS) -D RW 
test_parsejson: 
	$(CC) $(CFLAGS) -o test_client cJSON.o pushpush_client.o unit_test.c $(LIBS) -D PARSEJSON

test_update_cell:
	$(CC) $(CFLAGS) -o test_client cJSON.o pushpush_client.o unit_test.c $(LIBS) -D UPDATE_CELL 
test_move:
	$(CC) $(CFLAGS) -o test_client cJSON.o pushpush_client.o unit_test.c $(LIBS) -D MOVE 
test_check_val:
	$(CC) $(CFLAGS) -o test_client cJSON.o pushpush_client.o unit_test.c $(LIBS) -D CHECK_VAL 

#Fuzzing using AFL++
fuzz_cJSON: cJSON.c
	$(FCC) -c $^ -static
fuzz_client: pushpush_client.c
	$(FCC) -c $^ $(LIBS) -D TEST 
fuzz_read_write:
	$(FCC) -o $@ cJSON.o pushpush_client.o unit_test.c $(LIBS) -D RW
fuzz_parsejson:
	$(FCC) -o $@ cJSON.o pushpush_client.o unit_test.c $(LIBS) -D PARSEJSON 
fuzz_check_val:
	$(FCC) -o $@ cJSON.o pushpush_client.o unit_test.c $(LIBS) -D CHECK_VAL 

clean:
	rm *.o
	rm *.gcda
	rm *.gcno
	rm *.c.gcov
	rm test_client
