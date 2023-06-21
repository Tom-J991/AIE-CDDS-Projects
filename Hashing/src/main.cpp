#include <iostream>
#include <string>
#include <utility>

#include <raylib.h>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include <raygui.h>

#include "HashFunction.h"

unsigned int g_tableSize = 8;

void InsertHash(char *key, char **&hashTable);
char *FindHash(char *key, char **&hashTable);

int main()
{
	InitWindow(800, 600, "Hashing");
	SetTargetFPS(60);

	HashFunction::defaultHashFunction = HashFunction::ELFHash;

	// Create Hash Table
	char **hashTable = new char*[g_tableSize];
	for (int i = 0; i < g_tableSize; ++i)
		hashTable[i] = nullptr; // Init

	// Text Box Variables
	const unsigned int bufferSize = 64;
	char *textBoxBuffer = new char[bufferSize];
	textBoxBuffer[0] = '\0';
	bool textBoxEditMode = false;
	char *selected = nullptr;

	// Main Loop
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		{
			// Draw UI
			if (GuiTextBox({ 25, 25, 125, 30 }, textBoxBuffer, bufferSize, textBoxEditMode))
				textBoxEditMode = !textBoxEditMode;

			if (GuiButton({ 160, 25, 125, 30 }, GuiIconText(ICON_OK_TICK, "Insert")))
			{
				selected = FindHash(textBoxBuffer, hashTable);
				if (selected == nullptr)
					InsertHash(textBoxBuffer, hashTable);
			}

			// Draw Hash Table
			DrawText("Hash Table:", 320-2, 16, 18, GRAY);
			for (int i = 0; i < g_tableSize; ++i)
			{
				int y = i * 48;

				Color c = GRAY;
				if (selected == hashTable[i] && selected != nullptr)
					c = SKYBLUE;

				DrawRectangle(320-2, 40+y-2, 32+4, 32+4, DARKGRAY);
				DrawRectangle(320, 40+y, 32, 32, c);
				DrawText(std::to_string(i).c_str(), 320, 40+y, 14, WHITE);

				DrawRectangle(368-2, 40+y-2, 256+4, 32+4, DARKGRAY);
				DrawRectangle(368, 40+y, 256, 32, c);
				if (hashTable[i] != nullptr)
				{
					int offset = MeasureText(hashTable[i], 18)/2;
					DrawText(hashTable[i], 496-offset, 48+y, 18, WHITE);
				}
			}
		}
		EndDrawing();
	}

	CloseWindow();

	// Clean Up
	delete[] textBoxBuffer;
	delete[] hashTable;

	return 0;
}

void InsertHash(char *key, char **&hashTable)
{
	const unsigned int keySize = sizeof(key) / sizeof(key[0]);
	unsigned int hashedKey = HashFunction::defaultHashFunction(key, keySize);
	hashedKey = hashedKey % g_tableSize;

	// Copy to new char
	char *value = new char[keySize];
	strcpy(value, key);

	hashTable[hashedKey] = value;

	std::cout << "Value : " << value << std::endl;
	std::cout << "Hashed Key : " << hashedKey << std::endl;
}

char *FindHash(char *key, char **&hashTable)
{
	if (hashTable == nullptr)
		return nullptr;

	char *found = nullptr;

	const unsigned int keySize = sizeof(key) / sizeof(key[0]);
	unsigned int hashedKey = HashFunction::defaultHashFunction(key, keySize);
	hashedKey = hashedKey % g_tableSize;

	found = hashTable[hashedKey];

	return found;
}
