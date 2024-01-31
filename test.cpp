#include <iostream>
#include <dirent.h>
#include <fstream>
#include <unistd.h>
int main(int argc, char const *argv[])
{
	FILE * file = std::fopen("hyhy","w");
	if(file)
	{
		char buf[10] = "hello wof";
		char buf2[10];
		write(fileno(file),buf,10);
		std::fclose(file);
		FILE * infile = std::fopen("hyhy","r");
		int a = read(fileno(infile), buf2, 10);
		std::string str(buf2);
		std::cout << "str : " << str << std::endl;
		
	}else{
		std::cout << "not opened" << std::endl;
	}
	return 0;
}

