# Push Switch 디바이스 드라이버 및 응용 프로그램 작성

1. push switch 디바이스 드라이버 작성(push_switch_driver.c)

2. push switch 테스트 응용 프로그램 작성(test_push_switch.c)
- 설명
    - 키 입력시 응용 프로그램이 user_signal1() 호출
    - 변수 quit 값을 1로 만들고 main()의 while loop에서 빠져나올 수 있게 됨
- 동작
    - push switch 9개의 값을 주기적으로 읽어 들여 현재 어떤 스위치가 눌렸는지 저장하고 그 값을 화면에 출력
