#include "metrics.h"
#include "config.h"
#include "alarm.h"
#include "socket_client.h"
#include "logger.h"
#include <unistd.h>

int main() {
    Thresholds thresholds = load_thresholds("config/thresholds.conf");

    while (1) {
        Metrics m = collect_metrics();

        if (check_alarms(m, thresholds)) {
            log_message("ALARM: Threshold breached!");
            // Optional: send HTTP POST to cloud here
        }

        if (!send_metrics_to_agent(m)) {
            log_message("ERROR: Failed to send metrics or no ACK received.");
        } else {
            log_message("INFO: Metrics sent and ACK received.");
        }

        sleep(10);
    }

    return 0;
}
