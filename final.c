// Argyrokastritis Polydoros 2196

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define S_ARXIKA 0
#define S_GRAMMATA 1
#define S_MIDEN 2
#define S_PSIFIA 3
#define S_AK_TELEIA 4
#define S_MIKROTERO 5
#define S_MEGALITERO 6
#define S_ARXI_SXOLIA 7
#define S_TELOS_SXOLIA 8
#define S_SXOLIA 9

#define keno 0          // space/tab/newline
#define gramma 1        // a..z,A..Z
#define miden 2         // 0
#define psifia 3        // 1,2,3,4,5,6,7,8,9
#define equal 4         // =
#define smaller 5       // <
#define greater 6       // >
#define sin_sign 7      // +
#define plin_sign 8     // -
#define epi_sign 9      // *
#define dia_sign 10     // /
#define ak_teleia 11    // :
#define komma 12        // ,
#define quest_mark 13   // ;
#define left_s 14       // {
#define right_s 15      // }
#define left_p 16       // (
#define right_p 17      // )
#define left_a 18       // [
#define right_a 19      // ]
#define backslash 20    // backslash
#define wrong_char 21   // allos xaraktiras
#define f_end 22        // EOF

#define id_tk 50
#define num_tk 51
#define equal_tk 52
#define not_equal_tk 53
#define smaller_tk 54
#define smaller_equal_tk 55
#define greater_tk 56
#define greater_equal_tk 57
#define sin_sign_tk 58
#define plin_sign_tk 59
#define epi_sign_tk 60
#define dia_sign_tk 61
#define anathesi_tk 62
#define komma_tk 63
#define quest_mark_tk 64
#define left_s_tk 65  //{
#define right_s_tk 66
#define left_p_tk 67  //(
#define right_p_tk 68
#define left_a_tk 69  //[
#define right_a_tk 70
#define f_end_tk 71

#define and_tk 80
#define declare_tk 81
#define do_tk 82
#define else_tk 83
#define enddeclare_tk 84
#define exit_tk 85
#define procedure_tk 86
#define function_tk 87
#define print_tk 88
#define incase_tk 89
#define if_tk 90
#define in_tk 91
#define inout_tk 92
#define not_tk 93
#define forcase_tk 94
#define program_tk 95
#define or_tk 96
#define return_tk 97
#define while_tk 98
#define copy_tk 99
#define when_tk 100
#define call_tk 101

#define ERR1 110          // vrika char pou den anikei sti glossa
#define ERR2 111          // arithmos ektos tou [-32767,32767]
#define ERR3 112          // leipei to * meta to backslash
#define ERR4 113          // leipei to = meta tin :
#define ERR5 114          // vrika EOF eno evlepa sxolia
#define ERR6 115          // vrika psifio h' gramma afou eida 0
#define ERR7 116          // vrika gramma eno evlepa psifia

#define parametros 120
#define cv 121
#define ref 122
#define copy 123
#define metabliti 124
#define proc_func 125
#define procedure 126
#define function 127
#define prosorini 128


char word[31];
int token;
FILE *infile;
int line_number;

int METAVASEIS[10][23]=
{{S_ARXIKA,S_GRAMMATA,S_MIDEN,S_PSIFIA,equal_tk,S_MIKROTERO,S_MEGALITERO,sin_sign_tk,plin_sign_tk,epi_sign_tk,
  dia_sign_tk,S_AK_TELEIA,komma_tk,quest_mark_tk,left_s_tk,right_s_tk,left_p_tk,right_p_tk,left_a_tk,right_a_tk,
  S_ARXI_SXOLIA,ERR1,f_end_tk},
 {id_tk,S_GRAMMATA,S_GRAMMATA,S_GRAMMATA,id_tk,id_tk,id_tk,id_tk,id_tk,id_tk,
  id_tk,id_tk,id_tk,id_tk,id_tk,id_tk,id_tk,id_tk,id_tk,id_tk,
  id_tk,ERR1,id_tk},
 {num_tk,ERR6,ERR6,ERR6,num_tk,num_tk,num_tk,num_tk,num_tk,num_tk,
  num_tk,num_tk,num_tk,num_tk,num_tk,num_tk,num_tk,num_tk,num_tk,num_tk,
  num_tk,ERR1,num_tk},
 {num_tk,ERR7,S_PSIFIA,S_PSIFIA,num_tk,num_tk,num_tk,num_tk,num_tk,num_tk,
  num_tk,num_tk,num_tk,num_tk,num_tk,num_tk,num_tk,num_tk,num_tk,num_tk,
  num_tk,ERR1,num_tk},
 {ERR4,ERR4,ERR4,ERR4,anathesi_tk,ERR4,ERR4,ERR4,ERR4,ERR4,
  ERR4,ERR4,ERR4,ERR4,ERR4,ERR4,ERR4,ERR4,ERR4,ERR4,
  ERR4,ERR1,ERR4},
 {smaller_tk,smaller_tk,smaller_tk,smaller_tk,smaller_equal_tk,smaller_tk,not_equal_tk,smaller_tk,smaller_tk,smaller_tk,
  smaller_tk,smaller_tk,smaller_tk,smaller_tk,smaller_tk,smaller_tk,smaller_tk,smaller_tk,smaller_tk,smaller_tk,
  smaller_tk,ERR1,smaller_tk},
 {greater_tk,greater_tk,greater_tk,greater_tk,greater_equal_tk,greater_tk,greater_tk,greater_tk,greater_tk,greater_tk,
  greater_tk,greater_tk,greater_tk,greater_tk,greater_tk,greater_tk,greater_tk,greater_tk,greater_tk,greater_tk,
  greater_tk,ERR1,greater_tk},
 {ERR3,ERR3,ERR3,ERR3,ERR3,ERR3,ERR3,ERR3,ERR3,S_SXOLIA,
  ERR3,ERR3,ERR3,ERR3,ERR3,ERR3,ERR3,ERR3,ERR3,ERR3,
  ERR3,ERR1,ERR3},
 {S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_TELOS_SXOLIA,
  S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,
  S_ARXIKA,S_SXOLIA,ERR5},
 {S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_TELOS_SXOLIA,
  S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,S_SXOLIA,
  S_SXOLIA,S_SXOLIA,ERR5}};




int metritis,metritis_temps;

struct TETR
{ int AR;
  char AR1[31],AR2[31],AR3[31],AR4[31];
  struct TETR *next;
};
struct TETR_L
{ struct TETR *deiktis;
  struct TETR_L *next;
};

struct TETR *Lstart,*Lend;

int nextquad(void);
void genquad(char a[31],char b[31],char c[31],char d[31]);
void newtemp(char temps[31]);
struct TETR_L *makelist(struct TETR *d);
struct TETR_L *merge(struct TETR_L *List1,struct TETR_L *List2);
void backpatch(struct TETR_L *List,char P[31]);
void dimiourgia_tetradon(char *output);


struct argument
{ int parMode,type;
  char onoma[31];
  struct argument *next;
};

struct M
{ int type,offset;
};
struct S
{ int type,startQuad,framelength;
  struct argument *list;
};
struct P
{ int parMode,offset;
};
struct T
{ int offset;
};

union enosi
{ struct M var;
  struct S sub;
  struct P par;
  struct T tem;
};

struct entity
{ int type;
  union enosi epilogi;
  char onoma[31];
  struct entity *next;
};

struct scope
{ int nestingLevel;
  char onoma[31];
  struct entity *list;
  struct scope *enclosingScope;
};

struct scope *TOP=NULL;


void makeScope(char onoma[31]);
void removeScope(void);
void addEntity(struct entity *en_put);
void addArgument(struct argument *ar_put);
void addstartQuad(void);
void addframelength(void);
int current_offset(void);
void dimiourgia_pinaka_simvolwn(void);



void desmeumeni(void)
{  if (strcmp(word,"and")==0)
      token=and_tk;
   else if (strcmp(word,"call")==0)
      token=call_tk;
   else if (strcmp(word,"declare")==0)
      token=declare_tk;
   else if (strcmp(word,"do")==0)
      token=do_tk;
   else if (strcmp(word,"else")==0)
      token=else_tk;
   else if (strcmp(word,"enddeclare")==0)
      token=enddeclare_tk;
   else if (strcmp(word,"exit")==0)
      token=exit_tk;
   else if (strcmp(word,"procedure")==0)
      token=procedure_tk;
   else if (strcmp(word,"function")==0)
      token=function_tk;
   else if (strcmp(word,"print")==0)
      token=print_tk;
   else if (strcmp(word,"incase")==0)
      token=incase_tk;
   else if (strcmp(word,"if")==0)
      token=if_tk;
   else if (strcmp(word,"in")==0)
      token=in_tk;
   else if (strcmp(word,"inout")==0)
      token=inout_tk;
   else if (strcmp(word,"not")==0)
      token=not_tk;
   else if (strcmp(word,"forcase")==0)
      token=forcase_tk;
   else if (strcmp(word,"program")==0)
      token=program_tk;
   else if (strcmp(word,"or")==0)
      token=or_tk;
   else if (strcmp(word,"return")==0)
      token=return_tk;
   else if (strcmp(word,"while")==0)
      token=while_tk;
   else if (strcmp(word,"copy")==0)
      token=copy_tk;
   else if (strcmp(word,"when")==0)
      token=when_tk;
}

void sfalma(void)
{  if (token==ERR1)
      printf("vrika char pou den anikei sti glossa \n");
   else if (token==ERR2)
      printf("arithmos ektos tou [-32767,32767] \n");
   else if (token==ERR3)
      printf("leipei to * meta to backslash \n");
   else if (token==ERR4)
      printf("leipei to = meta tin : \n");
   else if (token==ERR5)
      printf("vrika EOF eno evlepa sxolia \n");
   else if (token==ERR6)
      printf("vrika psifio h' gramma afou eida 0 \n");
   else if (token==ERR7)
      printf("vrika gramma eno evlepa psifia \n");
   printf("to sfalma entopistike sti grammi: %d \n",line_number);
   exit(-1);
}

int metatropi(char temp)
{  if (temp==' ' || temp=='\t' || temp=='\n')
      return(keno);
   else if (temp>='a' && temp <='z')
      return(gramma);
   else if (temp>='A' && temp <='Z')
      return(gramma);
   else if (temp=='0')
      return(miden);
   else if (temp>='1' && temp <='9')
      return(psifia);
   else if (temp=='=')
      return(equal);
   else if (temp=='<')
      return(smaller);
   else if (temp=='>')
      return(greater);
   else if (temp=='+')
      return(sin_sign);
   else if (temp=='-')
      return(plin_sign);
   else if (temp=='*')
      return(epi_sign);
   else if (temp=='/')
      return(dia_sign);
   else if (temp==':')
      return(ak_teleia);
   else if (temp==',')
      return(komma);
   else if (temp==';')
      return(quest_mark);
   else if (temp=='{')
      return(left_s);
   else if (temp=='}')
      return(right_s);
   else if (temp=='(')
      return(left_p);
   else if (temp==')')
      return(right_p);
   else if (temp=='[')
      return(left_a);
   else if (temp==']')
      return(right_a);
   else if (temp=='\\')
      return(backslash);
   else if (temp==EOF)
      return(f_end);
   else
      return(wrong_char);
}

void lex(void)
{  char temp;
   int x;
   int akeraios;
   int state=S_ARXIKA;
   int counter=0;
   int num_check;

   for (x=0;x<31;x++)
     word[x]='\0';
   while (state>=S_ARXIKA && state<=S_SXOLIA)
   {  temp=getc(infile);
      if (temp=='\n')
	     line_number=line_number+1;

      akeraios=metatropi(temp);
      state=METAVASEIS[state][akeraios];
      if (counter<30 && state!=0 && state!=7 && state!=8 && state!=9)
      {  word[counter]=temp;
         counter=counter+1;
      }
  }
  token=state;

  if (token==num_tk || token==id_tk || token==smaller_tk || token==greater_tk)
  {   if (counter<30)
         word[counter-1]='\0';
      ungetc(temp,infile);

      if (temp=='\n')
         line_number=line_number-1;

      if (token==id_tk)
         desmeumeni();
      if (token==num_tk)
      {  num_check=atoi(word);
	     if (num_check>=32769)
            token=ERR2;
      }
  }

  if (token==ERR1 || token==ERR2 || token==ERR3 || token==ERR4 || token==ERR5 || token==ERR6 || token==ERR7)
     sfalma();
}



// SINTAKTIKOS ANALITIS
void program(void);
void block(char onoma[31],int main_check);
void declarations(void);
void varlist(void);
void subprograms(void);
void func(void);
void funcbody(char onoma[31]);
void formalpars(void);
void formalparlist(void);
void formalparitem(void);
void sequence(void);
void brackets_seq(void);
void brack_or_stat(void);
void statement(void);
void assignment_stat(void);
void if_stat(void);
void elsepart(void);
void do_while_stat(void);
void exit_stat(void);
void return_stat(void);
void print_stat(void);
void while_stat(void);
void incase_stat(void);
void forcase_stat(void);
void call_stat(void);
void actualpars(int what,char onoma[31]);
void actualparlist(void);
void actualparitem(void);
void condition(struct TETR_L **CTRUE,struct TETR_L **CFALSE);
void boolterm(struct TETR_L **BTTRUE,struct TETR_L **BTFALSE);
void boolfactor(struct TETR_L **BFTRUE,struct TETR_L **BFFALSE);
void expression(char E[31]);
void term(char T[31]);
void factor(char F[31]);
void idtail(int what,char onoma[31]);
void relational_oper(char R[31]);
void add_oper(char sin_plin[31]);
void mul_oper(char epi_dia[31]);
void optional_sign(char sin_plin[31]);

void program(void)
{  char onoma[31];
   if(token==program_tk)
   {   lex();
       if(token==id_tk)
	   {  strcpy(onoma,word);
	      lex();
	      block(onoma,1);
	   }
	   else
	   {  printf("Lathos. De vrethike to onoma tou programmatos\n");
          printf("to sfalma entopistike sti grammi: %d \n",line_number);
          exit(1);
	   }
   }
   else
   {   printf("Lathos. De vrethike to program\n");
       printf("to sfalma entopistike sti grammi: %d \n",line_number);
       exit(1);
   }
}

void block(char onoma[31],int main_check)
{  if(token==left_s_tk)
   {   lex();

	   if(main_check==1)
         makeScope(onoma);

	   declarations();
	   subprograms();
	   genquad("begin_block",onoma,"_","_");

       addstartQuad();
	   sequence();

	   if (main_check==1)
	      genquad("halt","_","_","_");
	   genquad("end_block",onoma,"_","_");

	   addframelength();
       dimiourgia_pinaka_simvolwn();
	   removeScope();

	   if(token==right_s_tk)
	   {  lex();
	   }
	   else
	   {  printf("Lathos. De vrethike to }\n");
          printf("to sfalma entopistike sti grammi: %d \n",line_number);
          exit(1);
	   }
   }
   else
   {   printf("Lathos. De vrethike to {\n");
       printf("to sfalma entopistike sti grammi: %d \n",line_number);
       exit(1);
   }
}

void declarations(void)
{  if(token==declare_tk)
   {   lex();
       varlist();
	   if(token==enddeclare_tk)
	   {  lex();
	   }
	   else
	   {  printf("Lathos. De vrethike to enddeclare\n");
          printf("to sfalma entopistike sti grammi: %d \n",line_number);
          exit(1);
	   }
   }

}


void varlist(void)
{  struct entity *en;

   if(token==id_tk)
   {   en=( struct entity * )malloc( sizeof(struct entity) );
       en->type=metabliti;
       en->epilogi.var.offset=current_offset();
       strcpy(en->onoma,word);
       en->next=NULL;
       addEntity(en);
       lex();

       while(token==komma_tk)
	   {  lex();
	      if(token==id_tk)
		  {  en=( struct entity * )malloc( sizeof(struct entity) );
             en->type=metabliti;
             en->epilogi.var.offset=current_offset();
             strcpy(en->onoma,word);
             en->next=NULL;
             addEntity(en);
             lex();
		  }
		  else
		  {  printf("Lathos. De vrethike to onoma metavlitis\n");
             printf("to sfalma entopistike sti grammi: %d \n",line_number);
             exit(1);
		  }
	   }
   }

}

void subprograms(void)
{  while(token==procedure_tk || token==function_tk)
       func();
}

void func(void)
{  char onoma[31];
   struct entity *en;

   if(token==procedure_tk)
   {   lex();

       en=( struct entity * )malloc( sizeof(struct entity) );
	   en->type=proc_func;
       en->epilogi.sub.type=procedure;
       en->epilogi.sub.list=NULL;
       strcpy(en->onoma,word);
       en->next=NULL;
	   addEntity(en);

       if(token==id_tk)
	   {  strcpy(onoma,word);
	      lex();
	      funcbody(onoma);
	   }
	   else
	   {  printf("Lathos. De vrethike to onoma metavlitis\n");
          printf("to sfalma entopistike sti grammi: %d \n",line_number);
          exit(1);
	   }
   }
   else if(token==function_tk)
   {   lex();

       en=( struct entity * )malloc( sizeof(struct entity) );
	   en->type=proc_func;
       en->epilogi.sub.type=function;
       en->epilogi.sub.list=NULL;
       strcpy(en->onoma,word);
       en->next=NULL;
	   addEntity(en);

       if(token==id_tk)
	   {  strcpy(onoma,word);
          lex();
	      funcbody(onoma);
	   }
	   else
	   {  printf("Lathos. De vrethike to onoma metavlitis\n");
          printf("to sfalma entopistike sti grammi: %d \n",line_number);
          exit(1);
	   }
   }
}

void funcbody(char onoma[31])
{  struct argument *ar;
   struct entity *en,*en_last;

   formalpars();

   makeScope(onoma);

   en=TOP->enclosingScope->list;
   en_last=en;
   en=en->next;
   while(en!=NULL)
   {  en_last=en;
      en=en->next;
   }
   ar=en_last->epilogi.sub.list;

   while(ar!=NULL)
   {  en=( struct entity * )malloc( sizeof(struct entity) );
      en->type=parametros;
      en->epilogi.par.parMode=ar->parMode;
      en->epilogi.par.offset=current_offset();
      strcpy(en->onoma,ar->onoma);
      en->next=NULL;
      addEntity(en);

      ar=ar->next;
   }

   block(onoma,2);
}

void formalpars(void)
{  if(token==left_p_tk)
   {   lex();
       formalparlist();
	   if(token==right_p_tk)
	   {  lex();
	   }
	   else
	   {  printf("Lathos. De vrethike to )\n");
          printf("to sfalma entopistike sti grammi: %d \n",line_number);
          exit(1);
	   }
   }

}

void formalparlist(void)
{  formalparitem();
   while(token==komma_tk)
   {   lex();
       formalparitem();
   }
}

void formalparitem(void)
{  struct argument *ar;
   int pMode;

   if(token==in_tk || token==inout_tk || token==copy_tk)
   {   if(token==in_tk)
         pMode=cv;
       else if(token==inout_tk)
         pMode=ref;
       else
         pMode=copy;

       lex();

       ar=( struct argument * )malloc( sizeof(struct argument) );
       ar->parMode=pMode;
       strcpy(ar->onoma,word);
       ar->next=NULL;
       addArgument(ar);

       if(token==id_tk)
       {  lex();
       }
       else
       {  printf("Lathos. De vrethike to onoma metavlitis\n");
          printf("to sfalma entopistike sti grammi: %d \n",line_number);
          exit(1);
       }
   }
   else
   {   printf("Lathos. De vrethike kapoia desmeumenh leksh apo tis in,inout kai copy \n");
       printf("to sfalma entopistike sti grammi: %d \n",line_number);
       exit(1);
   }

}

void sequence(void)
{  statement();
   while(token==quest_mark_tk)
   {   lex();
       statement();
   }
}

void brackets_seq(void)
{  if(token==left_s_tk)
   {	lex();
	sequence();
        if(token==right_s_tk)
	   {   lex();
	   }
	   else
	   {    printf("Lathos. De vrethike to }\n");
            printf("to sfalma entopistike sti grammi: %d \n",line_number);
                exit(1);
	   }
   }
}

void brack_or_stat(void)
{  if(token==left_s_tk)
      brackets_seq();
   else
      statement();
}

void statement(void)
{  if(token==id_tk)
	 assignment_stat();
   else if(token==if_tk)
	 if_stat();
   else if(token==while_tk)
	 while_stat();
   else if(token==do_tk)
	 do_while_stat();
   else  if(token==exit_tk)
     exit_stat();
   else if(token==incase_tk)
     incase_stat();
   else if(token==forcase_tk)
	 forcase_stat();
   else if(token==call_tk)
	 call_stat();
   else if(token==return_tk)
     return_stat();
   else if(token==print_tk)
     print_stat();
}

void assignment_stat(void)
{  char id[31],E[31];

   if(token==id_tk)
   {  strcpy(id,word);
      lex();
      if(token==anathesi_tk)
      {     lex();
            expression(E);
			genquad(":=",E,"_",id);
      }
      else
      {
            printf("uparxei la8os dioti den vre8hke h ekxwrhsh ':='.\n");
			printf("to sfalma entopistike sti grammi: %d \n",line_number);
            exit(1);
      }
  }
}

void if_stat(void)
{  char P[31];
   struct TETR_L *CTRUE,*CFALSE,*IF_List;

   if(token==if_tk)
   {  lex();
      if (token==left_p_tk)
	  {    lex();
           condition(&CTRUE,&CFALSE);

		   sprintf(P,"%d",nextquad());
		   backpatch(CTRUE,P);

           if(token==right_p_tk)
           {    lex();
                brack_or_stat();

				genquad("jump","_","_","_");
				IF_List=makelist(Lend);
				sprintf(P,"%d",nextquad());
				backpatch(CFALSE,P);

                elsepart();
				sprintf(P,"%d",nextquad());
				backpatch(IF_List,P);

           }
           else
           {    printf("Lathos. De vrethike to )\n");
		        printf("to sfalma entopistike sti grammi: %d \n",line_number);
                exit(1);
           }
      }
	  else
      {    printf("Lathos. De vrethike to (\n");
	       printf("to sfalma entopistike sti grammi: %d \n",line_number);
           exit(1);
      }
   }
}

void elsepart(void)
{  if(token==else_tk)
   {	lex();
	    brack_or_stat();
   }
}

void do_while_stat(void)
{  char P[31],Z[31];
   struct TETR_L *CTRUE,*CFALSE;

   if(token==do_tk)
   {  lex();

      sprintf(P,"%d",nextquad());

      brack_or_stat();
      if(token==while_tk)
      { 	lex();
    	    if (token==left_p_tk)
			{    lex();
                 condition(&CTRUE,&CFALSE);

				 backpatch(CTRUE,P);
				 sprintf(Z,"%d",nextquad());
				 backpatch(CFALSE,Z);

                 if(token==right_p_tk)
                 {    lex();
                 }
                 else
                 {    printf("Lathos. De vrethike to )\n");
				      printf("to sfalma entopistike sti grammi: %d \n",line_number);
                      exit(1);
                 }
			}
			else
            {    printf("Lathos. De vrethike to (\n");
			     printf("to sfalma entopistike sti grammi: %d \n",line_number);
                 exit(1);
            }
	  }
	  else
      {    printf("Lathos. De vrethike to while\n");
	       printf("to sfalma entopistike sti grammi: %d \n",line_number);
           exit(1);
      }
   }
}

void exit_stat(void)
{  if(token==exit_tk)
   {	lex();
   }
}

void return_stat(void)
{  char E[31];

   if(token==return_tk)
   {   lex();
       if (token==left_p_tk)
       {   lex();
           expression(E);
		   genquad("retv",E,"_","_");
           if(token==right_p_tk)
           {    lex();
           }
           else
           {    printf("Lathos. De vrethike to )\n");
		        printf("to sfalma entopistike sti grammi: %d \n",line_number);
                exit(1);
           }
	   }
	   else
       {    printf("Lathos. De vrethike to (\n");
	        printf("to sfalma entopistike sti grammi: %d \n",line_number);
            exit(1);
       }
   }
}

void print_stat(void)
{  char E[31];

   if(token==print_tk)
   {   lex();
       if (token==left_p_tk)
       {   lex();
           expression(E);
		   genquad("out",E,"_","_");
           if(token==right_p_tk)
           {    lex();
           }
           else
           {    printf("Lathos. De vrethike to )\n");
		        printf("to sfalma entopistike sti grammi: %d \n",line_number);
                exit(1);
           }
	   }
	   else
       {    printf("Lathos. De vrethike to (\n");
	        printf("to sfalma entopistike sti grammi: %d \n",line_number);
            exit(1);
       }
   }
}

void while_stat(void)
{   char P[31],Z[31];
    struct TETR_L *CTRUE,*CFALSE;

    if (token==while_tk)
    {   lex();
	    if (token==left_p_tk)
        {   lex();

		    sprintf(P,"%d",nextquad());

            condition(&CTRUE,&CFALSE);

			sprintf(Z,"%d",nextquad());
			backpatch(CTRUE,Z);

            if(token==right_p_tk)
            {   lex();
		        brack_or_stat();

				genquad("jump","_","_",P);
				sprintf(Z,"%d",nextquad());
				backpatch(CFALSE,Z);
            }
            else
            {    printf("Lathos. De vrethike to )\n");
			     printf("to sfalma entopistike sti grammi: %d \n",line_number);
                 exit(1);
            }
	    }
	    else
        {    printf("Lathos. De vrethike to (\n");
		     printf("to sfalma entopistike sti grammi: %d \n",line_number);
             exit(1);
        }
	}
}

void incase_stat(void)
{   char P[31],Z[31],w[31];
    struct TETR_L *CTRUE,*CFALSE;

    if(token==incase_tk)
    {    lex();

	     newtemp(w);
		 sprintf(Z,"%d",nextquad());
		 genquad(":=","1","_",w);

         if(token==left_s_tk)
         {   lex();
             while(token==when_tk)
             {  lex();
                 if(token==left_p_tk)
                 {    lex();
                      condition(&CTRUE,&CFALSE);

					  sprintf(P,"%d",nextquad());
					  backpatch(CTRUE,P);
					  genquad(":=","0","_",w);

                      if(token==right_p_tk)
                      {   lex();
                          brack_or_stat();

						  sprintf(P,"%d",nextquad());
						  backpatch(CFALSE,P);
                      }
	                  else
                      {   printf("Lathos. De vrethike to )\n");
		                  printf("to sfalma entopistike sti grammi: %d \n",line_number);
                          exit(1);
                      }
			     }
				 else
                 {   printf("Lathos. De vrethike to (\n");
		             printf("to sfalma entopistike sti grammi: %d \n",line_number);
                     exit(1);
                 }
			 }
             if(token==right_s_tk)
             {    lex();
			      genquad("=",w,"0",Z);
             }
             else
             {    printf("Lathos. De vrethike to }\n");
		          printf("to sfalma entopistike sti grammi: %d \n",line_number);
                  exit(1);
		     }
         }
         else
         {     printf("Lathos. De vrethike to {\n");
		       printf("to sfalma entopistike sti grammi: %d \n",line_number);
               exit(1);
	     }
     }
}

void forcase_stat(void)
{   char P[31],Z[31];
    struct TETR_L *CTRUE,*CFALSE;

    if(token==forcase_tk)
    {    lex();

	     sprintf(Z,"%d",nextquad());

         if(token==left_s_tk)
         {   lex();
             while(token==when_tk)
             {   lex();
                 if(token==left_p_tk)
                 {    lex();
                      condition(&CTRUE,&CFALSE);

					  sprintf(P,"%d",nextquad());
					  backpatch(CTRUE,P);

                      if(token==right_p_tk)
                      {   lex();
                          brack_or_stat();

						  genquad("jump","_","_",Z);
						  sprintf(P,"%d",nextquad());
						  backpatch(CFALSE,P);
                      }
	                  else
                      {   printf("Lathos. De vrethike to )\n");
		                  printf("to sfalma entopistike sti grammi: %d \n",line_number);
                          exit(1);
                      }
			     }
				 else
                 {   printf("Lathos. De vrethike to (\n");
		             printf("to sfalma entopistike sti grammi: %d \n",line_number);
                     exit(1);
                 }
			 }
             if(token==right_s_tk)
             {    lex();
             }
             else
             {    printf("Lathos. De vrethike to }\n");
		          printf("to sfalma entopistike sti grammi: %d \n",line_number);
                  exit(1);
		     }
         }
         else
         {     printf("Lathos. De vrethike to {\n");
		       printf("to sfalma entopistike sti grammi: %d \n",line_number);
               exit(1);
	     }
     }
}

void call_stat(void)
{   char onoma[31];
    if (token==call_tk)
    {    lex();
         if (token==id_tk)
         {     strcpy(onoma,word);
		       lex();
               actualpars(0,onoma);
			   genquad("call",onoma,"_","_");
         }
         else
         {     printf("Lathos. De vrethike to onoma diadikasias\n");
		       printf("to sfalma entopistike sti grammi: %d \n",line_number);
               exit(1);
         }
    }
}

void actualpars(int what,char onoma[31])
{  char w[31];
   if (token==left_p_tk)
   {	lex();
	    actualparlist();
	    if(what==1)
		{    newtemp(w);
			 genquad("par",w,"RET","_");
			 genquad("call",onoma,"_","_");
			 strcpy(onoma,w);
		}
		if(token==right_p_tk)
		{    lex();
        }
        else
        {    printf("Lathos. De vrethike to )\n");
		     printf("to sfalma entopistike sti grammi: %d \n",line_number);
                exit(1);
        }
   }
}

void actualparlist(void)
{   actualparitem();
    while(token==komma_tk)
	{   lex();
	       actualparitem();
	}
}

void actualparitem(void)
{  char E[31];

   if(token==in_tk)
   {   lex();
       expression(E);
	   genquad("par",E,"CV","_");
   }
   else if(token==inout_tk)
   {   lex();
       if(token==id_tk)
       {   genquad("par",word,"REF","_");
	       lex();
	   }
	   else
	   {   printf("Lathos. De vrethike kapoio onoma metavlitis \n");
           printf("to sfalma entopistike sti grammi: %d \n",line_number);
           exit(1);
       }
   }
   else if(token==copy_tk)
   {   lex();
       if(token==id_tk)
       {   genquad("par",word,"COPY","_");
	       lex();
	   }
	   else
	   {   printf("Lathos. De vrethike kapoio onoma metavlitis \n");
           printf("to sfalma entopistike sti grammi: %d \n",line_number);
           exit(1);
       }
   }
   else
   {    printf("Lathos. De vrethike kapoia desmeumenh leksh apo tis in,inout kai copy \n");
        printf("to sfalma entopistike sti grammi: %d \n",line_number);
        exit(1);
   }
}

void condition(struct TETR_L **CTRUE,struct TETR_L **CFALSE)
{  char P[31];
   struct TETR_L *BTTRUE_1,*BTFALSE_1,*BTTRUE_2,*BTFALSE_2;

   boolterm(&BTTRUE_1,&BTFALSE_1);
   *CTRUE=BTTRUE_1;
   *CFALSE=BTFALSE_1;
   while(token==or_tk)
   {   lex();

       sprintf(P,"%d",nextquad());
       backpatch(*CFALSE,P);
       boolterm(&BTTRUE_2,&BTFALSE_2);

	   *CTRUE=merge(*CTRUE,BTTRUE_2);
	   *CFALSE=BTFALSE_2;
   }
}

void boolterm(struct TETR_L **BTTRUE,struct TETR_L **BTFALSE)
{  char P[31];
   struct TETR_L *BFTRUE_1,*BFFALSE_1,*BFTRUE_2,*BFFALSE_2;

   boolfactor(&BFTRUE_1,&BFFALSE_1);
   *BTTRUE=BFTRUE_1;
   *BTFALSE=BFFALSE_1;
   while(token==and_tk)
   {   lex();

       sprintf(P,"%d",nextquad());
       backpatch(*BTTRUE,P);
       boolfactor(&BFTRUE_2,&BFFALSE_2);

	   *BTFALSE=merge(*BTFALSE,BFFALSE_2);
	   *BTTRUE=BFTRUE_2;
   }
}

void boolfactor(struct TETR_L **BFTRUE,struct TETR_L **BFFALSE)
{  struct TETR_L *CTRUE,*CFALSE;
   char E1[31],E2[31],R[31];

   if (token==not_tk)
   {    lex();
        if (token==left_a_tk)
		{   lex();
            condition(&CTRUE,&CFALSE);
			*BFTRUE=CFALSE;
            *BFFALSE=CTRUE;
            if (token==right_a_tk)
                lex();
            else
			{    printf("Lathos.Den vrethike to ]\n");
			     printf("to sfalma entopistike sti grammi: %d \n",line_number);
                 exit(1);
            }
        }
        else
		{        printf("Lathos.Den vrethike to [ \n");
                 exit(1);
        }
    }
    else if(token==left_a_tk)
    {   lex();
        condition(&CTRUE,&CFALSE);
		*BFTRUE=CTRUE;
		*BFFALSE=CFALSE;
        if (token==right_a_tk)
            lex();
        else
		{   printf("Lathos.Den vrethike to ]\n");
		    printf("to sfalma entopistike sti grammi: %d \n",line_number);
            exit(1);
        }
    }
    else
    {   expression(E1);
        relational_oper(R);
        expression(E2);

		genquad(R,E1,E2,"_");
		*BFTRUE=makelist(Lend);

		genquad("jump","_","_","_");
		*BFFALSE=makelist(Lend);
    }
}

void expression(char E[31])
{   char sin_plin[31],w[31],T1[31],T2[31];

    optional_sign(sin_plin);
    term(T1);
    while(token==sin_sign_tk || token==plin_sign_tk)
    {   add_oper(sin_plin);
        term(T2);

        newtemp(w);
		genquad(sin_plin,T1,T2,w);
		strcpy(T1,w);
    }
	strcpy(E,T1);
}

void term(char T[31])
{   char epi_dia[31],w[31],F1[31],F2[31];

    factor(F1);
    while(token==epi_sign_tk || token==dia_sign_tk)
    {   mul_oper(epi_dia);
        factor(F2);

		newtemp(w);
		genquad(epi_dia,F1,F2,w);
		strcpy(F1,w);
    }
	strcpy(T,F1);
}

void factor(char F[31])
{  char E[31];

   if (token==num_tk)
   {    strcpy(F,word);
        lex();
   }
   else if (token==left_p_tk)
   {    lex();
        expression(E);
		strcpy(F,E);
        if (token==right_p_tk)
        {    lex();
		}
        else
        {    printf("Lathos. De vrethike to )\n");
		     printf("to sfalma entopistike sti grammi: %d \n",line_number);
             exit(1);
        }
   }
   else if (token==id_tk)
   {    strcpy(F,word);
        lex();
        idtail(1,F);
   }
}

void idtail(int what,char onoma[31])
{    actualpars(what,onoma);
}

void relational_oper(char R[31])
{    if (token==equal_tk || token==smaller_tk || token==greater_tk || token==smaller_equal_tk || token==greater_equal_tk  || token==not_equal_tk)
     {  strcpy(R,word);
        lex();
     }
    else
    {   printf("Lathos.Den vrethike =,<,>,<=,>=,<> .\n");
	    printf("to sfalma entopistike sti grammi: %d \n",line_number);
        exit(1);
    }
}

void add_oper(char sin_plin[31])
{  if (token==sin_sign_tk || token==plin_sign_tk)
   {	strcpy(sin_plin,word);
        lex();
   }
   else
   {    printf("Lathos.Den vrethike + - \n");
        printf("to sfalma entopistike sti grammi: %d \n",line_number);
        exit(1);
   }
}

void mul_oper(char epi_dia[31])
{  if (token==epi_sign_tk || token==dia_sign_tk)
   { 	strcpy(epi_dia,word);
        lex();
   }
   else
   {    printf("Lathos.Den vrethike * / \n");
        printf("to sfalma entopistike sti grammi: %d \n",line_number);
        exit(1);
   }
}

void optional_sign(char sin_plin[31])
{   if (token==sin_sign_tk || token==plin_sign_tk)
    {    add_oper(sin_plin);
    }
}


int main(int argc,char *argv[])
{  int rrr;

   Lstart=NULL;
   Lend=NULL;
   metritis=100;
   metritis_temps=1;
   infile=fopen("test1.st","r");
   line_number=1;
   lex();
   program();
   dimiourgia_tetradon("2046_2196_test1.int");
   printf("test1.st ended\n\n\n");
   scanf("%d",&rrr);

   Lstart=NULL;
   Lend=NULL;
   metritis=100;
   metritis_temps=1;
   infile=fopen("test2.st","r");
   line_number=1;
   lex();
   program();
   dimiourgia_tetradon("2046_2196_test2.int");
   printf("test2.st ended\n\n\n");
   scanf("%d",&rrr);

   Lstart=NULL;
   Lend=NULL;
   metritis=100;
   metritis_temps=1;
   infile=fopen("test3.st","r");
   line_number=1;
   lex();
   program();
   dimiourgia_tetradon("2046_2196_test3.int");
   printf("test3.st ended\n\n\n");
   scanf("%d",&rrr);

   Lstart=NULL;
   Lend=NULL;
   metritis=100;
   metritis_temps=1;
   infile=fopen("test4.st","r");
   line_number=1;
   lex();
   program();
   dimiourgia_tetradon("2046_2196_test4.int");
   printf("test4.st ended\n\n\n");
   scanf("%d",&rrr);

   Lstart=NULL;
   Lend=NULL;
   metritis=100;
   metritis_temps=1;
   infile=fopen("test5.st","r");
   line_number=1;
   lex();
   program();
   dimiourgia_tetradon("2046_2196_test5.int");
   printf("test5.st ended\n\n\n");
   scanf("%d",&rrr);

}




int nextquad(void)
{   int count;

    count=metritis;
    return(count);
}

void genquad(char a[31],char b[31],char c[31],char d[31])
{   int count;
    struct TETR *x;

    count=nextquad();
    metritis+=10;
    x=(struct TETR *)malloc(sizeof(struct TETR));

    if (Lend==NULL)
    {    Lstart=x;
         Lend=x;
    }
    else
    {    Lend->next=x;
         Lend=x;
    }

    Lend->AR=count;
    strcpy(Lend->AR1,a);
    strcpy(Lend->AR2,b);
    strcpy(Lend->AR3,c);
    strcpy(Lend->AR4,d);
    Lend->next=NULL;
    return;
}

void newtemp(char temps[31])
{   int count;
    struct entity *en;

    count=metritis_temps;
    sprintf(temps,"T_%d",count);
    metritis_temps++;

    en=(struct entity *)malloc(sizeof(struct entity));
    en->type=prosorini;
    en->epilogi.tem.offset=current_offset();
    strcpy(en->onoma,temps);
    en->next=NULL;
    addEntity(en);
    return;
}


struct TETR_L *makelist(struct TETR *d)
{   struct TETR_L *q;

    q=(struct TETR_L *)malloc(sizeof(struct TETR_L));
    q->deiktis=d;
    q->next=NULL;
    return(q);
}

struct TETR_L *merge(struct TETR_L *List1,struct TETR_L *List2)
{   struct TETR_L *q;

    q=List1;
    while(q!=NULL)
    {    if(q->next==NULL)
         {    q->next=List2;
              break;
         }
         else
         {    q=q->next;
         }
    }
    return(List1);
}

void backpatch(struct TETR_L *List,char P[31])
{   struct TETR_L *q;

    q=List;
    while(q!=NULL)
    {    strcpy(q->deiktis->AR4,P);
         q=q->next;
    }
    return;
}

void dimiourgia_tetradon(char *output)
{   struct TETR *x;
    FILE *outfile=fopen(output,"w");

    x=Lstart;
    while(x!=Lend)
    {    fprintf(outfile,"%d %s %s %s %s \n",x->AR,x->AR1,x->AR2,x->AR3,x->AR4);
	     x=x->next;
    }
    fprintf(outfile,"%d %s %s %s %s \n",Lend->AR,Lend->AR1,Lend->AR2,Lend->AR3,Lend->AR4);
    return;
}




void makeScope(char onoma[31])
{  struct scope *sc,*sctest;

   sctest=TOP;
   sc=( struct scope * )malloc( sizeof(struct scope) );
   if(sctest!=NULL)
   {  sc->nestingLevel=TOP->nestingLevel+1;
      strcpy(sc->onoma,onoma);
      sc->list=NULL;
      sc->enclosingScope=TOP;
	  TOP=sc;
   }
   else
   {  sc->nestingLevel=0;
      strcpy(sc->onoma,onoma);
      sc->list=NULL;
      sc->enclosingScope=NULL;
	  TOP=sc;
   }
   return;
}

void removeScope(void)
{  struct scope *sc_del;
   struct entity *en,*en_del;
   struct argument *ar,*ar_del;

   en=TOP->list;
   en_del=en;
   while(en_del!=NULL)
   {  if(en->type==proc_func)
      {  ar=en->epilogi.sub.list;
         ar_del=ar;
         while(ar_del!=NULL)
         { ar=ar->next;
           free(ar_del);
           ar_del=ar;
         }
      }
      en=en->next;
      free(en_del);
      en_del=en;
   }
   sc_del=TOP;
   TOP=TOP->enclosingScope;
   free(sc_del);
   return;
}

void addEntity(struct entity *en_put)
{  struct entity *en,*en_last;

   en=TOP->list;
   if(en!=NULL)
   {  en_last=en;
      en=en->next;
      while(en!=NULL)
      {  en_last=en;
         en=en->next;
      }
      en_last->next=en_put;
   }
   else
      TOP->list=en_put;
   return;
}

void addArgument(struct argument *ar_put)
{  struct entity *en,*en_last;
   struct argument *ar,*ar_last;

   en=TOP->list;
   en_last=en;
   en=en->next;
   while(en!=NULL)
   {  en_last=en;
      en=en->next;
   }

   if(en_last->epilogi.sub.list!=NULL)
   {  ar=en_last->epilogi.sub.list;
      ar_last=ar;
      while(ar!=NULL)
      {  ar_last=ar;
         ar=ar->next;
      }
      ar_last->next=ar_put;
   }
   else
      en_last->epilogi.sub.list=ar_put;
   return;
}

void addstartQuad(void)
{  struct scope *sc;
   struct entity *en,*en_last;

   sc=TOP->enclosingScope;
   if(sc!=NULL)
   {  en=sc->list;
      en_last=en;
      en=en->next;
      while(en!=NULL)
      {  en_last=en;
         en=en->next;
      }
      en_last->epilogi.sub.startQuad=nextquad();
   }
   return;
}

void addframelength(void)
{  struct scope *sc;
   struct entity *en,*en_last;
   int offset;

   offset=current_offset();

   sc=TOP->enclosingScope;
   if(sc!=NULL)
   {  en=sc->list;
      en_last=en;
      en=en->next;
      while(en!=NULL)
      {  en_last=en;
         en=en->next;
      }
      en_last->epilogi.sub.framelength=offset;
   }
   return;
}

int current_offset(void)
{  struct entity *en;
   int offset=12;

   en=TOP->list;
   while(en!=NULL)
   {  if(en->type!=proc_func)
        offset+=4;
      en=en->next;
   }
   return(offset);
}

void dimiourgia_pinaka_simvolwn(void)
{  struct scope *sc=TOP;
   struct entity *en;
   struct argument *ar;

   while(sc!=NULL)
   {  en=sc->list;
      printf("To scope einai: %s \n",sc->onoma);
      while(en!=NULL)
      {  if(en->type == parametros && en->epilogi.par.parMode == cv)
            printf("Parametros(cv): %s,%d ",en->onoma,en->epilogi.par.offset);
         else if(en->type == parametros && en->epilogi.par.parMode == ref)
            printf("Parametros(ref): %s,%d ",en->onoma,en->epilogi.par.offset);
         else if(en->type == parametros && en->epilogi.par.parMode == copy)
            printf("Parametros(copy): %s,%d ",en->onoma,en->epilogi.par.offset);
         else if (en->type==metabliti)
            printf("Metabliti: %s,%d ",en->onoma,en->epilogi.var.offset);
         else if(en->type==prosorini)
            printf("Prosorini: %s,%d ",en->onoma,en->epilogi.tem.offset);
         else if(en->type==proc_func && en->epilogi.sub.type==procedure)
         {  printf("Synartisi: %s,%d,%d   ",en->onoma,en->epilogi.sub.startQuad,en->epilogi.sub.framelength);
            ar= en->epilogi.sub.list;
            while(ar!=NULL)
            {  if(ar->parMode==cv)
                 printf("%s(cv) ",ar->onoma);
               else if(ar->parMode==ref)
                 printf("%s(ref) ",ar->onoma);
               else
                 printf("%s(copy) ",ar->onoma);
            ar=ar->next;
            }
         }
         else if(en->type==proc_func && en->epilogi.sub.type==function)
         {  printf("Diadikasia: %s,%d,%d   ",en->onoma,en->epilogi.sub.startQuad,en->epilogi.sub.framelength);
            ar= en->epilogi.sub.list;
            while(ar!=NULL)
            {  if(ar->parMode==cv)
                 printf("%s(cv) ",ar->onoma);
               else if(ar->parMode==ref)
                 printf("%s(ref) ",ar->onoma);
               else
                 printf("%s(copy) ",ar->onoma);
            ar=ar->next;
            }
         }
         en=en->next;
         printf("\n");
       }
       sc=sc->enclosingScope;
       printf("\n\n");
   }
   printf("\n\n\n");
}



struct entity *search_entity(char onoma[31])
{  struct scope *sc;
   struct entity *en;

   sc=TOP;
   while(sc!=NULL)
   {   en=sc->list;
	   while(en!=NULL)
	   {   if(strcmp(en->onoma,onoma)==0)
		      return(en);
		   en=en->next;
	   }
	   sc=sc->enclosingScope;
   }
}

void gnlvcode(int offset,FILE *final_test)
{
    fprintf(final_test,"movi R[255],M[4+R[0]]\n");

    /*oses fores xreiastei
         fprintf(final_test,"movi R[255],M[4+R[255]]\n");	*/

    fprintf(final_test,"movi R[254],%d\n",offset);
    fprintf(final_test,"addi R[255],R[254],R[255]\n");

}

void loadvr(char v[31],int r)
{   struct entity *en;

    en=search_entity(v);

    /*an einai arithmos
      fprintf(final_test,"movi R[%d],%s\n",r,v);*/

    /*an global metavliti
      fprintf(final_test,"movi R[%d],M[600+%d]\n",r,en->epilogi.var.offset);*/

    /*an topiki/typiki me timi kai idio vathos/prosorini
      fprintf(final_test,"movi R[%d],M[%d+R[0]]\n",r,en->epilogi.var.offset);
	  fprintf(final_test,"movi R[%d],M[%d+R[0]]\n",r,en->epilogi.par.offset);
	  fprintf(final_test,"movi R[%d],M[%d+R[0]]\n",r,en->epilogi.tem.offset);*/

	/*an typiki me anafora kai idio vathos
	  fprintf(final_test,"movi R[255],M[%d+R[0]]\n",en->epilogi.par.offset);
      fprintf(final_test,"movi R[%d],M[R[255]]\n",r);*/

	/*an topiki/typiki me timi kai mikrotero vathos
      gnlvcode(en->epilogi.var.offset);
      fprintf(final_test,"movi R[%d],M[R[255]]\n",r);

	  gnlvcode(en->epilogi.par.offset);
      fprintf(final_test,"movi R[%d],M[R[255]]\n",r);*/


	/*an typiki me anafora kai mikrotero vathos
      gnlvcode(en->epilogi.par.offset);
      fprintf(final_test,"movi R[255],M[R[255]]\n");
      fprintf(final_test,"movi R[%d],M[R[255]]\n",r);*/
}

void storerv(int r,char v[31])
{   struct entity *en;

    en=search_entity(v);

    /*an global metavliti
      fprintf(final_test,"movi M[600+%d],R[%d]\n",en->epilogi.var.offset,r);*/

    /*an topiki/typiki me timi kai idio vathos/prosorini
      fprintf(final_test,"movi M[%d+R[0]],R[%d]\n",en->epilogi.var.offset,r);
	  fprintf(final_test,"movi M[%d+R[0]],R[%d]\n",en->epilogi.par.offset,r);
	  fprintf(final_test,"movi M[%d+R[0]],R[%d]\n",en->epilogi.tem.offset,r);*/

	/*an typiki me anafora kai idio vathos
	  fprintf(final_test,"movi R[255],M[%d+R[0]]\n",en->epilogi.par.offset);
      fprintf(final_test,"movi M[R[255]],R[%d]\n",r);*/

	/*an topiki/typiki me timi kai mikrotero vathos
      gnlvcode(en->epilogi.var.offset);
      fprintf(final_test,"movi M[R[255]],R[%d]\n",r);

	  gnlvcode(en->epilogi.par.offset);
      fprintf(final_test,"movi M[R[255]],R[%d]\n",r);*/


	/*an typiki me anafora kai mikrotero vathos
      gnlvcode(en->epilogi.par.offset);
      fprintf(final_test,"movi R[255],M[R[255]]\n");
      fprintf(final_test,"movi M[R[255]],R[%d]\n",r);*/


}

void final_code(struct TETR *tetr,FILE *final_test)
{
    fprintf(final_test,"L%d: \n",tetr->AR);

    if(strcmp(tetr->AR1,":=")== 0)
    {   loadvr(tetr->AR2,1);
        storerv(1,tetr->AR4);
    }
	else if(strcmp(tetr->AR1,"<")== 0)
    {   loadvr(tetr->AR2,1);
        loadvr(tetr->AR3,2);
        fprintf(final_test,"cmpi R[1],R[2]\n");
        fprintf(final_test,"jb L%s\n",tetr->AR4);
    }
    else if(strcmp(tetr->AR1,"<=")== 0)
    {   loadvr(tetr->AR2,1);
        loadvr(tetr->AR3,2);
        fprintf(final_test,"cmpi R[1],R[2]\n");
        fprintf(final_test,"jbe L%s\n",tetr->AR4);
    }
    else if(strcmp(tetr->AR1,">")== 0)
    {   loadvr(tetr->AR2,1);
        loadvr(tetr->AR3,2);
        fprintf(final_test,"cmpi R[1],R[2]\n");
        fprintf(final_test,"ja L%s\n",tetr->AR4);
    }
    else if(strcmp(tetr->AR1,">=")== 0)
    {   loadvr(tetr->AR2,1);
        loadvr(tetr->AR3,2);
        fprintf(final_test,"cmpi R[1],R[2]\n");
        fprintf(final_test,"jae L%s\n",tetr->AR4);
    }
    else if(strcmp(tetr->AR1,"=")== 0)
    {   loadvr(tetr->AR2,1);
        loadvr(tetr->AR3,2);
        fprintf(final_test,"cmpi R[1],R[2]\n");
        fprintf(final_test,"je L%s\n",tetr->AR4);
    }
    else if(strcmp(tetr->AR1,"<>")== 0)
    {   loadvr(tetr->AR2,1);
        loadvr(tetr->AR3,2);
        fprintf(final_test,"cmpi R[1],R[2]\n");
        fprintf(final_test,"jne L%s\n",tetr->AR4);
    }
    else if(strcmp(tetr->AR1,"out")== 0)
    {   loadvr(tetr->AR2,1);
        fprintf(final_test,"outi R[1]\n");
    }
    else if(strcmp(tetr->AR1,"retv")== 0)
    {   loadvr(tetr->AR2,1);
        fprintf(final_test,"movi R[255],M[8+R[0]]\n");
        fprintf(final_test,"movi M[R[255]],R[1]\n");
    }
	else if(strcmp(tetr->AR1,"+")== 0)
    {   loadvr(tetr->AR2,1);
        loadvr(tetr->AR3,2);
        fprintf(final_test,"addi R[3],R[1],R[2]\n");
        storerv(3,tetr->AR4);
    }
    else if(strcmp(tetr->AR1,"-")== 0)
    {   loadvr(tetr->AR2,1);
        loadvr(tetr->AR3,2);
        fprintf(final_test,"subi R[3],R[1],R[2]\n");
        storerv(3,tetr->AR4);
    }
    else if(strcmp(tetr->AR1,"*")== 0)
    {   loadvr(tetr->AR2,1);
        loadvr(tetr->AR3,2);
        fprintf(final_test,"muli R[3],R[1],R[2]\n");
        storerv(3,tetr->AR4);
    }
    else if(strcmp(tetr->AR1,"/")== 0)
    {   loadvr(tetr->AR2,1);
        loadvr(tetr->AR3,2);
        fprintf(final_test,"divi R[3],R[1],R[2]\n");
        storerv(3,tetr->AR4);
    }
    else if(strcmp(tetr->AR1,"jump")== 0)
    {   fprintf(final_test,"jmp L%s\n",tetr->AR4);
    }
    else if(strcmp(tetr->AR1,"end_block")== 0)
    {   fprintf(final_test,"jmp M[R[0]]\n");
    }
	else if(strcmp(tetr->AR1,"halt")== 0)
    {   fprintf(final_test,"halt\n");
    }
    else if(strcmp(tetr->AR1,"par")== 0)
    {
    }
    else if(strcmp(tetr->AR1,"call")== 0)
    {
    }
}
