shell: help_m.c cd_m.c pwd_m.c type_m.c nice_m.c ulimit_m.c echo_m.c kill_m.c sig.c export_m.c execute_m.c redirect_m.c pipeline_m.c shell.c 
	gcc -o shell help_m.c cd_m.c pwd_m.c type_m.c nice_m.c ulimit_m.c echo_m.c kill_m.c sig.c export_m.c execute_m.c redirect_m.c pipeline_m.c shell.c -lreadline
clean: 
	rm -f shell

