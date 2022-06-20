#include "buttonsControl.hpp"

static volatile int keepRunning = 1;

std::atomic<int> child_pid;
std::atomic<int> *children;

constexpr std::atomic_int handler_exit_code = {103};
constexpr std::atomic_int FORK_NUM = {6};     

void intHandler(int dummy) {
    keepRunning = 0;
}

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

int main (void)
{
    int fd_button;
    int ubuff;

    // smartNavSys
    string program_smartNavSys ("/home/ubuntu/smartNavSys/smartNavSys");
    const char *arg_list_smartNavSys[] = {program_smartNavSys.data(), nullptr};

    // Add the apps you want to run
    string programs2run[(int)FORK_NUM] = {program_smartNavSys.data()};

    const char **argsOfPrograms2run[(int)FORK_NUM] = {arg_list_smartNavSys};

    if ( (fd_button = open("/dev/chardev_buttons_EMIOgpio_PL_1", O_RDWR)) == -1){
        printf("Error abriendo chardev_buttons_EMIOgpio_PL_1\n");
        return -1;
    }

    signal(SIGINT, intHandler);
    
    while(keepRunning){
        if ( ( read(fd_button, &ubuff, BYTE2READ)) == -1){
            printf("Error leyendo leds_control_chardev\n");
            return -1;
        } 
        printf("El boton apretado fue %d\n", ubuff);   

        switch (ubuff)
        {
        case 1:
            children = reinterpret_cast<std::atomic_int *>(new int[FORK_NUM]);
            signal(SIGQUIT, sigquitHandler);

            for (int i = 0; i < FORK_NUM; ++i) {
                children[i] = spawnChild(programs2run[i].c_str(), argsOfPrograms2run[i]);
            }

            while ((child_pid = wait(nullptr)) > 0)
                cout << "child " << child_pid << " terminated" << endl;
            break;
        default:
            printf("Error, el boton no existe\n"); 
            break;
        }
    }

    close(fd_button);
    return 0;
}
