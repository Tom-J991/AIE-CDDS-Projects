#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

int main()
{
	InitWindow(800, 600, "Doubly Linked List");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText("Window", 190, 200, 20, LIGHTGRAY);

		GuiButton({ 600, 40, 120, 20 }, "Test");

		EndDrawing();
	}

	CloseWindow();

	return 0;
}