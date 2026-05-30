#include <glut.h>
#include "texturemodel.h"
#include "linedmodel.h"
#include <math.h>
#include <stdlib.h>
// FIX NGAY: TUONG NGOAI BI SAI TEXTURE , VAO TRONG BI MAT NGOI , LOI CHUA XOAY DUOC CAMERA
// FIX NGAY: TUONG NGOAI BI SAI TEXTURE , VAO TRONG BI MAT NGOI , LOI CHUA XOAY DUOC CAMERA
// FIX NGAY: TUONG NGOAI BI SAI TEXTURE , VAO TRONG BI MAT NGOI , LOI CHUA XOAY DUOC CAMERA
// FIX NGAY: TUONG NGOAI BI SAI TEXTURE , VAO TRONG BI MAT NGOI , LOI CHUA XOAY DUOC CAMERA
// FIX NGAY: TUONG NGOAI BI SAI TEXTURE , VAO TRONG BI MAT NGOI , LOI CHUA XOAY DUOC CAMERA
// FIX NGAY	: TUONG NGOAI BI SAI TEXTURE , VAO TRONG BI MAT NGOI , LOI CHUA XOAY DUOC CAMERA

#ifndef PI
#define PI 3.14159265358979323846
#endif

namespace ntdhau {

	float camX = 5.0f, camZ = 15.0f; // Vị trí bắt đầu của camera
	float lx = 0.0f, lz = -1.0f;     // Vector hướng nhìn ban đầu (nhìn dọc theo trục -Z)
	float angle = -1.5f;           // Góc nhìn ngang (bắt đầu hướng về phía -Z)
	float speed = 0.5f;              // Tốc độ di chuyển
	float heightAngle = -0.3f;       // Góc nhìn dọc (hơi cúi xuống để nhìn thấy lưới)
	float height_view = -0.3f;

// Quy uoc ten ngan:
// m... la model, p... la vi tri, w/h/d la rong/cao/sau.
const float yDat = -1.5f;
const float zTrc = -14.0f;
const float zSau = -27.0f;
const float zTam = (zTrc + zSau) / 2.0f;
const float wNha = 24.0f;
const float dNha = zTrc - zSau;

// Model nen moi truong.
TextureModel mSky, mSkyTop, mCo;

// Model phan than nha: tuong duoc tach rieng de giua mat tien co cua vao.
TextureModel mTuongTrc, mTuongTren, mTuongSau, mTuongTrai, mTuongPhai;

// Model mat tien: kinh, cua so, chan tuong xam va khung cua.
TextureModel mKinh, mLam, mCsCao, mCsNho;
TextureModel mChanBen, mChanSau;
TextureModel mKhungBen, mKhungTren;

// Model ben trong va mai.
TextureModel mMai, mDauMai;
TextureModel mSan, mDuong;

Vector3 pSky, pSkyTop, pCo;
Vector3 pTuongTrcTrai, pTuongTrcPhai, pTuongTren;
Vector3 pTuongSau, pTuongTrai, pTuongPhai;
Vector3 pKinhTrai, pKinhPhai, pLam;
Vector3 pChanTrai, pChanPhai, pChanSau;
Vector3 pMai, pDauMai;
Vector3 pSan, pDuong;
Vector3 pKhungTrai, pKhungPhai, pKhungTren;

void ve(TextureModel* m, Vector3 p) {
	glPushMatrix();
	glTranslatef(p.x, p.y, p.z);
	m->draw();
	glPopMatrix();
}

void veMau(TextureModel* m, Vector3 p, float r, float g, float b) {
	glColor3f(r, g, b);
	ve(m, p);
	glColor3f(1.0f, 1.0f, 1.0f);
}

// Tao model dang hop chu nhat co day du 6 mat.
// Dung cho tuong, khung cua, mang kinh, chan tuong va cac khoi don gian.
void taoHop(TextureModel* m, const char* tex, float w, float h, float d, float rx, float ry) {
	m->clear();
	m->setTextureFromBMP(tex);

	float x1 = -w / 2.0f;
	float x2 = w / 2.0f;
	float y1 = 0.0f;
	float y2 = h;
	float z1 = -d / 2.0f;
	float z2 = d / 2.0f;

	m->addVertex(point3(x1, y1, z2)); // 0: truoc trai duoi
	m->addVertex(point3(x2, y1, z2)); // 1: truoc phai duoi
	m->addVertex(point3(x2, y2, z2)); // 2: truoc phai tren
	m->addVertex(point3(x1, y2, z2)); // 3: truoc trai tren
	m->addVertex(point3(x1, y1, z1)); // 4: sau trai duoi
	m->addVertex(point3(x2, y1, z1)); // 5: sau phai duoi
	m->addVertex(point3(x2, y2, z1)); // 6: sau phai tren
	m->addVertex(point3(x1, y2, z1)); // 7: sau trai tren

	m->addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(rx, 0), texCoord2(rx, ry), texCoord2(0, ry)));
	m->addQuad(quadIndex(5, 4, 7, 6, texCoord2(0, 0), texCoord2(rx, 0), texCoord2(rx, ry), texCoord2(0, ry)));
	m->addQuad(quadIndex(4, 0, 3, 7, texCoord2(0, 0), texCoord2(rx, 0), texCoord2(rx, ry), texCoord2(0, ry)));
	m->addQuad(quadIndex(1, 5, 6, 2, texCoord2(0, 0), texCoord2(rx, 0), texCoord2(rx, ry), texCoord2(0, ry)));
	m->addQuad(quadIndex(3, 2, 6, 7, texCoord2(0, 0), texCoord2(rx, 0), texCoord2(rx, ry), texCoord2(0, ry)));
	m->addQuad(quadIndex(4, 5, 1, 0, texCoord2(0, 0), texCoord2(rx, 0), texCoord2(rx, ry), texCoord2(0, ry)));
}

// Tao model mat phang nam ngang tren truc XZ.
// Dung cho san co, san bong ro va duong vao.
void taoMatXZ(TextureModel* m, const char* tex, float w, float d, float rx, float rz) {
	m->clear();
	m->setTextureFromBMP(tex);

	float x1 = -w / 2.0f;
	float x2 = w / 2.0f;
	float z1 = -d / 2.0f;
	float z2 = d / 2.0f;

	m->addVertex(point3(x1, 0.0f, z2));
	m->addVertex(point3(x2, 0.0f, z2));
	m->addVertex(point3(x2, 0.0f, z1));
	m->addVertex(point3(x1, 0.0f, z1));
	m->addQuad(quadIndex(0, 1, 2, 3,
		texCoord2(0, 0), texCoord2(rx, 0), texCoord2(rx, rz), texCoord2(0, rz)));
}

// Tao mat phang nhung chi lay mot vung texture.
// San bong ro dung ham nay de cat bo phan mau thua cua anh nenbongro.bmp.
void taoMatXZCat(TextureModel* m, const char* tex, float w, float d, float s1, float t1, float s2, float t2) {
	m->clear();
	m->setTextureFromBMP(tex);

	float x1 = -w / 2.0f;
	float x2 = w / 2.0f;
	float z1 = -d / 2.0f;
	float z2 = d / 2.0f;

	m->addVertex(point3(x1, 0.0f, z2));
	m->addVertex(point3(x2, 0.0f, z2));
	m->addVertex(point3(x2, 0.0f, z1));
	m->addVertex(point3(x1, 0.0f, z1));
	m->addQuad(quadIndex(0, 1, 2, 3, texCoord2(s1, t1), texCoord2(s2, t1), texCoord2(s2, t2), texCoord2(s1, t2)));
}

void taoSky() {
	mSky.clear();
	mSky.setTextureFromBMP("data/sky.bmp");
	mSky.addVertex(point3(-100, -100, -100));
	mSky.addVertex(point3(100, -100, -100));
	mSky.addVertex(point3(-100, 100, -100));
	mSky.addVertex(point3(100, 100, -100));
	mSky.addVertex(point3(-100, -100, 100));
	mSky.addVertex(point3(100, -100, 100));
	mSky.addVertex(point3(-100, 100, 100));
	mSky.addVertex(point3(100, 100, 100));
	mSky.addQuad(quadIndex(2, 3, 1, 0, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
	mSky.addQuad(quadIndex(6, 7, 5, 4, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
	mSky.addQuad(quadIndex(2, 6, 4, 0, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
	mSky.addQuad(quadIndex(3, 7, 5, 1, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));

	pSky = point3(0, 0, 0);
}

void taoSkyTop() {
	mSkyTop.clear();
	mSkyTop.setTextureFromBMP("data/skytop.bmp");
	mSkyTop.addVertex(point3(-100, 100, -100));
	mSkyTop.addVertex(point3(100, 100, -100));
	mSkyTop.addVertex(point3(100, 100, 100));
	mSkyTop.addVertex(point3(-100, 100, 100));
	mSkyTop.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));

	pSkyTop = point3(0, 0, 0);
}

void taoCo() {
	mCo.clear();
	mCo.setTextureFromBMP("data/nen.bmp");
	mCo.addVertex(point3(-100, yDat, 100));
	mCo.addVertex(point3(100, yDat, 100));
	mCo.addVertex(point3(100, yDat, -100));
	mCo.addVertex(point3(-100, yDat, -100));
	mCo.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(100, 0), texCoord2(100, 100), texCoord2(0, 100)));

	pCo = point3(0, 0, 0);
}

// Cac mang tuong cam duoc tach rieng de tao khoang cua vao o giua mat tien.
void taoTuong() {
	taoHop(&mTuongTrc, "data/wall.bmp", 9.9f, 4.10f, 0.18f, 2.0f, 1.0f);
	taoHop(&mTuongTren, "data/wall.bmp", 4.5f, 2.95f, 0.18f, 1.0f, 1.0f);
	taoHop(&mTuongSau, "data/wall.bmp", wNha + 0.2f, 5.0f, 0.18f, 4.0f, 1.0f);
	taoHop(&mTuongTrai, "data/wall.bmp", 0.18f, 5.0f, dNha + 0.2f, 1.0f, 2.0f);
	taoHop(&mTuongPhai, "data/wall.bmp", 0.18f, 5.0f, dNha + 0.2f, 1.0f, 2.0f);

	pTuongTrcTrai = point3(-7.05f, -0.10f, zTrc);
	pTuongTrcPhai = point3(7.05f, -0.10f, zTrc);
	pTuongTren = point3(0.0f, 1.0f, zTrc);
	pTuongSau = point3(0.0f, -0.15f, zSau);
	pTuongTrai = point3(-wNha / 2.0f, -0.15f, zTam);
	pTuongPhai = point3(wNha / 2.0f, -0.15f, zTam);
}

// Phan chan tuong xam, kinh tang tret, khung cua va san ben trong.
// Cua vao la khoang rong giua hai mang kinh, camera co the di qua.
void taoLoiVao() {
	taoHop(&mKinh, "data/glass.bmp", 10.0f, 1.48f, 0.10f, 2.0f, 1.0f);
	taoHop(&mChanBen, "data/nen.bmp", 0.12f, 1.48f, dNha + 0.6f, 1.0f, 2.0f);
	taoHop(&mChanSau, "data/nen.bmp", wNha + 0.6f, 1.48f, 0.12f, 3.0f, 1.0f);
	taoHop(&mLam, "data/nen.bmp", 24.0f, 0.85f, 0.06f, 4.0f, 1.0f);
	taoHop(&mKhungBen, "data/nen.bmp", 0.18f, 2.5f, 0.20f, 1.0f, 1.0f);
	taoHop(&mKhungTren, "data/nen.bmp", 4.6f, 0.20f, 0.20f, 1.0f, 1.0f);
	taoMatXZCat(&mSan, "data/nenbongro.bmp", 20.0f, 10.5f, 0.0f, 0.0f, 1.0f, 0.68f);
	taoMatXZ(&mDuong, "data/nen.bmp", 4.6f, 7.0f, 1.0f, 2.0f);

	pKinhTrai = point3(-7.15f, yDat, zTrc + 0.12f);
	pKinhPhai = point3(7.15f, yDat, zTrc + 0.12f);
	pChanTrai = point3(-wNha / 2.0f - 0.12f, yDat, zTam);
	pChanPhai = point3(wNha / 2.0f + 0.12f, yDat, zTam);
	pChanSau = point3(0.0f, yDat, zSau - 0.12f);
	pLam = point3(0.0f, 3.90f, zTrc + 0.16f);
	pKhungTrai = point3(-2.35f, yDat, zTrc + 0.22f);
	pKhungPhai = point3(2.35f, yDat, zTrc + 0.22f);
	pKhungTren = point3(0.0f, 0.85f, zTrc + 0.22f);
	pSan = point3(0.0f, yDat + 0.02f, zTam);
	pDuong = point3(0.0f, yDat + 0.01f, zTrc + 3.4f);
}

// Cua so chi la cac khoi mong gan len mat tien.
void taoCuaSo() {
	taoHop(&mCsCao, "data/glass.bmp", 0.42f, 1.0f, 0.06f, 1.0f, 1.0f);
	taoHop(&mCsNho, "data/glass.bmp", 0.36f, 0.40f, 0.06f, 1.0f, 1.0f);
}

void taoNha() {
	taoTuong();
	taoLoiVao();
	taoCuaSo();
}

void veCuaSo() {
	Vector3 p;

	for (int i = 0; i < 9; i++) {
		p = point3(-8.0f + i * 2.0f, 1.95f, zTrc + 0.20f);
		ve(&mCsCao, p);
	}
	for (int i = 0; i < 7; i++) {
		p = point3(-6.0f + i * 2.0f, 3.05f, zTrc + 0.20f);
		ve(&mCsNho, p);
	}
}

void veNha() {
	veMau(&mSan, pSan, 0.78f, 0.78f, 0.74f);
	veMau(&mDuong, pDuong, 0.70f, 0.70f, 0.66f);

	veMau(&mTuongTrai, pTuongTrai, 0.78f, 0.67f, 0.55f);
	veMau(&mTuongPhai, pTuongPhai, 0.78f, 0.67f, 0.55f);
	veMau(&mTuongSau, pTuongSau, 0.78f, 0.67f, 0.55f);
	veMau(&mTuongTrc, pTuongTrcTrai, 0.78f, 0.67f, 0.55f);
	veMau(&mTuongTrc, pTuongTrcPhai, 0.78f, 0.67f, 0.55f);
	veMau(&mTuongTren, pTuongTren, 0.78f, 0.67f, 0.55f);

	veMau(&mKinh, pKinhTrai, 0.72f, 0.90f, 0.96f);
	veMau(&mKinh, pKinhPhai, 0.72f, 0.90f, 0.96f);
	veMau(&mChanBen, pChanTrai, 0.72f, 0.90f, 0.96f);
	veMau(&mChanBen, pChanPhai, 0.72f, 0.90f, 0.96f);
	veMau(&mChanSau, pChanSau, 0.72f, 0.90f, 0.96f);
	veMau(&mLam, pLam, 0.10f, 0.16f, 0.18f);
	veMau(&mKhungBen, pKhungTrai, 0.18f, 0.20f, 0.21f);
	veMau(&mKhungBen, pKhungPhai, 0.18f, 0.20f, 0.21f);
	veMau(&mKhungTren, pKhungTren, 0.18f, 0.20f, 0.21f);

	veCuaSo();

	veMau(&mMai, pMai, 1.0f, 1.0f, 1.0f);
	veMau(&mDauMai, pDauMai, 1.0f, 1.0f, 1.0f);
}

void resize(int w, int h) {
	if (h == 0) h = 1;
	const float ar = (float)w / (float)h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, ar, 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(
		camX, 2.0f, camZ,                            // Vị trí camera
		camX + lx, 2.0f + height_view, camZ + lz,    // Điểm nhìn tới
		0.0f, 1.0f, 0.0f                             // Trục Y hướng lên
	);

	glEnable(GL_TEXTURE_2D);

	ve(&mSky, pSky);
	ve(&mSkyTop, pSkyTop);
	ve(&mCo, pCo);
	veNha();

	glutSwapBuffers();
	glFlush();
}

void processKeys(unsigned char key, int xx, int yy) {
	switch (key) {
	case '>':
		speed += 0.1f;
		break;
	case '<':
		speed -= 0.1f;
		break;
	case 'w': // Ngẩng lên
		if (heightAngle < 1.5f) {
			heightAngle += 0.05f;
			height_view = sin(heightAngle);
		}
		break;
	case 's': // Cúi xuống
		if (heightAngle > (-1.5f)) {
			heightAngle -= 0.05f;
			height_view = sin(heightAngle);
		}
		break;
	case 'a': // Xoay trái
		angle -= 0.05f;
		lx = cos(angle);
		lz = sin(angle);
		break;
	case 'd': // Xoay phải
		angle += 0.05f;
		lx = cos(angle);
		lz = sin(angle);
		break;
	}
	glutPostRedisplay();
}

void processSpecialKeys(int key, int xx, int yy) {
	float fraction = speed;
	switch (key) {
	case GLUT_KEY_LEFT: // Đi ngang sang trái
		camX += lz * fraction;
		camZ -= lx * fraction;
		break;
	case GLUT_KEY_RIGHT: // Đi ngang sang phải
		camX -= lz * fraction;
		camZ += lx * fraction;
		break;
	case GLUT_KEY_UP: // Tiến tới trước
		camX += lx * fraction;
		camZ += lz * fraction;
		break;
	case GLUT_KEY_DOWN: // Lùi về sau
		camX -= lx * fraction;
		camZ -= lz * fraction;
		break;
	}
	glutPostRedisplay();
}

void init() {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	lx = cos(angle);
	lz = sin(angle);

	taoSky();
	taoSkyTop();
	taoCo();
	taoNha();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("NHA THI DAU Hau");

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutIdleFunc(display);
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

	init();
	glutMainLoop();
	return 0;
}

}
