#include <stdio.h>
#include <stdlib.h>

typedef struct node     // Binary Search Tree에서 노드를 구성할 구조체 선언
{
    int key;
    struct node *left;
    struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */


int main()
{
	char command;
	int key;
	Node* head = NULL;      // headnode의 주소를 담을 구조체 포인터 생성
	Node* ptr = NULL;	

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);                   // headnode를 생성해준다.
			break;
		case 'q': case 'Q':
			freeBST(head);                          // 이진탐색트리의 메모리 전부 해제.
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);                      // 새로운 노드 생성
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);              // 노드 지우기
			break;
		case 'f': case 'F':                         // 노드 찾기
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);       // iterative 방식으로 찾기
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);     //  recursive 방식으로 찾기
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);       // 중위순회
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);      // 전위순회
			break;
		case 't': case 'T':
			postorderTraversal(head->left);     // 후위순회
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initializeBST(Node** h)         // 이진트리의 시작인 headnode 생성
{
    if(h!=NULL)
        freeBST(*h);

    (*h)=(Node*)malloc(sizeof(Node));       // *h는 headnode가 만들어질 메모리의 위치
    (*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	return 1;
}

int insert(Node* head, int key)     // node 삽입부분
{
    Node* newNode=(Node*)malloc(sizeof(Node));      // 새로운 node 생성
    newNode->key=key;
    newNode->left=NULL;
    newNode->right=NULL;

    if(head->left==NULL)            // headnode뒤에 아무런 노드가 없을 때
    {
        head->left=newNode;
        return 1;
    }

    Node *ptr=head->left;           // newNode가 들어갈 위치를 잡기 위함
    Node *parentNode=NULL;          // newNode의 부모노드를 잡기 위함

    while(ptr!=NULL)                // newNode를 넣을 위치까지 ptr을 움직인다.
    {   
        if(ptr->key==key)  return 1;       // 사용자가 입력한 값이 이미 트리에 있을 경우

        parentNode=ptr;

        if(ptr->key<key)                    // 입력받은 key가 현재 ptr노드의 키보다 작으면 오른쪽으로 간다.
            ptr=ptr->right;
        else
            ptr=ptr->left;
    }

    if(parentNode->key>key)
        parentNode->left=newNode;
    else
        parentNode->right=newNode;

    
    return 1;
}


int deleteLeafNode(Node* head, int key)     // 노드 지우기
{
	if (head == NULL)                           // head가 아예 없는 경우
    {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

    if (head->left == NULL)                     // headNode는 있지만 그 밑에 subnode가 없는 경우
    {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

    Node* ptr=head->left;                       // 임시 ptr를 생성
    Node* parentNode=head;                      // 임시 parentNode 생성

    while(ptr!=NULL)
    {

        if(ptr->key==key)                           // 삭제하려는 key값을 가진 노드를 찾음
        {
            if(ptr->left==NULL&&ptr->right==NULL)   // 그리고 그 key값을 가진 노드의 자식 노드가 없을 때
            {
                if(parentNode==head)                // 그리고 그 key값을 가진 노드가 headNode 일때
                    head->left=NULL;
                
                if(parentNode->left==ptr)           // 삭제하려는 node가 루트노드 바로 밑에 있을 때..
                    parentNode->left=NULL;
                else
                    parentNode->right=NULL;

                free(ptr);
            }

            else                                    // 삭제 하려는 노드가 leaf노드가 아닐 때
				printf("the node [%d] is not a leaf \n", ptr->key);

            return 1;
        }
        
        parentNode = ptr;                           // 부모노드를 옮긴다.

        if(ptr->key<key)                            // 입력받은 key가 비교하려는 노드의 key보가 크면 ptr을 오른쪽 서브트리로 이동
            ptr=ptr->right;
        else    
            ptr=ptr->left;                          // 아니면 왼쪽 서브트리로 이동

    }

    printf("Cannot find the node for key [%d]\n ", key);    // 못찾음

    return 1;
}

Node* searchIterative(Node* head, int key)          // 노드를 iterative방식으로 찾는다.
{
    Node* ptr=head->left;                      // 임시노드 생성

    while(ptr!=NULL)                           // 노드 생성
    {
        if(ptr->key==key)                      // 찾았으면 노드 주소값으로 반환
            return ptr;

        if(ptr->key<key)                        // 입력받은 key가 크면 오른쪽
            ptr=ptr->right;
        else
            ptr=ptr->left;                     // 작으면 왼쪽
    }

    return NULL;                      
             // 없으면 NULL
}

Node* searchRecursive(Node* ptr, int key)       // recursive방식으로 찾는다.
{
    if(ptr==NULL)                               // 2번 이상의 recursive call로 원하는 node를 찾았을 경우 recursive call을 멈추게한다.
        return NULL;
    
    if(ptr->key > key)
        ptr=searchRecursive(ptr->right,key);    // 작으면 오른쪽으로
    else
        ptr=searchRecursive(ptr->left,key);     // 크면 왼쪽으로

    return ptr;                                 // 한번의 recursive call로 원하는 node를 찾았을 경우
}

void inorderTraversal(Node* ptr)    // 출력순서 : 1.left  2.root  3.right
                                    // recursive 방식의 inordertraver 이다.
{
    if(ptr)                         // ptr이 NULL이 아니면
    {
        inorderTraversal(ptr->left);    // 왼쪽먼저 돌고
		printf(" [%d] ", ptr->key);     // 루트 출력
        inorderTraversal(ptr->right);   // 다음 오른쪽
    }
}

void preorderTraversal(Node* ptr)   // 출력순서 : 1.root  2.left  3.right
{
    if(ptr)
    {
        printf(" [%d] ", ptr->key);     // 루트 출력
        preorderTraversal(ptr->left);   // 다음 왼쪽
        preorderTraversal(ptr->right);  // 다음 오른쪽
    }
}

void postorderTraversal(Node* ptr)  // 출력순서 : 1.left  2.right  3.root
{
    if(ptr)
    {   
        postorderTraversal(ptr->left);  // 왼쪽으로 recursive
        postorderTraversal(ptr->right); // 다음 오른쪽 recursive
        printf(" [%d] ", ptr->key);     // 루트 출력
    }
}

void freeNode(Node* ptr)        // recursive을 활용한 노드 메모리 해제하기
{
    if(ptr)
    {
        freeNode(ptr->left);
        freeNode(ptr->right);
        free(ptr);
    }

}

int freeBST(Node* head)             // 이진트리 초기화 하기
{
    if(head->left!=NULL)            // headNode만 있을 때...
    {
        free(head);
        return 1;
    }

    Node *p=head->left;             // 임시 포인터 p를 왼쪽으로 보낸다.

    freeNode(p);                    // 노드를 없애고
    free(head);                     // headNode 없앤다.

    return 1;
}