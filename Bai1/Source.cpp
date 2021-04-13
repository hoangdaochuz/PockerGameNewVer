// Ham xao tron va in ra ket qua xao tron
#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
const int SUIT = 4;
const int FACES = 13;

struct LABAI {
	int vitri;
	int suit;
	int face;
};


void KhoiTaoBoBai(int BoBai[])
{
	for (int i = 0; i < SUIT * FACES; i++) {
		BoBai[i] = i + 1;
	}
}

void XaoTronBoBai(int BoBai[])
{
	/*
		-y tuong :
			+khoi tao cac vi tri minIndex, maxIndex,swpaPosition. 
			+Duyet mang. minIndex bat dau tu vi tri duyet tang len 1 don vi.
			+swapPosition duoc random 1 cach ngau nhien trong khoang tu minIndex-> maxIndex de chon ra vi tri can swap
			+ cu the tiep tuc cho toi khi het mang
	*/

	srand(time(NULL));
	int minIndex;
	int maxIndex=SUIT*FACES-1;
	int swapPosition;
	int i = 0;
	while (i < SUIT * FACES - 1)
	{
		minIndex = i + 1;
		swapPosition = minIndex + rand() % (maxIndex + 1 - minIndex);
		swap(BoBai[i], BoBai[swapPosition]);
		i++;
	}
}

/*void XuatMang(int deck[][FACES])
{
	for (int i = 0; i < SUIT; i++) {
		for (int j = 0; j < FACES; j++) {
			cout << deck[i][j] << " ";
		}
		cout << endl;
	}
}*/
/*void XuatMang1D(int BoBai[]) {
	for (int i = 0; i < SUIT * FACES; i++) {
		cout << BoBai[i] << " ";
	}
}*/

void ChuyenBoBaiThanhMang2Chieu(int BoBai[], int Array2D[][FACES])
{
	int k = 0;
	for (int i = 0; i < SUIT; i++) {
		for (int j = 0; j < FACES; j++) {
			Array2D[i][j] = BoBai[k];
			k++;
		}
	}
}

void BienMang2DThanhLaBai(int Array2D[][FACES], LABAI A[])
{
	int k = 0;
	for (int i = 0; i < SUIT; i++) {
		for (int j = 0; j < FACES; j++) {
			A[k].vitri = Array2D[i][j];
			A[k].suit = i;
			A[k].face = j;
			k++;
		}
	}
 }

/*void XuatLabai(LABAI A[])
{
	for (int i = 0; i < 52; i++) {
		cout << "(" << A[i].suit << "," << A[i].face << ")";
		cout << endl;
	}
}*/

void shuffleCards(int deck[][FACES],LABAI A[])
{
	//LABAI A[SUIT * FACES];
	int BoBai[SUIT * FACES];// Khoi tao 1 mang de chua 52 la bai
	KhoiTaoBoBai(BoBai);// 1 bo bai luc dau co 52 la duoc xep tu 1 den 52
	int Array2D[SUIT][FACES];
	//cout << "Bo Bai truoc khi xao la: \n";
	ChuyenBoBaiThanhMang2Chieu(BoBai, Array2D);
	BienMang2DThanhLaBai(Array2D, A);
	//XuatMang(Array2D);
	//cout << endl;
	//XuatLabai(A);
	
	//cout << "Bo bai sau khi xao la: \n";
	XaoTronBoBai(BoBai);// Xao tron thu tu cua 52 la bai
	int k = 0;
	for (int i = 0; i < SUIT; i++) {
		for (int j = 0; j < FACES; j++) {
			deck[i][j] = BoBai[k++];// gan thu tu da xao cua bo bai vao deck. Day thuc chat la bien mang 2 chieu thanh mang 1 chieu roi xao tron thu tu cua no. Sau do gan vao lai mang 2 chieu
		}
	}
}

void XuatLaBai(int a, LABAI A[], char suit[][20], char faces[][20])
{
	for (int i = 0; i < 52; i++) {
		if (a == A[i].vitri) {
			cout << "(" << suit[A[i].suit] << "," << faces[A[i].face] << ")";
		}
	}
}

void printCardsShuffling(int deck[][FACES], char suit[][20], char faces[][20], LABAI A[])
{
	for (int i = 0; i < SUIT; i++) {
		for (int j = 0; j < FACES; j++) {
			XuatLaBai(deck[i][j], A,suit,faces);
			cout << endl;
		}
	}
}
void TimViTri(int a, LABAI A[], int**& result,int j)
{
	for (int i = 0; i < 52; i++) {
		if (a == A[i].vitri) {
			result[j][0] = A[i].suit;
			result[j][1] = A[i].face;
		}
	}
}

int** dealingForHand(int deck[SUIT][FACES],LABAI A[])
{
	int** result;
	int n = 5;
	result = new int* [n];
	for (int i = 0; i < n; i++) {
		result[i] = new int[2];
	}
	int tempArray[5];
	for (int i = 0; i < 5; i++) {
		tempArray[i] = deck[0][i];
	}
	/*for (int i = 0; i < 5; i++) {
		cout << tempArray[i] << " ";
	}*/
	for (int i = 0; i < 5; i++) {
		TimViTri(tempArray[i], A, result,i);
	}
	/*for (int i = 0; i < 5; i++) {
		cout << "(" << result[i][0] << "," << result[i][1] << ")";
	}*/
	return result;
}

void printHand(int** hand, char suit[][20], char faces[][20], LABAI A[])
{
	for (int i = 0; i < 5; i++) {
		cout << "(" << suit[hand[i][0]] << "," << faces[hand[i][1]] << ")" << " ";
	}
}

void Sort(int a[])
{
	for(int i=0;i<4;i++){
		for(int j=i+1;j<5;j++){
			if(a[i]>a[j])
				swap(a[i],a[j]);
		}
	}
}

int isStraightFlush(int hand[5][2])
{
	int a[5];
	int b[5];
	int k=0;
	for(int i=0;i<5;i++){
		a[k]=hand[i][1];
		k++;
	}
	Sort(a);
	int check=1;
	for(int i=0;i<4;i++){
		if(a[i]+1==a[i+1])
			check++;
	}
	if(check!=5){
		return 0;
	}else{
		int h=0;
		for(int i=0;i<5;i++){
			b[h]=hand[i][0];
			h++;
		}
		Sort(b);
		int check=1;
		for(int i=0;i<4;i++){
			if(b[i]==b[i+1]){
				check++;
			}
		}
		if(check!=5){
			return 0;
		}
	}
	
	return 1;

}
int isFourOfAKind(int hand[5][2])
{	int a[5];
	int b[5];
	int k=0;
	for(int i=0;i<5;i++){
		a[k]=hand[i][0];
		k++;
	}
	Sort(a);
	int check=1;
	for(int i=0;i<4;i++){
		if(a[i]+1==a[i+1])
			check++;
	}
	if(check!=4){
		return 0;
	}else{
		int h=0;
		for(int i=0;i<5;i++){
			b[h]=hand[i][1];
			h++;
		}
		Sort(b);
		int check=1;
		for(int i=0;i<4;i++){
			if(b[i]==b[i+1]){
				check++;
			}
		}
		if(check!=4){
			return 0;
		}
	}
	
	return 1;
}
int isFullHouse(int** hand)
{
	
}
int isFlush(int** hand)
{
	
}
int isStraight(int** hand)
{
	
}
int isThreeOfAKind(int** hand)
{
	
}

int isTwoPair(int** hand)
{
	
}
int isOnePair(int** hand)
{
	
}

void KiemTraCacTruongHop(int** hand)
{
	if(isStraightFlush(hand)){
		cout<<" Straight Flush";
	}else{
		if(isFourOfAKind(hand)){
			cout<<"Four of a kind";
		}else{
			if(isFullHouse(hand)){
				cout<<"Full House";
			}else{
				if(isFlush(hand)){
					cout<<"Flush";
				}else{
					if(isStraight(hand)){
						cout<<"Straight";
					}else{
						if(isThreeOfAKind(hand)){
							cout<<"Three of A kind";
						}else{
							if(isTwoPair(hand)){
								cout<<"Two pair";
							}else{
								if(isOnePair(hand)){
									cout<<"one pair";
								}else{
									cout<<"khong co truong hop nao ca";
								}
							}
						}
					}
				}
			}
		}
	}
}

int main()
{
	
	LABAI A[52];
	int  deck[SUIT][FACES];
	shuffleCards(deck,A);// Xao tron the bai. Day giong nhu viec xao bai truoc khi chia
	//XuatMang(deck);
	char suit[4][20]= { "Hearts", "Diamonds", "Clubs", "Spades" };
	char faces[13][20] = { "Ace", "Two", "Three", "Four", "Five","Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen","King" };
	printCardsShuffling(deck, suit, faces, A);
	int** hand = dealingForHand(deck,A);
	cout << "5 la bai cua nguoi do la: \n";
	printHand(hand, suit, faces, A);
	KiemTraCacTruongHop(hand);

}
