#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/resource.h>

#include "ulimit_m.h"

void print_m(int temp);

void getLimit(struct rlimit limit,int flag){
	int temp;
	if (getrlimit(flag, &limit) == 0) {
		temp = (int)limit.rlim_cur;
  	}else{
  		temp = -2;
  	}
  	print_m(temp);
}



void print_m(int temp){
	if(temp==-1){		
		printf("%s\n","unlmited");
	}
  	if (temp == -2)
  	{
  		printf("%s\n","ulimit failed");
  	}
  	if(temp>=0){
  		printf("%d\n",temp);
  	}
}

void getLimits(char* line[]){
	struct rlimit limit; 
	int flag;
	if(strcmp(line[0],"-c")==0){
		flag = RLIMIT_CORE;
		getLimit(limit,flag);
	}

	if(strcmp(line[0],"-d")==0){
		flag = RLIMIT_DATA;
		getLimit(limit,flag);
	}
	if(strcmp(line[0],"-e")==0){
		flag = RLIMIT_NICE;
		getLimit(limit,flag);
	}
	if(strcmp(line[0],"-f")==0){
		flag = RLIMIT_FSIZE;
		getLimit(limit,flag);
	}
	if(strcmp(line[0],"-i")==0){
		flag = RLIMIT_SIGPENDING;
		getLimit(limit,flag);
	}
	if(strcmp(line[0],"-l")==0){
		flag = RLIMIT_MEMLOCK;
		getLimit(limit,flag);
	}
	if(strcmp(line[0],"-m")==0){
		flag = RLIMIT_RSS;
		getLimit(limit,flag);
	}
	if(strcmp(line[0],"-n")==0){
		flag = RLIMIT_NOFILE;
		getLimit(limit,flag);
	}
	if(strcmp(line[0],"-p")==0){
		flag = RLIMIT_RTTIME;
		getLimit(limit,flag);
	}
	if(strcmp(line[0],"-q")==0){
		flag = RLIMIT_MSGQUEUE;
		getLimit(limit,flag);
	}
	if(strcmp(line[0],"-r")==0){
		flag = RLIMIT_RTPRIO;
		getLimit(limit,flag);
	}
	if(strcmp(line[0],"-s")==0){
		flag = RLIMIT_STACK;
		getLimit(limit,flag);
	}
	if(strcmp(line[0],"-t")==0){
		flag = RLIMIT_CPU;
		getLimit(limit,flag);
	}
	if(strcmp(line[0],"-u")==0){
		flag = RLIMIT_NPROC;
		getLimit(limit,flag);
	}
	if(strcmp(line[0],"-v")==0){
		flag = RLIMIT_AS;
		getLimit(limit,flag);
	}
	if(strcmp(line[0],"-x")==0){
		flag = RLIMIT_LOCKS;
		getLimit(limit,flag);
	}
	if(strcmp(line[0],"-a")==0){
		printf("%s","core file size          (blocks, -c) ");
		flag = RLIMIT_CORE;
		getLimit(limit,flag);
		printf("%s","data seg size           (kbytes, -d) ");
		flag = RLIMIT_DATA;
		getLimit(limit,flag);
		printf("%s","scheduling priority             (-e) ");
		flag = RLIMIT_NICE;
		getLimit(limit,flag);
		printf("%s","file size               (blocks, -f) ");
		flag = RLIMIT_FSIZE;
		getLimit(limit,flag);
		printf("%s","pending signals                 (-i) ");
		flag = RLIMIT_SIGPENDING;
		getLimit(limit,flag);
		printf("%s","max locked memory       (kbytes, -l) ");
		flag = RLIMIT_MEMLOCK;
		getLimit(limit,flag);
		printf("%s","max memory size         (kbytes, -m) ");
		flag = RLIMIT_RSS;
		getLimit(limit,flag);
		printf("%s","open files                      (-n) ");
		flag = RLIMIT_NOFILE;
		getLimit(limit,flag);
		printf("%s","pipe size            (512 bytes, -p) ");
		flag = RLIMIT_RTTIME;
		getLimit(limit,flag);
		printf("%s","POSIX message queues     (bytes, -q) ");
		flag = RLIMIT_MSGQUEUE;
		getLimit(limit,flag);
		printf("%s","real-time priority              (-r) ");
		flag = RLIMIT_RTPRIO;
		getLimit(limit,flag);
		printf("%s","stack size              (kbytes, -s) ");
		flag = RLIMIT_STACK;
		getLimit(limit,flag);
		printf("%s","cpu time               (seconds, -t) ");
		flag = RLIMIT_CPU;
		getLimit(limit,flag);
		printf("%s","max user processes              (-u) ");
		flag = RLIMIT_NPROC;
		getLimit(limit,flag);
		printf("%s","virtual memory          (kbytes, -v) ");
		flag = RLIMIT_AS;
		getLimit(limit,flag);
		printf("%s","file locks                      (-x) ");
		flag = RLIMIT_LOCKS;
		getLimit(limit,flag);
	}
}

void setLimit(struct rlimit limit,int flag){
	if (setrlimit(flag, &limit) != 0) {
		printf("%s\n","ulimit failed");
  	}
}

void setLimits(char* line[]){
	struct rlimit limit; 
	int flag;
	limit.rlim_cur = atoi(line[1]);
	limit.rlim_max = atoi(line[1]);
	if(strcmp(line[0],"-c")==0){
		flag = RLIMIT_CORE;
		setLimit(limit,flag);
	}

	if(strcmp(line[0],"-d")==0){
		flag = RLIMIT_DATA;
		setLimit(limit,flag);
	}
	if(strcmp(line[0],"-e")==0){
		flag = RLIMIT_NICE;
		setLimit(limit,flag);
	}
	if(strcmp(line[0],"-f")==0){
		flag = RLIMIT_FSIZE;
		setLimit(limit,flag);
	}
	if(strcmp(line[0],"-i")==0){
		flag = RLIMIT_SIGPENDING;
		setLimit(limit,flag);
	}
	if(strcmp(line[0],"-l")==0){
		flag = RLIMIT_MEMLOCK;
		setLimit(limit,flag);
	}
	if(strcmp(line[0],"-m")==0){
		flag = RLIMIT_RSS;
		setLimit(limit,flag);
	}
	if(strcmp(line[0],"-n")==0){
		flag = RLIMIT_NOFILE;
		setLimit(limit,flag);
	}
	if(strcmp(line[0],"-p")==0){
		flag = RLIMIT_RTTIME;
		setLimit(limit,flag);
	}
	if(strcmp(line[0],"-q")==0){
		flag = RLIMIT_MSGQUEUE;
		setLimit(limit,flag);
	}
	if(strcmp(line[0],"-r")==0){
		flag = RLIMIT_RTPRIO;
		setLimit(limit,flag);
	}
	if(strcmp(line[0],"-s")==0){
		flag = RLIMIT_STACK;
		setLimit(limit,flag);
	}
	if(strcmp(line[0],"-t")==0){
		flag = RLIMIT_CPU;
		setLimit(limit,flag);
	}
	if(strcmp(line[0],"-u")==0){
		flag = RLIMIT_NPROC;
		setLimit(limit,flag);
	}
	if(strcmp(line[0],"-v")==0){
		flag = RLIMIT_AS;
		setLimit(limit,flag);
	}
	if(strcmp(line[0],"-x")==0){
		flag = RLIMIT_LOCKS;
		setLimit(limit,flag);
	}
}
void ulimit_m(int numb_of_params,char*params[MAX_PARAM_NUMBER]){
	if(numb_of_params==1)
		getLimits(params);
	else
		if(numb_of_params==2)
			setLimits(params);
		else
			printf("%s\n","error");
}
