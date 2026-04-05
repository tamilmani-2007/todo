#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define FILEPATH "/home/thamizh/cli_project/base/todo_base/todo_base.csv"

void guide(){	
	printf("insufficient arguments! \n");
	printf("Usage: \n");
	printf("  1. todo do <task> --> to add tasks \n");
	printf("  2. todo todos	    --> to show the todos \n");
	printf("  3. todo clear     --> to truncate the todos \n");
	printf("	=> 3.1 todo clear <finished task> --> to remove the finidhed task \n");
}
int isEmpty(FILE *fp){
	if( fp == NULL ){
		perror("Error occured");
		return 1;
	}
	return 0;
}

int get_lastindex(){
	FILE *fp = fopen(FILEPATH, "r");
	if(isEmpty(fp)) return -1;
	
	char *line = NULL;
	size_t len = 0;
	int last_index = 0;

	while(getline(&line, &len, fp) != -1){
		last_index++;
	}
	return last_index/2 ;

}

void add_todo(char todo[]){
	int last_index = get_lastindex();
	FILE *fp;
	fp = fopen(FILEPATH, "a");

	if(isEmpty(fp)){
		printf("Error Occured while add to do!!!\n");
		return;
	}	
	fprintf(fp, "%d. %s \n\n", last_index+1, todo);	
	fclose(fp);
}

void show_todos(){
	FILE *fp;
	fp = fopen(FILEPATH, "r");

	if(isEmpty(fp)){
		printf("Error Occured while showing todos!!!\n");
		return;
	}
	char *line = NULL;
	size_t len = 0;

	while (getline(&line, &len, fp) != -1){
		printf("%s", line);
	}
	free(line);
	fclose(fp);

}

void erase_todo(){
	FILE *fp = fopen(FILEPATH, "w");
	
	if(isEmpty(fp)){
		printf("Error occured while truncate todo's");
		return;
	}
	fclose(fp);
}

int main(int argc , char *argv[]){
	if (argc<2){
		guide();	
		return 1;
	}

	if(strcmp(argv[1], "do") == 0){      		// for adding todos	
		for(int i = 2; i< argc; i++){
			add_todo(argv[i]);
		}
	} 

	else if(strcmp(argv[1], "todos") == 0){
		show_todos();				//to show the todos from csv
	}

	else if((strcmp(argv[1], "clear") == 0) && argc == 2){
		char choice;
		printf("Are you sure want to delete the todos[Y/n]:");
		scanf(" %c", &choice);
		if( choice == 'Y' || choice == 'y' ){
			erase_todo();
			printf("Your todos are removed...\n");
		}
	}
	else if((strcmp(argv[1], "clear") == 0) && argc >2){
		if(argc == 3){
			printf("for deleting particular todo with index i");
		}
		else if(strcmp(argv[4], "to") && argc == 5){
			printf("for deleting todos with ranges... ex: i to j");
		}
		else if(strcmp(argv[4], "to")){
			printf("for deleting todos after index i");
		}
	}
}
