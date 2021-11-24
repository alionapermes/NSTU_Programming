#ifndef ERRORLOG_H
#define ERRORLOG_H

#define LOG_ERROR 1
#defene LOG_ACTION 2
#define LOG_DEBUG 3


void
write_log(const char* path, int type);


#endif

