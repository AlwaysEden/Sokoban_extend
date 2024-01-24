#!/bin/bash

# 특정 디렉토리
directory_path="testcases"

# 디렉토리 내의 파일들에 대한 반복문
for file in "$directory_path"/*
do
    # 파일이 실제로 존재하는지 확인
    if [ -f "$file" ]; then
        # ./write < testcase/(파일) 명령어 실행
        ./write < "$file"
    else
        echo "Skipping non-regular file: $file"
    fi
done

