#include <stdio.h>
#include <time.h>

#include "logger.h"

static FILE *log_file = NULL;

void logger_init(void)
{
    log_file =
        fopen(
            "gateway_log.csv",
            "w"
        );

    if(log_file)
    {
        fprintf(
            log_file,
            "Timestamp,Level,Message\n"
        );
    }
}

void logger_log(
    const char *level,
    const char *message
)
{
    if(!log_file)
    {
        return;
    }

    time_t now =
        time(NULL);

    fprintf(
        log_file,
        "%lld,%s,%s\n",
        (long long)now,
        level,
        message
    );

    fflush(
        log_file
    );

    printf(
        "[LOG] %s : %s\n",
        level,
        message
    );
}

void logger_close(void)
{
    if(log_file)
    {
        fclose(
            log_file
        );

        log_file = NULL;
    }
}