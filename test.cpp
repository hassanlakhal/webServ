#include <iostream>
#include <dirent.h>

int main(int argc, char const *argv[])
{
	DIR *dir;
	struct dirent *dent;
	if((dir = opendir("./methods/")) != NULL){
		while ((dent = readdir(dir)) != NULL)
		{
			std::cout << dent->d_name << std::endl;
		}

	}else{
		std::cout << "bad folder" << std::endl;
	}
	closedir(dir);
	return 0;
}

