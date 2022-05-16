
#include <stdio.h>
#include <stdlib.h>

typedef struct node 
{
	int key;
	struct node* left;
	struct node* right;

} Node;

 

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);

 
int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

 
int main()

{

	char command;
	int key;
	Node* head = NULL;

        printf("    [---------[노관범]-----------------[2020039102]----------]\n"); 
	do 
    {
		printf("\n\n");
		printf("----------------------------------------------------------------\n"); 
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = "); // 명령어 입력
		scanf(" %c", &command);

		switch (command) 
        {

		case 'z': case 'Z': // z, Z를 입력하면 초기화하는 함수 호출
			initializeBST(&head);
			break;

		case 'q': case 'Q': // q, Q를 입력하면 메모리를 해제하는 함수 호출
			freeBST(head);
			break;

		case 'i': case 'I': // i, I를 입력하면 트리에 노드 삽입하는 함수 호출
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;

		case 'd': case 'D': // d, D를 입력하면 사용자가 입력한 값을 갖는 노드 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R': // r, R을 입력하면 순환 호출 하는 함수 호출
			recursiveInorder(head->left);
			break;

		case 't': case 'T': // t, T를 입력하면 반복 중위 함수 호출
			iterativeInorder(head->left);
			break;

		case 'l': case 'L': // l. L를 입력하면 레벨 순회 함수 호출
			levelOrder(head->left);
			break;


		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;

		}

	} while (command != 'q' && command != 'Q'); // 명령어 q, Q를 입력받기 전까지 반복

	return 1;

}


int initializeBST(Node** h)  // 초기화 하는 함수
{
	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

 
	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;
	front = rear = -1;

	return 1;

}

 
void recursiveInorder(Node* ptr) // 순환 호출을 하는 중위 운행 함수
{
	if (ptr) 
	{
		recursiveInorder(ptr->left); // 왼쪽노드를 탐색한다
		printf(" [%d] ", ptr->key); // 노드의 KEY값을 출력한다
		recursiveInorder(ptr->right); // 오른쪽 노드를 탐색한다

	}

}

 
void iterativeInorder(Node* node) // 중위 운행 함수

{
	for (;;)
	{
		for (; node; node = node->left) // 현재 node를 왼쪽노드로 변경한다
			push(node); // 현재 node를 스택에 삽입

		node = pop(); // 

		if (!node) break; // NULL 이라면

		printf("[%d]  ", node->key); // node의 key값을 출력
		node = node->right; // 오른쪽 노드로 변경

	}

}

 
void levelOrder(Node* ptr) // 레벨 오더 운행법

{
	if(ptr==NULL) return ; // NULL이면 종료
    enQueue(ptr); // ptr 노드를 원형 큐에 삽입
	for (;;)
	{
		ptr = deQueue(); // 원형큐에서 ptr 노드를 빼낸다
		if (ptr) // NULL이 아니라면
		{
			printf("[%d]  ", ptr->key); // ptr노드의 key값을 출력

			if (ptr->left) 
				enQueue(ptr->left); // ptr 노드의 왼쪽노드를 원형큐 삽입

			if (ptr->right) 
				enQueue(ptr->right); // ptr 노드의 오른쪽 노드를 원형큐에 삽입

		}
		else break; // NULL이면 종료

	}

}

 
int insert(Node* head, int key) // 트리에 노드를 추가하는 함수

{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;


	if (head->left == NULL) 
    {
		head->left = newNode;
		return 1;

	}


	/* head->left is the root */
	Node* ptr = head->left;

 
	Node* parentNode = NULL;
	while (ptr != NULL) 
    {
		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;


		/* we have to move onto children nodes,
		* keep tracking the parent using parentNode */
		parentNode = ptr;


		/* key comparison, if current node's key is greater than input key
		* then the new node has to be inserted into the right subtree;
		* otherwise the left subtree. */

		if (ptr->key < key)
			ptr = ptr->right;

		else
			ptr = ptr->left;

	}

	/* linking the new node to the parent */

	if (parentNode->key > key)
		parentNode->left = newNode;

	else
		parentNode->right = newNode;

	return 1;

}

 

int deleteNode(Node* head, int key) // 노드를 삭제하는 함수
{
	Node* search; // key값을 갖는 노드를 가리킬 포인터 변수
	Node* prev; // search의 부모노드를 가리킬 포인터 변수
	search = head->left; // 헤드노드를 search에 대입

	if (head->left == NULL) 
	{
		printf("트리에 노드가 존재하지 않습니다.\n"); // 경고문 출력
		return 0; // 함수 종료
 
	}

	while (search != NULL) // search의 값이 NULL이 아니라면 
	{
		prev = search; // prev에 search의 값을 대입

		if (search->key < key) // search의 key값이 입력받은 key값보다 작다면
			search = search->right; // search의 노드를 현재 노드의 오른쪽 노드로 변경한다

		else if (search->key > key) // search의 key값이 입력받은 key값보다 크다면
			search = search->left; // search의 노드를 현재 노드의 왼쪽 노드로 변경한다

		else // search의 key값과 입력받은 key값이 같다면
			break; 
	}

	if (search == NULL) // 위의 반복문에서 key값을 갖는 노드를 찾지 못했다면 
	{
		printf("해당 값 = [%d]을 가진 노드가 존재하지 않습니다.\n ", key); // 경고문 출력
		return 0; // 함수 종료
	}

 

	if (search->right == NULL && search->left == NULL) // 삭제하고자 하는 노드가 단말노드일때
	{
		if(prev!=NULL) // search가 가리키는 노드가 트리의 첫번째 노드가 아니라면
        {
        if (prev->right == search) // 오른쪽 노드가 search 노드가 맞다면
			prev->right = NULL; // 오른쪽 노드에 NULL값 대입

		else if (prev->left == search) // 왼쪽노드가 search 노드가 맞다면
			prev->left = NULL; // 왼쪽 노드에 NULL값 대입
        }

        else head->left==NULL; // search가 가리키는 노드가 트리의 첫번째 노드이면
        //  헤드노드의 오른쪽 노드에 NULL값 대입

        free(search); // search가 가리키는 노드의 메모리 해제
        return 0; // 함수 종료
	}

 
	else if (search->left == NULL ||search->right == NULL) // 삭제하고자 하는 노드의 자식트리가 1개일때
	{
		Node* child; // search의 자식 노드를 가리킬 포인터 변수 선언

		if (search->left == NULL) // 만약 search의 왼쪽 노드가 없다면
			child = search->right; // child 에 search의 오른쪽 노드  대입

		else if(search->right==NULL) // 만약 search의 오른쪽 노드가 없다면
			child = search->left; // child에 search의 왼쪽 노드  대입


		if(prev!=head->left) // 만약 search의 노드의 트리의 첫번째 노드가 아니라면
        {
        if (prev->left == search) // 왼쪽 노드가 search노드가 맞다면
		{
            prev->left = child; // search의 왼쪽 노드에 child 노드 대입
        }

		else if (prev->right == search) // 오른쪽 노드가 search노드가 맞다면
		{	
            prev->right = child; // search의 오른쪽 노드에 child 노드 대입
        }
        }
        else head->left=child; // 트리의 첫번째 노드라면
        

		free(search); // search가 가리키는 노드의 메모리 해제
        return 0; // 함수 종료

	}

	else  // 삭제하고자하는 노드의 서브트리가 2개일때
	{
		Node* search2 = search->right; // 현재 노드의 오른쪽 노드를 가리킬 search2 포인터 변수 선언
		Node* prev2=search2; // search2노드 가리킬 prev2 포인터 변수 선언

		while (search2->left != NULL) // search2의 왼쪽노드가 더이상 없을때까지 계속 반복
		{
			prev2 = search2; // prev2에 search2노드 대입
			search2 = search2->left; // search2노드를 search2노드의 왼쪽 노드로 변경한다
		}

 
		if (prev2 != NULL) // 만약 prev2의 노드가 NULL이 아니라면 
			prev2->left = search2->right; // prev2 노드의 왼쪽 노드에 search2 노드의 오른쪽 노드 대입
            

		search->key = search2->key; // search의 key값에 search2 노드의 key값을 대입
        

		free(search2); // search2가 가리키는 노드의 메모리 해제
		return 0; // 함수 종료

	}
	
}


void freeNode(Node* ptr) // 트리에 있는 모든 메모리를 해제하는 함수
{
	// 후위 운행 방식으로 트리의 노드들의 메모리를 해제한다
    if (ptr) 
	{
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}

}


int freeBST(Node* head) // 이진탐색 트리의 노드들을 해제하는 함수
{
	if (head->left == head) // 만약 트리에 노드들이 없다면
	{
		free(head); // 헤드노드 메모리 해제
		return 1;
	}

	Node* p = head->left; // p에 루트노드를 대입한다
	freeNode(p); // freeNode 함수를 호출
	free(head); // 헤드노드 메모리 해제

	return 1;

}


Node* pop() // 스택에 원소를 빼내는는 함수
{
	Node* p=NULL; // p값을 NULL로 초기화한다

	if(top>=0) // 만약 스택에 원소들이 존재한다면
		p= stack[top--]; // 현재 스택의 top이 가리키고있는 배열의 인덱스를 p에 대입
        // 대입한 후, top의 값을 -1 감소시킨다

	return p; // 포인터 p 반환

}


void push(Node* aNode) // 스택에서 원소를 추가하는 함수
{
	if(top<MAX_STACK_SIZE-1) // 만약 스택이 꽉 차지 않았다면,
		stack[++top] = aNode; // 현재 top변수를 1만큼 증가하고, 스택의 top이 가리키고있는
        // 배열의 인덱스에 aNode를 대입
}

 

Node* deQueue() // 원형큐에서 원소를 빼내는 함수
{
    if(rear==front) // 원형큐에서 빼낼 원소가 없다면
        return NULL; // NULL값 반환

	front = (front + 1) % MAX_QUEUE_SIZE; // front에 1을 더하고 20으로 나눈 후 나머지 값을 front에 대입
    
	return queue[front]; // queue의 배열의 인덱스가 front인 배열을 리턴

}

 
void enQueue(Node* aNode) // 원형큐에서 원소를 추가하는 함수
{
	if((rear+1)%MAX_QUEUE_SIZE==front) // 만약 큐에 원소가 가득 찼다면(더 이상 집어넣을 수 없다면)
    {
         return ; // 종료
    }
    
    rear = (rear + 1) % MAX_QUEUE_SIZE; // rear에 1을 더하고 20으로 나눈 후 나머지 값을 rear에 대입
	queue[rear] = aNode; // queue의 배열의 인덱스가 rear인 곳에 aNode를 대입
}