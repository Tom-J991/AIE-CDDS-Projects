#include "listnode.h"

#include <raylib.h>
#include <string>

ListNode::ListNode(int data)
	: m_data { data }
	, m_pNext { nullptr }
	, m_pPrev { nullptr }
{ }
ListNode::~ListNode()
{ }

void ListNode::Draw(int x, int y)
{
	DrawRectangle(x, y, 34, 34, YELLOW);
	DrawRectangle(x, y, 32, 32, GREEN);
	int offset = MeasureText(std::to_string(m_data).c_str(), 12) / 2;
	DrawText(std::to_string(m_data).c_str(), x + 16 - offset, y + 10, 12, WHITE);
}
