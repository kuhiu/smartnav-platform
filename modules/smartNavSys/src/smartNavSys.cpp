#include "smartNavSys.hpp"

std::atomic<int> child_pid;
std::atomic<int> *children;

constexpr std::atomic_int handler_exit_code = {103};
constexpr std::atomic_int FORK_NUM = {6};               // Edit

void sigquitHandler(int signal_number)
{
    for (int i = 0; i < FORK_NUM; ++i) {
        kill(children[i], SIGTERM);
    }
    while ((child_pid = wait(nullptr)) > 0);
    _exit(handler_exit_code);
}

pid_t spawnChild(const char* program, const char** arg_list)
{
    pid_t ch_pid = fork();
    if (ch_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    else if (ch_pid > 0) {
        cout << "spawn child with pid - " << ch_pid << endl;
        return ch_pid;
    } 
    else {
        execvp(program, (char**)arg_list);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
}

int main(){
    // Img proc
    string program_imgproc ("./main.bin");
    const char *arg_list_imgproc[] = {program_imgproc.data(), nullptr};

    // FuzzyControl
    string program_fuzzzyControl ("./FuzzyControl/FuzzyControl");
    const char *arg_list_fuzzzyControl[] = {program_fuzzzyControl.data(), nullptr};

    // readSTATE
    string program_readState ("./readSTATE/readSTATE");
    const char *arg_list_readState[] = {program_readState.data(), nullptr};

    // distanceSensors
    string program_distanceSensors ("./distanceSensors/distanceSensors");
    const char *arg_list_distanceSensors[] = {program_distanceSensors.data(), nullptr};

    // usrSpace_drive
    string program_usrSpace_drive ("./apps/usrSpace_drive");
    const char *arg_list_usrSpace_drive[] = {program_usrSpace_drive.data(), nullptr}; 

    // Server (python)
    string program_server ("./PngServer/pngserver_ShowCNN.py");
    string intrepreter ("python3");
    const char *arg_list_server[] = {intrepreter.data(), program_server.data(), nullptr};

    // Add the apps you want to run
    string programs2run[(int)FORK_NUM] = {program_fuzzzyControl.data(), program_imgproc.data(), intrepreter.data(),\
    program_readState.data(), program_distanceSensors.data(), program_usrSpace_drive.data()};

    const char **argsOfPrograms2run[(int)FORK_NUM] = {arg_list_fuzzzyControl, arg_list_imgproc, arg_list_server,\
    arg_list_readState, arg_list_distanceSensors, arg_list_usrSpace_drive};

/*     if (!exists((path)program_fuzzzyControl)){
        cout << "Program file " << program_fuzzzyControl.data() << " does not exist in current directory!" << endl;
        exit(EXIT_FAILURE);
    } */

    children = reinterpret_cast<std::atomic_int *>(new int[FORK_NUM]);
    signal(SIGQUIT, sigquitHandler);

    for (int i = 0; i < FORK_NUM; ++i) {
        children[i] = spawnChild(programs2run[i].c_str(), argsOfPrograms2run[i]);
    }

    while ((child_pid = wait(nullptr)) > 0)
        cout << "child " << child_pid << " terminated" << endl;

    return EXIT_SUCCESS;
}