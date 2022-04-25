#include<stdio.h>
#include<stdlib.h>


typedef struct Node { // 값을 담을 노드의 구조체
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head { // 첫 노드를 가리키는 헤드노드 구조체
	struct Node* first;
}headNode;

int initialize(headNode** h); // 리스트를 초기화하는 함수
int freeList(headNode* h); // 리스트의 노드들에 할당된 메모리를 해제하는 함수
int insertNode(headNode* h, int key); // 노드를 삽입하는 함수
int insertLast(headNode* h, int key); // 리스트의 마지막에 노드를 삽입하는 함수
int insertFirst(headNode* h, int key); // 리스트의 맨 처음에 노드를 삽입하는 함수
int deleteNode(headNode* h, int key); // 노드를 삭제하는 함수
int deleteLast(headNode* h); // 마지막 노드를 삭제하는 함수
int deleteFirst(headNode* h); // 처음 노드를 삭제하는 함수
int invertList(headNode* h); // 리스트를 역순으로 재배치하는 함수
void printList(headNode* h); // 리스트를 출력하는 함수


int main()
{
	char command;
	int key;
	headNode* headnode=NULL;

	printf("[----- [김지민] [2021041068] -----]\n");

	do{	// 메뉴 출력
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		// 명령키 입력
		printf("Command = "); 
		scanf(" %c", &command);

		switch(command) { // 입력된 명령키에 따른 동작 수행
		case 'z': case 'Z': // z, Z 명령키 입력 시, 리스트 초기화
			initialize(&headnode); 
			break;
		case 'p': case 'P': // p, P 명령키 입력 시, 리스트 출력
			printList(headnode);
			break;
		case 'i': case 'I': // i, I 명령키 입력 시, 입력값을 갖는 노드 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D': // d, D 명령키 입력 시, 입력값과 동일한 값을 가진 노드를 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': // n, N 명령키 입력 시, 마지막 노드 뒤에 입력값을 갖는 노드를 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E': // e, E 명령키 입력 시, 마지막 노드를 삭제
			deleteLast(headnode);
			break;
		case 'f': case 'F': // f, F 명령키 입력 시, 맨 앞에 입력값을 갖는 노드를 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T': // t, T 명령키 입력 시, 맨 앞에 있는 노드 삭제
			deleteFirst(headnode);
			break;
		case 'r': case 'R': // r, R 명령키 입력 시, 리스트를 역순으로 재배치
			invertList(headnode);
			break;
		case 'q': case 'Q': // q, Q 명령키 입력 시, 리스트의 노드들에 할당된 메모리를 해제
			freeList(headnode);
			break;
		default: // 그 외의 명령키 입력 시, 오류 메시지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); // q, Q 명령키 입력 시에만 프로그램 종료

	return 1;
}


int initialize(headNode** h) { // 리스트를 초기화하는 함수

	// 헤드 노드가 존재할 경우, 헤드 노드에 할당된 메모리 해제
	if(*h != NULL)
		freeList(*h);

	// 헤드 노드 생성 및 first 멤버 초기화
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	
	return 1;
}

int freeList(headNode* h){ // 리스트의 노드들에 할당된 메모리를 해제하는 함수

	listNode* p = h->first;
	listNode* prev = NULL;

	// 처음부터 마지막 노드까지 메모리 할당 해제
	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	// 헤드 노드에 할당된 메모리 해제
	free(h);

	return 0;
}


void printList(headNode* h) { // 리스트를 출력하는 함수
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { // 출력할 리스트가 없을 경우, 안내 메시지 출력 후 함수 종료
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	// 출력할 리스트가 존재할 경우, 첫 노드부터 마지막 노드까지 일정한 형식으로 출력
	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	// 노드 수 출력
	printf("  items = %d\n", i);
}

int insertLast(headNode* h, int key) { // 리스트에 마지막에 노드 삽입하는 함수

	// 삽입할 노드 생성 및 초기화
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	// 아무 노드도 없을 경우
	if (h->first == NULL)
	{	// 맨 앞이자 마지막 노드로 삽입
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

	// 노드가 존재할 경우, 마지막 노드를 탐색 
	while(n->rlink != NULL) {
		n = n->rlink;
	}
	// 탐색한 마지막 노드의 뒤에 삽입
	n->rlink = node;
	node->llink = n;

	return 0;
}

int deleteLast(headNode* h) { // 리스트의 마지막 노드 삭제하는 함수

	// 노드가 없을 경우, 안내 메시지 출력 후 함수 종료
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	// 노드가 하나만 존재하는 경우, h->first를 NULL로 초기화하고 그 노드의 메모리 할당을 해제
	if(n->rlink == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	// 리스트의 마지막 노드를 탐색
	while(n->rlink != NULL) {
		trail = n;
		n = n->rlink;
	}

	// 마지막 노드의 전 노드를 마지막 노드로 설정하기 위해 NULL 할당
	trail->rlink = NULL;
	free(n);

	return 0;
}

int insertFirst(headNode* h, int key) { // 리스트의 맨 앞에 입력값을 갖는 노드를 삽입하는 함수

	// 삽입할 노드 생성
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	// 아무 노드도 없을 경우
	if(h->first == NULL)
	{	// 맨 처음에 노드 삽입
		h->first = node;
		return 1;
	}

	// 노드가 존재할 경우, 헤드노드와 리스트노드 사이에 노드 삽입
	node->rlink = h->first;
	node->llink = NULL;
	listNode *p = h->first;
	p->llink = node;
	h->first = node;

	return 0;
}

int deleteFirst(headNode* h) { // 리스트의 맨 앞 노드 삭제하는 함수

	if (h->first == NULL) // 아무 노드도 존재하지 않을 경우, 안내 메시지 출력 후 함수 종료
	{
		printf("nothing to delete.\n");
		return 0;
	}

	// 노드가 존재할 경우, 2번째 노드와 헤드 노드를 연결하고 첫 노드는 메모리 할당 해제 
	listNode* n = h->first;
	h->first = n->rlink;

	free(n);

	return 0;
}

int invertList(headNode* h) { // 리스트를 역순으로 배치하는 함수

	if(h->first == NULL) { // 아무 노드도 없을 경우, 안내 메시지 출력 후 함수 종료
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	// 노드가 존재할 경우, 리스트를 역순으로 재배치해 임시 저장
	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	// 역순으로 재배치된 리스트를 헤드 노드에 전달
	h->first = middle;

	return 0;
}

int insertNode(headNode* h, int key) { // 리스트의 노드들 중 입력값보다 큰 값을 갖는 노드 앞에 입력값을 갖는 노드를 삽입하는 함수

	// 삽입할 노드 생성 및 초기화
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	// 아무 노드도 없을 경우, 리스트의 처음에 노드 삽입
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

	
	// 마지막 노드까지 입력값보다 큰 값을 갖는 노드가 있는지 탐색
	while(n != NULL) {
		if(n->key >= key) {
			// 삽입할 위치가 리스트의 처음인 경우, insertFirst() 이용해 삽입
			if(n == h->first) {
				insertFirst(h, key);
			} else { // 삽입할 위치가 노드들의 중간이거나 마지막일 경우, 노드 삽입
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	// 입력값보다 큰 값을 갖는 노드가 없을 경우, 리스트의 마지막 노드 뒤에 삽입
	insertLast(h, key);
	return 0;
}

int deleteNode(headNode* h, int key) { // 입력값과 동일한 값을 갖는 노드 삭제하는 함수

	if (h->first == NULL) // 아무 노드도 없을 경우, 안내 메시지 출력 후 함수 종료
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;
	// 마지막 노드까지 입력값과 동일한 값을 갖는 노드가 있는지 탐색
	while(n != NULL) {
		if(n->key == key) {
			// 삭제할 노드가 첫 노드일 경우, deleteFirst()를 이용해 노드 삭제
			if(n == h->first) { 
				deleteFirst(h);
			} else if (n->rlink == NULL){ // 삭제할 노드가 마지막 노드일 경우, deleteLast()를 이용해 노드 삭제 
				deleteLast(h);
			} else { // 삭제할 노드가 중간 노드일 경우, 양 옆의 노드를 연결하고 해당 노드 삭제
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}

		n = n->rlink;
	}

	// 입력값과 동일한 값을 갖는 노드가 존재하지 않을 경우, 오류 메시지 출력
	printf("cannot find the node for key = %d\n", key);
	return 1;
}


