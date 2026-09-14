#ifndef HTTPC_PROPERTIES
#define HTTPC_PROPERTIES

/***************/
/* USER REGION */
/***************/

/* Default listening port */
#define DEFAULT_PORT 8000

/* Read index html by default? */
#define READ_INDEX_HTML 1

/********************/
/* DEVELOPER REGION */
/********************/

/* Max buffer size on stack */
#define MAX_BUFFER_SIZE 8192

/* Max number of handled events per one epoll loop iteration */
#define MAX_CONNECTIONS_PER_ITERATION 64

#endif
