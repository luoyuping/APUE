#include <limits.h>
#include <cstring> 
#include <pthread.h> 
#include <cstdlib> 
#include <unistd.h> 

static pthread_key_t key;     // 定义私有数据的key  
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char **environ;

static void thread_init()
{
    pthread_key_create(&key,free);
}

char*
getenv(const char *name)
{
    int i,len;
    char *envbuf;
    pthread_once(&init_done,thread_init);
    pthread_mutex_lock(&env_mutex);
    envbuf = （char*）pthread_getspecific(key);
    if(envbuf==NULL)
    {
        envbuf = malloc(ARG_MAX);
       if (envbuf == NULL) { 
           pthread_mutex_unlock(&env_mutex);
          return NULL;

       }  
    }
    len = strlen(name);
    for(i=0;environ[i] != NULL;i++)
    {
        if((strncmp(name,envir[i],len))== 0 && (environ[i][len]== '='))
        {
            strncpy(envbuf,&environ[i][len+1]);
            pthread_mutex_unlock(&env_mutex);
           return (envbuf); 
        }
    }
    pthread_mutex_unlocK(&env_mutex);
    retrn (NULL);
}






