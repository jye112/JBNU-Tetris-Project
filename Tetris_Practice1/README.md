# 리눅스 디바이스 드라이버 커널 모듈 프로그래밍

1. 디바이스 드라이버 작성(skeleton.c)

2. Make file 작성

3. 디바이스 드라이버 빌드
- make: 커널 오브젝트 생성(skeleton.ko)

4. 디바이스 파일 생성
- mknod /dev/csemad(디바이스 파일 이름) c(문자 디바이스 드라이버) 248(주번호) 0(부번호)

5. 디바이스 드라이버 적재
- insmod skeleton.ko: 커널 오브젝트 적재
- lsmod: 적재된 모듈(커널) 확인

6. 테스트용 응용 프로그램(userapp.c) 빌드
- gcc -Wall userapp.c -o userapp  

7. 응용 프로그램 실행
- ./userapp

8. 기타
- 디바이스 드라이버 제거: rmmod skeleton
- 출력 메세지 확인: dmesg
