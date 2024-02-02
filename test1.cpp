#include <iostream>
#include <fstream>
#include <string>
#include<ctime>
#include<sstream>
#include<cstdlib>
#include<cstdlib>
#include <unistd.h> 
void encryptFileName(std::string& fileName, char key) 
{

    std::stringstream iss;
    iss << time(NULL);
    for (size_t i = 0; i < fileName.size(); ++i) 
    {
        fileName[i] ^= (key);
    }
    usleep(200);
    fileName += iss.str();
}

int main() 
{
    // Get the original filename
    std::string originalFileName;
    std::cout << "Enter the original filename: ";
    std::cin >> originalFileName;
    srand(time(0));
    int a = 65 + rand() % (26);
    char encryptionKey = a; 
    encryptFileName(originalFileName, encryptionKey);

    // Create and write to the encrypted filename
    std::ofstream encryptedFile(originalFileName.c_str());
    encryptedFile << "This is the content of the encrypted file." << std::endl;
    encryptedFile.close();

    std::cout << "File created with encrypted name: " << originalFileName << std::endl;
    std::remove(originalFileName.c_str());

    return 0;
}
