#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define TOGGLE_SIZE 10

//最下位ビットを0番とする

class Toggle{
public:
	const int Size;
	Toggle():
	Toggles(NULL),
	Size(TOGGLE_SIZE)
	{
		Toggles = new bool[Size];
		memset(Toggles, false, sizeof(bool)*Size);
	}

	~Toggle(){
		delete [] Toggles;
	}

	//16進数でスイッチの状態を設定する
	void SetSwitch(int state){
		for(int ii=0; ii<Size; ii++, state>>=1){
			Toggles[ii] = (state&1) ? true : false;
		}
	}

	//スイッチを逆転させる
	void Inverse(){
		for(int ii=0; ii<Size; ii++){
			Toggles[ii] = Toggles[ii] ? false : true;
		}
	}

	//数字をグレーコードに変換
	void Int2GrayCode(int num){
		int gray = num ^ (num>>1);
		SetSwitch(gray);
	}

	void Print(){
		for(int ii=Size-1; 0<=ii; ii--){
			printf("%d", Toggles[ii]);
		}
		printf("\n");
	}
	void Print2File(FILE** file){
		if(*file == NULL){
			return;
		}
		for(int ii=0; ii<Size; ii++){
			fprintf(*file, "%d", Toggles[ii]);
		}
		fprintf(*file, "\n");
	}

	bool GetToggle(int index){
		return Toggles[index];
	}

	int operator-(Toggle& right){
		int point = 0;
		for(int ii=0; ii<Size; ii++){
			if(Toggles[ii] != right.GetToggle(ii)){
				point++;
			}
		}
		return point;
	}

	bool operator==(Toggle& right){
		bool equal = true;
		for(int ii=0; ii<Size; ii++){
			if(Toggles[ii] != right.GetToggle(ii)){
				equal = false;
			}
		}
		return equal;
	}

private:
	bool* Toggles;
};


int main(){
	Toggle* toggle = new Toggle[1025];

	//スイッチの順番を設定
	int state = 0;//スイッチの状態
	for(int ii=0; ii<512; ii++, state++){
		//奇数個目はグレイ・コードで1つずつ追加していく
		toggle[ii*2].Int2GrayCode(state);

		//偶数個目は1つ前の反転
		toggle[ii*2+1].Int2GrayCode(state);
		toggle[ii*2+1].Inverse();
	}
	toggle[1024].Int2GrayCode(0);//仕事終わり

	//トグルを計算してみる
	int salary = 0;
	for(int ii=0; ii<1024; ii++){
		salary += toggle[ii+1]-toggle[ii];
	}
	printf("給料:%dトグル\n", salary);

	//被りチェック
	for(int ii=1; ii<=1024; ii++){
		for(int jj=1; jj<=1024; jj++){
			if(ii == jj){
				continue;
			}
			if(toggle[ii] == toggle[jj]){
				printf("Detict Same\n");
			}
		}
	}


	FILE* fp = fopen("../answer.txt", "w");
	for(int ii=1; ii<=1024; ii++){
		toggle[ii].Print();
		toggle[ii].Print2File(&fp);
	}

	delete [] toggle;
	return 0;
}
