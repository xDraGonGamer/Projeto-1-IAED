/*ist199333 Tiago Santos*/
#include <stdio.h>
#include <string.h>
#define ERRO 0
#define SUCESSO 1
#define NTAREFAS 10000
#define NUTILIZADORES 50
#define NATIVIDADES 10
#define UTILVAZIO "                  "
#define TODODESC "TO DO"
#define DONEDESC "DONE"
#define INPROGRESSDESC "IN PROGRESS"
#define UTILIZADORSIZE 21
#define ATIVIDADESIZE 21
#define TAREFASIZE 51
#define ERRO_TOOMANYTASKS "too many tasks"
#define ERRO_DUPLICATEDESCRIPTION "duplicate description"
#define ERRO_INVALIDDURATION "invalid duration"
#define ERRO_INVALIDTIME "invalid time"
#define ERRO_USERALREADYEXISTS "user already exists"
#define ERRO_TOOMANYUSERS "too many users"
#define ERRO_NOSUCHTASK "no such task"
#define ERRO_TASKALREADYSTARTED "task already started"
#define ERRO_NOSUCHUSER "no such user"
#define ERRO_NOSUCHACTIVITY "no such activity"
#define ERRO_DUPLICATEACTIVITY "duplicate activity"
#define ERRO_INVALIDDESCRIPTION "invalid description"
#define ERRO_TOOMANYACTIVITIES "too many activities"

typedef struct{
	char uid[UTILIZADORSIZE];
}Utilizador;

typedef struct{
	char desc[ATIVIDADESIZE];
}Atividade;

typedef struct{
	int id, tprev, ti;/*task identificator/expected time/initial time*/
	char desc[TAREFASIZE];
	Utilizador utilizador;
	Atividade atividade;
}Tarefa;

int ativContains(Atividade atividades[], int natividades, Atividade atividade){
	/*checks the array for an instance of atividade*/
	int i;
	for(i = 0; i < natividades; i++){
		if(strcmp(atividades[i].desc, atividade.desc) == 0){
			return 1;
		}
	}
	return 0;
}

int userContains(Utilizador users[], int nutilizadores, Utilizador user){
	/*checks the array for an instance of user*/
	int i;
	for(i = 0; i < nutilizadores; i++){
		if(strcmp(users[i].uid, user.uid) == 0){
			return 1;
		}
	}
	return 0;
}

void sortAlphabetically(Tarefa tarefasaux[], int ntarefas){
	/*sorts the string array alphabetically
	  bubble sort*/
	int done, i;
	Tarefa aux;
	do{
		done = 1;/*control variable*/
		for(i = 0; i < ntarefas - 1; i++){
			if(strcmp(tarefasaux[i].desc,tarefasaux[i+1].desc) > 0){
				aux = tarefasaux[i];/*swap*/
				tarefasaux[i] = tarefasaux[i+1];
				tarefasaux[i+1] = aux;
				done = 0;/*vector must be reevaluated*/
			}
		}
	}while(done == 0);/*if no rearragements are done, 
			    the vector is correctly sorted*/
}

int tCommand(int ntarefas, Tarefa tarefas[]){/*returns 1 if a task is added, 0 otherwise*/
	int i, j;
	char cmd, desc[TAREFASIZE];
	Tarefa tarefa;
	Utilizador util;
	Atividade todo;
	strcpy(util.uid, UTILVAZIO);
	strcpy(todo.desc, TODODESC);
	if(ntarefas == NTAREFAS){ /*checks task limit*/
		printf("%s\n", ERRO_TOOMANYTASKS);
		return 0;
	}
	getchar();
	i = 0;
	while((cmd = getchar()) != ' '){
		if(cmd == '.' || cmd == '-'){/*invalid characters*/
			printf("%s\n", ERRO_INVALIDDURATION);
			return 0;
		}
		i = i * 10 + cmd - '0';
	}
	scanf("%s", desc);
	for(j = 0; j < ntarefas; j ++){ /*ver se existe alguma tarefa com a mesma desc*/
        	if(strcmp(desc, tarefas[j].desc) == 0){
                	printf("%s\n", ERRO_DUPLICATEDESCRIPTION);
			return 0;
                }
	}
        tarefa.tprev = i;/*initializes the task parameters*/
        strcpy(tarefa.desc, desc);
        tarefa.ti = 0;
        tarefa.atividade = todo;
        tarefa.id = ntarefas + 1;
        strcpy(tarefa.utilizador.uid, UTILVAZIO);
        tarefas[ntarefas] = tarefa;
        printf("task %d\n", ++ntarefas);
	return 1;
}

void lCommand(Tarefa tarefas[], int ntarefas){
	char cmd;
	int i;
	Tarefa tarefa;
        if((cmd = getchar()) == '\n'){
        	sortAlphabetically(tarefas, ntarefas);
        	for(i = 0; i < ntarefas; i++){/*lists all tasks alphabetically*/
        		tarefa = tarefas[i];
                	printf("%d %s #%d %s\n", tarefa.id, tarefa.atividade.desc, tarefa.tprev, tarefa.desc);
        	}
		return;
	}
        while(cmd != '\n'){
                scanf("%d", &i);
		if(i > ntarefas || i == 0){ /*id out of bounds*/
			printf("%d: %s\n", i, ERRO_NOSUCHTASK);
		}else{
                	tarefa = tarefas[i - 1];
                	printf("%d %s #%d %s\n", i, tarefa.atividade.desc, tarefa.tprev, tarefa.desc);
        	}
		cmd = getchar();
        }
}

int nCommand(){/*returns the time added*/
	int i = 0;
	char cmd;
	getchar();
        while((cmd = getchar()) != '\n'){ /*invalid characters*/
        	if(cmd == '-' || cmd == '.' || cmd == ','){
                	printf("%s\n", ERRO_INVALIDTIME);
                        return -1;
                }
                i = i * 10 + cmd - '0'; 
	}
        return i;
}

int uCommand(Utilizador users[], int nutilizadores){/*returns ammount of users added*/
	int i;
	Utilizador user;
	if(getchar() == '\n'){
        	for(i = 0; i < nutilizadores; i++){
                	printf("%s\n", users[i].uid);/*lists users by order of arrival*/
                }
                return 0;
        }
        if(nutilizadores == NUTILIZADORES){/*checks user limit*/
        	printf("%s\n", ERRO_TOOMANYUSERS);
                return 0;
        }
        scanf("%s", user.uid);
	if(userContains(users, nutilizadores, user)){
		printf("%s\n", ERRO_USERALREADYEXISTS);
		return 0;
	}
        users[nutilizadores] = user;
	return 1;
}

void mCommand(Tarefa tarefas[], int ntarefas, Utilizador users[], int nutilizadores, Atividade atividades[], int natividades, int tsys){
	int id, i, estado = ERRO, gasto;
	char cmd;
	Tarefa tarefa;
	Utilizador util;
	Atividade ativ;
	scanf("%d", &id);
	scanf("%s", util.uid);
	i = 0;
	getchar();
	while((cmd = getchar()) != '\n'){
		ativ.desc[i++] = cmd;/*reads activity argument*/
	}
	ativ.desc[i] = '\0';
	for(i = 0; i < ntarefas; i++){
		if(tarefas[i].id == id){
			estado = SUCESSO;/*control variable*/
			tarefa = tarefas[i];
			break;
		}
	}
	if(estado == ERRO){
		printf("%s\n", ERRO_NOSUCHTASK);
		return;
	}
	if(strcmp(ativ.desc, TODODESC) == 0 && strcmp(tarefa.atividade.desc, TODODESC) != 0){
		printf("%s\n", ERRO_TASKALREADYSTARTED);
		return; /*task cannot go back to TO DO*/
	}
	if(userContains(users, nutilizadores, util) == 0){
		printf("%s\n", ERRO_NOSUCHUSER);
		return;/*checks if entered user exists*/
	}
	if(ativContains(atividades, natividades, ativ) == 0){
		printf("%s\n", ERRO_NOSUCHACTIVITY);
		return;/*checks if entered activity exists*/
	}
	if(strcmp(ativ.desc, TODODESC) != 0 && tarefa.ti == 0){
                tarefa.ti = tsys; /*when task is initiated*/
        }
	tarefa.atividade = ativ;
	if(strcmp(ativ.desc, DONEDESC) == 0 && strcmp(tarefa.atividade.desc, DONEDESC) != 0){
		gasto = tsys - tarefa.ti;
		printf("duration=%d slack=%d\n", gasto, gasto - tarefa.tprev); 
	}/*if the task is moved to DONE*/
	tarefas[i] = tarefa;
}

void dSort(Tarefa tarefas[], int n){
	int i, done = 0;/*sorts the array by initial time and alphabetically*/
	Tarefa aux;     /*bubble sort*/
	do{
		done = 1;
		for(i = 0; i < n - 1; i++){
			if(tarefas[i].ti > tarefas[i+1].ti){
				aux = tarefas[i];
				tarefas[i] = tarefas[i+1];
				tarefas[i+1] = aux;
				done = 0;
				continue;
			}else if(tarefas[i].id == tarefas[i + 1].id){
			     if(strcmp(tarefas[i].desc, tarefas[i+1].desc) > 0){
					aux = tarefas[i];
					tarefas[i] = tarefas[i+1];
					tarefas[i+1] = aux;
					done = 0;
			     }
			}
		}
	}while(done == 0);
}

void dCommand(Tarefa tarefas[], int ntarefas, Atividade atividades[], int natividades){
	int i = 0, index = 0;
	char cmd;
	Atividade ativ;
	Tarefa tarefa, aux[NTAREFAS];
	while((cmd = getchar()) != '\n'){/*reads activity argument*/
		ativ.desc[i++] = cmd;
	}
	ativ.desc[i] = '\0';
	if(ativContains(atividades, natividades, ativ) == 0){/*checks if the activity is valid*/
		printf("%s\n", ERRO_NOSUCHACTIVITY);
		return;
	}
	for(i = 0; i < ntarefas; i++){
		tarefa = tarefas[i];
		if(strcmp(tarefa.atividade.desc, ativ.desc) == 0){/*chooses all tasks that are in the activity*/
			aux[index++] = tarefa;
		}
	}
	dSort(aux, index); /*sorts the tasks*/
	for(i = 0; i < index; i++){
		tarefa = aux[i];
		printf("%d %d %s\n", tarefa.id, tarefa.ti, tarefa.desc);
	}
}

int aCommand(Atividade atividades[], int natividades){/*returns the ammount of activities added*/
	char cmd;
	int i;
	Atividade ativ;
	if((cmd = getchar()) == '\n'){
		for(i = 0; i < natividades; i++){
			printf("%s\n", atividades[i].desc);/*lists all activities*/
		}
		return 0;
	}
	if(natividades == NATIVIDADES){/*checks number of activities*/
		printf("%s\n", ERRO_TOOMANYACTIVITIES);
		return 0;
	}
	i = 0;
	while((cmd = getchar()) != '\n'){
		if(cmd >= 'a' && cmd <= 'z'){/*reads activity description*/
			while((cmd = getchar()) != '\n');
			printf("%s\n", ERRO_INVALIDDESCRIPTION);
			return 0;
		}else{
			ativ.desc[i++] = cmd;
		}
	}
	ativ.desc[i] = '\0';
	if(ativContains(atividades, natividades, ativ)){
		printf("%s\n", ERRO_DUPLICATEACTIVITY);/*checks if activity already exists*/
		return 0;
	}
	atividades[natividades] = ativ;
	return 1;
}

void iniciaAtividades(Atividade atividades[]){/*initializes default activities*/
	Atividade todo, done, inprogress;
	strcpy(inprogress.desc, INPROGRESSDESC);
	strcpy(done.desc, DONEDESC);
	strcpy(todo.desc, TODODESC);
	atividades[0] = todo;
	atividades[1] = inprogress;
	atividades[2] = done;
}

int main(){
	int tsys=0, ntarefas=0, natividades=3, nutilizadores=0, i;
	Tarefa tarefas[NTAREFAS];
	Utilizador users[NUTILIZADORES];
	Atividade atividades[NATIVIDADES];
	char cmd;
	iniciaAtividades(atividades);
	while(2){
		/*scanf("%c", &cmd);*/
		cmd = getchar();/*gets command*/
		switch(cmd){
			case 'q': /*terminate the program*/
				return 0;
			case 't': /*add task to system*/
				ntarefas += tCommand(ntarefas, tarefas);
				break;
			case 'l':/*lists tasks*/
				lCommand(tarefas, ntarefas);
				break;
			case 'n':/*checks or changes system time*/
				i = nCommand();
				if(i != -1){
					printf("%d\n", tsys += i);
				}
				break;
			case 'u':/*adds user to system or lists all users in system*/
				nutilizadores += uCommand(users, nutilizadores);
				break;
			case 'm':/*move task*/
				mCommand(tarefas, ntarefas, users, nutilizadores, atividades, natividades, tsys);
				break;
			case 'd':/*lists all tasks in activity*/
				dCommand(tarefas, ntarefas, atividades, natividades);
				break;
			case 'a':/*adds activity or lists all activities in the system*/
				natividades += aCommand(atividades, natividades);
				break;
		}
	}
	return 0;
}

