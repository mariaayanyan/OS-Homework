#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <string.h>

void makeDir(const std::string& path)
{
	if (mkdir(path.c_str(), 0777) != 0)
	{
		if (errno != EEXIST)
		{
			perror("Failed to create the directory");
			exit(errno);
		}
	}
}

int main()
{
	// to read commands with arguments
	std::string cmd;

	int pid = getpid();
	std::string dir = "/opt/silentshell";

	// create a directory to redirect stdin, stdout, stderr
	makeDir(dir);

	while (std::getline(std::cin, cmd))
	{
		std::istringstream iss(cmd);
		std::string command, arg;

		std::vector<std::string> args;

		// separate the command from the arguments
		iss >> command;

		// seperate the arguments from each other 
		while (iss >> arg)
		{
			args.push_back(arg);
		}

		// create an array of arguments to pass to the exec* functions
		char** argv = new char* [args.size() + 2];

		argv[0] = new char[command.size()];
		strcpy(argv[0], command.c_str());
		
		for (int i = 0; i < args.size(); ++i)
		{
			argv[i + 1] = new char[args[i].size()];
			strcpy(argv[i + 1], args[i].c_str());
		}

		argv[args.size() + 1] = NULL;

		// create child process
		pid = fork();

		// failed to create
		if(pid == -1)
		{
			perror("Failed to create child process");
			exit(errno);
		}

		// if in child process
		if (pid == 0)
		{
			std::string path = dir +  "/" +  std::to_string(getpid());
			makeDir(path);

			// for stdout
			std::string cur = path + "/out.std";

			int fd = open(cur.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP);
			if (fd == -1)
			{
				cur = "Failed to open " + cur;
				perror(cur.c_str());
				exit(errno);
			}

			dup2(fd, fileno(stdout));

			// for stderr
			cur = path + "/err.std";
			fd = open(cur.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP);

			if (fd == -1)
			{
				cur = "Failed to open " + cur;
				perror(cur.c_str());
				exit(errno);
			}

			dup2(fd, fileno(stderr));

			// for stdin
			cur = path + "/in.std";
			fd = open(cur.c_str(), O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);

			if (fd == -1)
			{
				cur = "Failed to open " + cur;
				perror(cur.c_str());
				exit(errno);
			}

			dup2(fd, fileno(stdin));

			if (command[0] == '/')
				execv(command.c_str(), argv);
			else
				execvp(command.c_str(), argv);
		}
		
		// wait for child in parent
		else if(pid > 0)
		{
			int childStatus = -1;
			waitpid(pid, &childStatus, 0);
		}
	
		for (int i = 0; i < args.size() + 2; ++i)
			delete[] argv[i];
		delete[] argv;
	}

}