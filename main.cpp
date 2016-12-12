#include <windows.h>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <time.h>
#define CMAX 52
#define TMAX 50
#define random(num) ((rand()*rand())%num)

using namespace std;

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;

const int MaxCard=52;
const int CardGap=4;

struct SCard { //카드를 구성하는 구조체 
	char Name[7];
	SCard() { Name[0]=0; }
	SCard(const char *pName) {
		strcpy(Name, pName);
	}
	string getName() {
			return string(this->Name); //출력을 위한 도구
	}

//카드객체의 알파벳이 들어가 알파벳에 값을 넣어주는 함수  
	int GetNumber() const {
		if (isdigit(Name[0])) return Name[0]-'0';
//		if (Name[2]=='O') return 10;
		if (Name[0]=='J') return 11;
		if (Name[0]=='Q') return 12;
		if (Name[0]=='K') return 13;
	};
//카드객체에 특수문자가 들어가 특수문자에 값을 넣어주는 함수  
	int GetKind() const {
		if (strcmp(Name+2, "♠")==0) return 0;
		else if (strcmp(Name+2, "♣")==0) return 1;
		else if (strcmp(Name+2, "♥")==0) return 2;
		else return 3;
	}
	friend ostream &operator <<(ostream &c, const SCard &C) {
		return c << C.Name;
	}
//클래스 객체끼리 크기 비교해 주는 기준을 생성 
	bool operator ==(const SCard &Other) const {
		return (strcmp(Name, Other.Name)==0);
	}
	bool operator <(const SCard &Other) const {
		if (GetNumber() < Other.GetNumber()) return true;
	}
	bool operator >(const SCard &Other) const {
		if (GetNumber() > Other.GetNumber()) return true;
	}
	bool operator +(const SCard &Other) const {
		if (GetNumber() + Other.GetNumber()) return true;
	}
};

SCard GCard[MaxCard]={
	"1♠", "2♠", "3♠", "4♠", "5♠", "6♠", "7♠", "8♠", "9♠", "10♠", "J♠", "Q♠", "K♠",
	"1♣", "2♣", "3♣", "4♣", "5♣", "6♣", "7♣", "8♣", "9♣", "10♣", "J♣", "Q♣", "K♣",
	"1♥", "2♥", "3♥", "4♥", "5♥", "6♥", "7♥", "8♥", "9♥", "10♥", "J♥", "Q♥", "K♥", 
	"1◆", "2◆", "3◆", "4◆", "5◆", "6◆", "7◆", "8◆", "9◆", "10◆", "J◆", "Q◆", "K◆"
};

class CCardSet {
	protected:
		SCard Card[MaxCard];
		int Num;
//카드를 두는 좌표값 
		const int sx,sy;
		CCardSet(int asx,int asy) : sx(asx), sy(asy) { Num=0;}
	public:
// 카드를 하나도 없는 상태로 집합을 생성  
		int GetNum() { return Num;} 
		SCard GetCard(int idx) { return Card[idx];}
		void Reset() {
			for (int i=0;i<MaxCard;i++) Card[i].Name[0]=0;
			Num=0;
		}
		void InsertCard(SCard C);
		SCard RemoveCard(int idx);
		int FindSameCard(SCard C,int *pSame);
		int FindFirstCard(const char *pName);
};
//카드를 정렬 
void CCardSet::InsertCard(SCard C) {
	int i;
	
	if (C.Name[0] == 0) return;
	for (i=0;i<Num;i++) {
		if (C < Card[i]) break;
	}
	memmove(&Card[i+1],&Card[i],sizeof(SCard)*(Num-1));
	Card[i]=C;
	Num++;
}
//플레이어가 카드를 내거나 데크에서 한장을 나누어줄때 쓸 함수 정의 
SCard CCardSet::RemoveCard(int idx) {
	assert(idx < Num);
	printf("a");
	SCard C=Card[idx];
	printf("b");
	memmove(&Card[idx],&Card[idx+1],sizeof(SCard)*(Num-idx-1));
	Num--;
	printf("c");
	return C;
	printf("d");
}
//gotoxy함수 
void gotoxy(int sx, int sy) {
COORD Pos = {sx - 1, sy - 1};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
} 
//delay함수
void delay(clock_t sleep)
{	
    clock_t cur = clock(), el;

    for(;;){              /* 무한루프를 돌린다. */ 
        el = clock();  /* 현재까지 프로그램이 실행된 TICK */
        if((el - cur) > sleep)
            break;
    }
}
//randomize 함수 
void randomize(void) {
  srand((unsigned) time(NULL));
  // 첫부분의 숫자는 거의 랜덤하지 않기에, 앞부분에서 랜덤한 개수로 뽑아서 버림
  for (int i = 0; i < (rand() % RAND_MAX); i++) (rand() % RAND_MAX);
}
//데크
class CDeck : public CCardSet {
	public:
	CDeck(int asx,int asy) : CCardSet(asx,asy) { ; }
	    
		void Shuffle() {
	        int i,n;
	       // srand((unsigned int)time(NULL));
	    	for (i=0;i<MaxCard;i++) {
	           	do {
	               	n=random(MaxCard);
	       		} while (Card[n].Name[0] != NULL);
	        Card[n]=GCard[i];
	        Num++;
		   	}
	    }
//한장씩 배분 
    SCard Pop() { return RemoveCard(Num-1);}
    bool IsEmpty() { return Num==0; }
    bool IsNotLast() { return Num > 1; }
//카드남은 데크 두는 곳
    void Draw(bool bFlip){
		gotoxy(sx,sy);
        cout << "|???| ";
    }
};

/////////////////////////////////////////////여기여기여기; ㅕ아ㅓㄴ오ㅓ라ㅓ;모댜ㅓㅗ휸머ㅏㅇ류ㅣㅂ저ㅏㅗㅠㄷㄹ 
/*
class CCopy : public CDeck {
//		SCard.Name;
		public:
		void setname(string name) {
			this->name = cDeck->GetCard(i).getName();
		}
};
*/
//플레이어
class CPlayer : public CCardSet {
public:
	CPlayer(int asx,int asy) : CCardSet(asx,asy) { ; }
	void Draw(bool MyTurn) {
		int i,x;
		for (i=0,x=sx;i<Num;i++,x+=CardGap) {
			gotoxy(x,sy);
			cout << Card[i];
			if (MyTurn) {
					gotoxy(x,sy+1);
				cout << '[' << i+1 << ']';
			}
		}
	}
};
//담요 
class CBlanket: public CPlayer
{
public:
     CBlanket(int asx,int asy) : CPlayer(asx,asy) { ; }
     void Draw() {
          CPlayer::Draw(false);
     }
     void DrawSelNum(int *pSame) {
          int n;
          int *p;
          for (n=1,p=pSame;*p!=-1;p++,n++) {
              gotoxy(sx+*p*CardGap,sy-1);
              cout << '[' << n << ']';
          }
     }
     void DrawTempCard(int idx,SCard C) {
          gotoxy(sx+idx*CardGap,sy+1);
          cout << C;
     }
};

CDeck Deck(18,9);
CPlayer Down(20,5), Up(3,5);
CBlanket Blanket(5,12);
//CPlayerPae DownPae(40,10), UpPae(40,10);
bool DownTurn;

void Initialize() {
     int i;
     Deck.Shuffle();
     for (i=0;i<8;i++) {
         Down.InsertCard(Deck.Pop());
         Up.InsertCard(Deck.Pop());
         if (i < 4) Blanket.InsertCard(Deck.Pop());
	 }	 
}

void DrawScreen() {
     system("cls");
     Down.Draw(DownTurn);
     Up.Draw(!DownTurn);
     Blanket.Draw();
     Deck.Draw(false);
//     UpPae.Draw();
//     DownPae.Draw();
}

void OutPrompt(const char *Mes,int Wait/*=0*/) {
     gotoxy(5,23);
     for (int i=5;i<79;i++) { cout << ' '; }
     gotoxy(5,23);
     cout << Mes;
     delay(Wait);
}
 
int InputInt(const char *Mes, int start, int end) {
     int ch;
 
     OutPrompt(Mes,1);
     for (;;) {
          ch=tolower(getch());
          if (ch == 0xE0 || ch == 0) {
              ch=getch();
              continue;
          }
          if (!(isdigit(ch) || ch=='a')) continue;
          if (ch=='a') ch=10; else ch=ch-'0';
          if (ch >= start && ch <= end) {
              return ch;
          }
          OutPrompt("무효한 번호입니다. 지정한 범위에 맞게 다시 입력해 주세요.",1);
     }
}

int main() {
	int i,ch;
     int arSame[4],SameNum;
     char Mes[256];
     CPlayer *Turn;
     CPlayerPae *TurnPae,*OtherPae;
     int UserIdx,UserSel,DeckSel;
     SCard UserCard, DeckCard;
     bool UserTriple, DeckTriple;
     int nSnatch;
     int NewScore;
     
    randomize();
//	Initialize();
	DrawScreen();
          if (DownTurn) {
              Turn=&Down;
//              TurnPae=&SouthPae;
//            OtherPae=&NorthPae;
          } else {
              Turn=&Up;
//              TurnPae=&NorthPae;
//              OtherPae=&SouthPae;
          }
 
          sprintf(Mes,"내고 싶은 카드를 선택하세요(1~%d,0:종료) ",Turn->GetNum());
          ch=InputInt(Mes,0,Turn->GetNum());
          if (ch == 0) {
              if (InputInt("정말 끝낼겁니까?(0:예,1:아니오)",0,1)==0) ;
                   return NULL;
              //else
              //     return 1;
          }
//카드크기 비교  
	int a = 0; //카드 1 
	int b = 9; //카드 10
	int c = 10; //카드 j = 11
	cout << "스페이드 1과 스페이드 10 비교"	;
	if(GCard[a] < GCard[b]) {  
		cout << GCard[b];
	} else {
		cout << GCard[a];
	}
	cout << "\n스페이드 1과 스페이드 J 비교"	;
	if(GCard[a] < GCard[c]) {
		cout << GCard[c];
	} else {
		cout << GCard[a];
	}

//카드패를 놓아두는 곳
/*	CDeck *Deck = new CDeck(20, 5);
	Deck->Shuffle();
//	Deck.Pop() ;
	Deck->Draw(1);
//    cout << Deck.Draw)<<endl; 
*?
//플레이어
	CPlayer *Player = new CPlayer(20,4);
	Player->Draw(9);
//나중에 카드의 값 들을 숫자로 나타내는 부분
	int t,y;
	t = atoi(GCard[9].Name);
	printf("\n%d\n", t);
//카드의 둘 뒤치를 선정후 섞어주고 택을 만듬
	CDeck *cDeck = new CDeck(0,0);
	cDeck->Shuffle();
	cout <<"Deck 카드 \n" ;
	for(int i =0;i<52;i++) {
	cout << cDeck->GetCard(i).getName();
	};
//플래이어
	CPlayer *GPlayer = new CPlayer(15,30);
//	Deck->Pop();
//	CPlayer->Draw();

/*	R *r = new R
	public :
		void setname(string name) {
			this->name = name;
		}
	
	R.setName(cDeck->GetCard(0).getName())
	
	RemoveCar
*/
	return 0;
};
