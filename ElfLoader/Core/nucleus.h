#ifndef __NU_SWILIB_H__
#define __NU_SWILIB_H__

/* Nucleus PLUS RTOS API LIB,  17.01.2012 */

#define NU_SWILIB_BEGIN_NUMBER  0x300

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

//Cтруктуры

#define         NU_TASK_SIZE                    42 + 4
#define         NU_HISR_SIZE                    22 + 4
#define         NU_MAILBOX_SIZE                 13 + 4
#define         NU_QUEUE_SIZE                   18 + 50
#define         NU_PIPE_SIZE                    18 + 4
#define         NU_SEMAPHORE_SIZE               10 + 4
#define         NU_EVENT_GROUP_SIZE             9  + 4
#define         NU_PARTITION_POOL_SIZE          15 + 4
#define         NU_MEMORY_POOL_SIZE             17 + 4
#define         NU_TIMER_SIZE                   17 + 4
#define         NU_PROTECT_SIZE                 2  + 4
#define         NU_DRIVER_SIZE                  3  + 4

typedef struct NU_TASK_STRUCT
{
    UNSIGNED      words[NU_TASK_SIZE];
} NU_TASK;

typedef struct NU_MAILBOX_STRUCT
{
    UNSIGNED      words[NU_MAILBOX_SIZE];
} NU_MAILBOX;

typedef struct NU_QUEUE_STRUCT
{
    UNSIGNED      words[NU_QUEUE_SIZE];
} NU_QUEUE;

typedef struct NU_PIPE_STRUCT
{
    UNSIGNED      words[NU_PIPE_SIZE];
} NU_PIPE;

typedef struct NU_SEMAPHORE_STRUCT
{
    UNSIGNED      words[NU_SEMAPHORE_SIZE];
} NU_SEMAPHORE;

typedef struct NU_EVENT_GROUP_STRUCT
{
    UNSIGNED      words[NU_EVENT_GROUP_SIZE];
} NU_EVENT_GROUP;

typedef struct NU_PARTITION_POOL_STRUCT
{
    UNSIGNED       words[NU_PARTITION_POOL_SIZE];
} NU_PARTITION_POOL;

typedef struct NU_MEMORY_POOL_STRUCT
{
    UNSIGNED      words[NU_MEMORY_POOL_SIZE];
} NU_MEMORY_POOL;

typedef struct NU_HISR_STRUCT
{
    UNSIGNED      words[NU_HISR_SIZE];
} NU_HISR;

typedef struct NU_PROTECT_STRUCT
{
    UNSIGNED      words[NU_PROTECT_SIZE];
} NU_PROTECT;

typedef struct NU_TIMER_STRUCT
{
    UNSIGNED       words[NU_TIMER_SIZE];
} NU_TIMER;

/* Define I/O driver request structures.  */

struct NU_INITIALIZE_STRUCT
{
    VOID       *nu_io_address;              /* Base IO address          */
    UNSIGNED    nu_logical_units;           /* Number of logical units  */
    VOID       *nu_memory;                  /* Generic memory pointer   */
    INT         nu_vector;                  /* Interrupt vector number  */
};

struct NU_ASSIGN_STRUCT
{
    UNSIGNED    nu_logical_unit;            /* Logical unit number      */
    INT         nu_assign_info;             /* Additional assign info   */
};

struct NU_RELEASE_STRUCT
{
    UNSIGNED    nu_logical_unit;            /* Logical unit number      */
    INT         nu_release_info;            /* Additional release info  */
};

struct NU_INPUT_STRUCT
{
    UNSIGNED    nu_logical_unit;            /* Logical unit number      */
    UNSIGNED    nu_offset;                  /* Offset of input          */
    UNSIGNED    nu_request_size;            /* Requested input size     */
    UNSIGNED    nu_actual_size;             /* Actual input size        */
    VOID       *nu_buffer_ptr;              /* Input buffer pointer     */
};

struct NU_OUTPUT_STRUCT
{
    UNSIGNED    nu_logical_unit;            /* Logical unit number      */
    UNSIGNED    nu_offset;                  /* Offset of output         */
    UNSIGNED    nu_request_size;            /* Requested output size    */
    UNSIGNED    nu_actual_size;             /* Actual output size       */
    VOID       *nu_buffer_ptr;              /* Output buffer pointer    */
};

struct NU_STATUS_STRUCT
{
    UNSIGNED    nu_logical_unit;            /* Logical unit number      */
    VOID       *nu_extra_status;            /* Additional status ptr    */
};

struct NU_TERMINATE_STRUCT
{
    UNSIGNED    nu_logical_unit;            /* Logical unit number      */
};


typedef  union NU_REQUEST_INFO_UNION
{
    struct NU_INITIALIZE_STRUCT     nu_initialize;
    struct NU_ASSIGN_STRUCT         nu_assign;
    struct NU_RELEASE_STRUCT        nu_release;
    struct NU_INPUT_STRUCT          nu_input;
    struct NU_OUTPUT_STRUCT         nu_output;
    struct NU_STATUS_STRUCT         nu_status;
    struct NU_TERMINATE_STRUCT      nu_terminate;
} nu_request_info_union;

typedef struct NU_DRIVER_REQUEST_STRUCT
{
    INT                   nu_function;                /* I/O request function     */
    UNSIGNED              nu_timeout;                 /* Timeout on request       */
    STATUS                nu_status;                  /* Status of request        */
    UNSIGNED              nu_supplemental;            /* Supplemental information */
    VOID                 *nu_supplemental_ptr;        /* Supplemental info pointer*/
    nu_request_info_union nu_request_info;
    
} NU_DRIVER_REQUEST;

typedef struct NU_DRIVER_STRUCT
{
    UNSIGNED       words[NU_DRIVER_SIZE];      /* CS_NODE_STRUCT */
    CHAR           nu_driver_name[NU_MAX_NAME];
    VOID          *nu_info_ptr;
    UNSIGNED       nu_driver_id;
    VOID           (*nu_driver_entry)(struct NU_DRIVER_STRUCT *,
                                                NU_DRIVER_REQUEST *);
} NU_DRIVER;


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

#pragma diag_suppress=Ta035

/* Define SVC / USR functions */

#define NU_SUPERVISOR_MODE() NU_SUPERVISOR_MODE_P( *( ( VOID ** ) ( NU_SUPERV_USER_VARIABLES() ) ) )
#define NU_USER_MODE()       NU_USER_MODE_P( *( ( VOID ** ) ( NU_SUPERV_USER_VARIABLES() ) ) )


/* Работа с задачами / Define task control functions */

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x00
__swi __arm STATUS   NU_Create_Task(NU_TASK *task, CHAR *name, 
                                    VOID (*task_entry)(UNSIGNED, VOID *), UNSIGNED argc,
                                    VOID *argv, VOID *stack_address, UNSIGNED stack_size,
                                    OPTION priority, UNSIGNED time_slice, 
                                    OPTION preempt, OPTION auto_start);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x01
__swi __arm STATUS    NU_Delete_Task(NU_TASK *task);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x02
__swi __arm STATUS    NU_Reset_Task(NU_TASK *task, UNSIGNED argc, VOID *argv);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x03
__swi __arm STATUS    NU_Terminate_Task(NU_TASK *task);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x04
__swi __arm STATUS    NU_Resume_Task(NU_TASK *task);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x05
__swi __arm STATUS    NU_Suspend_Task(NU_TASK *task);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x06
__swi __arm VOID      NU_Relinquish(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x07
__swi __arm VOID      NU_Sleep(UNSIGNED ticks);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x08
__swi __arm OPTION    NU_Change_Priority(NU_TASK *task, OPTION new_priority);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x09
__swi __arm OPTION    NU_Change_Preemption(OPTION preempt);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x0A
__swi __arm UNSIGNED  NU_Change_Time_Slice(NU_TASK *task, UNSIGNED time_slice);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x0B
__swi __arm UNSIGNED  NU_Check_Stack(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x0C
__swi __arm NU_TASK  *NU_Current_Task_Pointer(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x0D
__swi __arm UNSIGNED  NU_Established_Tasks(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x0E
__swi __arm STATUS    NU_Task_Information(NU_TASK *task, CHAR *name, 
                                          DATA_ELEMENT *status, UNSIGNED *scheduled_count,
                                          OPTION *priority, OPTION *preempt,
                                          UNSIGNED *time_slice, VOID **stack_base,
                                          UNSIGNED *stack_size, UNSIGNED *minimum_stack);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x0F
__swi __arm UNSIGNED  NU_Task_Pointers(NU_TASK **pointer_list, 
                                       UNSIGNED maximum_pointers);






/* Работа с почтовыми ящиками / Define Mailbox management functions */


#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x10
__swi __arm STATUS    NU_Create_Mailbox(NU_MAILBOX *mailbox, CHAR *name, OPTION suspend_type);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x11
__swi __arm STATUS    NU_Delete_Mailbox(NU_MAILBOX *mailbox);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x12
__swi __arm STATUS    NU_Reset_Mailbox(NU_MAILBOX *mailbox);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x13
__swi __arm STATUS    NU_Send_To_Mailbox(NU_MAILBOX *mailbox, VOID *message, 
                                         UNSIGNED suspend);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x14
__swi __arm STATUS    NU_Broadcast_To_Mailbox(NU_MAILBOX *mailbox, VOID *message,
                                              UNSIGNED suspend);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x15
__swi __arm STATUS    NU_Receive_From_Mailbox(NU_MAILBOX *mailbox, VOID *message,
                                              UNSIGNED suspend);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x16
__swi __arm UNSIGNED  NU_Established_Mailboxes(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x17
__swi __arm STATUS    NU_Mailbox_Information(NU_MAILBOX *mailbox, CHAR *name, 
                                             OPTION *suspend_type, OPTION *message_present,
                                             UNSIGNED *tasks_waiting, NU_TASK **first_task);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x18
__swi __arm UNSIGNED  NU_Mailbox_Pointers(NU_MAILBOX **pointer_list,  UNSIGNED maximum_pointers);



/* Работа с очередями / Define Queue management functions */

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x19
__swi __arm STATUS    NU_Create_Queue(NU_QUEUE *queue, CHAR *name, 
                                      VOID *start_address, UNSIGNED queue_size, 
                                      OPTION message_type, UNSIGNED message_size,
                                      OPTION suspend_type);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x1A
__swi __arm STATUS    NU_Delete_Queue(NU_QUEUE *queue);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x1B
__swi __arm STATUS    NU_Reset_Queue(NU_QUEUE *queue);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x1C
__swi __arm STATUS    NU_Send_To_Front_Of_Queue(NU_QUEUE *queue, VOID *message, 
                                                UNSIGNED size, UNSIGNED suspend);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x1D
__swi __arm STATUS    NU_Send_To_Queue(NU_QUEUE *queue, VOID *message, 
                                       UNSIGNED size, UNSIGNED suspend);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x1E
__swi __arm STATUS    NU_Broadcast_To_Queue(NU_QUEUE *queue, VOID *message, 
                                            UNSIGNED size, UNSIGNED suspend);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x1F
__swi __arm STATUS    NU_Receive_From_Queue(NU_QUEUE *queue, VOID *message,
                                            UNSIGNED size, UNSIGNED *actual_size, UNSIGNED suspend);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x20
__swi __arm UNSIGNED  NU_Established_Queues(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x21
__swi __arm STATUS    NU_Queue_Information(NU_QUEUE *queue, CHAR *name, 
                                           VOID **start_address, UNSIGNED *queue_size, 
                                           UNSIGNED *available, UNSIGNED *messages, 
                                           OPTION *message_type, UNSIGNED *message_size,
                                           OPTION *suspend_type, UNSIGNED *tasks_waiting,
                                           NU_TASK **first_task);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x22
__swi __arm UNSIGNED   NU_Queue_Pointers(NU_QUEUE **pointer_list, 
                                         UNSIGNED maximum_pointers);


/* Работа с каналами / Define Pipe management functions */


#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x23
__swi __arm STATUS    NU_Create_Pipe(NU_PIPE *pipe, CHAR *name, 
                                     VOID *start_address, UNSIGNED pipe_size, 
                                     OPTION message_type, UNSIGNED message_size,
                                     OPTION suspend_type);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x24
__swi __arm STATUS    NU_Delete_Pipe(NU_PIPE *pipe);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x25
__swi __arm STATUS    NU_Reset_Pipe(NU_PIPE *pipe);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x26
__swi __arm STATUS    NU_Send_To_Front_Of_Pipe(NU_PIPE *pipe, VOID *message, 
                                               UNSIGNED size, UNSIGNED suspend);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x27
__swi __arm STATUS    NU_Send_To_Pipe(NU_PIPE *pipe, VOID *message, 
                                      UNSIGNED size, UNSIGNED suspend);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x28
__swi __arm STATUS    NU_Broadcast_To_Pipe(NU_PIPE *pipe, VOID *message, 
                                           UNSIGNED size, UNSIGNED suspend);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x29
__swi __arm STATUS    NU_Receive_From_Pipe(NU_PIPE *pipe, VOID *message,
                                           UNSIGNED size, UNSIGNED *actual_size, UNSIGNED suspend);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x2A
__swi __arm UNSIGNED  NU_Established_Pipes(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x2B
__swi __arm STATUS    NU_Pipe_Information(NU_PIPE *pipe, CHAR *name, 
                                          VOID **start_address, UNSIGNED *pipe_size, 
                                          UNSIGNED *available, UNSIGNED *messages, 
                                          OPTION *message_type, UNSIGNED *message_size,
                                          OPTION *suspend_type, UNSIGNED *tasks_waiting,
                                          NU_TASK **first_task);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x2C
__swi __arm UNSIGNED  NU_Pipe_Pointers(NU_PIPE **pointer_list, 
                                                UNSIGNED maximum_pointers);


/* Работа с cемафорами / Define Semaphore management functions */


#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x2D
__swi __arm STATUS    NU_Create_Semaphore(NU_SEMAPHORE *semaphore, CHAR *name, 
                                          UNSIGNED initial_count, OPTION suspend_type);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x2E
__swi __arm STATUS    NU_Delete_Semaphore(NU_SEMAPHORE *semaphore);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x2F
__swi __arm STATUS    NU_Reset_Semaphore(NU_SEMAPHORE *semaphore, UNSIGNED initial_count);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x30
__swi __arm STATUS    NU_Obtain_Semaphore(NU_SEMAPHORE *semaphore, UNSIGNED suspend);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x31
__swi __arm STATUS    NU_Release_Semaphore(NU_SEMAPHORE *semaphore);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x32
__swi __arm UNSIGNED  NU_Established_Semaphores(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x33
__swi __arm STATUS    NU_Semaphore_Information(NU_SEMAPHORE *semaphore, CHAR *name, 
                                               UNSIGNED *current_count, OPTION *suspend_type, 
                                               UNSIGNED *tasks_waiting, NU_TASK **first_task);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x34
__swi __arm UNSIGNED  NU_Semaphore_Pointers(NU_SEMAPHORE **pointer_list, 
                                                UNSIGNED maximum_pointers);


/* Работа с группами событий / Define Event Group management functions */


#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x35
__swi __arm STATUS    NU_Create_Event_Group(NU_EVENT_GROUP *group, CHAR *name);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x36
__swi __arm STATUS    NU_Delete_Event_Group(NU_EVENT_GROUP *group);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x37
__swi __arm STATUS    NU_Set_Events(NU_EVENT_GROUP *group, UNSIGNED events, OPTION operation);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x38
__swi __arm STATUS    NU_Retrieve_Events(NU_EVENT_GROUP *group, 
                                         UNSIGNED requested_flags, OPTION operation, 
                                         UNSIGNED *retrieved_flags, UNSIGNED suspend);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x39
__swi __arm UNSIGNED  NU_Established_Event_Groups(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x3A
__swi __arm STATUS    NU_Event_Group_Information(NU_EVENT_GROUP *group, CHAR *name, 
                                                 UNSIGNED *event_flags, UNSIGNED *tasks_waiting, 
                                                 NU_TASK **first_task);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x3B
__swi __arm UNSIGNED  NU_Event_Group_Pointers(NU_EVENT_GROUP **pointer_list, 
                                              UNSIGNED maximum_pointers);


/* Работа с сигналами / Define Signal processing functions */


#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x3C
__swi __arm UNSIGNED  NU_Control_Signals(UNSIGNED signal_enable_mask);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x3D
__swi __arm UNSIGNED  NU_Receive_Signals(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x3E
__swi __arm STATUS   NU_Register_Signal_Handler(VOID (*signal_handler)(UNSIGNED));

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x3F
__swi __arm STATUS   NU_Send_Signals(NU_TASK *task, UNSIGNED signals);


/* Работа с областями фрагментного захвата памяти / Define Partition memory management functions */


#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x40
__swi __arm STATUS    NU_Create_Partition_Pool(NU_PARTITION_POOL *pool, CHAR *name, 
                                               VOID *start_address, UNSIGNED pool_size,
                                               UNSIGNED partition_size, OPTION suspend_type);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x41
__swi __arm STATUS    NU_Delete_Partition_Pool(NU_PARTITION_POOL *pool);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x42
__swi __arm STATUS    NU_Allocate_Partition(NU_PARTITION_POOL *pool, 
                                            VOID **return_pointer, UNSIGNED suspend);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x43
__swi __arm STATUS    NU_Deallocate_Partition(VOID *partition);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x44
__swi __arm UNSIGNED  NU_Established_Partition_Pools(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x45
__swi __arm STATUS    NU_Partition_Pool_Information(NU_PARTITION_POOL *pool, 
                                                    CHAR *name, 
                                                    VOID **start_address, UNSIGNED *pool_size,
                                                    UNSIGNED *partition_size, UNSIGNED *available,
                                                    UNSIGNED *allocated, OPTION *suspend_type, 
                                                    UNSIGNED *tasks_waiting, NU_TASK **first_task);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x46
__swi __arm UNSIGNED  NU_Partition_Pool_Pointers(NU_PARTITION_POOL **pointer_list, 
                                                 UNSIGNED maximum_pointers);


/* Работа с областями динамического захвата памяти /  Define Dynamic memory management functions */


#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x47
__swi __arm STATUS    NU_Create_Memory_Pool(NU_MEMORY_POOL *pool, CHAR *name, 
                                            VOID *start_address, UNSIGNED pool_size,
                                            UNSIGNED min_allocation, OPTION suspend_type);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x48
__swi __arm STATUS    NU_Delete_Memory_Pool(NU_MEMORY_POOL *pool);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x49
__swi __arm STATUS    NU_Allocate_Memory(NU_MEMORY_POOL *pool, VOID **return_pointer,
                                         UNSIGNED size, UNSIGNED suspend);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x4A
__swi __arm STATUS    NU_Deallocate_Memory(VOID *memory);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x4B
__swi __arm UNSIGNED  NU_Established_Memory_Pools(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x4C
__swi __arm STATUS    NU_Memory_Pool_Information(NU_MEMORY_POOL *pool, CHAR *name, 
                                                 VOID **start_address, UNSIGNED *pool_size,
                                                 UNSIGNED *min_allocation, UNSIGNED *available,
                                                 OPTION *suspend_type, UNSIGNED *tasks_waiting, 
                                                 NU_TASK **first_task);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x4D
__swi __arm UNSIGNED  NU_Memory_Pool_Pointers(NU_MEMORY_POOL **pointer_list, 
                                              UNSIGNED maximum_pointers);


/* Работа с прерываниями / Define Interrupt management functions */


#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x4E
__swi __arm INT       NU_Control_Interrupts(INT new_level);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x4F
__swi __arm INT       NU_Local_Control_Interrupts(INT new_level);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x50
__swi __arm VOID      NU_Restore_Interrupts(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x51
__swi __arm VOID     *NU_Setup_Vector(INT vector, VOID *new_vector);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x52
__swi __arm STATUS    NU_Register_LISR(INT vector, VOID (*new_lisr)(INT),  VOID (**old_lisr)(INT));

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x53
__swi __arm STATUS    NU_Activate_HISR(NU_HISR *hisr);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x54
__swi __arm STATUS    NU_Create_HISR(NU_HISR *hisr, CHAR *name, VOID (*hisr_entry)(VOID), OPTION priority,
                                     VOID *stack_address, UNSIGNED stack_size);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x55
__swi __arm STATUS    NU_Delete_HISR(NU_HISR *hisr);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x56
__swi __arm NU_HISR  *NU_Current_HISR_Pointer(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x57
__swi __arm UNSIGNED  NU_Established_HISRs(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x58
__swi __arm STATUS    NU_HISR_Information(NU_HISR *hisr, CHAR *name,
                                          UNSIGNED *scheduled_count, DATA_ELEMENT *priority,
                                          VOID **stack_base, UNSIGNED *stack_size,
                                          UNSIGNED *minimum_stack);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x59
__swi __arm UNSIGNED  NU_HISR_Pointers(NU_HISR **pointer_list,  UNSIGNED maximum_pointers);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x5A
__swi __arm VOID      NU_Protect(NU_PROTECT *protect_struct);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x5B
__swi __arm VOID      NU_Unprotect(VOID);


/* Работа с таймерами  / Timer management functions */


#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x5C
__swi __arm STATUS     NU_Create_Timer(NU_TIMER *timer, CHAR *name, 
                                  VOID (*expiration_routine)(UNSIGNED), UNSIGNED id,
                                  UNSIGNED initial_time, UNSIGNED reschedule_time,
                                  OPTION enable);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x5D
__swi __arm STATUS     NU_Delete_Timer(NU_TIMER *timer);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x5E
__swi __arm STATUS     NU_Reset_Timer(NU_TIMER *timer, 
                                 VOID (*expiration_routine)(UNSIGNED), 
                                 UNSIGNED initial_time, UNSIGNED reschedule_timer,
                                 OPTION enable);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x5F
__swi __arm STATUS     NU_Control_Timer(NU_TIMER *timer, OPTION enable);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x60
__swi __arm UNSIGNED   NU_Established_Timers(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x61
__swi __arm STATUS     NU_Timer_Information(NU_TIMER *timer, CHAR *name, 
                                       OPTION *enable, UNSIGNED *expirations, UNSIGNED *id,
                                       UNSIGNED *initial_time, UNSIGNED *reschedule_time);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x62
__swi __arm UNSIGNED   NU_Timer_Pointers(NU_TIMER **pointer_list, 
                                    UNSIGNED maximum_pointers);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x63
__swi __arm VOID       NU_Set_Clock(UNSIGNED new_value);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x64
__swi __arm UNSIGNED   NU_Retrieve_Clock(VOID);


/* Различные ф-ии для разработчиков / Development support functions */


#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x65
__swi __arm CHAR      *NU_Release_Information(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x66
__swi __arm CHAR      *NU_License_Information(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x67
__swi __arm VOID       NU_Disable_History_Saving(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x68
__swi __arm VOID       NU_Enable_History_Saving(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x69
__swi __arm VOID       NU_Make_History_Entry(UNSIGNED param1, UNSIGNED param2, UNSIGNED param3);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x6A
__swi __arm STATUS     NU_Retrieve_History_Entry(DATA_ELEMENT *id, 
                                                 UNSIGNED *param1, UNSIGNED *param2, UNSIGNED *param3,
                                                 UNSIGNED *time, NU_TASK **task, NU_HISR **hisr);


/* Работа с драйверами / Input/Output Driver functions */


#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x6B
__swi __arm STATUS    NU_Create_Driver(NU_DRIVER *driver, CHAR *name, 
                                       VOID (*driver_entry)(NU_DRIVER *, NU_DRIVER_REQUEST *));

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x6C
__swi __arm STATUS    NU_Delete_Driver(NU_DRIVER *driver);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x6D
__swi __arm STATUS    NU_Request_Driver(NU_DRIVER *driver,  NU_DRIVER_REQUEST *request);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x6E
__swi __arm STATUS    NU_Resume_Driver(NU_TASK *task);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x6F
__swi __arm STATUS    NU_Suspend_Driver(VOID (*terminate_routine)(VOID *),
                                        VOID *information, UNSIGNED timeout);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x70
__swi __arm UNSIGNED  NU_Established_Drivers(VOID);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x71
__swi __arm UNSIGNED  NU_Driver_Pointers(NU_DRIVER **pointer_list, 
                                         UNSIGNED maximum_pointers);


/* Установка управляющего и пользовательского режимов / Define Supervisor and User mode functions */


#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x72
__swi __arm UNSIGNED  NU_IS_SUPERVISOR_MODE();

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x73
__swi __arm VOID      NU_SUPERVISOR_MODE_P(VOID *nu_svc_usr_var);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x74
__swi __arm VOID      NU_USER_MODE_P(VOID *nu_svc_usr_var);

#pragma swi_number=NU_SWILIB_BEGIN_NUMBER+0x8075
__swi __arm VOID     *NU_SUPERV_USER_VARIABLES(VOID);

#endif
