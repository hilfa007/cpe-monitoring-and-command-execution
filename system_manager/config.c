#include "config.h"
#include <stdio.h>
#include <string.h>

Thresholds load_thresholds(const char *filename) {
    Thresholds t = {80.0, 75.0, 90.0}; // defaults
    FILE *fp = fopen(filename, "r");
    if (!fp) return t;

    char key[32];
    float value;
    while (fscanf(fp, "%[^=]=%f\n", key, &value) != EOF) {
        if (strcmp(key, "memory") == 0) t.memory = value;
        else if (strcmp(key, "cpu") == 0) t.cpu = value;
        else if (strcmp(key, "disk") == 0) t.disk = value;
    }
    fclose(fp);
    return t;
}
