#include "GL/glew.h"
#include "GL/glut.h"
#include <iostream>
#include "SceneDisplay.h"

using namespace std;

SceneDisplay sceneDis(100, 100, 900, 900);

#define ONE_MODE 1
#define TWO_MODE 2

//���ǲ���ʾ����ʹ�ô���
void OneDisplay(){

	glutWireSphere(10, 10, 10);
}
//ɨ�ɲ���ʾ����ʹ�ô���
void TwoDisplay(){

	glutSolidCone(5, 10, 10, 10);
}

void myKey(unsigned char key, int x, int y){
	switch (key){
	
	}
}
//���Ҽ��Ĳ˵��Ĵ�������
void processMenu(int bt){
	switch (bt){
	case ONE_MODE:
		sceneDis.setUsrDisplayFunc(OneDisplay);
		sceneDis.update();
		printf("AllDisplay..................\n");
		break;
	case TWO_MODE:
		sceneDis.setUsrDisplayFunc(TwoDisplay);
		sceneDis.update();
		printf("SliceDisplay..................\n");
		break;
	}
}
//ϲ���ּ���main������
int main(){
	
	int fillMenu = glutCreateMenu(processMenu);
	glutAddMenuEntry("one", ONE_MODE);
	glutAddMenuEntry("two", TWO_MODE);
	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	sceneDis.setXYZSpan(-30, 30, -30, 30, 4, 50);
	sceneDis.setEyePos(0, 0, 20);
	//sceneDis.setWindowsPos(100, 100, 900, 900);

	sceneDis.setUsrDisplayFunc(OneDisplay);
	//����ʹ��shader�Ĺ���
	sceneDis.setShaderState(1);
	//sceneDis.setUsrKeyboardFunc(myKey);
	//sceneDis.startTimer();
	sceneDis.start();
}