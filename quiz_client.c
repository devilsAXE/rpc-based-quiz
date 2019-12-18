


#include "quiz.h"
/******************************* PROCEDURE #1 ***********************/
	int
quiz_prog_1(char *host, int type, char *userName, int ques, char *xx)
{
	CLIENT *clnt;
	quiz_master  *result_1;
	quizzer  quizproc_1_arg;
	quizproc_1_arg.type = type;
	strcpy(quizproc_1_arg.username, userName);
	if(type == 'a'){
		strcpy(quizproc_1_arg.answer, xx);	
		quizproc_1_arg.x_1 = ques;
	}
#ifndef	DEBUG
	clnt = clnt_create (host, QUIZ_PROG, QUIZ_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = quizproc_1(&quizproc_1_arg, clnt);
	if (result_1 == (quiz_master *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	else{
		if(type == 2)
			printf("Q.%d : %s\n",result_1->question_number,result_1->question);
		if(type == 'L'){
			printf("LEADERBOARD\n");
			printf("User \t Score\n");
			printf("%s", result_1->leader_board); 
		}
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
	if(type == 2)
		return result_1->question_number;
	if(type == 'a'||type == 's'||type == 'E')
		return result_1->score_1;
	else
		return result_1->x_1;;
}

/******************************* PROCEDURE #2 ***********************/
	int
quizscore_prog_1(char *host, int type, char *username, int ques, char *xx)
{
	CLIENT *clnt;
	quiz_master  *result_1;
	quizzer  quizscoreproc_1_arg;
	quizscoreproc_1_arg.type = type;
	strcpy(quizscoreproc_1_arg.username,username);
	strcpy(quizscoreproc_1_arg.answer, xx);	
	quizscoreproc_1_arg.x_1 = ques;


#ifndef	DEBUG
	clnt = clnt_create (host, QUIZSCORE_PROG, QUIZSCORE_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	result_1 = quizscoreproc_1(&quizscoreproc_1_arg, clnt);
	if (result_1 == (quiz_master *) NULL) {
		clnt_perror (clnt, "call failed");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
	return result_1->score_1;
#endif	 /* DEBUG */
}


	int
main (int argc, char *argv[])
{
	char *host = "127.0.0.1";
	char userName[256];
	printf("Enter Username : ");
	fflush(stdout);
	scanf("%s",userName);
	//long userId = hash(userName);
	int status = quiz_prog_1(host,1,userName,0,""); // REGISTRATION
	int type;
	if(status == -1)
		printf("-----Successfully Resgistered------\n");

	int qNum;
	do{	
		system("clear");
		printf("\t MENU - %s\n",userName);	
		printf("\t1. Ask Question \n");
		printf("\t2. My Score \n");
		printf("\t3. Leaderboard \n");
		printf("\t4. Exit \n");
		scanf("%d",&type);
		if((type == 1 || type == 2 || type == 3 || type==4)){
			switch(type){
				case 1: ;
					qNum  = quiz_prog_1(host,2,userName,0,"");
					type = 'a';


				case 'a':;
					  char ans[1024];
					  int sco =  99;
					  printf("Answer %d :",qNum);
					  scanf("%s",ans);
					  printf("\n");	
					  sco = quizscore_prog_1(host,type,userName,qNum,ans);
					  if(sco)
					  	printf("Congrats you're correct, you get %d point\n", sco);
					  else  printf("Oops! That's wrong, you get %d point\n", sco);
					  sleep(2);
					  break;

				case 2:;
				       int y = quiz_prog_1(host,'s',userName,0,"");
				       printf("Your current total : %d\n ", y); 
				       sleep(2);	
				       break;

				case 3:;system("clear");
				       int z = quiz_prog_1(host,'L',userName,0,"");
				       sleep(2);
				       break;
				case 4:;
				       int r = quiz_prog_1(host,'E',userName,0,"");
				       printf("Well played %s, your FINAL SCORE : %d\n ",userName, r); 
				       exit(0);


			}
		}
		else{
			printf("Try Again.. Enter Right Key\n");
			break;

		}		       				

	}while(1);
	exit (0);
}
