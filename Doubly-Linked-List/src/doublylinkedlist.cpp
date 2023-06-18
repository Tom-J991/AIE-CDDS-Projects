#include "doublylinkedlist.h"

#include "listnode.h"

#include <raylib.h>

DoublyLinkedList::DoublyLinkedList()
	: m_head { nullptr }
	, m_tail { nullptr }
{ }
DoublyLinkedList::~DoublyLinkedList()
{ }

void DoublyLinkedList::Insert(ListNode *node, int data)
{
	ListNode *newNode = new ListNode(data);
	newNode->SetNext(node);
	if (node != nullptr)
	{
		newNode->SetPrev(node->GetPrev());
		if (node->HasPrev())
			node->GetPrev()->SetNext(newNode);
		node->SetPrev(newNode);
	}
	if (m_head == node)
		m_head = newNode;
	if (m_tail == nullptr)
		m_tail = newNode;
}

void DoublyLinkedList::PushBack(int data)
{
	ListNode *newNode = new ListNode(data);
	if (m_tail != nullptr)
	{
		newNode->SetPrev(m_tail);
		m_tail->SetNext(newNode);
	}
	m_tail = newNode;
	if (m_head == nullptr)
		m_head = newNode;
}
void DoublyLinkedList::PushFront(int data)
{
	ListNode *newNode = new ListNode(data);
	if (m_head != nullptr)
	{
		newNode->SetNext(m_head);
		m_head->SetPrev(newNode);
	}
	m_head = newNode;
	if (m_tail == nullptr)
		m_tail = newNode;
}

void DoublyLinkedList::Erase(ListNode *node)
{
	if (node != nullptr)
	{
		if (m_head == node)
			PopFront();
		else if (m_tail == node)
			PopBack();
		else
		{
			ListNode *tmp = node;
			if (node->HasNext())
			{
				if (node->HasPrev())
					node->GetNext()->SetPrev(node->GetPrev());
				else
					node->GetNext()->SetPrev(nullptr);
			}
			if (node->HasPrev())
			{
				if (node->HasNext())
					node->GetPrev()->SetNext(node->GetNext());
				else
					node->GetPrev()->SetNext(nullptr);
			}
			delete tmp;
			tmp = nullptr;
		}
	}
}
void DoublyLinkedList::Remove(int data)
{
	// Removes first one found from front of list
	ListNode *current = m_head;
	while (current != nullptr)
	{
		ListNode *next = current->GetNext();
		if (current->GetData() == data)
		{
			Erase(current);
			current = nullptr;
			next = nullptr;
			break;
		}
		current = next;
		next = nullptr;
	}
}
void DoublyLinkedList::Clear()
{
	ListNode *current = m_head;
	while (current != nullptr)
	{
		ListNode *next = current->GetNext();
		Erase(current);
		current = next;
		next = nullptr;
	}
}

void DoublyLinkedList::PopBack()
{
	if (m_tail != nullptr)
	{
		ListNode *tmp = m_tail;
		if (m_tail->HasPrev())
			m_tail->GetPrev()->SetNext(nullptr);
		m_tail = m_tail->GetPrev();
		delete tmp;
		tmp = nullptr;
	}
}
void DoublyLinkedList::PopFront()
{
	if (m_head != nullptr)
	{
		ListNode *tmp = m_head;
		if (m_head->HasNext())
			m_head->GetNext()->SetPrev(nullptr);
		m_head = m_head->GetNext();
		delete tmp;
		tmp = nullptr;
	}
}

void DoublyLinkedList::Sort()
{
	if (m_head == nullptr)
		return;

	// Bubble Sort
	ListNode *current = m_head;
	while (current != nullptr)
	{
		ListNode *next = current->GetNext();
		while (next != nullptr)
		{
			if (current->GetData() > next->GetData())
			{
				int tmp = current->GetData();
				current->SetData(next->GetData());
				next->SetData(tmp);
			}
			next = next->GetNext();
		}
		current = current->GetNext();
	}
}

unsigned int DoublyLinkedList::Count()
{
	unsigned int count = 0;
	ListNode *current = m_head;
	while (current != nullptr)
	{
		count++;
		current = current->GetNext();
	}
	return count;
}

void DoublyLinkedList::Draw()
{
	Draw(m_head, 40, 320, 64);
}
void DoublyLinkedList::Draw(ListNode *node, int x, int y, int horizontalSpacing)
{
	if (node)
	{
		if (node->HasPrev())
		{
			DrawLine(x, y + 12, x - horizontalSpacing, y + 12, RED);
		}
		if (node->HasNext())
		{
			DrawLine(x, y + 24, x + horizontalSpacing, y + 24, GREEN);
			Draw(node->GetNext(), x + horizontalSpacing, y, horizontalSpacing);
		}
		node->Draw(x, y);
	}
}
