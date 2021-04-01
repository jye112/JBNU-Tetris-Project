# LED 디바이스 드라이버 및 응용 프로그램 작성

< LED 디바이스 드라이버 작성(led_driver.c) >

1. init

- LED port의 주번호, 디바이스 이름, file operation 등록: register_chrdev() 사용
  - int register_chrdev(unsigned int major, const char* name, struct file_operation *fops)

- LED port가 제대로 등록되지 않았을 경우 경고 메세지 출력하고 종료
  - csemad_led_addr: LED port의 물리 주소에 대한 커널 공간 주소
  - void *ioremap(unsigned long phys_addr, unsigned long size): 물리 주소에 대한 가상 주소 할당


2. exit

- LED port에 대해 할당된 가상주소를 해제
  - void iounmap(void *addr): 할당된 가상 주소 해제
- LED port 등록 해지 
  - int unregister_chrdev(unsigned int major, const char *name)
  
3. open
- open led port

4. release
- close led port
 
5. write
- 사용자 공간 버퍼(gdata)로부터 1바이트 데이터를 커널 공간 버퍼로 복사: copy_from_user() 사용
  - unsigned long copy_from_user(void *to, const void *from, unsigned long n)
  - to: 복사될 커널 공간의 주소, from: 원본 데이터의 사용자 공간 주소, n: 복사할 데이터의 바이트 크기
- copy_from_user()의 return  값이 0이 아닐 경우 return -EFAULT
- csemad_led_addr에 사용자 공간에서 읽은 1바이트 데이터를 씀


6. read
- csemad_led_addr로부터 1바이트 데이터 읽음
- 읽은 데이터를 사용자 공간의 버퍼(gdata)로 복사: copy_to_user() 사용
  - unsigned long copy_to_user(void *to, const *from, unsigned long n)
  - to: 복사될 사용자 공간의 주소, from: 원본 데이터의 커널 공간 주소, n: 복사할 데이터의 바이트 크기
- csemad_led_addr에 사용자 공간에서 읽은 1바이트 데이터를 씀


< LED 테스트 응용 프로그램 작성(test_led.c) >
1. 설명
- open()/close() 함수로 LED port를 열고 닫음
-  read()를 통해 읽은 값은 8개 led들 중에서 현재 켜져 있는 led들을 이용해 8-bit binary encoding으로 해석
-  write()를 이용해 8-bit binary encoding 형태의 값을 쓰는 동작으로 원하는 led(들)을 켜거나 끌 수 있음

2. LED 테스트 프로그램 빌드
- make
- sudo insmod led_driver.ko : 디바이스 드라이버 적재
- sudo mknod /dev/csemad_led c 260 0 : 디바이스 노드 생성

3. 동작
- 1-255 사이의 숫자를 명령어의 인자로 입력 받아 이진수에 해당하는 LED들을 점등
- LED port로부터 값을 읽어 출력 - 인자로 입력 받은 값과 같은 값이 출력되어야 함
