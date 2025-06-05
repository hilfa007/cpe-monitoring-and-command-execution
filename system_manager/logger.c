#include "logger.h"
#include <stdio.h>
#include <time.h>

void log_message(const char *message) {
    FILE *fp = fopen("logs/system_manager.log", "a");
    if (!fp) return;

    time_t now = time(NULL);
    fprintf(fp, "[%s] %s\n", ctime(&now), message);
    fclose(fp);
}
