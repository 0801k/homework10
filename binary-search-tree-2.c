
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

        printf("    [---------[�����]-----------------[2020039102]----------]\n"); 
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

		printf("Command = "); // ��ɾ� �Է�
		scanf(" %c", &command);

		switch (command) 
        {

		case 'z': case 'Z': // z, Z�� �Է��ϸ� �ʱ�ȭ�ϴ� �Լ� ȣ��
			initializeBST(&head);
			break;

		case 'q': case 'Q': // q, Q�� �Է��ϸ� �޸𸮸� �����ϴ� �Լ� ȣ��
			freeBST(head);
			break;

		case 'i': case 'I': // i, I�� �Է��ϸ� Ʈ���� ��� �����ϴ� �Լ� ȣ��
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;

		case 'd': case 'D': // d, D�� �Է��ϸ� ����ڰ� �Է��� ���� ���� ��� ����
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R': // r, R�� �Է��ϸ� ��ȯ ȣ�� �ϴ� �Լ� ȣ��
			recursiveInorder(head->left);
			break;

		case 't': case 'T': // t, T�� �Է��ϸ� �ݺ� ���� �Լ� ȣ��
			iterativeInorder(head->left);
			break;

		case 'l': case 'L': // l. L�� �Է��ϸ� ���� ��ȸ �Լ� ȣ��
			levelOrder(head->left);
			break;


		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;

		}

	} while (command != 'q' && command != 'Q'); // ��ɾ� q, Q�� �Է¹ޱ� ������ �ݺ�

	return 1;

}


int initializeBST(Node** h)  // �ʱ�ȭ �ϴ� �Լ�
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

 
void recursiveInorder(Node* ptr) // ��ȯ ȣ���� �ϴ� ���� ���� �Լ�
{
	if (ptr) 
	{
		recursiveInorder(ptr->left); // ���ʳ�带 Ž���Ѵ�
		printf(" [%d] ", ptr->key); // ����� KEY���� ����Ѵ�
		recursiveInorder(ptr->right); // ������ ��带 Ž���Ѵ�

	}

}

 
void iterativeInorder(Node* node) // ���� ���� �Լ�

{
	for (;;)
	{
		for (; node; node = node->left) // ���� node�� ���ʳ��� �����Ѵ�
			push(node); // ���� node�� ���ÿ� ����

		node = pop(); // 

		if (!node) break; // NULL �̶��

		printf("[%d]  ", node->key); // node�� key���� ���
		node = node->right; // ������ ���� ����

	}

}

 
void levelOrder(Node* ptr) // ���� ���� �����

{
	if(ptr==NULL) return ; // NULL�̸� ����
    enQueue(ptr); // ptr ��带 ���� ť�� ����
	for (;;)
	{
		ptr = deQueue(); // ����ť���� ptr ��带 ������
		if (ptr) // NULL�� �ƴ϶��
		{
			printf("[%d]  ", ptr->key); // ptr����� key���� ���

			if (ptr->left) 
				enQueue(ptr->left); // ptr ����� ���ʳ�带 ����ť ����

			if (ptr->right) 
				enQueue(ptr->right); // ptr ����� ������ ��带 ����ť�� ����

		}
		else break; // NULL�̸� ����

	}

}

 
int insert(Node* head, int key) // Ʈ���� ��带 �߰��ϴ� �Լ�

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

 

int deleteNode(Node* head, int key) // ��带 �����ϴ� �Լ�
{
	Node* search; // key���� ���� ��带 ����ų ������ ����
	Node* prev; // search�� �θ��带 ����ų ������ ����
	search = head->left; // ����带 search�� ����

	if (head->left == NULL) 
	{
		printf("Ʈ���� ��尡 �������� �ʽ��ϴ�.\n"); // ��� ���
		return 0; // �Լ� ����
 
	}

	while (search != NULL) // search�� ���� NULL�� �ƴ϶�� 
	{
		prev = search; // prev�� search�� ���� ����

		if (search->key < key) // search�� key���� �Է¹��� key������ �۴ٸ�
			search = search->right; // search�� ��带 ���� ����� ������ ���� �����Ѵ�

		else if (search->key > key) // search�� key���� �Է¹��� key������ ũ�ٸ�
			search = search->left; // search�� ��带 ���� ����� ���� ���� �����Ѵ�

		else // search�� key���� �Է¹��� key���� ���ٸ�
			break; 
	}

	if (search == NULL) // ���� �ݺ������� key���� ���� ��带 ã�� ���ߴٸ� 
	{
		printf("�ش� �� = [%d]�� ���� ��尡 �������� �ʽ��ϴ�.\n ", key); // ��� ���
		return 0; // �Լ� ����
	}

 

	if (search->right == NULL && search->left == NULL) // �����ϰ��� �ϴ� ��尡 �ܸ�����϶�
	{
		if(prev!=NULL) // search�� ����Ű�� ��尡 Ʈ���� ù��° ��尡 �ƴ϶��
        {
        if (prev->right == search) // ������ ��尡 search ��尡 �´ٸ�
			prev->right = NULL; // ������ ��忡 NULL�� ����

		else if (prev->left == search) // ���ʳ�尡 search ��尡 �´ٸ�
			prev->left = NULL; // ���� ��忡 NULL�� ����
        }

        else head->left==NULL; // search�� ����Ű�� ��尡 Ʈ���� ù��° ����̸�
        //  ������� ������ ��忡 NULL�� ����

        free(search); // search�� ����Ű�� ����� �޸� ����
        return 0; // �Լ� ����
	}

 
	else if (search->left == NULL ||search->right == NULL) // �����ϰ��� �ϴ� ����� �ڽ�Ʈ���� 1���϶�
	{
		Node* child; // search�� �ڽ� ��带 ����ų ������ ���� ����

		if (search->left == NULL) // ���� search�� ���� ��尡 ���ٸ�
			child = search->right; // child �� search�� ������ ���  ����

		else if(search->right==NULL) // ���� search�� ������ ��尡 ���ٸ�
			child = search->left; // child�� search�� ���� ���  ����


		if(prev!=head->left) // ���� search�� ����� Ʈ���� ù��° ��尡 �ƴ϶��
        {
        if (prev->left == search) // ���� ��尡 search��尡 �´ٸ�
		{
            prev->left = child; // search�� ���� ��忡 child ��� ����
        }

		else if (prev->right == search) // ������ ��尡 search��尡 �´ٸ�
		{	
            prev->right = child; // search�� ������ ��忡 child ��� ����
        }
        }
        else head->left=child; // Ʈ���� ù��° �����
        

		free(search); // search�� ����Ű�� ����� �޸� ����
        return 0; // �Լ� ����

	}

	else  // �����ϰ����ϴ� ����� ����Ʈ���� 2���϶�
	{
		Node* search2 = search->right; // ���� ����� ������ ��带 ����ų search2 ������ ���� ����
		Node* prev2=search2; // search2��� ����ų prev2 ������ ���� ����

		while (search2->left != NULL) // search2�� ���ʳ�尡 ���̻� ���������� ��� �ݺ�
		{
			prev2 = search2; // prev2�� search2��� ����
			search2 = search2->left; // search2��带 search2����� ���� ���� �����Ѵ�
		}

 
		if (prev2 != NULL) // ���� prev2�� ��尡 NULL�� �ƴ϶�� 
			prev2->left = search2->right; // prev2 ����� ���� ��忡 search2 ����� ������ ��� ����
            

		search->key = search2->key; // search�� key���� search2 ����� key���� ����
        

		free(search2); // search2�� ����Ű�� ����� �޸� ����
		return 0; // �Լ� ����

	}
	
}


void freeNode(Node* ptr) // Ʈ���� �ִ� ��� �޸𸮸� �����ϴ� �Լ�
{
	// ���� ���� ������� Ʈ���� ������ �޸𸮸� �����Ѵ�
    if (ptr) 
	{
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}

}


int freeBST(Node* head) // ����Ž�� Ʈ���� ������ �����ϴ� �Լ�
{
	if (head->left == head) // ���� Ʈ���� ������ ���ٸ�
	{
		free(head); // ����� �޸� ����
		return 1;
	}

	Node* p = head->left; // p�� ��Ʈ��带 �����Ѵ�
	freeNode(p); // freeNode �Լ��� ȣ��
	free(head); // ����� �޸� ����

	return 1;

}


Node* pop() // ���ÿ� ���Ҹ� �����´� �Լ�
{
	Node* p=NULL; // p���� NULL�� �ʱ�ȭ�Ѵ�

	if(top>=0) // ���� ���ÿ� ���ҵ��� �����Ѵٸ�
		p= stack[top--]; // ���� ������ top�� ����Ű���ִ� �迭�� �ε����� p�� ����
        // ������ ��, top�� ���� -1 ���ҽ�Ų��

	return p; // ������ p ��ȯ

}


void push(Node* aNode) // ���ÿ��� ���Ҹ� �߰��ϴ� �Լ�
{
	if(top<MAX_STACK_SIZE-1) // ���� ������ �� ���� �ʾҴٸ�,
		stack[++top] = aNode; // ���� top������ 1��ŭ �����ϰ�, ������ top�� ����Ű���ִ�
        // �迭�� �ε����� aNode�� ����
}

 

Node* deQueue() // ����ť���� ���Ҹ� ������ �Լ�
{
    if(rear==front) // ����ť���� ���� ���Ұ� ���ٸ�
        return NULL; // NULL�� ��ȯ

	front = (front + 1) % MAX_QUEUE_SIZE; // front�� 1�� ���ϰ� 20���� ���� �� ������ ���� front�� ����
    
	return queue[front]; // queue�� �迭�� �ε����� front�� �迭�� ����

}

 
void enQueue(Node* aNode) // ����ť���� ���Ҹ� �߰��ϴ� �Լ�
{
	if((rear+1)%MAX_QUEUE_SIZE==front) // ���� ť�� ���Ұ� ���� á�ٸ�(�� �̻� ������� �� ���ٸ�)
    {
         return ; // ����
    }
    
    rear = (rear + 1) % MAX_QUEUE_SIZE; // rear�� 1�� ���ϰ� 20���� ���� �� ������ ���� rear�� ����
	queue[rear] = aNode; // queue�� �迭�� �ε����� rear�� ���� aNode�� ����
}