#include <windows.h>
#include <iostream>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <ctime>

using namespace std;

const int MaxCard=52;
const int CardGap=4;

struct SCard { //카드를 구성하는 구조체 
	char Name[7];
	SCard() { Name[2]=0; }
	SCard(const char *pName) {
		strcpy(Name, pName);
	}
//카드객체의 알파벳이 들어가 알파벳에 값을 넣어주는 함수  
	int GetNumber() const {
		if (isdigit(Name[2])) return Name[2]-'0';
		if (Name[2]=='O') return 10;
		if (Name[2]=='J') return 11;
		if (Name[2]=='Q') return 12;
		if (Name[2]=='K') return 13;
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
	"| 1♠|", "| 2♠|", "| 3♠|", "| 4♠|", "| 5♠|", "| 6♠|", "| 7♠|", "| 8♠|", "| 9♠|", "|1O♠|", "| J♠|", "| Q♠|", "| K♠|",
	"| 1♣|", "| 2♣|", "| 3♣|", "| 4♣|", "| 5♣|", "| 6♣|", "| 7♣|", "| 8♣|", "| 9♣|", "|1O♣|", "| J♣|", "| Q♣|", "| K♣|",
	"| 1♥|", "| 2♥|", "| 3♥|", "| 4♥|", "| 5♥|", "| 6♥|", "| 7♥|", "| 8♥|", "| 9♥|", "|1O♥|", "| J♥|", "| Q♥|", "| K♥|", 
	"| 1◆|", "| 2◆|", "| 3◆|", "| 4◆|", "| 5◆|", "| 6◆|", "| 7◆|", "| 8◆|", "| 9◆|", "|1O◆|", "| J◆|", "| Q◆|", "| K◆|"
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
void gotoxy(int sx, int sy) 
{

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
    void Draw(){
		gotoxy(sx,sy);
        cout << "|???| ";
    }

};

int main() {
	
// 카드 객체 출력 	 
	for(int i=0; i<52; i++) {
		cout << GCard[i];
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
//랜덤으로 숫자 나오게 하는 부분중 일부분 
	int n;
	srand((unsigned int)time(NULL));
	cout << "\n 랜덤으로 생성되는 카드:";
 	cout << GCard[rand()%52] <<endl;
 	
//	cout << CDeck::Draw()
		gotoxy(30,10);
        cout << "|???| ";
    
	CDeck *Deck = new CDeck(40,20);
	Deck->Draw();
//    cout << Deck.Draw()<<endl;
	    
	return 0;
};
