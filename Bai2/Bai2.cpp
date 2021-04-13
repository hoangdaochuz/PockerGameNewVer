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

// Ham khoi tao 1 bo bai co 52 la, va 52 la nay xep theo thu tu ban dau cua no.
void KhoiTaoBoBai(int BoBai[])
{
	for (int i = 0; i < SUIT * FACES; i++) {
		BoBai[i] = i + 1;
	}
}
// Ham xao bai len. Giong nhu viec xao bai truoc khi choi de tat ca cac vi tri cua no thay doi.
// VD: Dau tien, khi mo hop bai ra thi bai duoc sap xep san. Gia su con dau tien duoc danh so 1 la con A co.
// khi xao bai len thi con dau tien khong con la con A co nua
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
	int maxIndex = SUIT * FACES - 1;
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

// Ham chuyen doi bo bai tu mang 1 chieu thanh mnag 2 chieu. Hinh dang giong nhu hinh ve trong file project
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
// Bien mang 2 chieu cua bo bai thanh mang cac la bai co kieu LABAI.
// Dieu nay giup biet duoc cac thuoc tinh cua 1 la bai
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


// Ham xao bai 
void shuffleCards(int deck[][FACES], LABAI A[])
{
	
	int BoBai[SUIT * FACES];// Khoi tao 1 mang de chua 52 la bai
	KhoiTaoBoBai(BoBai);// 1 bo bai luc dau co 52 la duoc xep thu tu tu 1 den 52. 
	int Array2D[SUIT][FACES];
	
	ChuyenBoBaiThanhMang2Chieu(BoBai, Array2D);
	BienMang2DThanhLaBai(Array2D, A);
	
	XaoTronBoBai(BoBai);// Xao tron thu tu cua 52 la bai
	int k = 0;
	for (int i = 0; i < SUIT; i++) {
		for (int j = 0; j < FACES; j++) {
			deck[i][j] = BoBai[k++];// gan thu tu da xao cua bo bai vao deck. Day thuc chat la bien mang 2 chieu thanh mang 1 chieu roi xao tron thu tu cua no. Sau do gan vao lai mang 2 chieu
		}
	}
}
// Xuat la bai 
void XuatLaBai(int a, LABAI A[], char* suits[], char* faces[])
{
	for (int i = 0; i < 52; i++) {
		if (a == A[i].vitri) {
			cout << "(" << suits[A[i].suit] << "," << faces[A[i].face] << ")";
		}
	}
}
// Ham in cac thu tu cua la bai da duoc xao
void printCardsShuffling(int deck[][FACES], char* suits[], char* faces[], LABAI A[])
{
	for (int i = 0; i < SUIT; i++) {
		for (int j = 0; j < FACES; j++) {
			XuatLaBai(deck[i][j], A, suits, faces);  // Xuat la bai theo yeu cau cua de
			cout << endl;
		}
	}
}
// Ham tim vi tri cua so thu tu 
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
	int n = 5;// vi nguoi do chi duoc nhan 5 la bai
	// Cap phat dong bo nho cho mang 2 chieu de luu gia tri cua 1 quan bai. Do la suit và face
	result = new int* [n];
	for (int i = 0; i < n; i++) {
		result[i] = new int[2];
	}
	// Khoi tao mang tam 1 chieu de copy 5  quan bai dau tien sau khi duoc xao
	int tempArray[5];
	for (int i = 0; i < 5; i++) {
		tempArray[i] = deck[0][i];
	}
	// Duyet mang tam, voi moi vi tri, kiem tra xem quan bai  dang o vi tri nao so voi luc dau.
	// VD: luc dau quan bai thu nhat luc chua xao bai la A co , co so thu tu la 1. Sau khi xao, vi tri quan bai thu 1 là 6 ro.
	// Nhung luc dau, khi chua xao thi 6 ro co so thu tu la 19.
	// Nhu vay quan bai co stt 19 se o ô(0,0).
	// Do do ta can tim vi tri luc dau cua no thong qua so thu tu. Co the xem so thu tu do la hang so
	for (int i = 0; i < 5; i++) {
		TimViTri(tempArray[i], A, result,i);
	}
	return result;
}
// Ham in ra cac la bai cua nguoi do
void printHand(int** hand, char suit[][20], char faces[][20], LABAI A[])
{
	for (int i = 0; i < 5; i++) {
		cout << "(" << suit[hand[i][0]] << "," << faces[hand[i][1]] << ")" << " ";
	}
}


int main()
{
	LABAI A[52]; //Tao cau truc cua 1 la bai. 1 la bai se co vi tri luc ban dau, 1 cai suit va 1 cai face. Cau truc nay la co dinh trong bo bai 
	int  deck[SUIT][FACES];
	shuffleCards(deck, A);// Xao tron the bai. Day giong nhu viec xao bai truoc khi chia
	char* suit[] = { (char*)"Hearts", (char* )"Diamonds", (char*)"Clubs", (char*)"Spades" };
	char* faces[] = { (char*)"Ace", (char*)"Two", (char*)"Three", (char*)"Four", (char*)"Five",(char*)"Six", (char*)"Seven", (char*)"Eight", (char*)"Nine", (char*)"Ten", (char*)"Jack", (char*)"Queen",(char*)"King" };
	printCardsShuffling(deck, suit, faces, A);
	int** hand = dealingForHand(deck,A);// Ham tra ve 1 cac la bai cua nguoi do
	cout << "5 la bai cua nguoi do la: \n";
	printHand(hand, suit, faces, A);//  in ra cac la bai cua nguoi do
}