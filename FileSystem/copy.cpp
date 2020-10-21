#include <iostream>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

bool lseekCheck(int offset)
{
	if(offset == -1)
	{
		if(errno == ENXIO)
			return false;
		std::cout << "lseek() failed: " << strerror(errno) << '\n';
		exit(errno);
	}
	return true;
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
	
	int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP);
	int start = 0;

	int sourceSize = 0, destSize = 0; // physical sizes

	struct stat sfile; //pointer to stat struct
	int stat_check = stat(argv[1], &sfile); //stat system call
	
	// something went wrong
	if(stat_check == -1)
	{
		std::cout << "Failed to check the status of the file " << argv[1] << ": " << strerror(errno) << '\n';
		exit(errno);
	}

	while(1)
	{
		int curPosition = lseek(source_fd, start, SEEK_HOLE); // get the position of the hole
		lseekCheck(curPosition); 

		int bufferSize = curPosition - start; // the amount of data to read before the hole
		char* buffer = new char[bufferSize];

		start = lseek(source_fd, start, SEEK_SET); // get back to the data block
		lseekCheck(start);
		
		// read buffer
		int readBytes = read(source_fd, buffer, bufferSize);

		// failed to read
		if(readBytes == -1)
		{
			std::cout << "Failed to read from the file " << argv[1] << ": " << strerror(errno) << '\n';
			exit(errno);
		}

		sourceSize += readBytes;
		
		// write buffer to destination file
		int writeCount = write(dest_fd, buffer, readBytes);
		delete[] buffer;

		// failed to write
		if(writeCount == -1)
		{
			std::cout << "Failed to write to the file " << argv[2] << ": " << strerror(errno) << '\n';
			exit(errno);
		}

		destSize += writeCount; 

		int end = start + readBytes; // mark the end of the data block

		curPosition = lseek(source_fd, curPosition, SEEK_DATA); // get to the next data block

		// check if there's any data left
		if(!lseekCheck(curPosition))
		{
			// write the hole at the end		
			lseek(dest_fd, sfile.st_size - end, SEEK_END);
			break;
		}

		start = curPosition; // mark the start of the new data block
		
		//write the hole
		curPosition = lseek(dest_fd, curPosition - end, SEEK_END);
		lseekCheck(curPosition);
	}

	close(source_fd);
	close(dest_fd);	

	// print the logical and physical size of the source file
	std::cout << "Logical size:\n" << sfile.st_size  << "B\t" << argv[1] << '\n';
	std::cout << "Physical size:\n" << sourceSize << "B\t" << argv[1] << '\n';

	stat_check = stat(argv[2], &sfile); //stat system call

	// something went wrong
	if(stat_check == -1)
	{
		std::cout << "Failed to check the status of the file " << argv[1] << ": " << strerror(errno) << '\n';
		exit(errno);
	}

	// print the logical and physical size of the destination file
	std::cout << "\nLogical size:\n" << sfile.st_size << "B\t" << argv[2] << '\n';
	std::cout << "Physical size:\n" << destSize << "B\t" << argv[2] << '\n';
}