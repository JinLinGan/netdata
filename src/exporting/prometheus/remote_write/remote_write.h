// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef NETDATA_EXPORTING_PROMETHEUS_REMOTE_WRITE_H
#define NETDATA_EXPORTING_PROMETHEUS_REMOTE_WRITE_H

#include "exporting/exporting_engine.h"
#include "exporting/prometheus/prometheus.h"
#include "remote_write_request.h"


#define PROMETHEUS_ELEMENT_MAX  256
#define PROMETHEUS_LABELS_MAX   1024

struct prometheus_remote_write_specific_data {
    void *write_request;

    bool initialized;
    int  labels_count;
    // string arrays for Prometheus tasg
    char keys [PROMETHEUS_LABELS_MAX] [PROMETHEUS_ELEMENT_MAX+1];
    char values [PROMETHEUS_LABELS_MAX] [PROMETHEUS_ELEMENT_MAX+1];
};

void inited(struct prometheus_remote_write_specific_data *specific_data);

void add_default_labels_to_request(char *key,char *value, struct prometheus_remote_write_specific_data *specific_data);
void add_common_labels(struct prometheus_remote_write_specific_data *specific_data);
struct prometheus_remote_write_variables_callback_options {
    RRDHOST *host;
    time_t now;
    struct instance *instance;
};

int init_prometheus_remote_write_instance(struct instance *instance);
void clean_prometheus_remote_write(struct instance *instance);

int format_host_prometheus_remote_write(struct instance *instance, RRDHOST *host);
int format_chart_prometheus_remote_write(struct instance *instance, RRDSET *st);
int format_dimension_prometheus_remote_write(struct instance *instance, RRDDIM *rd);
int format_variables_prometheus_remote_write(struct instance *instance, RRDHOST *host);
int format_batch_prometheus_remote_write(struct instance *instance);

void prometheus_remote_write_prepare_header(struct instance *instance);
int process_prometheus_remote_write_response(BUFFER *buffer, struct instance *instance);

#endif //NETDATA_EXPORTING_PROMETHEUS_REMOTE_WRITE_H
