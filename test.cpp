#include <glut.h>
#include "imageloader.h"
#include "texturemodel.h"
#include "linedmodel.h"
#include <math.h>

namespace test {

    TextureModel Wall, Wallside, sannha, sannhath, skyTop;
    Vector3 wall1_pos, wall2_pos, wall3_pos, wall4_pos, sannha_pos, sannhath_pos, skyTop_pos;

    float camX = 5.0f, camZ = 55.0f; // Vị trí bắt đầu của camera
    float lx = 0.0f, lz = -1.0f;     // Vector hướng nhìn ban đầu (nhìn dọc theo trục -Z)
    float angle = -1.5f;           // Góc nhìn ngang (bắt đầu hướng về phía -Z)
    float speed = 0.5f;              // Tốc độ di chuyển
    float heightAngle = 0.0f;       // Góc nhìn dọc (hơi cúi xuống để nhìn thấy lưới)
    float height_view = -0.3f;       // Độ lệch chiều cao hướng nhìn so với tầm mắt

    void draw(TextureModel* m, Vector3 t) {
        glPushMatrix();
        glTranslatef(t.x, t.y, t.z);
        m->draw();
        glPopMatrix();
    }

    void makeSkyTop() {
        skyTop.clear();
        skyTop.setTextureFromBMP("data/skytop.bmp");
        skyTop.addVertex(point3(-100, 100, -100));
        skyTop.addVertex(point3(100, 100, -100));
        skyTop.addVertex(point3(100, 100, 100));
        skyTop.addVertex(point3(-100, 100, 100));
        skyTop.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));

        skyTop_pos = point3(0, 0, 0);
    }

    void drawsannha() {
        sannha.clear();
        sannha.setTextureFromBMP("data/nen.bmp");
        sannha.addVertex(point3(0, 0, 0));
        sannha.addVertex(point3(50, 0, 0));
        sannha.addVertex(point3(50, 0, 50));
        sannha.addVertex(point3(0, 0, 50));
        sannha.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 50), texCoord2(50, 50), texCoord2(50, 0), texCoord2(0, 0)));
        sannha_pos = point3(0.0f, -0.01f, 0.0f);
    }

    void drawWall1() {
		Wallside.clear();
		Wallside.setTextureFromBMP("data/wall.bmp");

		Wallside.addVertex(point3(-15.0, 0.0, 15.0)); // 0: Dưới trái
        Wallside.addVertex(point3(15.0, 0.0, 15.0));
        Wallside.addVertex(point3(15.0, 10.0, 15.0));
		Wallside.addVertex(point3(-15.0, 10.0, 15.0));

		Wallside.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));

        wall1_pos = point3(25.0, 3.0, 25.0);
        wall2_pos = point3(25.0, 3.0, -5.0);
    }

    void drawWall2() {
		Wall.clear();
		Wall.setTextureFromBMP("data/wall.bmp");

		Wall.addVertex(point3(15.0, 0, 15.0)); // 0: Dưới trái
        Wall.addVertex(point3(15.0, 0, -15.0));
        Wall.addVertex(point3(15.0, 10.0, -15.0));
		Wall.addVertex(point3(15.0, 10.0, 15.0));

		Wall.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));

		wall3_pos = point3(25.0, 3.0, 25.0);
		wall4_pos = point3(-5.0, 3.0, 25.0);
    }

    void drawsannhath() {
		sannhath.clear();
        sannhath.setTextureFromBMP("data/Wood.bmp");

        sannhath.addVertex(point3(0, 0, 0)); // 0: Dưới trái
        sannhath.addVertex(point3(0, 0, 30.0));
        sannhath.addVertex(point3(30.0, 0, 30.0));
        sannhath.addVertex(point3(30.0, 0, 0));

        sannhath.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 10), texCoord2(10, 10), texCoord2(10, 0), texCoord2(0, 0)));

        sannhath_pos = point3(10.0, 3.0, 10.0);
    }

    void resize(int width, int height) {
        if (height == 0) height = 1;
        const float ar = (float)width / (float)height;
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
        gluPerspective(45.0f, ar, 0.1f, 1000.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }


    //void drawCube() {
    //    Cube.clear();
    //    Cube.setTextureFromBMP("data/bricks.bmp");

    //    // Mặt trước (Z = 1)
    //    Cube.addVertex(point3(-0.5, -0.5, 0.5)); // 0: Dưới trái
    //    Cube.addVertex(point3(0.5, -0.5, 0.5)); // 1: Dưới phải
    //    Cube.addVertex(point3(0.5, 0.5, 0.5)); // 2: Trên phải
    //    Cube.addVertex(point3(-0.5, 0.5, 0.5)); // 3: Trên trái

    //    // Mặt sau (Z = -1)
    //    Cube.addVertex(point3(-0.5, -0.5, -0.5)); // 4: Dưới trái
    //    Cube.addVertex(point3(0.5, -0.5, -0.5)); // 5: Dưới phải
    //    Cube.addVertex(point3(0.5, 0.5, -0.5)); // 6: Trên phải
    //    Cube.addVertex(point3(-0.5, 0.5, -0.5)); // 7: Trên trái

    //    // --- 6 MẶT (Quads) ---
    //    Cube.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Trước
    //    Cube.addQuad(quadIndex(5, 4, 7, 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Sau
    //    Cube.addQuad(quadIndex(3, 2, 6, 7, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Trên
    //    Cube.addQuad(quadIndex(4, 5, 1, 0, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Dưới
    //    Cube.addQuad(quadIndex(1, 5, 6, 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Phải
    //    Cube.addQuad(quadIndex(4, 0, 3, 7, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Trái

    //    cube_pos = point3(20.0, 0.0, 20.0);
    //}

    void display()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        // --- ĐẶT CAMERA ĐỘNG ---
        gluLookAt(
            camX, 2.0f, camZ,                            // Vị trí camera
            camX + lx, 2.0f + height_view, camZ + lz,    // Điểm nhìn tới
            0.0f, 1.0f, 0.0f                             // Trục Y hướng lên
        );

		glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
		draw(&Wallside, wall1_pos);
        draw(&Wallside, wall2_pos);
        draw(&Wall, wall3_pos);
        draw(&Wall, wall4_pos);
		draw(&sannha, sannha_pos);
		draw(&sannhath, sannhath_pos);

        glPopMatrix();
        glutSwapBuffers();
    }

    // --- HÀM XỬ LÝ XOAY CAMERA 
    void processKeys(unsigned char key, int xx, int yy) {
        switch (key) {
        case '>':
            speed += 0.1f;
            break;
        case '<':
            speed -= 0.1f;
            break;
        case 'w':
            if (heightAngle < 1.5f) {
                heightAngle += 0.05f;
                height_view = sin(heightAngle);
            }
            break;
        case 's': 
            if (heightAngle > (-1.5f)) {
                heightAngle -= 0.05f;
                height_view = sin(heightAngle);
            }
            break;
        case 'a':
            angle -= 0.05f;
            lx = cos(angle);
            lz = sin(angle);
            break;
        case 'd':
            angle += 0.05f;
            lx = cos(angle);
            lz = sin(angle);
            break;
        }
        glutPostRedisplay();
    }

    // HÀM XỬ LÝ DI CHUYỂN
    void processSpecialKeys(int key, int xx, int yy) {
        float fraction = speed;
        switch (key) {
        case GLUT_KEY_LEFT:
            camX += lz * fraction;
            camZ -= lx * fraction;
            break;
        case GLUT_KEY_RIGHT: 
            camX -= lz * fraction;
            camZ += lx * fraction;
            break;
        case GLUT_KEY_UP: 
            camX += lx * fraction;
            camZ += lz * fraction;
            break;
        case GLUT_KEY_DOWN: 
            camX -= lx * fraction;
            camZ -= lz * fraction;
            break;
        }
        glutPostRedisplay();
    }

    void init()
    {
        glClearColor(0, 0, 0, 1);
        glEnable(GL_DEPTH_TEST);

        // BẬT TÍNH NĂNG DÁN ẢNH (Quan trọng)
        glEnable(GL_TEXTURE_2D);

        drawWall1();
        drawWall2();
		drawsannhath();
		drawsannha();

        lx = cos(angle);
        lz = sin(angle);
        height_view = sin(heightAngle);
    }

    int main(int argc, char** argv)
    {
        glutInit(&argc, argv);

        // Chuyển sang GLUT_DOUBLE để camera di chuyển mượt, không bị chớp nháy
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        
        glutInitWindowPosition(50, 50);
        glutInitWindowSize(600, 600);
        glutCreateWindow("test");

        

        glutDisplayFunc(display);
        glutReshapeFunc(resize);
        // Đăng ký các hàm sự kiện bàn phím
        glutKeyboardFunc(processKeys);
        glutSpecialFunc(processSpecialKeys);
        init();
        glutMainLoop();

        return 0;
    }
}