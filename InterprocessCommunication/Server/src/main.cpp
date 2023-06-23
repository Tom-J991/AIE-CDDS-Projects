#include <iostream>
#include <windows.h>

struct MyData
{
	int i;
	float f;
	char c;
	bool b;
	double d;
};

// Server
int main()
{
	char start;
	std::cout << "Start Server? (Y/N): ";
	std::cin >> start;
	std::cout << std::endl;

	if (start == 'n' || start == 'N')
		return 0;

	// Create shared memory block.
	HANDLE fileHandle = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(MyData), L"MySharedMemory");
	if (fileHandle)
	{
		// Get pointer to shared memory.
		MyData *data = (MyData*)MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MyData));
		if (data)
		{
			// Fill out data.
			MyData myData{ };
			myData.i = 8;
			myData.f = 3.14159f;
			myData.c = 'W';
			myData.b = true;
			myData.d = 1.12345;

			*data = myData; // Write data to memory.

			UnmapViewOfFile(data); // Unmap pointer.
		}
		// Keep application open until prompted.
		bool end = false;
		std::cout << "Type P to exit." << std::endl;
		while (!end)
		{
			char p;
			std::cin >> p;
			if (p == 'P' || p == 'p')
				end = true;
		}

		CloseHandle(fileHandle); // Leave and delete shared memory block.
	}
	else
	{
		// Error
		std::cout << "Could not create shared memory block." << std::endl;
	}

	return 0;
}