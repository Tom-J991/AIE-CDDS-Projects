#pragma once

class ListNode
{
public:
	ListNode(int data);
	~ListNode();

	int GetData() { return m_data; }
	ListNode *GetNext() { return m_pNext; }
	ListNode *GetPrev() { return m_pPrev; }

	void SetData(int data) { m_data = data; }
	void SetNext(ListNode *next) { m_pNext = next; }
	void SetPrev(ListNode *prev) { m_pPrev = prev; }

	bool HasNext() { return (m_pNext != nullptr); }
	bool HasPrev() { return (m_pPrev != nullptr); }

private:
	int m_data;

	ListNode *m_pNext;
	ListNode *m_pPrev;

};
