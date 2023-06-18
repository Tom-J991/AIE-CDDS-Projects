#pragma once

class ListNode;

class DoublyLinkedList
{
public:
	DoublyLinkedList();
	~DoublyLinkedList();

	void Insert(ListNode *node, int data);
	void PushBack(int data);
	void PushFront(int data);

	void Erase(ListNode *node);
	void Remove(int data);
	void Clear();
	void PopBack();
	void PopFront();

	void Sort();

	void Draw();

	ListNode *First() { return m_head; }
	ListNode *Last() { return m_tail; }

	unsigned int Count();
	bool Empty() const { return m_head == nullptr && m_tail == nullptr; }

private:
	void Draw(ListNode *node, int x, int y, int horizontalSpacing);

private:
	ListNode *m_head;
	ListNode *m_tail;

};
