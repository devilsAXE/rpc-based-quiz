************************************************************************************************
			ADVANCED OPERATING SYSTEM 
			    ASSIGNEMENT #1	
		INSTRUCTOR : Dr Amit Dua
		TEAM MEMBER 1 : Aman Kumar Sharma (h20180137@pilani.bits-pilani.ac.in) 
		
************************************************************************************************

OBJECTIVE : Design a Quiz application, where the client-server uses Remote Procedure Calls to com-
	    municate with each other. 

EXECUTION: (IF RUNNING ON DIFFERENT MACHINES) 
	   
	 	  1. Open the quiz_client.c set the value of string variable 
	   	     host to IP address of the machine you are running your quiz_server.
		  2. Save your file and in terminal execute "make -f Makefile.quiz" 
		  3. Execute ./quiz_server on your other machine 
		  4. Execute the ./quiz_client of this machine and follow the workflow given below. 
	  
	  (IF RUNNING ON SAME MACHINES) 

	  	1. Simply run the quiz_server as "sudo ./quiz_server", enter your 
	  	   system's password. 

	  	2. Open a new instance of the Terminal and run "./quiz_client" , you'll be asked to enter the 
	  	   username, make sure it is unique. If runtime is aborted abruptly, you can log in using the 
	  	   username and continue from where you left. 

SOLUTION : We implemented the given task on the linux based Sun RPC. The client stub when run asks
	   for a unique username with which the client would be identified for subsequent procedures 
           Following is a rough workflow of the client stub.
<pre>
		******************
		| Enter Username |
		******************
			||
			\/							
		*************************  <<---------------------------|	
		| 	MENU		|				|
		| 1. Ask Question	|				|
	   	| 2. Current Score	|				|	
	  	| 3. Leaderboard 	|				|
          	| 4. Voluntarily Exit	|				|
      ---------	*************************----------			|	
      |	          |                   |		  |			|
    if (1)      if(2)		    if(3)	if(4)			|
      |		  |		      |		  |			|	
a random 	User's curr	shows all con-   Exits the match  	|
question is     score is 	tenders with 	previous record 	|
shown  		shown		decreasing 	is deleted 		|
  |	 	|		score		(EXIT)			|
  |_____________|_________________|_____________________________________|



</pre>











