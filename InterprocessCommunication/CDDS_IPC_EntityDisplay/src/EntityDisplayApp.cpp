#include "EntityDisplayApp.h"

EntityDisplayApp::EntityDisplayApp(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight) 
{ }
EntityDisplayApp::~EntityDisplayApp() 
{ }

bool EntityDisplayApp::Startup()
{
	InitWindow(m_screenWidth, m_screenHeight, "EntityDisplayApp");
	SetTargetFPS(60);

	// Access shared memory block
	h = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"SharedEntites");

	return true;
}

void EntityDisplayApp::Shutdown() 
{
	CloseWindow(); // Close window and OpenGL context
	if (h) // Closed shared memory block
		CloseHandle(h);
}

void EntityDisplayApp::Update(float deltaTime) 
{
	Load(); // Update entities from shared memory
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

void EntityDisplayApp::Load()
{
	// Access shared memory
	LPVOID fullData = (int *)MapViewOfFile(h, FILE_MAP_ALL_ACCESS, 0, 0, 0);

	char *sizeLocation = (char *)fullData;
	int *sizeMemory = (int *)sizeLocation;

	// Set entity count
	m_entityCount = *sizeMemory;
	if (m_entities == nullptr) // Create entity array if it doesn't exist
		m_entities = new Entity[m_entityCount];

	// Set each entity
	for (size_t i = 0; i < m_entityCount; ++i)
	{
		char *entityLocation = (char *)fullData + sizeof(int) + sizeof(Entity) * i;
		Entity *entityMemory = (Entity *)entityLocation;
		m_entities[i] = *entityMemory;
	}

	// Close shared memory
	UnmapViewOfFile(fullData);
}
