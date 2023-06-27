#include "apue.h"
#include <sys/wait.h>

static void	sig_int(int);		/* our signal-catching function */
int
main(void)
{
		char	buf[MAXLINE];	/* from apue.h */
		pid_t	pid;
		int		status;
		if (signal(SIGINT, sig_int) == SIG_ERR)
				err_sys("signal error");

		printf("%% ");	/* print prompt (printf requires %% to print %) */
		while (fgets(buf, MAXLINE, stdin) != NULL) {
				if (buf[strlen(buf) - 1] == '\n')
						buf[strlen(buf) - 1] = 0; /* replace newline with null */

				//implementation of string token, making parameter available for command
				const char* s = " ";
				char *token, *str1;
				int cnt = 0;
				char* args[48];
				str1 = strdup(buf);
				for(int i = 0; ; i++, str1 = NULL){
					token = strtok(str1, s);
					if(token == NULL)
						break;
					args[i] = token;
					cnt++;
				}
				free(str1);
				args[cnt] = (char *)NULL;	
				
				if(strcmp(args[0], "cd") == 0){
					//execvp("chdir", &args[1]);
					chdir(args[1]);
					continue;
				}
				//////////////////////////

				if ((pid = fork()) < 0) {
						err_sys("fork error");
				}
				else if (pid == 0) {		/* child */

						//use execvp instead execlp
						execvp(args[0], &args[0]);
						//execlp(buf, buf, (char *)0);
						//////////////////////////////////////
						
						err_ret("couldn't execute: %s", buf);
						exit(127);
				}

				/* parent */
				if ((pid = waitpid(pid, &status, 0)) < 0){
					err_sys("waitpid error");
				}
				printf("%% ");
		}
		exit(0);
}

		void
sig_int(int signo)
{
		printf("interrupt\n%% ");
}

