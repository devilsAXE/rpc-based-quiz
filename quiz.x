struct quizzer{
	char answer[256];
	char leaderboard[1024];
	char username[256];
	int type;
	unsigned long userID;
	int x_1;
	int x_2;
};
struct quiz_master{
	char question[1024];
	char leader_board[1024];
	int score_1;
	int question_number;
	int x_1;
	int x_2;
};
program QUIZ_PROG{
	version QUIZ_VER{
		quiz_master QUIZPROC(quizzer)=1;
		
		}=1;
}=0x13451111;


program QUIZSCORE_PROG{
	version QUIZSCORE_VER{
		quiz_master QUIZSCOREPROC(quizzer)=1;
		
		}=1;
}=0x20000099;
