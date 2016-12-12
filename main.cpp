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

struct SCard { //ī�带 �����ϴ� ����ü 
	char Name[7];
	SCard() { Name[0]=0; }
	SCard(const char *pName) {
		strcpy(Name, pName);
	}
	string getName() {
			return string(this->Name); //����� ���� ����
	}

//ī�尴ü�� ���ĺ��� �� ���ĺ��� ���� �־��ִ� �Լ�  
	int GetNumber() const {
		if (isdigit(Name[0])) return Name[0]-'0';
//		if (Name[2]=='O') return 10;
		if (Name[0]=='J') return 11;
		if (Name[0]=='Q') return 12;
		if (Name[0]=='K') return 13;
	};
//ī�尴ü�� Ư�����ڰ� �� Ư�����ڿ� ���� �־��ִ� �Լ�  
	int GetKind() const {
		if (strcmp(Name+2, "��")==0) return 0;
		else if (strcmp(Name+2, "��")==0) return 1;
		else if (strcmp(Name+2, "��")==0) return 2;
		else return 3;
	}
	friend ostream &operator <<(ostream &c, const SCard &C) {
		return c << C.Name;
	}
//Ŭ���� ��ü���� ũ�� ���� �ִ� ������ ���� 
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
	"1��", "2��", "3��", "4��", "5��", "6��", "7��", "8��", "9��", "10��", "J��", "Q��", "K��",
	"1��", "2��", "3��", "4��", "5��", "6��", "7��", "8��", "9��", "10��", "J��", "Q��", "K��",
	"1��", "2��", "3��", "4��", "5��", "6��", "7��", "8��", "9��", "10��", "J��", "Q��", "K��", 
	"1��", "2��", "3��", "4��", "5��", "6��", "7��", "8��", "9��", "10��", "J��", "Q��", "K��"
};

class CCardSet {
	protected:
		SCard Card[MaxCard];
		int Num;
//ī�带 �δ� ��ǥ�� 
		const int sx,sy;
		CCardSet(int asx,int asy) : sx(asx), sy(asy) { Num=0;}
	public:
// ī�带 �ϳ��� ���� ���·� ������ ����  
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
//ī�带 ���� 
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
//�÷��̾ ī�带 ���ų� ��ũ���� ������ �������ٶ� �� �Լ� ���� 
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
//gotoxy�Լ� 
void gotoxy(int sx, int sy) {
COORD Pos = {sx - 1, sy - 1};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
} 
//delay�Լ�
void delay(clock_t sleep)
{	
    clock_t cur = clock(), el;

    for(;;){              /* ���ѷ����� ������. */ 
        el = clock();  /* ������� ���α׷��� ����� TICK */
        if((el - cur) > sleep)
            break;
    }
}
//randomize �Լ� 
void randomize(void) {
  srand((unsigned) time(NULL));
  // ù�κ��� ���ڴ� ���� �������� �ʱ⿡, �պκп��� ������ ������ �̾Ƽ� ����
  for (int i = 0; i < (rand() % RAND_MAX); i++) (rand() % RAND_MAX);
}
//��ũ
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
//���徿 ��� 
    SCard Pop() { return RemoveCard(Num-1);}
    bool IsEmpty() { return Num==0; }
    bool IsNotLast() { return Num > 1; }
//ī�峲�� ��ũ �δ� ��
    void Draw(bool bFlip){
		gotoxy(sx,sy);
        cout << "|???| ";
    }
};

/////////////////////////////////////////////���⿩�⿩��; �žƤä����ö��;����ä���Ӥ������Ӥ������ǤФ��� 
/*
class CCopy : public CDeck {
//		SCard.Name;
		public:
		void setname(string name) {
			this->name = cDeck->GetCard(i).getName();
		}
};
*/
//�÷��̾�
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
//��� 
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
          OutPrompt("��ȿ�� ��ȣ�Դϴ�. ������ ������ �°� �ٽ� �Է��� �ּ���.",1);
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
 
          sprintf(Mes,"���� ���� ī�带 �����ϼ���(1~%d,0:����) ",Turn->GetNum());
          ch=InputInt(Mes,0,Turn->GetNum());
          if (ch == 0) {
              if (InputInt("���� �����̴ϱ�?(0:��,1:�ƴϿ�)",0,1)==0) ;
                   return NULL;
              //else
              //     return 1;
          }
//ī��ũ�� ��  
	int a = 0; //ī�� 1 
	int b = 9; //ī�� 10
	int c = 10; //ī�� j = 11
	cout << "�����̵� 1�� �����̵� 10 ��"	;
	if(GCard[a] < GCard[b]) {  
		cout << GCard[b];
	} else {
		cout << GCard[a];
	}
	cout << "\n�����̵� 1�� �����̵� J ��"	;
	if(GCard[a] < GCard[c]) {
		cout << GCard[c];
	} else {
		cout << GCard[a];
	}

//ī���и� ���Ƶδ� ��
/*	CDeck *Deck = new CDeck(20, 5);
	Deck->Shuffle();
//	Deck.Pop() ;
	Deck->Draw(1);
//    cout << Deck.Draw)<<endl; 
*?
//�÷��̾�
	CPlayer *Player = new CPlayer(20,4);
	Player->Draw(9);
//���߿� ī���� �� ���� ���ڷ� ��Ÿ���� �κ�
	int t,y;
	t = atoi(GCard[9].Name);
	printf("\n%d\n", t);
//ī���� �� ��ġ�� ������ �����ְ� ���� ����
	CDeck *cDeck = new CDeck(0,0);
	cDeck->Shuffle();
	cout <<"Deck ī�� \n" ;
	for(int i =0;i<52;i++) {
	cout << cDeck->GetCard(i).getName();
	};
//�÷��̾�
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
