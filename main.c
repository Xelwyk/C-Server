#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <microhttpd.h>
#include <string.h>

#define PORT 8888

int read_received(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                 size_t *upload_data_size, void **con_cls);

int print_key(void *cls, enum MHD_ValueKind kind,
              const char *key, const char *value);

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_INTERNAL_POLLING_THREAD, PORT, NULL, NULL,
                              &read_received, NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        return 1;
    }

    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}

int read_received(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                 size_t *upload_data_size, void **con_cls) {
    
    const char *page = "<html><body>Hello, browser!</body></html>";
    struct MHD_Response *response;
    int ret;

    MHD_get_connection_values(connection, MHD_HEADER_KIND, &print_key, NULL);

    response = MHD_create_response_from_buffer(strlen(page), (void*)page, MHD_RESPMEM_PERSISTENT);

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int print_key(void *cls, enum MHD_ValueKind kind,
              const char *key, const char *value) {
    printf("%s: %s\n", key, value);
    return MHD_YES;
}

