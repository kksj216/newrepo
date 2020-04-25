RUD Project
## This is 2020 OSS CRUD mini-project

#### 이 CRUD project는 유기견 관리 프로그램입니다. 유기견의 정보를 데이터로 가지며, 새로운 유기견에 대한 데이터를 추가하거나 기존을 데이터를 수정, 삭제, 검색, 정렬 및 파일에 저장하고 불러올 수 있습니다. 
//유기견은 발견 이후 약 15일간 유기견 보호소에서 관리하다가 이후에 임시 보호 등의 조치가 취해집니다. 이 프로그램에서 유기견들의 정보는 2 개의 구조체 배열에 저장되는데, 하나는 전체 등록되는 유기견(dogs)들의 데이터, 다른 하나는 보호소에서 관리중인 유기견(shelter)의 데이터를 저장합니다. 메인 메뉴는 shelter의 데이터를 직접적으로 다루며, dogs의 데이터는 메인 메뉴 실행 중 간접적으로 다뤄집니다. 다뤄지는 내용은 본 설명서 중 메인 메뉴 아래에 설명하겠습니다.

### 1. To Make execute file

make execute file : `make main`
 ```
 gcc -g -Wall -c abandoned.c
 gcc -g -Wall -o main main.c abandoned.o
 ```
make execute file with __debug__ : `make main_debug`
 ```
 gcc -g -Wall -DDEBUG -c abandoned.c
 gcc -g -Wall -DDEBUG -o main main.c abandoned.o
 ```

remove execute file : `make clean`
 ```
 rm *.o main
 ```
### 2. About main menu

1. create_record 새로운 유기견 정보 추가(견종, 성별, 털색, 무게, 발견지)
//각 유기견의 번호는 create 시 자동으로 지정되며, 상태는 ‘On_notice’으로 지정됨
//이때 dogs에도 데이터가 추가됨(상태는 ‘In_shelter’로 지정)
//create 명령이 실행되기 전, dogs.txt 파일에 내용이 있으면 dogs에 데이터 추가
2. read_record 특정 번호의 유기견 정보를 출력
3. update_record 특정 번호의 유기견의 상태를 ‘Notice_expiration’으로 변경
4. delete_record 특정 번호의 유기견 정보를 삭제. 이때 삭제 이유는 메뉴로 나우어 선택
//dogs에서는 데이터가 삭제되지 않으며, 유기견이 shelter에서 삭제되는 이유에 따라 상태가 {입양, 임시보호, 반환, 사망}으로 지정됨
5. list_record 현재 저장되어 있는 모든 유기견들의 정보를 출력
6. save_file 유기견들의 정보를 파일에 저장
7. load_file 파일에 있는 유기견들의 정보 불러오기
8. search_record 검색조건에 따른 유기견들의 번호 및 정보 출력. 이때, 검색조건은 메뉴로 나누어 선택
8.1. search_by_breed 견종으로 번호 검색
8.2. search_by_sex 성별로 번호 검색
8.3. search_by_color 털색으로 번호 검색
8.4. search_by_dis 발견지으로 번호 검색
8.5. search_by_st 상태로 번호 검색
9. sort_record 유기견들을 번호순으로 배열에 새롭게 정렬
10. stat_record 현재 저장되어 있는 정보들을 정리하여 출력
//dogs에 있는 데이터도 포함함
0. 메뉴 ‘0’을 입력하면, 프로그램이 종료되기 전에 dogs의 데이터를 dogs.txt 파일에 저장

