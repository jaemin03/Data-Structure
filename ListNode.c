#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>


typedef struct element
{
	int value;
	char name[20];
}element;

typedef struct ListNode { // ��� Ÿ���� ����ü�� �����Ѵ�.
	struct element data;
	struct ListNode* link;
} ListNode;

void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

ListNode* insert_first(ListNode* head, element value) // ���Կ���
{
	ListNode* p =
		(ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = head;
	head = p;
	return head;
}

// ��� pre �ڿ� ���ο� ��� ����
ListNode* insert(ListNode* head, ListNode* pre, element value)
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = value;
	p->link = pre->link;
	pre->link = p;
	return head;
}


ListNode* delete_first(ListNode* head) // ��������
{
	ListNode* removed;
	if (head == NULL) return NULL;
	removed = head;
	head = removed->link;
	free(removed);
	return head;
}

// pre�� ����Ű�� ����� ���� ��带 �����Ѵ�.
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

ListNode* delete_min(ListNode* head) // �ּҰ��� ���� ��带 ã�� ����
{
	ListNode* p = head->link;
	ListNode* min = head; //�ּҰ��� ���� ��� ����
	ListNode* pre = head; //�ּҰ��� ���� ����� �����

	while (p != NULL)
	{
		if (p->data.value < min->data.value)
		{
			pre = min;
			min = p;
		}
		p = p->link;
	}

	printf("�õ� Ż�� : %s(%d)\n\n", min->data.name, min->data.value);

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
	return NULL; // Ž�� ����
}

// �׽�Ʈ ���α׷�
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
		printf("%d����\n", i+1);
		rand_list(head);
		print_list(head);
		head = delete_min(head);
	}


	return 0;
}