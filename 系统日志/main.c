#include <syslog.h>

int main(int argc, char *argv[])
{
    openlog(argv[0], LOG_PID, LOG_USER);
    syslog(LOG_INFO, "program started.");

    syslog(LOG_INFO, "program terminated.");
    closelog();
    return 0;
}
