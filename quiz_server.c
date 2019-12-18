#include "quiz.h"
#include <stdio.h>
#define MAXIDS 1000
const int init = 0;
static int array[MAXIDS]={0};
static char names[MAXIDS][256]={""};
static unsigned long users_data[MAXIDS]={0};
static int userNumber = 0;
struct PlayerScore {
    int index;
    int score;
};
int compare (const void * a, const void * b)
{
    return ( (*(struct PlayerScore*)b).score - (*(struct PlayerScore*)a).score );
}
/******************************* HASHING FOR USER IDENTIFICATION ***********************/

unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

quiz_master *
quizproc_1_svc(quizzer *argp, struct svc_req *rqstp)
{	
	char const* const fileName = "users.txt";
	static quiz_master  result;
	int type = argp->type;
	char userName[256];
	strcpy(userName,argp->username);
	unsigned long userId = hash(userName);
	int fileId;
	char userFile[50];
	switch(type){
        /**********REGISTERING NEW USER / IDENTIFYING EXISTING USER ********/

	case 1 :;	int find = 0;
			for(int i = 0; i < MAXIDS; i++){
				
				if(users_data[i]==userId){
					fileId = i;
					find = 1;
					printf(" USER FOUND AT:%d with score: %d\n ",i, array[fileId]); 
					break;
				} 
			}
			if(!find){
				for(int i = 0; i < MAXIDS; i++){
					if(users_data[i]==0){
						users_data[i] = userId;
						strcpy(names[i],userName);
						fileId = i;
						break;
					}	 
				}
			}
			printf("%ld\n",users_data[fileId]);
			result.x_1 = -1;
			type = 0;
			break; 
	/****************** ASKING QUESTION RANDOMLY **************************/
	case 2:;	
			int qNum = 0, qno = 0, marks = 0, fnd = 0, totMarks = 0;
			char *ans;
			
			/* RANDOM QUESTION NUMBER GENERATOR */
			srand(time(0));
			qNum = rand() % (50) + 1; 
			char Question[1024], *ptr;
			FILE *fil = fopen("Questions.txt","r");
			int q = 0;
			while(fgets(Question,1024,fil)!=NULL){
				char *que;
				que=que;
				q= atoi(Question+1);
				if( q == qNum){
					que = strchr(Question,')');
					strcpy(result.question,que+1); // QUESTION COPIED
				break;
				}
			}
			fclose(fil);
			result.question_number = qNum; // Send Question Number to identify answer corresponding to the question
			break;
	/****************** DISPLAYING SCORE **************************/
	case 's':;
			for(int i = 0; i < MAXIDS; i++){
				if(users_data[i]==userId){
					fileId = i;
					break;
				} 
			}
			printf(" ------ SCORE : %d\n ", array[fileId]); 
			result.score_1 = array[fileId];
			break;
	/****************** DISPLAYING LEADERBOARD (TODO) **************************/
	case 'L':;	
			struct PlayerScore ps[MAXIDS];
			int c = 0;
			for(int n=0;n<MAXIDS; n++){
				if(users_data[n]!=0){
		        		ps[c].index = n;
      					ps[c].score = array[n];
					c++;
				}
  			}
			qsort (ps,c, sizeof(struct PlayerScore), compare);
			
		/************** MAKE THIS APPEAR ON THE CLIENT SIDE (TODO) **********/
			char leaderboard[1024];
			int  idx, skore = 0, l =0;
			for(int i = 0; i < c; i++){
				char tempname[64];
				strcpy(tempname,names[ps[i].index]);
				int le = strlen(tempname);
				skore = ps[i].score;
				idx = i;
				int k =0;
				//printf("%d. %s --> %d\n ",i,tempname,ps[i].score);
				while(k < le){
					leaderboard[l]= tempname[k];
					l++;
					k++;
				}
				leaderboard[l] = '\t';
				l++;
				if(!skore){leaderboard[l] = '0';l++;}
				while(skore){
				leaderboard[l] = skore%10 +'0';	
				skore = skore/10;
				l++;
				} 
				leaderboard[l] = '\n';
				l++;
				leaderboard[l] = '\0';
			}
			
			printf("%s",leaderboard);				
			
			
			strcpy(result.leader_board,leaderboard);
			break;
		
	/********************* EXITING VOLUNTARILY  ********************************/
	case 'E':;     
			for(int i = 0; i < MAXIDS; i++){
				if(users_data[i]==userId){
					fileId = i;
					break;
				} 
			} 			
			result.score_1 = array[fileId];
			users_data[fileId] = 0;
			array[fileId] = 0;
			break;
	}

	return &result;
}


/******************************* ANSWER  EVALUATION PROCEDURE *************************/


quiz_master *
quizscoreproc_1_svc(quizzer *argp, struct svc_req *rqstp)
{
	char const* const fileName = "users.txt";
	static quiz_master  result;
	unsigned long userid = hash(argp->username);
	int type = argp ->type, q = 0;
	char answer[1024],checkAnswer[1024];
	int questionNum = argp->x_1, score_ques = 0;
	strcpy(answer,argp->answer);	
	FILE *fans = fopen("answers.txt","r");
	while(fgets(checkAnswer,1024,fans)!=NULL){
		char *correctAns;
		q = atoi(checkAnswer);
		if( q == questionNum){
			correctAns = strchr(checkAnswer,')')+1;
			char *end = correctAns + strlen(correctAns) - 1;
		        while(end > correctAns && isspace((unsigned char)*end)) end--;
			end[1] = '\0';
			int len = strlen(correctAns);
			if(!strcmp(answer,correctAns)){
				score_ques = 1;
				fclose(fans);
				}
			else{
				score_ques = 0;
				fclose(fans);
			 }
			break;
			}
		};

	int found = 0, fileId;
	for(int i = 0; i < MAXIDS; i++){
		if(users_data[i]==userid){
			fileId = i;
			break;
		} 
	}
	array[fileId] += score_ques;
	result.score_1 = score_ques;

	return &result;
}
