#include <windows.h>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stack>
#include <cstdlib>
#include <ctime>
#define CMAX 52
#define TMAX 50

using namespace std;

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
		if (strcmp(Name+5, "♠")==0) return 0;
		else if (strcmp(Name+5, "♣")==0) return 1;
		else if (strcmp(Name+5, "♥")==0) return 2;
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
//카드패 스택 
class DStack {
	char stack[CMAX];
	int tos;
public :
	void init();
	void push(char *ch);
	char pop();
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
			for (int i=0;i<MaxCard;i++) Card[i].Name[2]=0;
			Num=0;
		}
		void insertCard(SCard C);
		SCard RemoveCard(int idx);
		int FindSameCard(SCard C,int *pSame);
		int FindFirstCard(const char *pName);
};
//카드를 정렬 
void CCardSet::insertCard(SCard C) {
	int i;

	for (i=0;i<Num;i++) {
		if (C < Card[i]) break;
	}
	memmove(&Card[i+1],&Card[i],sizeof(SCard)*(Num-1));
	Card[i]=C;
	Num++;
}
//플레이어가 카드를 내거나 데크에서 한장을 나누어줄때 쓸 함수 
SCard CCardSet::RemoveCard(int idx) {
	assert(idx < Num);
	SCard C=Card[idx];
	memmove(&Card[idx],&Card[idx+1],sizeof(SCard)*(Num-idx-1));
	Num--;
	return C;
}
//gotoxy함수 
void gotoxy(int sx, int sy) {
COORD Pos = {sx - 1, sy - 1};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
} 
//데크 
class CDeck : public CCardSet {
	public:
	CDeck(int asx,int asy) : CCardSet(asx,asy) { ; }

	    void Shuffle() {
	        int i,n;
	        srand((unsigned int)time(NULL));
	    	for (i=0;i<MaxCard;i++) {
	           	do {
	               	n=rand() % 52;
	       		} while (Card[n].Name[0] != NULL);
	        Card[n]=GCard[i];
	        Num++;
		   	}
	    }
//한장씩 배분 
    SCard Pop() { return RemoveCard(Num-1); }
    bool IsEmpty() { return Num==0; }
    bool IsNotLast() { return Num > 1; }
//카드남은 데크 두는 곳  
    void Draw(){
		gotoxy(sx,sy);
        cout << "|???| ";
    }
};

class Copy : public CDeck {
		public :
		void setname(string name) {
			this->name = name;
		}
};

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

int main() {
	
	

// 카드 객체 출력 	 
	for(int i=0; i<52; i++) {
		cout << GCard[rand()%52];
		cout << " ";
		if ((i+1) % 13 == 0) {
			cout <<"\n";
		};
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
	CDeck *Deck = new CDeck(20,20);
	Deck->Shuffle();
	Deck->Draw();
//    cout << Deck.Draw)<<endl; 
//플레이어
	CPlayer *Player = new CPlayer(30,20);
	Player->Draw(12);
//나중에 카드의 값 들을 숫자로 나타내는 부분
	int t;
	t = atoi(GCard[9].Name);
	printf("\n%d\n", t);

	CDeck *TDeck = new CDeck(22,22);
	TDeck->Shuffle();
	int i;
	for (int u=0;u<52;u++) {
		cout << SCard();
	};

//카드의 둘 뒤치를 선정후 섞어주고 택을 만듬
	CDeck *cDeck = new CDeck(21, 30);
	cDeck->Shuffle();
	cout <<"Deck 카드 \n" ;
	for(int i =0;i<52;i++) {
	cout << cDeck->GetCard(i).getName();
	};
/*	R *r = new R
	
	public :
		void setname(string name) {
			this->name = name;
		}
	
	R.setName(cDeck->GetCard(0).getName())
	
	RemoveCar
*/	
//택스텍 출력
//	DStack ds1;
//	int k;
//	ds1.init() ;
//	char h[];
//	for(int i=0;i<CMAX;i++) {
//	char c[2];
//	c[0] = 1;
//	ds1.push('12');
//	*h = GCard[1];
//	};
//	for (int i=0;i<52;i++) cout <<ds1.pop() <<endl;
//	SCard *p;
//	p = Gcard;
	return 0;

};
