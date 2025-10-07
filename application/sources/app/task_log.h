#ifndef __TASK_LOG_H__
#define __TASK_LOG_H__

#include "ring_buffer.h"
// #define BUFFER_LOG_SIZE					(256)
#define BUFFER_LOG_SIZE					(4)
typedef enum {
    AC_LOG_NONE,         // 0: không log
    AC_LOG_DW_INIT_OK,        
    AC_LOG_DW_INIT_FAIL,        
    AC_LOG_DW_UPDATE_OK,         
    AC_LOG_DW_UPDATE_FAIL,         
} AC_LogCode_t;

typedef struct 
{
    AC_LogCode_t log_code;
    uint32_t timestamp; //2 days
}logdbg_t;

extern logdbg_t buffer_log[];
extern ring_buffer_t ring_buffer_log;
extern void put_log(AC_LogCode_t code);

// extern  logdbg;



#endif //__TASK_LOG_H__
