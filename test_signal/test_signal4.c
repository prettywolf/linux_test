/**
 *	@filename :
 * 		test_signal4.c
 * 
 * 	@note :
 * 
 **/ 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <setjmp.h>

#define MAXLINE 1024

static void sig_alarm(int signo);

static jmp_buf env_alrm;

static void test_jmp(void) {
		
	printf("%s : 0\n", __FUNCTION__);	
	if (setjmp(env_alrm) != 0) {
		printf("longjump called\n");
	} else {	
		printf("%s : 1\n", __FUNCTION__);
		raise(SIGUSR1);
	}

	return;
}

int main(void) {		
	
	signal(SIGUSR1, sig_alarm);
	
	do {
		printf("test_jmp\n");
		test_jmp(); 
	} while (1);
			
	return 0;
}

void sig_alarm(int signo) {
	sigset_t set;

	printf("sig %d\n", signo);
	sigemptyset(&set);
	sigprocmask(SIG_SETMASK, &set, NULL);
	longjmp(env_alrm, -1);
}