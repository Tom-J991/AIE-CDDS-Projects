#include "EntityDisplayApp.h"

EntityDisplayApp::EntityDisplayApp(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight) 
{ }
EntityDisplayApp::~EntityDisplayApp() 
{ }

bool EntityDisplayApp::Startup()
{
	InitWindow(m_screenWidth, m_screenHeight, "EntityDisplayApp");
	SetTargetFPS(60);

	// Access shared memory.
	h = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"EntityMemory");
	if (h)
	{
		dataPointer = (SharedEntity*)MapViewOfFile(h, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(SharedEntity));
		if (dataPointer)
			m_entityCount = dataPointer->entityCount;
	}

	m_entities = new Entity[m_entityCount];

	return true;
}

void EntityDisplayApp::Shutdown() 
{
	CloseWindow(); // Close window and OpenGL context
	if (h)
	{
		if (dataPointer)
			UnmapViewOfFile(dataPointer); // Unmap pointer.
		CloseHandle(h); // Leave shared memory.
	}
}

void EntityDisplayApp::Update(float deltaTime) 
{
	if (h && dataPointer) // If shared memory exists.
	{
		for (int i = 0; i < m_entityCount; ++i)
		{
			m_entities[i] = dataPointer->entityArray[i];
		}
	}
}

void EntityDisplayApp::Draw() 
{
	BeginDrawing();
	ClearBackground(RAYWHITE);

	// draw entities
	if (m_entities != nullptr)
	{
		for (int i = 0; i < m_entityCount; ++i)
		{
			Entity &entity = m_entities[i];
			DrawRectanglePro(
				Rectangle{ entity.x, entity.y, entity.size, entity.size }, // rectangle
				Vector2{ entity.size / 2, entity.size / 2 }, // origin
				entity.rotation,
				Color{ entity.r, entity.g, entity.b, 255 });
		}
	}

	// output some text, uses the last used colour
	DrawText("Press ESC to quit", 630, 15, 12, LIGHTGRAY);

	EndDrawing();
}
