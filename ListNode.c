#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>


typedef struct element
{
	int value;
	char name[20];
}element;

typedef struct ListNode { // 노드 타입을 구조체로 정의한다.
	struct element data;
	struct ListNode* link;
} ListNode;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListNode* insert_first(ListNode* head, element value) // 삽입연산
{
	ListNode* p =
		(ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

// 노드 pre 뒤에 새로운 노드 삽입
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}


ListNode* delete_first(ListNode* head) // 삭제연산
{
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

// pre가 가리키는 노드의 다음 노드를 삭제한다.
ListNode* delete(ListNode* head, ListNode* pre)
{
	ListNode* removed;
	removed = pre->link;
	pre->link = removed->link;
	free(removed);

	return head;
}

void print_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
		printf("(%s : %d) ->", p->data.name, p->data.value);
	printf("NULL \n");
}

void rand_list(ListNode* head)
{
	for (ListNode* p = head; p != NULL; p = p->link)
	{
		p->data.value = rand();
	}
}

ListNode* delete_min(ListNode* head) // 최소값을 가진 노드를 찾고 삭제
{
	ListNode* p = head->link;
	ListNode* min = head; //최소값을 가진 노드 저장
	ListNode* pre = head; //최소값을 가진 노드의 전노드

	while (p != NULL)
	{
		if (p->data.value < min->data.value)
		{
			pre = min;
			min = p;
		}
		p = p->link;
	}

	printf("꼴등 탈락 : %s(%d)\n\n", min->data.name, min->data.value);

	if (head == min) head = delete_first(head);
	else head = delete(head, pre);

	return head;
}

ListNode* search_list(ListNode* head, element x)
{
	ListNode* p = head;
	while (p != NULL) {
		if (p->data.value == x.value) return p;
		p = p->link;
	}
	return NULL; // 탐색 실패
}

// 테스트 프로그램
int main(void)
{
	ListNode* head = NULL;
	ListNode* p = head;
	element user[5];

	strcpy(user[0].name, "jiyoung");
	strcpy(user[1].name, "bomi");
	strcpy(user[2].name, "minji");
	strcpy(user[3].name, "kiho");
	strcpy(user[4].name, "sejong");

	user[0].value = 0;
	user[1].value = 0;
	user[2].value = 0;
	user[3].value = 0;
	user[4].value = 0;
	
	for (int i = 0; i < 5; i++)
	{
		head = insert_first(head, user[i]);
	}

	print_list(head);

	for (int i = 0; i < 4; i++)
	{
		printf("%d라운드\n", i+1);
		rand_list(head);
		print_list(head);
		head = delete_min(head);
	}


	return 0;
}