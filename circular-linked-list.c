/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */

#include<stdio.h>
#include<stdlib.h>

/* 헤더 노드(더미 공간)가 있는 이중 연결 원형 리스트 */
typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);


int main()
{
	char command;
	int key;
	listNode* headnode=NULL;	

	printf("[----- [jinyoungLee] [2020039063] -----]\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


/* 헤드노드 초기화 */
int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 
		headNode의 포인터 및 데이터 초기화 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}


/* 메모리 해제 */
int freeList(listNode* h){
	
	listNode* p=h->rlink;    //p가 처음노드를 가리키도록 설정 
	
	//노드가 존재하면 메모리 해제하기
	while(p->rlink!=h)      //원형이므로, p->rlink!=NULL을 조건식으로 사용하면 안 된다. 
	{
		p=p->rlink;
		free(p->llink);  	//이전 노드 메모리 해제 
	}
	//p가 마지막 노드일 때
	free(p);	//마지막 노드 메모리 해제
	free(h);  	//헤더 노드 메모리 해제 			
	return 0;
}


/* 리스트 출력 */
void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	//리스트에 헤더노드를 가진 공백일 때, 
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;	//p는 헤더노드가 가리키는 첫번째 노드를 가리키도록 설정 

	//각 노드마다 데이터 값 출력
	while(p != NULL && p != h) {                                 //Q.왜 p!=NULL?
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;		//다음노드로 설정
		i++;
	}
	printf("  items = %d\n", i);	//노드의 개수 출력(헤더노드 제외)


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}
}


/**
 * list '마지막'에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* newnode=(listNode*)malloc(sizeof(listNode)); //새 노드 생성(동적할당)
	/* newnode 초기화 */
	newnode->key=key;
	newnode->rlink=NULL;
	newnode->llink=NULL;

	//헤더노드가 존재한 공백일 때  
	if((h->llink==h)&&(h->rlink==h)) 
	{
		newnode->llink=h;
		newnode->rlink=h;
		h->llink=newnode;
		h->rlink=newnode;
		return 1;
	}
	
	//헤더노드가 존재하고, 또다른 노드가 존재할 때
	else
	{		
		newnode->rlink=h;
		newnode->llink=h->llink;
		h->llink->rlink=newnode;
		h->llink=newnode;
		return 1;
	}
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	listNode* deleted=NULL;		//삭제할 노드를 가리키는 포인터 생성
	deleted=h->llink;			//deleted를 리스트의 마지막 노드로 설정하기
	
	//헤더노드가 존재한 공백일 때 -> 삭제할 노드가 없으므로 에러 발생 
	if((h->llink==h)&&(h->rlink==h))    
	{
		printf("ERROR: There is no node to remove.\n");
		return -1;
	}

	//헤더노드가 존재하고, 또다른 노드가 1개 존재할 때
	else if(deleted->rlink==h)      
	{
		deleted->llink->rlink=h;
		deleted->rlink->llink=h;
		// h->rlink=h;
		// h->llink=h;
		free(deleted); //노드 삭제(메모리 해제)
		return 1;
	}

	//헤더노드가 존재하고, 또다른 노드가 2개 이상 존재할 때
	else  
	{
		deleted->llink->rlink=h;
		h->llink=deleted->llink;
		free(deleted);  //노드 삭제(메모리 해제)
		return 1;
	}
}


/**
 * list '처음에' key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* newnode=(listNode*)malloc(sizeof(listNode)); //새 노드 생성(동적할당)
	/* newnode 초기화 */
	newnode->key=key;
	newnode->rlink=NULL;
	newnode->llink=NULL;

	//헤더노드가 존재한 공백일 때  
	if((h->llink==h)&&(h->rlink==h)) 
	{
		newnode->llink=h;
		newnode->rlink=h;
		h->llink=newnode;
		h->rlink=newnode;
		return 1;
	}
	
	//헤더노드가 존재하고, 또다른 노드가 존재할 때
	else
	{
		newnode->llink=h;
		newnode->rlink=h->rlink;
		h->rlink->llink=newnode;
		h->rlink=newnode;
		return 1;
	}
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	listNode* deleted=NULL;		//삭제할 노드를 가리키는 포인터 생성
	deleted=h->rlink;			//deleted를 리스트의 헤더 노드를 제외한 처음 노드로 설정하기

	//헤더노드가 존재한 공백일 때 -> 삭제할 노드가 없으므로 에러 발생 
	if((h->llink==h)&&(h->rlink==h))    
	{
		printf("ERROR: There is no node to remove.\n");
		return -1;
	}

	//헤더노드가 존재하고, 또다른 노드가 1개 존재할 때
	else if(deleted->rlink==h)    
	{
		deleted->llink->rlink=h;
		deleted->rlink->llink=h;
		free(deleted); //노드 삭제(메모리 해제)
		return 1;
	}

	//헤더노드가 존재하고, 또다른 노드가 2개 이상 존재할 때
	else  
	{
		deleted->rlink->llink=h;  
		h->rlink=deleted->rlink;   
		free(deleted);  //노드 삭제(메모리 해제)
		return 1;
	}
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	//listNode형 포인터 2개 필요(이유: 하나만 존재시, 연속적으로 역순으로 재배치가 불가능하다.)
	listNode* tail=h->rlink;
	listNode* lead=tail->rlink;  

	//노드가 없을 때와 노드가 1개일 때는 역순으로 재배치할 노드가 없음(기존과 동일한 순서)
	if(((h->llink==h)&&(h->rlink==h))||(h->rlink->rlink==h))
		return -1;

	//노드가 2개 이상일 때      ////////////////////////////////////////*무슨 문제지????*/
	else
	{
		//처음 노드일 때(tail이 처음 노드를 가리킬 때)
		tail->rlink=h;
		tail->llink=lead;
		h->rlink=tail;
		
		tail=lead;			//tail을 다음노드로 변경 
		lead=lead->rlink; 	//lead를 다음노드로 변경
		
		while(lead!=h)   //다시!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!11
		{
			tail->rlink=tail->llink;	//tail의 rlink가 가리키는 주소를 tail의 llink가 가리키는 주소로 변경
			tail->llink=lead;			//tail의 llink가 가리키는 주소를 다음노드의 주소로 변경 
			 
			tail=lead;			//tail을 다음노드로 변경 
			lead=lead->rlink; 	//lead를 다음노드로 변경
		}
		//마지막 노드일 때(tail이 마지막 노드를 가리킬 때) 
		tail->rlink=tail->llink;
		tail->llink=h;
		h->llink=tail;
		return 0;
	}
}


/**
 *  리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 
 **/
int insertNode(listNode* h, int key) {
	listNode* newnode=(listNode*)malloc(sizeof(listNode)); //새 노드 생성(동적할당)
	/* newnode 초기화 */
	newnode->key=key;
	newnode->rlink=NULL;
	newnode->llink=NULL;

	//헤더노드가 존재한 공백일 때  
	if((h->llink==h)&&(h->rlink==h)) 
	{
		newnode->llink=h;
		newnode->rlink=h;
		h->llink=newnode;
		h->rlink=newnode;
		return 0;
	}
	
	/* 헤더노드가 존재하고, 또다른 노드가 존재할 때
		1. 입력받은 key가 제일 작을 때(처음노드로 삽입)
		2. 노드 중간에 삽입
		3. 입력받은 key가 제일 클 때(마지막노드로 삽입) */
	else
	{
		listNode* p=h->rlink;  //p는 헤드노드 제외한 리스트의 처음노드를 가리키도록 설정
		while(p!=h)
		{
			if((p->key)>key)  	//1. 입력받은 key가 제일 작을 때(처음노드로 삽입), 2. 노드 중간에 삽입		
			{
				newnode->rlink=p;
				newnode->llink=p->llink;
				p->llink->rlink=newnode;
				p->llink=newnode;
				return 0;
			}
			else
				p=p->rlink;		//조건에 해당되지 않으면, p는 다음노드를 가리키도록 설정
		}
		//3. 입력받은 key가 제일 클 때(마지막노드로 삽입) : p==h일때
		newnode->rlink=h;
		newnode->llink=h->llink;
		h->llink->rlink=newnode;
		h->llink=newnode;
		return 0;
	}
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	listNode* deleted=NULL;		//삭제할 노드를 가리키는 포인터 생성
	deleted=h->rlink;			//deleted를 헤더노드 제외한 리스트의 처음 노드로 설정하기

	//헤더노드가 존재한 공백일 때 -> 삭제할 노드가 없으므로 에러 발생 
	if((h->llink==h)&&(h->rlink==h))    
	{
		printf("ERROR: There is no node to remove.\n");
		return -1;
	}

	/* 헤더노드가 존재하고, 또다른 노드가 1개 존재할 때
		1. key에 대한 노드가 존재할 때
		2. key에 대한 노드가 존재하지 않을 때 */
	else if(deleted->rlink==h)     
	{
		//key에 대한 노드가 존재할 때
		if(key==(deleted->key))
		{
			deleted->llink->rlink=h;
			deleted->rlink->llink=h;
			free(deleted); //노드 삭제(메모리 해제)
			return 0;
		}
		//key에 대한 노드가 존재하지 않을 떄
		else
		{
			printf("ERROR: There is no node to remove.\n");
			return -1;
		}
	}

	/* 헤더노드가 존재하고, 또다른 노드가 2개 이상 존재할 때
		-key에 대한 노드 존재할 때
			1. 입력받은 key 처음노드의 값일 때(처음노드 삭제)
			2. 입력받은 key가 마지막노드의 값일 때(마지막노드 삭제)
			3. 그 이외(중간노드 삭제)
		-key에 대한 노드 존재하지 않을 때 */
	else
	{
		while(deleted!=h)
		{
			//1,2,3 case 모두 해당(h대신 deleted->rlink와 deleted->llink 표현을 이용하여 코드를 가독성 있게 만듦)
			if((deleted->key)==key)  			
			{
				deleted->llink->rlink=deleted->rlink;
				deleted->rlink->llink=deleted->llink;
				free(deleted);	//노드 삭제(메모리 해제)
				return 0;			
			}
			else
				deleted=deleted->rlink;		//조건에 해당되지 않으면, p는 다음노드를 가리키도록 설정
		}
		// p==h일때 (key에 대한 노드 존재하지 않을 때와 동일한 의미) -> 삭제할 노드가 없어 오류 발생
		printf("ERROR: There is no node to remove.\n");
		return -1;
	}
}
