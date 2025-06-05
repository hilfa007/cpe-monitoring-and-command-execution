#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    float memory;
    float cpu;
    float disk;
} Thresholds;

Thresholds load_thresholds(const char *filename);

#endif
