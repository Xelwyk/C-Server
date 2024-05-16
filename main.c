#include <stdio.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <microhttpd.h>
#include <string.h>

#define PORT 8888

struct connection_info_struct {
    int connectiontype;
    char *answerstring;
    struct MHD_PostProcessor *postprocessor;
};

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

static int iterate_post(void *coninfo_cls, enum MHD_ValueKind kind, const char *key),
                        const char *filename, const char *content_type,
                        const char *transfer_encoding, const char *data,
                        uint64_t off, size_t size) {
    struct connection_info_struct *con_info = coninfo_cls;
}
