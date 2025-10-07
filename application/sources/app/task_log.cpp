#include <stdbool.h>

#include "fsm.h"
#include "port.h"
#include "message.h"

#include "xprintf.h"

#include "sys_dbg.h"
#include "sys_ctrl.h"
#include "sys_irq.h"
#include "sys_io.h"

#include "app.h"
#include "app_dbg.h"
#include "task_log.h"
#include "task_list.h"

ring_buffer_t ring_buffer_log;
logdbg_t buffer_log[BUFFER_LOG_SIZE];

void put_log(AC_LogCode_t code)
{

    // task_post_pure_msg(AC_TASK_LOG_ID, AC_LOG_PUT);
    task_post_common_msg(AC_TASK_LOG_ID, AC_LOG_PUT, (uint8_t *)&code, sizeof(code));
}

void task_log(ak_msg_t *msg)
{
    switch (msg->sig)
    {

    case AC_LOG_PRINT:
    {
        uint16_t temp_fillsize = ring_buffer_log.fill_size;
        uint16_t temp_index = ring_buffer_log.head_index;

        if (temp_fillsize == 0)
        {
            APP_DBG_SIG("AC_LOG_NO_DATA\n");
            break;
        }

        while (temp_fillsize > 0)
        {
            logdbg_t log;
            memcpy(&log,
                   ring_buffer_log.buffer + temp_index * ring_buffer_log.element_size,
                   sizeof(logdbg_t));

            switch (log.log_code)
            {
            case AC_LOG_DW_INIT_OK:
                APP_DBG_SIG("[LOG] AC_LOG_DW_INIT_OK\n");
                break;
            case AC_LOG_DW_INIT_FAIL:
                APP_DBG_SIG("[LOG] AC_LOG_DW_INIT_FAIL\n");
                break;
            case AC_LOG_DW_UPDATE_OK:
                APP_DBG_SIG("[LOG] AC_LOG_DW_UPDATE_OK\n");
                break;
            case AC_LOG_DW_UPDATE_FAIL:
                APP_DBG_SIG("[LOG] AC_LOG_DW_UPDATE_FAIL\n");
                break;
            default:
                break;
            }

            temp_index = (temp_index + 1) % ring_buffer_log.buffer_size;
            temp_fillsize--;
        }
    }
    break;

    case AC_LOG_PUT:
    {
        logdbg_t temp;
        temp.log_code = *(AC_LogCode_t *)get_data_common_msg(msg);

        uint8_t ret = ring_buffer_put_log(&ring_buffer_log, &temp);
        if (ret == RET_RING_BUFFER_NG)
        {
            uint16_t temp_fillsize = ring_buffer_log.fill_size;
            if (temp_fillsize == BUFFER_LOG_SIZE-1)
            {
                APP_DBG_SIG("AC_LOG_QUEUE_FULL\n");
                return;

            }
            APP_DBG_SIG("AC_LOG_PUT_NG\n");
        }
        else
            APP_DBG_SIG("AC_LOG_PUT_OK\n");
    }

    break;

    default:
        break;
    }
}