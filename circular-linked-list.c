/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */
///////반환값 한 번만 확인하고 제출하기!!! 

#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

//헤더 노드(더미 공간)가 있는 이중 연결 원형 리스트 
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


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
 * list 마지막에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	listNode* newnode=(listNode*)malloc(sizeof(listNode)); //새 노드 생성(동적할당)
	/* newnode 초기화 */
	newnode->key=key;
	newnode->rlink=NULL;
	newnode->llink=NULL;

	//노드가 존재하지 않을 때  
	if((h->llink==h)&&(h->rlink==h)) 
	{
		newnode->llink=h;
		newnode->rlink=h;
		h->llink=newnode;
		h->rlink=newnode;
		return 1;
	}
	
	//노드가 존재할 때
	else
	{
		// listNode*inserted=h->llink;  //list마지막 노드를 가리키는 포인터 생성 
		// newnode->rlink=h;
		// newnode->llink=inserted;
		// inserted->rlink=newnode;
		// h->llink=newnode;
		
		//list마지막 노드를 가리키는 포인터 생성하지 않고, 헤더노드 이용하면,
		newnode->rlink=h;
		newnode->llink=h->llink;
		h->llink->rlink=newnode;
		h->llink=newnode;
		return 1;
	}
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	listNode* deleted=NULL;		//삭제할 노드를 가리키는 포인터 생성
	deleted=h->llink;			//deleted를 마지막 노드로 설정하기

	//노드가 존재하지 않을 때 -> 삭제할 노드가 없으므로 에러 발생 
	if((h->llink==h)&&(h->rlink==h))    /*Q. if(h==NULL)과 동일? 흠.. 아닌 거 같아.*/
	{
		printf("ERROR: There is no node to remove.\n");
		return -1;
	}

	//노드가 1개 존재할 때
	else if(deleted->rlink==h)  //Q. deleted->rlink==h->llink와 동일한가?
	{
		deleted->llink->rlink=h;
		deleted->rlink->llink=h;
		// // 동일한 코드인가?
		// h->rlink=h;
		// h->llink=h;

		free(deleted); //노드 삭제(메모리 해제)
		return 1;
	}

	//노드가 2개 이상 존재할 때
	else  
	{
		deleted->llink->rlink=h;
		h->llink=deleted->llink;
		free(deleted);  //노드 삭제(메모리 해제)
		return 1;
	}
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	listNode* newnode=(listNode*)malloc(sizeof(listNode)); //새 노드 생성(동적할당)
	/* newnode 초기화 */
	newnode->key=key;
	newnode->rlink=NULL;
	newnode->llink=NULL;

	//노드가 존재하지 않을 때  
	if((h->llink==h)&&(h->rlink==h)) 
	{
		newnode->llink=h;
		newnode->rlink=h;
		h->llink=newnode;
		h->rlink=newnode;
		return 1;
	}
	
	//노드가 존재할 때
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
	deleted=h->rlink;			//deleted를 처음 노드로 설정하기

	//노드가 존재하지 않을 때 -> 삭제할 노드가 없으므로 에러 발생 
	if((h->llink==h)&&(h->rlink==h))    /*Q. if(h==NULL)과 동일? 흠.. 아닌 거 같아.*/
	{
		printf("ERROR: There is no node to remove.\n");
		return -1;
	}

	//노드가 1개 존재할 때
	else if(deleted->rlink==h)  //Q. deleted->rlink==h->llink와 동일한가?
	{
		deleted->llink->rlink=h;
		deleted->rlink->llink=h;
		// // 동일한 코드인가?
		// h->rlink=h;
		// h->llink=h;

		free(deleted); //노드 삭제(메모리 해제)
		return 1;
	}

	//노드가 2개 이상 존재할 때
	else  
	{
		deleted->rlink->llink=h;  //Q. deleted->rlink->link=h->rlink;라고 안 해도 되나?
		h->rlink=deleted->rlink;   //Q. h->rlink=deleted->rlink->rlink;라고 안 해도 되나?
		free(deleted);  //노드 삭제(메모리 해제)
		return 1;
	}
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	

	return 0;
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

	//노드가 존재하지 않을 때  
	if((h->llink==h)&&(h->rlink==h)) 
	{
		newnode->llink=h;
		newnode->rlink=h;
		h->llink=newnode;
		h->rlink=newnode;
		return 0;
	}
	
	/* 노드가 존재할 때
		1. 입력받은 key가 제일 작을 때(처음노드로 삽입)
		2. 입력받은 key가 제일 클 때(마지막노드로 삽입)
		3. 그 이외(노드 중간에 삽입) */
	else
	{
		if(key<(h->rlink->key))   		//Q. 조건식을 이렇게 쓰는 게 맞나?
		{
			newnode->llink=h;
			newnode->rlink=h->rlink;
			h->rlink->llink=newnode;
			h->rlink=newnode;
			return 0;
		}
		else if(key>(h->llink->key))	//Q. 조건식을 이렇게 쓰는 게 맞나?
		{
			newnode->rlink=h;
			newnode->llink=h->llink;
			h->llink->rlink=newnode;
			h->llink=newnode;
			return 0;
		}
		else
		{
			listNode* p=h->rlink;  //p는 처음노드를 가리키도록 설정 
			while((p->rlink)!=NULL)
			{
				if((p->key)>key)
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
			//p가 마지막 노드일 때 key가 마지막 노드보다 값이 작으면,
			newnode->rlink=p;
			newnode->llink=p->llink;
			p->llink->rlink=newnode;
			p->llink=newnode;
			return 0;
		}
	}
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	return 0;
}


