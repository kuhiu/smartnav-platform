#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <iostream>
#include <sys/wait.h>
#include <atomic>
#include <experimental/filesystem>
#include <string.h>


#define BYTE2READ 4

using std::cout; using std::endl;
using std::string;