#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>

#include <string>
#include <sstream>

#include "doublylinkedlist.h"
#include "listnode.h"

int main()
{
	InitWindow(800, 600, "Doubly Linked List");
	SetTargetFPS(60);

	DoublyLinkedList doublyLinkedList;

	std::stringstream ss;
	int valueBoxValue = 0;
	bool valueBoxEditMode = false;
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		GuiSetStyle(TEXTBOX, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);

		if (GuiValueBox({ 25, 25, 125, 30 }, NULL, &valueBoxValue, 0, 100, valueBoxEditMode)) valueBoxEditMode = !valueBoxEditMode;

		if (GuiButton({ 160, 25, 125, 30 }, GuiIconText(ICON_OK_TICK, "Push Back")))
			doublyLinkedList.PushBack(valueBoxValue);
		if (GuiButton({ 160, 60, 125, 30 }, GuiIconText(ICON_OK_TICK, "Push Front")))
			doublyLinkedList.PushFront(valueBoxValue);
		if (GuiButton({ 160, 95, 125, 30 }, GuiIconText(ICON_CROSS, "Remove")))
			doublyLinkedList.Remove(valueBoxValue);
		if (GuiButton({ 160, 130, 125, 30 }, GuiIconText(ICON_CROSS, "Pop Back")))
			doublyLinkedList.PopBack();
		if (GuiButton({ 160, 165, 125, 30 }, GuiIconText(ICON_CROSS, "Pop Front")))
			doublyLinkedList.PopFront();
		// Not sure how to implement the Insert method as a button since it requires a pointer to the node to insert behind of.

		// First
		if (doublyLinkedList.First() != nullptr)
			ss << "First: " << doublyLinkedList.First()->GetData();
		else
			ss << "First: " << std::to_string(-1); // Default
		GuiDrawText(ss.str().c_str(), { 25, 60, 125, 30 }, TEXT_ALIGN_CENTER, BLACK);
		ss.str("");

		// Last
		if (doublyLinkedList.Last() != nullptr)
			ss << "Last: " << doublyLinkedList.Last()->GetData();
		else
			ss << "Last: " << std::to_string(-1); // Default
		GuiDrawText(ss.str().c_str(), { 25, 95, 125, 30 }, TEXT_ALIGN_CENTER, BLACK);
		ss.str("");

		// Count
		ss << "Count: " << doublyLinkedList.Count();
		GuiDrawText(ss.str().c_str(), {25, 130, 125, 30}, TEXT_ALIGN_CENTER, BLACK);
		ss.str("");

		doublyLinkedList.Draw();

		EndDrawing();
	}

	CloseWindow();

	doublyLinkedList.Clear();

	return 0;
}