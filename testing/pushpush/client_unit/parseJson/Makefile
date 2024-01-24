parseJson:
	gcc -fprofile-arcs -ftest-coverage -o parseJson parseJson.c ../../../../cJSON.c
exec:
	./parseJson <<< "testcases/map1.json"

clean:
	rm parseJson
	rm *.gc*
