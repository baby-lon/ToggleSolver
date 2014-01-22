#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define TOGGLE_SIZE 10

//�ŉ��ʃr�b�g��0�ԂƂ���

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

	//16�i���ŃX�C�b�`�̏�Ԃ�ݒ肷��
	void SetSwitch(int state){
		for(int ii=0; ii<Size; ii++, state>>=1){
			Toggles[ii] = (state&1) ? true : false;
		}
	}

	//�X�C�b�`���t�]������
	void Inverse(){
		for(int ii=0; ii<Size; ii++){
			Toggles[ii] = Toggles[ii] ? false : true;
		}
	}

	//�������O���[�R�[�h�ɕϊ�
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

	//�X�C�b�`�̏��Ԃ�ݒ�
	int state = 0;//�X�C�b�`�̏��
	for(int ii=0; ii<512; ii++, state++){
		//��ڂ̓O���C�E�R�[�h��1���ǉ����Ă���
		toggle[ii*2].Int2GrayCode(state);

		//�����ڂ�1�O�̔��]
		toggle[ii*2+1].Int2GrayCode(state);
		toggle[ii*2+1].Inverse();
	}
	toggle[1024].Int2GrayCode(0);//�d���I���

	//�g�O�����v�Z���Ă݂�
	int salary = 0;
	for(int ii=0; ii<1024; ii++){
		salary += toggle[ii+1]-toggle[ii];
	}
	printf("����:%d�g�O��\n", salary);

	//���`�F�b�N
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
