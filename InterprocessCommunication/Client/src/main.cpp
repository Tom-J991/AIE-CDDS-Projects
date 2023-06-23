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

// Client
int main()
{
	// Access shared memory block.
	HANDLE fileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"MySharedMemory");
	if (fileHandle)
	{
		// Create pointer to shared memory.
		MyData *data = (MyData*)MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MyData));
		if (data)
		{
			std::cout << "MyData = { ";
			std::cout << data->i << ", ";
			std::cout << data->f << ", ";
			std::cout << data->c << ", ";
			std::cout << data->b << ", ";
			std::cout << data->d << ", ";
			std::cout << " };" << std::endl;

			UnmapViewOfFile(data); // Unmap pointer.
		}
		CloseHandle(fileHandle); // Leave shared memory block.
	}
	else
	{
		// Couldn't find it.
		std::cout << "Could not find shared memory." << std::endl;
	}

	std::cin.ignore();
	return 0;
}