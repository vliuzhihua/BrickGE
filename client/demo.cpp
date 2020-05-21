#include "GL/glew.h"
#include "GL/glut.h"
#include <iostream>
#include "SceneDisplay.h"
#include "tiny_obj_loader.h"

using namespace std;

SceneDisplay sceneDis(100, 100, 900, 900);

#define ONE_MODE 1
#define TWO_MODE 2

GLuint vertexBO, texcoordBO, normalBO, indexBO;
tinyobj::attrib_t attrib;
std::vector<tinyobj::shape_t> shapes;
std::vector<tinyobj::material_t> materials;

//���ǲ���ʾ����ʹ�ô���
void OneDisplay(){
	sceneDis.setShaderState(1);
	
	//glutWireSphere(10, 10, 10);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBO);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, normalBO);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, 0);

	//glBindBuffer(GL_ARRAY_BUFFER, texcoordBO);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//glTexCoordPointer(2, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBO);
	glEnableClientState(GL_INDEX_ARRAY);
	glIndexPointer(GL_UNSIGNED_INT, 0, 0);

	//glDrawArrays(GL_QUADS, 0, attrib.vertices.size());
	//glDrawBuffer(GL_QUADS);
	glDrawElements(GL_TRIANGLE_STRIP, shapes[0].mesh.indices.size(), GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLES, 0, attrib.vertices.size());

	glDisableClientState(GL_INDEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
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

	//

	std::string warn, err;
	std::string file_name = "res/models/brick_rough_ue4ifa0va/ue4ifa0va__LOD0.obj";
	std::string dir_name = "res/models/brick_rough_ue4ifa0va";

	bool re = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, file_name.c_str(), dir_name.c_str());

	glGenBuffers(1, &vertexBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBO);
	glBufferData(GL_ARRAY_BUFFER, attrib.vertices.size() * sizeof(GLfloat), attrib.vertices.data(), GL_STREAM_DRAW);
	
	glGenBuffers(1, &texcoordBO);
	glBindBuffer(GL_ARRAY_BUFFER, texcoordBO);
	glBufferData(GL_ARRAY_BUFFER, attrib.texcoords.size() * sizeof(GLfloat), attrib.texcoords.data(), GL_STREAM_DRAW);

	glGenBuffers(1, &normalBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalBO);
	glBufferData(GL_ARRAY_BUFFER, attrib.normals.size() * sizeof(GLfloat), attrib.normals.data(), GL_STREAM_DRAW);

	glGenBuffers(1, &indexBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shapes[0].mesh.indices.size() * sizeof(unsigned int), shapes[0].mesh.indices.data(), GL_STATIC_DRAW);
	
	
	sceneDis.start();
}