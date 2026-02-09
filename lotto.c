#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define Row 5
#define Col 46
#define N 6
#define Max 8
#define Recent 15
#define FN "lotto.txt"

typedef struct{
	int no[Max];
}Data;

typedef struct _Node Node;

struct _Node{
	Data data;
	Node *prev;
	Node *next;
};

void CreateNo(int **lotto);
int Menu(void);
void Menu1(int **lotto);
void Menu2(int **lotto);
void Menu3(int **lotto);
void Menu4(int **lotto);
void Menu5(int **lotto, int *maxim, int idx);
void Menu6(int **lotto, int *maxim, int idx);
void Menu7(int **lotto, int *maxim, int idx);
void Menu8(int max, int *maxim, int idx);
void Menu9(void);
void GetNo1(int **lotto, int end); // end개의 번호 생성
int GetNo2(int **lotto); // 번호 1개 추가
void GetNo3(int **lotto); // 연속된 번호 생성
void GetNo5(int **lotto, int *maxim, int idx); // 최근 Recent회 최빈번호 1개 추가
void GetNo7(int **lotto, int *maxim, int idx, int c); // 1개 번호 입력 후, 중복없이 최근 Recent회 최빈번호 1개 추가
void GetNo8(int max, int *maxim, int idx); // 최근 Recent회 최빈번호 출력
int Duplicate(int *plotto, int value);
int Concatenate(int *lotto, int value);
void Print(int **lotto);
void Line(char c, int size);
void Cls(void);
void Clear(int **lotto);
void Free(int **lotto);
void ErrorMessage(void);
void Initialize(void);
void  AddNode(Data d);
void Input(void);
//void Print(void);
void Count(int *idx, int *max, int *cnt, int *maxim);
void Print10(void); // 최근 Recent회 추첨된 번호 출력
void PrintMax(int *cnt, int max);
void Enter(void);
void FreeNode(void);

Node *Head, *Tail;

int main(void){
	int *lotto[Row], m;
	int idx, max, cnt[Col]={0}, maxim[Col]={0}; 
	
	srand((unsigned)time(NULL));
	CreateNo(lotto);
	Initialize();
	Input();
	Count(&idx, &max, cnt, maxim);
	
	while(1){
		Cls();
		Clear(lotto);
		
		m=Menu();
		if(m==0) break;
		else if(m==1) Menu1(lotto);
		else if(m==2) Menu2(lotto);
		else if(m==3) Menu3(lotto);
		else if(m==4) Menu4(lotto);
		else if(m==5) Menu5(lotto, maxim, idx);
		else if(m==6) Menu6(lotto, maxim, idx);
		else if(m==7) Menu7(lotto, maxim, idx);
		else if(m==8) Menu8(max, maxim, idx);
		else if(m==9) Menu9();
	}
	
	Free(lotto);
	FreeNode();
	printf("Bye!\n");
	
	return 0;
}

int Menu(void){
	int c, ck;
	
	while(1){
		Cls();
		Line('-', 41);
		printf("                 메    뉴\n");
		Line('-', 41);
		printf("1. 랜덤 추첨\n");
		printf("2. 1개 번호 추가\n");
		printf("3. 연속번호 추가\n");
		printf("4. 1개 번호 / 연속번호 추가\n");
		printf("5. 최근 %d회 최빈번호 1개 추가\n", Recent);
		printf("6. 최근 %d회 최빈번호 1개 / 연속번호 추가\n", Recent);
		printf("7. 1개 번호 / %d회 최빈번호 / 연속번호\n", Recent);
		printf("8. 최근 %d회 최빈번호 출력\n", Recent);
		printf("9. 최근 %d회 추첨번호 출력\n", Recent);
		printf("0. 종    료\n");
		Line('-', 41);
		printf("입   력 >> ");
		ck=scanf("%d", &c);
		while(getchar()!='\n');
		if(ck!=1 || (c<0 || c>9)) ErrorMessage();
		else break;
	}
	
	return c;
}

void Menu1(int **lotto){
	GetNo1(lotto, N);
	Print(lotto);
	Enter();
}

void Menu2(int **lotto){
	GetNo2(lotto);
	GetNo1(lotto, N-1);
	Print(lotto);
	Enter();
}

void Menu3(int **lotto){
	GetNo1(lotto, N-1);
	GetNo3(lotto);
	Print(lotto);
	Enter();
}

void Menu4(int **lotto){
	GetNo2(lotto);
	GetNo1(lotto, N-2);
	GetNo3(lotto);
	Print(lotto);
	Enter();
}

void Menu5(int **lotto, int *maxim, int idx){
	GetNo5(lotto, maxim, idx);
	GetNo1(lotto, N-1);
	Print(lotto);
	Enter();
}

void Menu6(int **lotto, int *maxim, int idx){
	GetNo5(lotto, maxim, idx);
	GetNo1(lotto, N-2);
	GetNo3(lotto);
	Print(lotto);
	Enter();
}

void Menu7(int **lotto, int *maxim, int idx){
	int c;

	c=GetNo2(lotto);
	GetNo7(lotto, maxim, idx, c);
	GetNo1(lotto, N-3);
	GetNo3(lotto);
	Print(lotto);
	Enter();
}

void Menu8(int max, int *maxim, int idx){
	GetNo8(max, maxim, idx);
	Enter();
}

void Menu9(void){
	Print10();
	Enter();
}

void GetNo1(int **lotto, int end){
	int i, j, value, *plotto;
	
	for(i=0; i<Row; i++){
		plotto=lotto[i];
		for(j=0; j<end; j++){
			value=rand()%(Col-1)+1;
			if(Duplicate(plotto, value)){
				j--;
				continue;
			}
						
			plotto[value]=1;
		}
	}
}

int GetNo2(int **lotto){
	int c, ck, i;
	
	while(1){
		Cls();
		printf("번호를 1개 입력하세요(1~45) >> ");
		ck=(scanf("%d", &c));
		while(getchar()!='\n');
		if(ck!=1 || (c<1 || c>Col-1)) ErrorMessage();
		else break;
	}
	
	for(i=0; i<Row; i++) lotto[i][c]=1;
	
	return c;
}

void GetNo3(int **lotto){
	int i, j, value, *plotto;
	
	for(i=0; i<Row; i++){
		plotto=lotto[i];
		for(j=0; j<1; j++){
			value=rand()%(Col-1)+1;
			if(Duplicate(plotto, value)){
				j--;
			continue;
			}
						
			if(!Concatenate(plotto, value)){
				j--;
				continue;
			}
			
			plotto[value]=1;
		}
	}
}

void GetNo5(int **lotto, int *maxim, int idx){
	int i, value;
	
	for(i=0; i<Row; i++){
		value=maxim[rand()%idx+1];
		lotto[i][value]=1;
	}
}

void GetNo7(int **lotto, int *maxim, int idx, int c){
	int i, value;
	
	for(i=0; i<Row; i++){
		value=maxim[rand()%idx+1];
		if(c==value){
			i--;
			continue;
		}
		lotto[i][value]=1;
	}
}

void GetNo8(int max, int *maxim, int idx){
	int i;
	
	Cls();
	printf("최근 %d회 동안 %d번 추첨된 번호 : ", Recent, max);
	for(i=1; i<=idx; i++) printf("%d%c", maxim[i], i==idx ? '\n' : ' ');
}

int Concatenate(int *lotto, int value){
	if(value==1){
		if(lotto[2]==1) return 1;
		else return 0;
	}
		
	if(value==45){
		if(lotto[44]==1) return 1;
		else return 0;
	}
	
	if(lotto[value-1]==1 || lotto[value+1]==1) return 1;
	
	return 0;
}

int Duplicate(int *lotto, int value){
	if(lotto[value]==1) return 1;
	
	return 0;
}

void Print(int **lotto){
	int i, j, *plotto;
	
	Cls();
	printf("      똥행복권\n");
	printf("     LOttO6/45\n");
	Line('-', 19);
	
	for(i=0; i<Row; i++){
		plotto=lotto[i];
		printf("%c ", i+'A');
		for(j=1; j<Col; j++){
			if(plotto[j]==1) printf("%02d%c", j, j==Col-1 ? '\n' : ' ');
		}
		
		if(!plotto[Col-1]) printf("\n");
	}
	
	Line('-', 19);
}

void Enter(void){
	printf("\n[Enter]를 누르셔요...");
	while(getchar()!='\n');
}

void Line(char c, int size){
	int i;
	
	for(i=0; i<size; i++) putchar(c);
	putchar('\n');
}

void Cls(void){
	system("clear");
}

void CreateNo(int **lotto){
	int i;
	
	for(i=0; i<Row; i++) lotto[i]=(int *)malloc(sizeof(int )*Col);
}

void Clear(int **lotto){
	int i, j, *plotto;
	
	for(i=0; i<Row; i++){
		plotto=lotto[i];
		for(j=0; j<Col; j++) plotto[j]=0;
	}
}

void Free(int **lotto){
	int i;
	
	for(i=0; i<Row; i++) free(lotto[i]);
}

void ErrorMessage(void){
	Cls();
	printf("잘못 누르셨어요! [Enter]를 누르셔요!");
	while(getchar()!='\n');
}

void Initialize(void){
	Head=(Node *)malloc(sizeof(Node));
	Tail=(Node *)malloc(sizeof(Node));
	Head->next=Tail;
	Head->prev=Head;
	Tail->next=Tail;
	Tail->prev=Head;
}

void AddNode(Data d){
	Node *s;
	
	s=(Node *)malloc(sizeof(Node));
	Tail->data=d;
	
	Tail->next=s;
	s->prev=Tail;
	Tail=s;
	Tail->next=Tail;
}

void Input(void){
	FILE *fp;
	Data d;
	int c, i;
	
	if((fp=fopen(FN, "r"))==NULL) exit(1);
	
	while(1){
		for(i=0; i<Max; i++) c=fscanf(fp, "%d", &d.no[i]);
		if(c==EOF) break;
		AddNode(d);
	}
	fclose(fp);
}

void Print10(void){
	Node *s;
	int i, cnt=0;
	
	Cls();
	Line('-', 25);
	printf("   최근 %d회 추첨 번호\n", Recent);
	Line('-', 25);
	
	s=Tail->prev;
	while(s!=Head){
		printf("%04d ", s->data.no[0]);
		for(i=1; i<Max; i++) printf("%02d%c", s->data.no[i], i==Max-1 ? '\n' : ' ');
		s=s->prev, cnt++;
		if(cnt==Recent) break;
	}
	
	Line('-', 25);
}

void Count(int *idx, int *max, int *cnt, int *maxim){
	Node *s;
	int i, c;
	
	
	s=Tail->prev, c=0;
	while(s!=Head){
		for(i=1; i<Max; i++) cnt[s->data.no[i]]++;
		s=s->prev, c++;
		if(c==Recent) break;
	}
	
	*max=cnt[1];
	for(i=2; i<Col; i++) if(cnt[i]>*max) *max=cnt[i];
	*idx=0;
	for(i=1; i<Col; i++) if(cnt[i]==*max) maxim[++(*idx)]=i;
}

void PrintMax(int *cnt, int max){
	int i;
	
	for(i=1; i<Col; i++) if(cnt[i]==max) printf("%d --> %d\n", i, cnt[i]);
}

void FreeNode(void){
	Node *s, *t;
	
	s=Head;
	while(s!=Tail){
		t=s->next;
		free(s);
		s=t;
	}
	
	free(s);
}
