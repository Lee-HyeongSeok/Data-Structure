## 가상메모리 - 페이지 교체 알고리즘 구현   
   
#### 1. FIFO   
#### 2. LRU
#### 3. LFU


## * 알고리즘 설명   
1. FIFO 알고리즘   
* 메모리에 적재된지 가장 오래된 페이지를 교체한다(페이지 적재시간을 페이지에 기록 하거나
페이지가 올라온 순서를 Queue에 저장하는 방식).   
	* 장점 : 이해가 쉽고, 구현이 간단하다.   
	* 단점 : 성능은 언제나 좋다고 장담할 수 없다.   
2. LRU 알고리즘   
* 가장 오래 사용되지 않은 페이지를 교체하는 알고리즘이다.     
	* 장점 : FIFO 알고리즘 보다 효율적이다.   
	* 단점 : 페이지 교체 횟수가 비교적 높다.   
3. LFU 알고리즘   
* 참조 횟수가 가장 작은 페이지를 교체하는 알고리즘이다(교체 대상 페이지가 다수일 경우 LRU
알고리즘을 사용하여 가장 오래 사용되지 않은 페이지로 교체한다).      
	* 장점 : 상대적으로 페이지 부재율이 낮다.
	* 단점 : 구현에 상당한 비용이 들며 최적 페이지 교체 정책을 제대로 유사하게 구현해내지 못 한다.   

## FIFO.c 코드구조   
<pre>
<code>
#define MAX_SIZE 3 // 블록 수를 3개로 설정

typedef struct { // 주기억장치를 구현한 구조체 
	int list[MAX_SIZE];
	int length;
} ArrayList;
</code>
</pre>   

#### input.txt 파일 리딩   
<pre>
<code>
int main() {
	// 받은 값의 개수를 표시
	// 배열리스트 생성
	ArrayList list1;
	init(&list1); // 리스트 초기화 

	// file open 함수 
	FILE * fp;
	fp = fopen("파일 경로 및 이름", "rt");

	int buffer;

	while (fscanf(fp, "%d", &buffer) != EOF) {
		// 99가 되기전까지 반복!
		if (buffer == 99)
			break;

		// 메모장에서 읽어들인 값을 add함수의 인자로 전달 
		add(&list1, buffer); 
		count++; // 적중률을 구하기 위한 총 데이터 개수 카운트
	}
	printf("적중률은 %d/%d 입니다.\n", hit, count);
	fclose(fp);
}
</code>
</pre>

#### add함수   
<pre>
<code>
void add(ArrayList *L, int item)
{
	int i;
	for (i = 0; i < L->length; i++) {
		// list숫자와 받은 숫자가 같으면 hit증가
		if (L->list[i] == item) {
			printf("Hit!!\n\n");
			hit++;
			return;
		}
	}
	// 배열에 값 삽입
	L->list[(count - hit) % 3] = item;

	//  배열이 꽉차지 않았다면 length 1증가
	if (L->length < MAX_SIZE)
		L->length++;

	// 값 출력
	display(L);
}
</code>
</pre>   

## LRU.c 코드구조   
<pre>
<code>
#define MAX_STACK_SIZE 4 // 블록 수를 4개로 설정 

typedef struct { //주기억장치를 구현한 구조체 
	int data[MAX_STACK_SIZE]; //데이터
	int seq[MAX_STACK_SIZE]; // 순서, 제일 먼저 들어간 데이터의 값이 제일 높다
	int top; //캐쉬에 데이터가 몇개가 들어가있는지 카운트
}StackType;
</code>
</pre>   

#### 가장 오래 사용되지 않은 페이지를 찾는 Max 함수   
<pre>
<code>
int Max(StackType *s) { //캐시메모리가 다 찼을 때 가장 오래된 것의 seq가 제일 크다.
	int max = 0; // 순서가 가장 큰 값 찾는 변수
	int index = 0; // 순서가 가장 큰 값의 인덱스
	max = s->seq[0]; // 첫 번째 캐시 메모리를 넣어준다
	for (int i = 1; i < MAX_STACK_SIZE; i++) { //나머지 캐시 메모리의 블록들과 비교하여 가장 순서가 가장 큰 값을 찾는다
		if (max < s->seq[i]) {
			max = s->seq[i];
			index = i;
		}
	}
	return index; // 가장 오래 사용되지 않은 값의 인덱스를 반환한다.
}
</code>
</pre>   

#### push 함수(읽어들인 값을 인자로 전달받는다)   
<pre>
<code>
int push(StackType*s, int data) { // 캐시 메모리에 3개 이하의 데이터가 있을 때와 가득 차있을 때로 나눠준다
	int hit = 0;
	if (s->top < 3) { // 캐시 메모리가 아직 다 안채워져 있을 때
		for (int i = 0; i <= s->top + 1; i++) { // top+1만큼동안 hit한 데이터가 있는지 탐색하고, 없다면 새로 추가해준다
			if (s->data[i] == data) {   //hit된다면
				if (s->seq[i] != 1) { //hit한 것의 시간이 1이면 나머지에 1을 더해줄 필요가 없이 그대로 가면된다
					for (int j = 0; j <= s->top + 1; j++) { //나머지 캐시메모리에 +1씩 해준다.
						if (j == i)
							continue;
						else
							s->seq[j]++;
					}
				}
				s->seq[i] = 1;
				hit++;
				break;
			}
		}
		if (hit == 0) { //hit가 안되면 새로 추가해준다
			s->data[++(s->top)] = data;
			s->seq[s->top] = 1;
			for (int i = 0; i < s->top; i++)
				s->seq[i]++;
		}
	}
	else if (s->top==3) {   // 캐시 메모리가 다 채워져 있을 때
		int index = 0;
		for (int i = 0; i < MAX_STACK_SIZE; i++) { //hit 인지 ?
			if (s->data[i] == data) {
				if (s->seq[i] != 1) { //hit한 것의 시간이 1이면 나머지에 1을 더해줄 필요가 없이 그대로 가면된다
					for (int j = 0; j < MAX_STACK_SIZE; j++) {
						if (j == i)
							continue;
						else
							s->seq[j]++;
					}
				}
				s->seq[i] = 1;
				hit++;
				break;
			}
		}
		if (hit==0) { //hit가 안되면 새로 추가해준다
			index = Max(s); // 가장 오래된 데이터 인덱스 받아옴(들어온 값이 캐시에 없을때)
			s->data[index] = data; //가장 오래된 데이터를 바꿔줌
			s->seq[index] = 1; // 1으로 다시 초기화
			for (int i = 0; i < MAX_STACK_SIZE; i++) {
				if (index == i)
					continue;
				else
					s->seq[i]++;
			}
		}
	}
	
	return hit; //hit가 됐으면 1,아니면 0을 반환
}
</code>
</pre>   

#### 데이터를 읽어들이는 readfile 함수   

<pre>
<code>
void readfile(StackType*s) {
	int cnt = 0,hit=0,block=0;
	FILE *fp;
	fp = fopen("c:\\input.txt", "r"); //파일 입출력
	int buffer;
	if (fp == NULL) {
		printf("실패");
		exit(1);
	}
	while (fscanf(fp, "%d", &buffer) != EOF) { //buffer가 끝날 때 까지 또는 30번 입력될 때 까지(과제의 입력조건)
		if (buffer == 99 || block++ >= 30) //99가 입력되거나 30개 보다 많은 블록이 입력되면 break
			break;
		hit += push( s, buffer); //hit된 수만큼 누적하여 더해준다.
		cnt++;  //총 몇개의 주기억장치 블록이 입력되었는지
	}
	ShowCache(s);
	printf("-----------------------\n");
	printf("적중률 : %d / %d\n", hit, cnt);
	printf("-----------------------\n");
	fclose(fp);
}
</code>
</pre>   

## LFU.c 코드구조   

<pre>
<code>
#define MAX_STACK_SIZE 4 // 블록 수를 4개로 설정

typedef struct { //주기억장치를 구현한 구조체
	int data[MAX_STACK_SIZE]; //배열을 통한 블록 구현 
	int use_set[MAX_STACK_SIZE]; // 몇번 사용되었는지 카운트
	int num[MAX_STACK_SIZE]; //들어오는 버퍼가 몇번째로 들어왔는지 카운트 
	int top; 
}StackType;
</code>
</pre>   

#### count 함수   
<pre>
<code>
//주기억장치가 다 찼을 때 사용된 횟수를 비교하여 제일 작은 값을 사용하고 
// 사용된 횟수가 같을경우 더 먼저 입력된 값을 사용한다
int count(StackType *s) { 
	int min = 0;
	int index = 0;
	min = s->use_set[0];
	index = 0;
	for (int i = 1; i < MAX_STACK_SIZE; i++) {
		if (min > s->use_set[i]) {
			min = s->use_set[i];
			index = i;
		}
		else if (min == s->use_set[i]) {
			if (s->num[index] > s->num[i]) {
				min = s->use_set[i];
				index = i;
			}
		}
	}
	return index;
}
</code>
</pre>   

#### push 함수   
<pre>
<code>
int push(StackType*s, int val, int num) { // 주기억장치에 3개 이하의 데이터가 있을 때와 가득 차있을 경우를 나눠준다
	int hit = 0;

	// 그렇지 않으면 같은 값이 있는지 검사하고 다음 인덱스에 넣어줘야함
	// 또 인덱스가 다 채워져있을 때는 가장 오래된 값을 카운트했던 것을 넣어줘야함
	if (s->top < 3) { // 스택이 아직 다 안채워져 있을 때
		for (int i = 0; i < MAX_STACK_SIZE; i++) {
			if (s->data[i] == val) {  // 같은 값이 있으면 hit!! Frequent  +1해주고 hit+1
				s->use_set[i] += 1;
				s->num[i] = num;//
				hit++;
				printf("hit\n\n");
				break;
			}
			else { //같은 값이 없으면 새로 추가해준다
				s->data[++(s->top)] = val;
				s->use_set[s->top] += 1;
				s->num[s->top] = num;//
				break;
			}
		}
	}
	else if (is_full(s)) {   // 스택이 다 채워져 있을 때, top은 움직이지 말고 새로운 데이터 추가
		int index = 0;
		int cnt = 0;
		for (int i = 0; i < MAX_STACK_SIZE; i++) {
			if (s->data[i] == val) { // 같은 값이 있으면 hit!! Frequent  +1해주고 hit+1
				s->use_set[i] += 1;
				s->num[i] = num;
				hit++;
				printf("hit\n\n");
				break;
			}
			else {
				cnt++; // 같은 값이 없을 때 그냥 카운트
			}
		}
		if (cnt == 4) { // 한 개 라도 같은 값이 없을 때 가장 오래된 값과 교체
			index = count(s); // 가장 오래된 데이터 인덱스 받아옴(들어온 값이 캐시에 없을때)
			s->data[index] = val;
			s->use_set[index] = 1; // 1으로 다시 초기화
			s->num[index] = num;
		}
	}
	ShowStack(s);
	printf("---------------\n");

	
	return hit;  // 히트 수 반환 
}
</code>
</pre>