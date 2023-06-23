#include "pch.h"
#include "listnode.h"

ListNode::ListNode(int data)
	: m_data { data }
	, m_pNext { nullptr }
	, m_pPrev { nullptr }
{ }
ListNode::~ListNode()
{ }
