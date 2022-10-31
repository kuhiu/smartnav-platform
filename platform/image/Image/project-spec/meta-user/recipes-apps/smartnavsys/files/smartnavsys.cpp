#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	cout << "Hello, PetaLinux World!\n";
	cout << "cmdline args:\n";
	while(argc--)
		cout << *argv++ << endl;

	return 0;
}


