#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <atomic>
#include <experimental/filesystem>
#include <string.h>

using std::cout; using std::endl;
using std::string; using std::experimental::filesystem::exists; using std::experimental::filesystem::path;