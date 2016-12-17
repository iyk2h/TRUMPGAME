#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <time.h>
#include <windows.h>

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;
void clrscr();
void gotoxy(int x, int y);
int wherex();
int wherey();
void setcursortype(CURSOR_TYPE c);

#define delay(n) Sleep(n)                     // n/1000�ʸ�ŭ �ð� ����
#define randomize() srand((unsigned)time(NULL))      // ���� �߻��� �ʱ�ȭ
#define random(n) (rand() % (n))               //0~n������ ���� �߻�

// ȭ���� ��� �����.
void clrscr() {
   system("cls");
}

// Ŀ���� x,y��ǥ�� �̵���Ų��.
void gotoxy(int x, int y) {
   COORD Cur;
   Cur.X=x;
   Cur.Y=y;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}

// Ŀ���� x ��ǥ�� �����Ѵ�.
int wherex()
{
   CONSOLE_SCREEN_BUFFER_INFO BufInfo;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);
   return BufInfo.dwCursorPosition.X;
}

// Ŀ���� y��ǥ�� �����Ѵ�.
int wherey()
{
   CONSOLE_SCREEN_BUFFER_INFO BufInfo;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&BufInfo);
   return BufInfo.dwCursorPosition.Y;
}

// Ŀ���� ����ų� �ٽ� ǥ���Ѵ�.
void setcursortype(CURSOR_TYPE c) {
   CONSOLE_CURSOR_INFO CurInfo;

   switch (c) {
   case NOCURSOR:
      CurInfo.dwSize=1;
      CurInfo.bVisible=FALSE;
      break;
   case SOLIDCURSOR:
      CurInfo.dwSize=100;
      CurInfo.bVisible=TRUE;
      break;
   case NORMALCURSOR:
      CurInfo.dwSize=20;
      CurInfo.bVisible=TRUE;
      break;
   }
   SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&CurInfo);
}

using namespace std;



const int MaxCard = 52;

const int CardGap = 4;

const int Speed = 1000;

const int PromptSpeed = 2000;

struct SCard {
   char Name[4];
   SCard() { Name[0] = 0; }
   SCard(const char *pName) {
      strcpy(Name, pName);
   }
   int GetNumber() const {
      if (isdigit(Name[0])) return Name[0] - '0';
//      if (Name[0] == 'T') return 10;
      if (Name[0] == 'J') return 11;
      if (Name[0] == 'Q') return 12;
      return 13;
   };
   int GetKind() const {
      if (strcmp(Name + 1, "��") == 0) return 0;
      else if (strcmp(Name + 1, "��") == 0) return 1;
      else if (strcmp(Name + 1, "��") == 0) return 2;
      else return 3;
   }
   friend ostream &operator <<(ostream &c, const SCard &C) {
      return c << C.Name;
   }
   bool operator ==(const SCard &Other) const {
      return (strcmp(Name, Other.Name) == 0);
   }
   bool operator <(const SCard &Other) const {
      if (GetNumber() < Other.GetNumber()) return true;
      if (GetNumber() > Other.GetNumber()) return false;
      if (GetKind() < Other.GetKind()) return true;
      
      return false;
   }
   bool operator +(const SCard &Other) const {
      if (GetNumber() + Other.GetNumber()) return true;
      //if (GetNumber() > Other.GetNumber()) return false;
      //if (GetKind() < Other.GetKind()) return true;
      
      return false;
   }
};

SCard GCard[MaxCard] = {
   "1��","2��","3��","4��","5��","6��","7��","8��","9��","T��","J��","Q��","K��",
   "1��","2��","3��","4��","5��","6��","7��","8��","9��","T��","J��","Q��","K��",
   "1��","2��","3��","4��","5��","6��","7��","8��","9��","T��","J��","Q��","K��",
   "1��","2��","3��","4��","5��","6��","7��","8��","9��","T��","J��","Q��","K��"
};

// ī���� ������ �����ϴ� Ŭ����
class CCardSet {
protected:
   SCard Card[MaxCard];
   int Num;
   const int sx,sy;
   CCardSet(int asx,int asy) : sx(asx), sy(asy) { Num=0; }

public:
   int GetNum() { return Num; }
   SCard GetCard(int idx) { return Card[idx]; }
   void Reset() { 
      for (int i=0;i<MaxCard;i++) Card[i].Name[0]=0;
      Num=0; 
   }
   void InsertCard(SCard C);
   SCard RemoveCard(int idx);
//   int FindSameCard(SCard C,int *pSame);
//   int FindFirstCard(const char *pName);
};

void CCardSet::InsertCard(SCard C) {
   int i;

   if (C.Name[0] == 0) return;
   for (i=0;i<Num;i++) {
      if (C < Card[i]) break;
   }
   memmove(&Card[i+1],&Card[i],sizeof(SCard)*(Num-i));
   Card[i]=C;
   Num++;
}

SCard CCardSet::RemoveCard(int idx) {
   assert(idx < Num);
   SCard C=Card[idx];
   memmove(&Card[idx],&Card[idx+1],sizeof(SCard)*(Num-idx-1));
   Num--;
   return C;
}
/*
int CCardSet::FindSameCard(SCard C,int *pSame) {
   int i,num;
   int *p=pSame;

   for (i=0,num=0;i<Num;i++) {
      if (Card[i].GetNumber() == C.GetNumber()) {
         num++;
         *p++=i;
      }
   }
   *p=-1;
   return num;
}
*/
/*
int CCardSet::FindFirstCard(const char *pName) {
   int i;
   for (i=0;i<Num;i++) {
      if (strstr(Card[i].Name,pName) != NULL) {
         return i;
      }
   }
   return -1;
}
*/
// ��信 ī�带 �׾� ���� ��ũ
class CDeck : public CCardSet {
public:
   CDeck(int asx,int asy) : CCardSet(asx,asy) { ; }
   void Shuffle() {
      int i,n;
          for (i=0;i<MaxCard;i++) {
                 do {
                     n=random(MaxCard);
                } while (Card[n].Name[0] != '\0');
           Card[n]=GCard[i];
           Num++;
            }
   }
   SCard Pop() { return RemoveCard(Num-1); }
   bool IsEmpty() { return Num==0; }
   bool IsNotLast() { return Num > 1; }
   void Draw(bool bFlip) {
      gotoxy(13,9);
      cout << "??? " /*<< (bFlip ? Card[Num-1].Name:"   ")*/; //��ũ ���� � ī�尡 �������� 
   }
};

//���Լ� 
void color (int col) 
{ 
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),col); //�� �Լ� 
} 
// ������ �ϴ� �÷��̾�
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
            color(13);
                cout << '[' << i+1 << ']';
                color(15);
         }
      }
   }
};
class placeset {
protected:
   SCard Card[MaxCard];
   int Num;
   const int sx,sy;
   placeset(int asx,int asy) : sx(asx), sy(asy) { Num=0; }

public:

   int GetNum() { return Num; }
   SCard GetCard(int idx) { return Card[idx]; }
   void Reset() { 
      for (int i=0;i<MaxCard;i++) Card[i].Name[0]=0;
      Num=0; 
   }
   void InsertCard(SCard C);
//   SCard RemoveCard(int idx);
//   int FindSameCard(SCard C,int *pSame);
//   int FindFirstCard(const char *pName);
};
void placeset::InsertCard(SCard C) {
   int i;
//   if (C.Name[0] == 0) return;
   for (i=0;i<Num;i++) {
//      if (C < Card[i]) break;
   }
   memmove(&Card[i+1],&Card[i],sizeof(SCard)*(Num-i));
   Card[i]=C;
   Num++;
}
class place : public placeset {
   int t;
public:
   place(int asx,int asy) :placeset(asx,asy) { ; }
   void Draw(bool MyTurn) {
      int i,x;
      for (i=0,x=sx;i<Num;i++,x+=CardGap) {
         gotoxy(sx,sy);

         t = atoi(Card[i].Name);
        if(Card[i].Name[0]=='T') {
            t=10;
    	}else if(Card[i].Name[0]=='J') {
            t=11;
    	} else if(Card[i].Name[0]=='Q') {
            t=12;
    	} else if(Card[i].Name[0]=='K') {
            t=13;
    	}
		cout << Card[i].Name ;
        }
   }
   int getNumber() {
         return t;
   }
};

// ������ ����Ǵ� ���
class CBlanket: public place {
public:
   CBlanket(int asx,int asy) : place(asx,asy) { ; }
   void Draw() {
      
      place::Draw(false);
   }
};
// ������ ����Ǵ� ���2
class CBlanket2: public place {
public:
   CBlanket2(int asx,int asy) : place(asx,asy) { ; }
   void Draw() {
      place::Draw(false);

   }
};
// ������ ����Ǵ� ���3
class CBlanket3: public place {
public:
   CBlanket3(int asx,int asy) : place(asx,asy) { ; }
   void Draw() {
      place::Draw(false);
   }
};
// ������ ����Ǵ� ���4
class CBlanket4: public place {
public:
   CBlanket4(int asx,int asy) : place(asx,asy) { ; }
   void Draw() {
      place::Draw(false);
   }
};
int gNum;
int CIn() {
	for (;;) {
		cin >> gNum;
		
		if(20< gNum && gNum <37) {
			return gNum;
		}else  
		cout << "���� ���� ���� �Է� �ٶ��ϴ�.";
	}
}
// �Լ� ����
void Initialize();
void DrawScreen();
void OutPrompt(const char *Mes,int Wait=0);
int InputInt(const char *Mes, int start, int end);

// ���� ����
CDeck Deck(5,1);
CPlayer South(5,20), North(5,2);
CBlanket Blanket(5,6);
CBlanket2 Blanket2(20,6);
CBlanket3 Blanket3(5,12);
CBlanket4 Blanket4(20,12);
bool SouthTurn;





	int problum;
// ���α׷��� �������ϴ� main �Լ�
int main() {
   int i,ch,a;
   int arSame[4],SameNum;
   char Mes[256];
   CPlayer *Turn;
   int UserIdx,UserSel,DeckSel;
   SCard UserCard, DeckCard;
   bool UserTriple, DeckTriple;
   int nSnatch;
   int NewScore;
   int t;
   randomize();  
   Initialize();
   DrawScreen();
    int A=Blanket.getNumber();
	int B=Blanket2.getNumber();
	int C=Blanket3.getNumber();
	int D=Blanket4.getNumber();
	
//	DrawScreen();
	if(A+B > C+D) {
       	cout << "�� �÷��̾ �������� ���մϴ�.�������� �Է��� �ּ���.(����20~37)";
		CIn();
		problum = gNum;
	} else if(A+B < C+D) {
       	cout << "�Ʒ� �÷��̾ �������� ���մϴ�.�������� �Է��� �ּ���.(����20~37)";
		//cin >> gNum;
		CIn();
		problum = gNum;        	
	}else cout << " ";
   for (SouthTurn=true;!Deck.IsEmpty();SouthTurn=!SouthTurn) {
    int AA=Blanket.getNumber();
	int BB=Blanket2.getNumber();
	int CC=Blanket3.getNumber();
	int DD=Blanket4.getNumber();
      if( AA+BB+CC+DD == problum) {
      	for(int i =0;i<3000;i++) {
      	color(random(15));
      	gotoxy(random(150),random(80));
		cout << "���ӳ�";
//		delay();
		}
      	return 0; 
//     	delay(1000);
	  } //else continue;
	  DrawScreen();
//	  cout << problum;
      if (SouthTurn) {
         Turn=&South;
      } else {
         Turn=&North;
      }
      for(int t=0;t<2;t++) {

         color(13);
         sprintf(Mes,"���� ���� ī�带 �����ϼ���(1~%d,[10] = a, 0:����) ",Turn->GetNum()-1);
           ch=InputInt(Mes,0,Turn->GetNum());
         if (ch == 0) {
            if (InputInt("���� �����̴ϱ�?(0:��,1:�ƴϿ�)",0,1)==0) 
               return 0;
            else 
               continue;
         }
         // �÷��̾ ī�带 ���� ����.
         UserTriple=DeckTriple=false;
         UserIdx=ch-1;
         UserCard=Turn->GetCard(UserIdx);
         //SameNum=Blanket.FindSameCard(UserCard,arSame);
         color(15);
         DrawScreen();

         color(11);
         sprintf(Mes,"ī�带 �ø��� ���� ������ ��ũ�� ��ȣ�� �����ϼ���(1~4) ",Turn->GetNum());
         a=InputInt(Mes,0,Turn->GetNum());
         color(15);
         switch (a) {
         case 1:
            UserSel=-1;
            Blanket.InsertCard(Turn->RemoveCard(UserIdx));
            DrawScreen();
            break;
         case 2:
            UserSel=-1;
            Blanket2.InsertCard(Turn->RemoveCard(UserIdx));
            DrawScreen();
            break;
         case 3:
            UserSel=-1;
            Blanket3.InsertCard(Turn->RemoveCard(UserIdx));
            DrawScreen();
            break;
         case 4:
            UserSel=-1;
            Blanket4.InsertCard(Turn->RemoveCard(UserIdx));
            DrawScreen();
            break;
         }   
      }
      // ��ũ���� ������ �����´�.
      int I;
      I = 0;
      if (I<27) {
      Turn->InsertCard(Deck.Pop());
      Turn->InsertCard(Deck.Pop());
   	  }
   	  I++;
   }
   DrawScreen();
   clrscr;
   OutPrompt("������ �������ϴ�.",0);
   
}
void Initialize() {
   int i;

   Deck.Shuffle();
   for (i=0;i<10;i++) {
      South.InsertCard(Deck.Pop());
      North.InsertCard(Deck.Pop());
      if (i < 1) Blanket.InsertCard(Deck.Pop());
      if (i < 1) Blanket2.InsertCard(Deck.Pop());
      if (i < 1) Blanket3.InsertCard(Deck.Pop());
      if (i < 1) Blanket4.InsertCard(Deck.Pop());
   }
}

void DrawScreen() {
   clrscr();
   South.Draw(SouthTurn);
   North.Draw(!SouthTurn);
   Blanket.Draw();
   gotoxy(5,7);
   color(11);
   cout << '[' << 1 << ']';
   color(15);
   Blanket2.Draw();
   gotoxy(20,7);
   color(11);
   cout << '[' << 2 << ']';
   color(15);
   Blanket3.Draw();
   gotoxy(5,13);
   color(11);
   cout << '[' << 3 << ']';
   color(15);
   Blanket4.Draw();
   gotoxy(20,13);
   color(11);
   cout << '[' << 4 << ']';
   color(15);
//lanket.Draw();
   Deck.Draw(false);
   if(problum == 0) cout << " ";
   else cout << problum;
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

   OutPrompt(Mes);
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
      OutPrompt("��ȿ�� ��ȣ�Դϴ�. ������ ������ �°� �ٽ� �Է��� �ּ���.");
   }
}


