8/8 신윤수 
초기화 함수 대충 설계
ssd HW 초기화 완료.

8/10 신윤수
parameter 구조체 생성 및 최적화
parameter 구조체 활용해야 하니 꼭 확인 할 것!

<문제점>
1. 현재 parameter 이름 규격화 필요.
-> 이해가 안되서...

2. init_Parameter에서 값 재설정시 init.h의 상수(i.e., DIE_NUM)로 지정할 것인지?
혹은 File I/O로 입력받은 Parameter를 지정해줄 것인지?

3. Pointer 사용 시 & 잘 사용할 것.
간혹 Struct Pointer에 접근하고자 할 때 &를 붙히는 경우가 있는데, 이는 버그로 이어질 수 있다.
(i.e., p_spare = &(page -> spare) --> p_spare = page -> spare)
단, Struct Array (Address + 1, 2, 3...)에서는 사용해도 괜찮다.
(i.e., p_die = &(way -> die[i]))

<필수 기능 리스트>
1. Mapping Table 구성
-> DRAM type Struct 구성 후, Page Mapping table, LPN based Operation 구성.

2. DRAM based Page Mapping Cache
-> 결국 DRAM에 모든 Page Mapping 값은 저장할 수 없으므로.

3. DRAM based Page Buffer (R/W, for Write)

4. Allocation(ch, chip, die, plane, block) Priority Set. 
-> for Dynamic Allocation

5.  Test Menu
-> 각 Operation 작동 Debug

6.  File System 기반 Trace Input 
-> Trace File List Indexing, Parameter Input Method Set. 
-> 파라미터를 어떻게 받을 것인지, Trace LPN은 어떻게 받을 것인지?
