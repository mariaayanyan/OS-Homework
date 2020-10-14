#include <iostream>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void printSize(const char options[], const char filename[])
{
	char* command = new char[strlen(filename) + strlen(options) + 1];
	
	strcat(command, options);
	strcat(command, filename);
	system(command);
	
	delete[] command;
}

int main(int argc, char* argv[])
{
	// source and/or destination file path missing
	if(argc < 3)
	{
		std::cout << "Not enough arguments.\n";
		return -1;		
	}

	int source_fd = open(argv[1], O_RDONLY);

	// something went wrong
	if(source_fd == -1)
	{
		std::cout << "Something went wrong while opening the file " << argv[1] << ": " << strerror(errno) << '\n';
		exit(errno);
	}

	system("echo \"Logical size: \"");
	printSize("du -h ", argv[1]);

	system("echo \"Apparent size: \"");
	printSize( "du -h --apparent-size ", argv[1]);
	
	
	int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC);

	int bufferSize = 16;
	char buffer[bufferSize + 1];

	while(1)
	{
		// read buffer
		int readBytes = read(source_fd, buffer, bufferSize);

		// stop if no more bytes to read
		if(readBytes == 0)
			break;

		buffer[readBytes] = '\0';
		write(dest_fd, buffer, readBytes);
	}

	close(source_fd);
	close(dest_fd);	

	std::cout << '\n';
	system("echo \"Logical size: \"");
	printSize("du -h ", argv[2]);

	system("echo \"Apparent size: \"");
	printSize("du -h --apparent-size ", argv[2]);
	
}