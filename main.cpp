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

struct SCard { //ī�带 �����ϴ� ����ü 
	char Name[7];
	SCard() { Name[2]=0; }
	SCard(const char *pName) {
		strcpy(Name, pName);
	}
//ī�尴ü�� ���ĺ��� �� ���ĺ��� ���� �־��ִ� �Լ�  
	int GetNumber() const {
		if (isdigit(Name[2])) return Name[2]-'0';
		if (Name[2]=='O') return 10;
		if (Name[2]=='J') return 11;
		if (Name[2]=='Q') return 12;
		if (Name[2]=='K') return 13;
	};
//ī�尴ü�� Ư�����ڰ� �� Ư�����ڿ� ���� �־��ִ� �Լ�  
	int GetKind() const {
		if (strcmp(Name+5, "��")==0) return 0;
		else if (strcmp(Name+5, "��")==0) return 1;
		else if (strcmp(Name+5, "��")==0) return 2;
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
	"| 1��|", "| 2��|", "| 3��|", "| 4��|", "| 5��|", "| 6��|", "| 7��|", "| 8��|", "| 9��|", "|1O��|", "| J��|", "| Q��|", "| K��|",
	"| 1��|", "| 2��|", "| 3��|", "| 4��|", "| 5��|", "| 6��|", "| 7��|", "| 8��|", "| 9��|", "|1O��|", "| J��|", "| Q��|", "| K��|",
	"| 1��|", "| 2��|", "| 3��|", "| 4��|", "| 5��|", "| 6��|", "| 7��|", "| 8��|", "| 9��|", "|1O��|", "| J��|", "| Q��|", "| K��|", 
	"| 1��|", "| 2��|", "| 3��|", "| 4��|", "| 5��|", "| 6��|", "| 7��|", "| 8��|", "| 9��|", "|1O��|", "| J��|", "| Q��|", "| K��|"
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
			for (int i=0;i<MaxCard;i++) Card[i].Name[2]=0;
			Num=0;
		}
		void insertCard(SCard C);
		SCard RemoveCard(int idx);
		int FindSameCard(SCard C,int *pSame);
		int FindFirstCard(const char *pName);
};
//ī�带 ���� 
void CCardSet::insertCard(SCard C) {
	int i;
	 
	for (i=0;i<Num;i++) {
		if (C < Card[i]) break;
	}
	memmove(&Card[i+1],&Card[i],sizeof(SCard)*(Num-1));
	Card[i]=C;
	Num++;
}
//�÷��̾ ī�带 ���ų� ��ũ���� ������ �������ٶ� �� �Լ� 
SCard CCardSet::RemoveCard(int idx) {
	assert(idx < Num);
	SCard C=Card[idx];
	memmove(&Card[idx],&Card[idx+1],sizeof(SCard)*(Num-idx-1));
	Num--;
	return C;
}
//gotoxy�Լ� 
void gotoxy(int sx, int sy) 
{

COORD Pos = {sx - 1, sy - 1};
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
} 
//��ũ 
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
//���徿 ��� 
    SCard Pop() { return RemoveCard(Num-1); }
    bool IsEmpty() { return Num==0; }
    bool IsNotLast() { return Num > 1; }
    void Draw(){
		gotoxy(sx,sy);
        cout << "|???| ";
    }

};

int main() {
	
// ī�� ��ü ��� 	 
	for(int i=0; i<52; i++) {
		cout << GCard[i];
		cout << " ";
		if ((i+1) % 13 == 0) {
			cout <<"\n";
		};
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
//�������� ���� ������ �ϴ� �κ��� �Ϻκ� 
	int n;
	srand((unsigned int)time(NULL));
	cout << "\n �������� �����Ǵ� ī��:";
 	cout << GCard[rand()%52] <<endl;
 	
//	cout << CDeck::Draw()
		gotoxy(30,10);
        cout << "|???| ";
    
	CDeck *Deck = new CDeck(40,20);
	Deck->Draw();
//    cout << Deck.Draw()<<endl;
	    
	return 0;
};
