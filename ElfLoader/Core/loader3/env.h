
#ifndef __ENV_H__
#define __ENV_H__


int setenv(const char *name, const char *value, int replace);
int unsetenv(const char *name);
char *getenv(const char *var);
int clearenv(void);
char **environ();

#endif
