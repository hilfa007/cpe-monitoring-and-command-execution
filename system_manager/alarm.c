#include "alarm.h"

int check_alarms(Metrics m, Thresholds t) {
    return (m.memory > t.memory || m.cpu > t.cpu || m.disk > t.disk);
}
