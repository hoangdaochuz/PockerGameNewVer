#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
const int SUIT = 4;
const int FACES = 13;
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

void XuatMang(int deck[][FACES])
{
	for (int i = 0; i < SUIT; i++) {
		for (int j = 0; j < FACES; j++) {
			cout << deck[i][j] << " ";
		}
		cout << endl;
	}
}

// Sau khi xao tron cac thu tu cua bo bai xong, ta chuyen no  vao mang 2 chieu de biet duoc vi tri suit va face cua no
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
// Ham xao tron cac la bai
void shuffleCards(int deck[][FACES])
{
	//LABAI A[SUIT * FACES];
	int BoBai[SUIT * FACES];// Khoi tao 1 mang de chua 52 la bai
	KhoiTaoBoBai(BoBai);// 1 bo bai luc dau co 52 la duoc xep tu 1 den 52
	int Array2D[SUIT][FACES];
	//cout << "Bo Bai truoc khi xao la: \n";
	ChuyenBoBaiThanhMang2Chieu(BoBai, Array2D);
	
	
	cout << "Bo bai sau khi xao la: \n";
	XaoTronBoBai(BoBai);// Xao tron thu tu cua 52 la bai
	int k = 0;
	for (int i = 0; i < SUIT; i++) {
		for (int j = 0; j < FACES; j++) {
			deck[i][j] = BoBai[k++];// gan thu tu da xao cua bo bai vao deck. Day thuc chat la bien mang 2 chieu thanh mang 1 chieu roi xao tron thu tu cua no. Sau do gan vao lai mang 2 chieu
		}
	}
    //XuatMang(deck);
}
// Ham in ra cac la bai da duoc xao tron
void printCardsShuffling(int deck[][FACES], char suit[][20], char faces[][20])
{   
    int NumCard=1;
	for(int i=0;i<SUIT;i++){

        for(int j=0;j<FACES;j++){
            if(deck[i][j]==NumCard){
                cout<<"("<<suit[i]<<","<<faces[j]<<")"<<endl;
                i=-1;
                j=-1;
				NumCard++;

            }
        } 
    }
}
// Ham chia bai cho 1 nguoi
int** dealingForHand(int deck[SUIT][FACES])
{
	// cap phat dong cho con tro result de chua 5 la bai. Tronng 5 la bai, moi la co 2 phan tu la suit va face
	int** result;
	int n = 5;
	int NumCard = 1;
	result = new int* [n];
	for (int i = 0; i < n; i++) {
		result[i] = new int[2];
	}

	int k = 0;
	// Tim kiem la bai co thu tu NumCard trong bo bai da duoc xao tron. Sau do gan vi tri dong va cot cua no vao result
	for (int i = 0; i < SUIT; i++)
	{
		for (int j = 0; j < FACES; j++) {
			if (deck[i][j] == NumCard) {
				result[k][0] = i;
				result[k][1] = j;
				NumCard++;
				i = -1;
				j = -1;
				k++;
			}
		}
		if (NumCard > 5) {
			break;
		}
	}
	
	
	return result;
}

// Ham in cac la bai cua 1 nguoi
void printHand(int** hand, char suit[][20], char faces[][20])
{
	for (int i = 0; i < 5; i++) {
		cout << "(" << suit[hand[i][0]] << "," << faces[hand[i][1]] << ")" << " ";
	}
}

void Sort(int a[])
{
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 5; j++) {
			if (a[i] > a[j])
				swap(a[i], a[j]);
		}
	}
}
// Ham kiem tra xem co phai la StraightFlush 
int isStraightFlush(int** hand)
{
	int a[5];
	int b[5];
	int k = 0;
	for (int i = 0; i < 5; i++) {
		a[k] = hand[i][1];
		k++;
	}
	Sort(a);
	int check = 1;
	for (int i = 0; i < 4; i++) {
		if (a[i] + 1 == a[i + 1])
			check++;
	}
	if (check != 5) {
		return 0;
	}
	else {
		int h = 0;
		for (int i = 0; i < 5; i++) {
			b[h] = hand[i][0];
			h++;
		}
		Sort(b);
		int check = 1;
		for (int i = 0; i < 4; i++) {
			if (b[i] == b[i + 1]) {
				check++;
			}
		}
		if (check != 5) {
			return 0;
		}
	}

	return 1;

}

// Ham kiem tra co phai la FourOfAKind
int isFourOfAKind(int** hand)
{
	int a[5];
	int b[5];
	int k = 0;
	for (int i = 0; i < 5; i++) {
		a[k] = hand[i][0];
		k++;
	}
	Sort(a);
	int check = 1;
	for (int i = 0; i < 4; i++) {
		if (a[i] + 1 == a[i + 1])
			check++;
	}
	if (check != 4) {
		return 0;
	}
	else {
		int h = 0;
		for (int i = 0; i < 5; i++) {
			b[h] = hand[i][1];
			h++;
		}
		Sort(b);
		int check = 1;
		for (int i = 0; i < 4; i++) {
			if (b[i] == b[i + 1]) {
				check++;
			}
		}
		if (check != 4) {
			return 0;
		}
	}

	return 1;
}

int demPhanTuTrung(int a[], int n, int x) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		if (a[i] == x) {
			count++;
		}
	}
	return count;
}

// Ham kiem tra xem cp phai FullHouse?
int isFullHouse(int** hand)
{
	int a[5];
	int k = 0;
	for (int i = 0; i < 5; i++)
	{
		a[k] = hand[i][1];
		k++;
	}
	Sort(a);
	int aFirst = a[0];
	int aLast = a[4];
	int m = demPhanTuTrung(a, 5, aFirst);
	int n = demPhanTuTrung(a, 5, aLast);
	if ((m == 3 && n == 2) || (m == 2 && n == 3)) {
		return 1;
	}
	else {
		return 0;
	}
}

// Kiem tra co phai la Flush
int isFlush(int** hand)
{
	int a[5];
	int k = 0;
	for (int i = 0; i < 5; i++) {
		a[k] = hand[i][0];
		k++;
	}
	for (int i = 0; i < 4; i++)
	{
		if (a[i] != a[i + 1]) {
			return 0;
		}
	}
	return 1;
}


// Co phai la Straight k?
int isStraight(int** hand)
{
	int a[5];
	int k = 0;
	for (int i = 0; i < 5; i++) {
		a[k] = hand[i][1];
		k++;
	}
	Sort(a);
	for (int i = 0; i < 4; i++)
	{
		if (a[i] + 1 != a[i + 1]) {
			return 0;
		}
	}
	return 1;
}

// ham kiem tra Three of a kind
int isThreeOfAKind(int** hand)
{
	int a[5];
	int k = 0;
	for (int i = 0; i < 5; i++) {
		a[k] = hand[i][1];
		k++;
	}
	Sort(a);
	int x = a[2];
	if (demPhanTuTrung(a, 5, x) == 3) {
		return 1;
	}
	else {
		return 0;
	}
}

// Ham kiem tra Two pair
int isTwoPair(int** hand)
{
	int a[5];
	int k = 0;
	for (int i = 0; i < 5; i++) {
		a[k] = hand[i][1];
		k++;
	}
	Sort(a);
	int x = a[1];
	int y = a[3];
	if (demPhanTuTrung(a, 5, x) == 2 && demPhanTuTrung(a, 5, y) == 2) {
		return 1;
	}
	else {
		return 0;
	}
}

// Ham kiem tra One pair
int isOnePair(int** hand)
{
	int a[5];
	int k=0;
	for(int i=0;i<5;i++){
		a[k]=hand[i][1];
		k++;
	}
	Sort(a);
	int x=a[1];
	int y=a[3];
	if((demPhanTuTrung(a,5,x)==2&&demPhanTuTrung(a,5,y)!=2)||(demPhanTuTrung(a,5,x)!=2&&demPhanTuTrung(a,5,y)==2)){
		return 1;
	}else{
		return 0;
	}
}


//Ham kiem tra xem 5 la bai cua nguoi do la truong hop nao va tra ve gia tri cho truong hop do
int getHighestCard(int** hand)
{
	if (isStraightFlush(hand)) {
		//cout << " Straight Flush";
		return 8;
	}
	else {
		if (isFourOfAKind(hand)) {
			//cout << "Four of a kind";
			return 7;
		}
		else {
			if (isFullHouse(hand)) {
				//cout << "Full House";
				return 6;
			}
			else {
				if (isFlush(hand)) {
					//cout << "Flush";
					return 5;
				}
				else {
					if (isStraight(hand)) {
						//cout << "Straight";
						return 4;
					}
					else {
						if (isThreeOfAKind(hand)) {
							//cout << "Three of A kind";
							return 3;
						}
						else {
							if (isTwoPair(hand)) {
								//cout << "Two pair";
								return 2;
							}
							else {
								if (isOnePair(hand)) {
									//cout << "one pair";
									return 1;
								}
								else {
									//cout << "khong co truong hop nao ca";
									return 0;
								}
							}
						}
					}
				}
			}
		}
	}
}


// Ham chia bai cho 1 nguoi choi. Nhung khong con la nhung la bai lien tiep, ma tuy thuoc vao so luong nguoi choi
int** DealingForOneHand(int deck[SUIT][FACES], int NumCard,int SoNguoiChoi)
{
	// Ham tuong tu nhu dealingForHand. Khac o cho la NumCard khong phai tang lien tuc ma tang tuy thuoc vao so luong nguoi choi 
	int** result;
	int n = 5;
	result = new int* [n];
	for (int i = 0; i < n; i++) {
		result[i] = new int[2];
	}
	int h = 0;
	
	
	
	for (int j = 0; j < SUIT; j++)
	{

		for (int k = 0; k < FACES; k++) {
			if (deck[j][k] == NumCard) {
				result[h][0] = j;
				result[h][1] = k;
				j = -1;
				k = -1;
				h++;
				NumCard = NumCard + SoNguoiChoi;
				break;
			}
		}
		if (h == 5) {
			break;
		}
		if (NumCard > 52) {
			break;
		}

	}
	return result;
}


// Ham chia bai da duoc xao tron cho n nguoi choi
int*** dealingForHands(int deck[SUIT][FACES], int n)
{

	// Cap phat dong cho mang cac la bai cua n nguoi choi
	int*** FiveCard_Of_N_People;
	FiveCard_Of_N_People = new int** [n];
	for (int i = 0; i < n; i++) {
		FiveCard_Of_N_People[i] = DealingForOneHand(deck,i+1,n);
	}
	return FiveCard_Of_N_People;
}


// In ra tung bo bai cua tung nguoi choi
void printHands(int*** hands, char suit[][20], char faces[][20],int SoNguoiChoi)
{
	for (int i = 0; i < SoNguoiChoi; i++)
	{
		cout << "5 la bai cua nguoi " << i + 1 << " la: \n";
		printHand(hands[i], suit, faces);
		cout << endl;
	}
}

// Ham tra ve so diem cua bo bai  cua 1 nguoi
int getStatusOfHand(int** hand)
{
	return getHighestCard(hand);
}

//Ham liet ke diem cua tung nguoi choi
int* rankingHands(int*** hands, int n)
{
	int* rank;
	rank = new int[n];
	for (int i = 0; i < n; i++)
	{
		rank[i] = getStatusOfHand(hands[i]);
	}
	return rank;
}

// in mang cac diem so cua cac nguoi choi. Theo thu tu nguoi choi thu i thi diem so cua ho la listRank[i]
void InMang(int listRank[],int n)
{
	for (int i = 0; i < n; i++) {
		cout << listRank[i] << " ";
	}
}
int TimMaxInListRankFinal(int ListRankFinal[], int n)
{
	int max = ListRankFinal[0];
	for (int i = 1; i < n; i++)
	{
		if (ListRankFinal[i] > max)
		{
			max = ListRankFinal[i];
		}
	}
	return max;
 }

void printWiner(int ListRankFinal[], int n,int markWiner)
{
	cout << "Nguoi chien thang la: ";
	for(int i=0;i<n;i++){
		if (ListRankFinal[i] == markWiner)
		{
			cout << i+1<<" ";
		}
	}
}

int* evaluateHands(int s, int deck[SUIT][FACES],int n, char suit[][20], char faces[][20])
{
	int* ListRankFinal; // Khoi tao mang de luu danh sach diem cuoi cung cua n nguoi choi. 
	ListRankFinal = new int[n];
	for (int k = 0; k < n; k++)
	{
		ListRankFinal[k] = 0;
	}
	for (int i = 0; i < s; i++)
	{
		shuffleCards(deck);
		int*** hands = dealingForHands(deck, n);
		printHands(hands, suit, faces, n);
		int* listRank = rankingHands(hands, n);
		cout << "Diem cua tung nguoi theo thu tu la: \n";
		InMang(listRank, n);
		cout << endl;
		for (int j = 0; j < n; j++)
		{
			ListRankFinal[j] += listRank[j];
		}

	}
	return ListRankFinal;
}

int main()
{
	srand(time(NULL));
	int  deck[SUIT][FACES];
	cout << "1 NGUOI CHOI\n";
	shuffleCards(deck);// Xao tron the bai. Day giong nhu viec xao bai truoc khi chia
	//XuatMang(deck);
	char suit[4][20]= { "Hearts", "Diamonds", "Clubs", "Spades" };
	char faces[13][20] = { "Ace", "Two", "Three", "Four", "Five","Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen","King" };
	printCardsShuffling(deck, suit, faces);
	int** hand = dealingForHand(deck);
	cout << "5 la bai cua nguoi do la: \n";
	printHand(hand, suit, faces);
	cout << endl;
	int point = getHighestCard(hand);
	cout << "Diem cao nhat cua bo bai nguoi do la: " << point<<endl;
	cout << "2 NGUOI CHOI: \n";
	int n;
	do {
		cout << "Nhap so luong nguoi choi. Khong qua 10 nguoi: ";
		cin >> n;
	} while (n>10||n<0);

	int*** hands= dealingForHands(deck,n);
	printHands(hands, suit, faces,n);
	int* listRank = rankingHands(hands, n);
	cout << "Diem cua tung nguoi theo thu tu la: \n";
	InMang(listRank,n);

	int s;
	cout << "Nhap so lan choi: ";
	cin >> s;
	int* ListRankFinal = evaluateHands(s,deck,n,suit,faces);
	cout << "Diem so cuoi cung cua " << n << " nguoi choi theo thu tu lan luot la: \n";
	for (int i = 0; i < n; i++)
	{
		cout << ListRankFinal[i] << " ";
	}
	int markWinner = TimMaxInListRankFinal(ListRankFinal, n);
	printWiner(ListRankFinal, n, markWinner);
}