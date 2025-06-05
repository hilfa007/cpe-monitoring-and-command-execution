#include "metrics.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <dirent.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <time.h>

float get_memory_usage() {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) return -1;

    char line[256];
    long total = 0, free = 0;
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "MemTotal: %ld kB", &total) == 1) continue;
        if (sscanf(line, "MemAvailable: %ld kB", &free) == 1) break;
    }
    fclose(fp);
    return 100.0 * (1 - ((float)free / total));
}

float get_cpu_load() {
    FILE *fp = fopen("/proc/loadavg", "r");
    float load = 0.0;
    if (fp) {
        fscanf(fp, "%f", &load);
        fclose(fp);
    }
    return load * 100; // scale for percentage
}

float get_uptime() {
    FILE *fp = fopen("/proc/uptime", "r");
    float uptime = 0.0;
    if (fp) {
        fscanf(fp, "%f", &uptime);
        fclose(fp);
    }
    return uptime;
}

float get_disk_usage() {
    struct statvfs stat;
    if (statvfs("/", &stat) != 0) return -1;
    return 100.0 * (1.0 - ((float)stat.f_bavail / stat.f_blocks));
}

int get_network_interfaces() {
    struct ifaddrs *ifaddr, *ifa;
    int count = 0;
    if (getifaddrs(&ifaddr) == -1) return -1;
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
        if (ifa->ifa_addr) count++;
    freeifaddrs(ifaddr);
    return count;
}

int get_process_count() {
    DIR *dir = opendir("/proc");
    struct dirent *entry;
    int count = 0;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR && atoi(entry->d_name) > 0)
            count++;
    }
    closedir(dir);
    return count;
}

Metrics collect_metrics() {
    Metrics m;
    m.memory = get_memory_usage();
    m.cpu = get_cpu_load();
    m.uptime = get_uptime();
    m.disk = get_disk_usage();
    m.net_interfaces = get_network_interfaces();
    m.processes = get_process_count();
    return m;
}
