
#ifndef __NUCLEUS_H__
#define __NUCLEUS_H__


#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

//Типы
typedef unsigned long           UNSIGNED;
typedef long                    SIGNED;
typedef unsigned char           DATA_ELEMENT;
typedef DATA_ELEMENT            OPTION;
typedef int                     STATUS;
typedef unsigned char           UNSIGNED_CHAR;
typedef char                    CHAR;
typedef int                     INT;
typedef unsigned long *         UNSIGNED_PTR;
typedef unsigned char *         BYTE_PTR;
typedef DATA_ELEMENT            BOOLEAN;
typedef unsigned int            UNSIGNED_INT;

#define VOID void


/* Define constants that are target dependent and/or are used for internal
   purposes.  */

#define         NU_MIN_STACK_SIZE               240
#define         NU_MAX_NAME                     8
#define         NU_MAX_VECTORS                  64
#define         NU_MAX_LISRS                    8



/* Define task suspension constants.  */

#define         NU_DRIVER_SUSPEND               10
#define         NU_EVENT_SUSPEND                7
#define         NU_FINISHED                     11
#define         NU_MAILBOX_SUSPEND              3
#define         NU_MEMORY_SUSPEND               9
#define         NU_PARTITION_SUSPEND            8
#define         NU_PIPE_SUSPEND                 5
#define         NU_PURE_SUSPEND                 1
#define         NU_QUEUE_SUSPEND                4
#define         NU_READY                        0
#define         NU_SEMAPHORE_SUSPEND            6
#define         NU_SLEEP_SUSPEND                2
#define         NU_TERMINATED                   12

/* Define constants for use in service parameters.  */

#define         NU_AND                          2
#define         NU_AND_CONSUME                  3
#define         NU_DISABLE_TIMER                4
#define         NU_ENABLE_TIMER                 5
#define         NU_FALSE                        0
#define         NU_FIFO                         6
#define         NU_FIXED_SIZE                   7
#define         NU_NO_PREEMPT                   8
#define         NU_NO_START                     9
#define         NU_NO_SUSPEND                   0
#define         NU_NULL                         0
#define         NU_OR                           0
#define         NU_OR_CONSUME                   1
#define         NU_PREEMPT                      10
#define         NU_PRIORITY                     11
#define         NU_START                        12
#define         NU_SUSPEND                      0xFFFFFFFFUL
#define         NU_TRUE                         1
#define         NU_VARIABLE_SIZE                13

/* Define service completion status constants.  */

#define         NU_SUCCESS                      0
#define         NU_END_OF_LOG                   -1
#define         NU_GROUP_DELETED                -2
#define         NU_INVALID_DELETE               -3
#define         NU_INVALID_DRIVER               -4
#define         NU_INVALID_ENABLE               -5
#define         NU_INVALID_ENTRY                -6
#define         NU_INVALID_FUNCTION             -7
#define         NU_INVALID_GROUP                -8
#define         NU_INVALID_HISR                 -9
#define         NU_INVALID_MAILBOX              -10
#define         NU_INVALID_MEMORY               -11
#define         NU_INVALID_MESSAGE              -12
#define         NU_INVALID_OPERATION            -13
#define         NU_INVALID_PIPE                 -14
#define         NU_INVALID_POINTER              -15
#define         NU_INVALID_POOL                 -16
#define         NU_INVALID_PREEMPT              -17
#define         NU_INVALID_PRIORITY             -18
#define         NU_INVALID_QUEUE                -19
#define         NU_INVALID_RESUME               -20
#define         NU_INVALID_SEMAPHORE            -21
#define         NU_INVALID_SIZE                 -22
#define         NU_INVALID_START                -23
#define         NU_INVALID_SUSPEND              -24
#define         NU_INVALID_TASK                 -25
#define         NU_INVALID_TIMER                -26
#define         NU_INVALID_VECTOR               -27
#define         NU_MAILBOX_DELETED              -28
#define         NU_MAILBOX_EMPTY                -29
#define         NU_MAILBOX_FULL                 -30
#define         NU_MAILBOX_RESET                -31
#define         NU_NO_MEMORY                    -32
#define         NU_NO_MORE_LISRS                -33
#define         NU_NO_PARTITION                 -34
#define         NU_NOT_DISABLED                 -35
#define         NU_NOT_PRESENT                  -36
#define         NU_NOT_REGISTERED               -37
#define         NU_NOT_TERMINATED               -38
#define         NU_PIPE_DELETED                 -39
#define         NU_PIPE_EMPTY                   -40
#define         NU_PIPE_FULL                    -41
#define         NU_PIPE_RESET                   -42
#define         NU_POOL_DELETED                 -43
#define         NU_QUEUE_DELETED                -44
#define         NU_QUEUE_EMPTY                  -45
#define         NU_QUEUE_FULL                   -46
#define         NU_QUEUE_RESET                  -47
#define         NU_SEMAPHORE_DELETED            -48
#define         NU_SEMAPHORE_RESET              -49
#define         NU_TIMEOUT                      -50
#define         NU_UNAVAILABLE                  -51
#define         NU_INVALID_DESCRIPTION          -52
#define         NU_INVALID_REGION               -53
#define         NU_MEMORY_CORRUPT               -54
#define         NU_INVALID_DEBUG_ALLOCATION     -55
#define         NU_EMPTY_DEBUG_ALLOCATION_LIST  -56

/* Define system errors.  */

#define         NU_ERROR_CREATING_TIMER_HISR    1
#define         NU_ERROR_CREATING_TIMER_TASK    2
#define         NU_STACK_OVERFLOW               3
#define         NU_UNHANDLED_INTERRUPT          4


/* Define I/O driver constants.  */

#define         NU_IO_ERROR                     -1
#define         NU_INITIALIZE                   1
#define         NU_ASSIGN                       2
#define         NU_RELEASE                      3
#define         NU_INPUT                        4
#define         NU_OUTPUT                       5
#define         NU_STATUS                       6
#define         NU_TERMINATE                    7


/* Define history entry IDs.  */

#define         NU_USER_ID                      1
#define         NU_CREATE_TASK_ID               2
#define         NU_DELETE_TASK_ID               3
#define         NU_RESET_TASK_ID                4
#define         NU_TERMINATE_TASK_ID            5
#define         NU_RESUME_TASK_ID               6
#define         NU_SUSPEND_TASK_ID              7
#define         NU_RELINQUISH_ID                8
#define         NU_SLEEP_ID                     9
#define         NU_CHANGE_PRIORITY_ID           10
#define         NU_CHANGE_PREEMPTION_ID         11
#define         NU_CREATE_MAILBOX_ID            12
#define         NU_DELETE_MAILBOX_ID            13
#define         NU_RESET_MAILBOX_ID             14
#define         NU_SEND_TO_MAILBOX_ID           15
#define         NU_BROADCAST_TO_MAILBOX_ID      16
#define         NU_RECEIVE_FROM_MAILBOX_ID      17
#define         NU_CREATE_QUEUE_ID              18
#define         NU_DELETE_QUEUE_ID              19
#define         NU_RESET_QUEUE_ID               20
#define         NU_SEND_TO_FRONT_OF_QUEUE_ID    21
#define         NU_SEND_TO_QUEUE_ID             22
#define         NU_BROADCAST_TO_QUEUE_ID        23
#define         NU_RECEIVE_FROM_QUEUE_ID        24
#define         NU_CREATE_PIPE_ID               25
#define         NU_DELETE_PIPE_ID               26
#define         NU_RESET_PIPE_ID                27
#define         NU_SEND_TO_FRONT_OF_PIPE_ID     28
#define         NU_SEND_TO_PIPE_ID              29
#define         NU_BROADCAST_TO_PIPE_ID         30
#define         NU_RECEIVE_FROM_PIPE_ID         31
#define         NU_CREATE_SEMAPHORE_ID          32
#define         NU_DELETE_SEMAPHORE_ID          33
#define         NU_RESET_SEMAPHORE_ID           34
#define         NU_OBTAIN_SEMAPHORE_ID          35
#define         NU_RELEASE_SEMAPHORE_ID         36
#define         NU_CREATE_EVENT_GROUP_ID        37
#define         NU_DELETE_EVENT_GROUP_ID        38
#define         NU_SET_EVENTS_ID                39
#define         NU_RETRIEVE_EVENTS_ID           40
#define         NU_CREATE_PARTITION_POOL_ID     41
#define         NU_DELETE_PARTITION_POOL_ID     42
#define         NU_ALLOCATE_PARTITION_ID        43
#define         NU_DEALLOCATE_PARTITION_ID      44
#define         NU_CREATE_MEMORY_POOL_ID        45
#define         NU_DELETE_MEMORY_POOL_ID        46
#define         NU_ALLOCATE_MEMORY_ID           47
#define         NU_DEALLOCATE_MEMORY_ID         48
#define         NU_CONTROL_SIGNALS_ID           49
#define         NU_RECEIVE_SIGNALS_ID           50
#define         NU_REGISTER_SIGNAL_HANDLER_ID   51
#define         NU_SEND_SIGNALS_ID              52
#define         NU_REGISTER_LISR_ID             53
#define         NU_CREATE_HISR_ID               54
#define         NU_DELETE_HISR_ID               55
#define         NU_CREATE_TIMER_ID              56
#define         NU_DELETE_TIMER_ID              57
#define         NU_CONTROL_TIMER_ID             58
#define         NU_RESET_TIMER_ID               59
#define         NU_CREATE_DRIVER_ID             60
#define         NU_DELETE_DRIVER_ID             61
#define         NU_REQUEST_DRIVER_ID            62
#define         NU_RESUME_DRIVER_ID             63
#define         NU_SUSPEND_DRIVER_ID            64
#define         NU_CHANGE_TIME_SLICE_ID         65
#define         NU_ASSERT_ID                    66
#define         NU_ALLOCATE_ALIGNED_ID          67


typedef struct NU_TASK_STRUCT
{
    pthread_t thread;
    pthread_attr_t attr;
    pthread_mutex_t suspend_mtx;
    pthread_cond_t resume_cond;
    void (*task_entry)(unsigned long, void *);
    unsigned long argc;
    void *argv;
    char started;
    struct NU_TASK_STRUCT *task_ptr;
} NU_TASK;



STATUS NU_Create_Task(NU_TASK *task, CHAR *name,
                                    VOID (*task_entry)(UNSIGNED, VOID *), UNSIGNED argc,
                                    VOID *argv, VOID *stack_address, UNSIGNED stack_size,
                                    OPTION priority, UNSIGNED time_slice,
                                    OPTION preempt, OPTION auto_start);
STATUS NU_Delete_Task(NU_TASK *task);
STATUS NU_Reset_Task(NU_TASK *task, UNSIGNED argc, VOID *argv);
STATUS NU_Terminate_Task(NU_TASK *task);
STATUS NU_Resume_Task(NU_TASK *task);
STATUS NU_Suspend_Task(NU_TASK *task);
VOID NU_Relinquish(VOID);
VOID NU_Sleep(UNSIGNED ticks);
OPTION NU_Change_Priority(NU_TASK *task, OPTION new_priority);
OPTION NU_Change_Preemption(OPTION preempt);
UNSIGNED NU_Change_Time_Slice(NU_TASK *task, UNSIGNED time_slice);
UNSIGNED NU_Check_Stack(VOID);
NU_TASK  *NU_Current_Task_Pointer(VOID);
UNSIGNED NU_Established_Tasks(VOID);
STATUS NU_Task_Information(NU_TASK *task, CHAR *name,
                                          DATA_ELEMENT *status, UNSIGNED *scheduled_count,
                                          OPTION *priority, OPTION *preempt,
                                          UNSIGNED *time_slice, VOID **stack_base,
                                          UNSIGNED *stack_size, UNSIGNED *minimum_stack);

UNSIGNED NU_Task_Pointers(NU_TASK **pointer_list, UNSIGNED maximum_pointers);



#ifdef __cplusplus
}
#endif
  
#endif
