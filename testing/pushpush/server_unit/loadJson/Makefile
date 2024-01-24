loadJson:
	gcc -fprofile-arcs -ftest-coverage -o loadJson loadJson.c ../../../../cJSON.c
exec:
	echo "testcases/map2.json" | ./loadJson

clean:
	rm loadJson
	rm *.gc*
