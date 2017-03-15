

#include <stdlib.h>
#include <iostream.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>

#include "games.h"

char head=(char)1;
char torso=(char)179;
char arm=(char)180;
char arms=(char)197;
char leg=(char)39;
char legs=(char)94;

const int rows=5;
const int cols=4;

/* initializes the array */
void initialize(char hangman[rows][cols]);
void initialize(char*,int,char*);
void initialize(char[]);
void initializeCharsUsed(char[]);
/* determines what to add */
void add(char hangman[rows][cols],int step);
void add(char*,char*,char);
/* prints the array */
void print(char hangman[rows][cols],char*,char[]);
/* for user defined game */
char *getAnswer(int&);
/* retrieves guesses */
char getGuess();
/* similar to strchr() function */
int inString(char*,char);
/* chooses game for one player game */
void getGame(char[]);
/* increments game, once done */
void setGame(char[]);

void main(){
  char hangman[rows][cols];	//stores the drawing
  int j=0;
  int step=-1;				//counts how many mistakes
  int ansLen;
  int gameNum;
  char choice='0';
  char ch;
  char charsUsed[27];
  char gamesPlayed[games];
  char *progress;
  char *answer;
  char repeat='y';

  /* options for game type */
  while(choice!='1' && choice!='2'){
    cerr<<"Choose:\t1) Computer Selected Password\n"
		<<"\t2) User Defined Password\n>>> ";
	cin>>choice;
  }

  initialize(gamesPlayed);
  answer=(char*)malloc(1);

  while(tolower(repeat)!='n'){
	initializeCharsUsed(charsUsed);
    if(choice=='2'){	//if 2 player game
	  cerr<<"\nEnter Secret Word: ";
      answer=strdup(getAnswer(ansLen));
	}
    else{				//else 1 player game
  	  getGame(gamesPlayed);
	  while(gamesPlayed[(gameNum=rand()%games)])
		;
  	  answer=strdup(onePlayerWords[gameNum]);
	  ansLen=strlen(answer);
	  gamesPlayed[gameNum]=1;
	  setGame(gamesPlayed);
	}
    progress=(char*)malloc(ansLen);

    initialize(hangman);
    initialize(progress,ansLen,answer);

    print(hangman,progress,charsUsed);//show the blank stand
    /* most of the conditionals ignore repeated guesses */
    while(step<5){
      if(inString(charsUsed,tolower((ch=getGuess())))){
	    if(!inString(answer,ch))
  	      add(hangman,++step);			//add incrementally pieces
	    else
          add(answer,progress,ch);
	    charsUsed[tolower(ch)-'a']='_';
	  }
        print(hangman,progress,charsUsed);//print each step
	    // if the string is complete, quit
	    if(strncmp(answer,progress,ansLen)==0){
  	      print(hangman,progress,"");
	      cout<<"\n\nYou Win!\n";
	      break;
		}
	} 

    // if max number of errors is reached, print lose message
    if(step>=5){
	  print(hangman,"","");
	  cout<<"\nYou lose\nSolution was \""<<answer<<"\"\n";
	}

	step=-1;	//reset for next game
  

    cerr<<"Enter \"n\" to quit, anything else to play again ";
    repeat=getch();
  }
    return;
}

/* sets all elements of the array equal to
   the space character, ascii 32, so it appears
   to be empty, and then assign the locations 
   that make up the stand */
void initialize(char hangman[rows][cols]){
  int i,j;
  for(i=0;i<rows;i++)	//sets all characters
    for(j=0;j<cols;j++)	//in the array = to 
      hangman[i][j]=(char)32;	//spaces (ascii 32)

  hangman[0][1]=(char)218;	//these
  hangman[0][2]=(char)196;	//assignments
  hangman[0][3]=(char)191;	//will draw 
  hangman[1][1]=(char)179;	//the stand
  hangman[2][1]=(char)179;	//for the
  hangman[3][1]=(char)179;	//hangman
  hangman[4][0]=(char)196;
  hangman[4][1]=(char)193;
  hangman[4][2]=(char)196;
  hangman[4][3]=(char)196;

  return;
}

/* initializes input string, putting underscores
   in only where characters exist */
void initialize(char *st,int len,char *answer){
  int i;
  for(i=0;i<len;i++)
	if(isalpha(answer[i]))
	  st[i]='_';
	else
	  st[i]=answer[i];
  st[i]='\0';

  return;
}

void initialize(char array[]){
  int i;

  for(i=0;i<games;i++)
	array[i]=0;

  return;
}

void initializeCharsUsed(char chars[]){
  strcpy(chars,"abcdefghijklmnopqrstuvwxyz");
  return;
}

/* depending on which step in the program/game
   a different character is added to the drawing */
void add(char hangman[rows][cols],int step){
  if(step==0)
    hangman[1][3]=head;	//adds the head
  else if(step==1)
    hangman[2][3]=torso;//appends the torso
  else if(step==2)
    hangman[2][3]=arm;	//replaces the torso
						//with a torso and an arm
  else if(step==3)
    hangman[2][3]=arms;	//replaces above with a
						//torso and two arms
  else if(step==4)
    hangman[3][3]=leg;	//adds one leg
  else if(step==5)
    hangman[3][3]=legs;	//replaces one leg with two

  return;
}

/* adds characters to the input string
   case insensitive */
void add(char *answer, char *progress, char ch){
  int i;
  int len;
  len=strlen(answer);
  for(i=0;i<len;i++)
	if(tolower(ch)==tolower(answer[i]))
	  progress[i]=answer[i];
}

/* prints the double array, character
   by character */
void print(char hangman[rows][cols],char *st,char remaining[]){
  int i,j;

  system("cls");

  for(i=0;i<rows;i++){
	for(j=0;j<cols;j++)
	  cout<<hangman[i][j];
	cout<<endl;
  }
  cout<<st<<endl;
  cout<<remaining<<endl;

  return;
}

/* for the user defined game */
char *getAnswer(int &count){
  char password[80];

  for(count=0;count<80;count++){
   	password[count]=getch();
    if(password[count]=='\r') 
	  break;
	else
   	  printf("*");
  }
  password[count]='\0';
  
  return(strdup(password));
}

char getGuess(){
  char ch;
  cerr<<"Enter Guess: ";
  ch=getch();
  return(ch);
}

int inString(char *st, char ch){
  int i;
  int len;
  len=strlen(st);

  for(i=0;i<len;i++)
	if(tolower(st[i])==tolower(ch))
	  return(1);
  return(0);
}

void getGame(char gamesPlayed[]){
  int i;
  char c;
  char allPlayed;
  FILE *game;

  game=fopen("Hangman (College Edition).pmn","r");
  allPlayed=1;

  if(game==NULL){
	return;
  }
  
  for(i=0;(c=fgetc(game))!=EOF;i++)
	if(c=='*')
	  gamesPlayed[i]=1;
	else{
	  allPlayed=0;
	  gamesPlayed[i]=0;
	}

  if(allPlayed){
	initialize(gamesPlayed);
  }

  fclose(game);
  return;
}

void setGame(char gamesPlayed[]){
  int j;
  FILE *game;

  game=fopen("Hangman (College Edition).pmn","w");

  for(j=0;j<games;j++)
	if(gamesPlayed[j])
	  fprintf(game,"*");
	else
	  fprintf(game," ");

  fclose(game);

  return;
}