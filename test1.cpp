#include <glut.h>
#include "imageloader.h"
#include "texturemodel.h"
#include "linedmodel.h"
#include <math.h>

// Định nghĩa hằng số PI nếu chưa có để dùng cho tính toán lượng giác
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace test1 {

    TextureModel Cube, Wall, Wallside, sannha, sannhath, skyTop, loidi, loidi1;
    Vector3 wall1_pos, wall2_pos, wall3_pos, wall4_pos, sannha_pos, sannhath_pos, skyTop_pos, loidi_pos, loidi1_pos, cube_pos;

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

    void drawArchDome3D(float cx, float cy, float cz_front, float r, float depth, int segments) {
        glDisable(GL_TEXTURE_2D); // Tắt texture để tô màu trơn (hoặc bật nếu muốn dán texture)

        // Tính tọa độ Z của mặt sau dựa trên chiều sâu (depth)
        float cz_back = cz_front - depth;

        // --- 1. VẼ BỀ MẶT CONG NỐI HAI NỬA HÌNH TRÒN (VỎ VÒM) ---
        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= segments; i++) {
            float theta = M_PI * (float)i / (float)segments;

            float x_offset = r * cosf(theta);
            float y_offset = r * sinf(theta);

            // Điểm trên nửa hình tròn TRƯỚC
            glVertex3f(cx + x_offset, cy + y_offset, cz_front);

            // Điểm tương ứng trên nửa hình tròn SAU
            glVertex3f(cx + x_offset, cy + y_offset, cz_back);
        }
        glEnd();

        // --- 2. VẼ MẶT PHẲNG ĐẬY PHÍA TRƯỚC (Nửa hình tròn trước) ---
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(cx, cy, cz_front); // Tâm mặt trước
        for (int i = 0; i <= segments; i++) {
            float theta = M_PI * (float)i / (float)segments;
            glVertex3f(cx + r * cosf(theta), cy + r * sinf(theta), cz_front);
        }
        glEnd();

        // --- 3. VẼ MẶT PHẲNG ĐẬY PHÍA SAU (Nửa hình tròn sau) ---
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(cx, cy, cz_back); // Tâm mặt sau
        for (int i = segments; i >= 0; i--) { // Chạy ngược lại để đảo hướng mặt (nhìn từ ngoài vào không bị lỗi hiển thị)
            float theta = M_PI * (float)i / (float)segments;
            glVertex3f(cx + r * cosf(theta), cy + r * sinf(theta), cz_back);
        }
        glEnd();

        glEnable(GL_TEXTURE_2D); // Bật lại texture cho các thành phần khác
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
        sannha.addVertex(point3(-30, 0, 30));
        sannha.addVertex(point3(30, 0, 30));
        sannha.addVertex(point3(30, 0, -30));
        sannha.addVertex(point3(-30, 0, -30));
        sannha.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 10), texCoord2(10, 10), texCoord2(0, 10), texCoord2(0, 0)));
        sannha_pos = point3(0.0f, 0.0f, 0.0f);
    }

    void makeloidi() {
        loidi.clear();
        loidi.setTextureFromBMP("data/nen.bmp");
        loidi.addVertex(point3(-5, 3, 5));
        loidi.addVertex(point3(5, 0, 5));
        loidi.addVertex(point3(5, 0, -5));
        loidi.addVertex(point3(-5, 3, -5));
        loidi.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(5, 0), texCoord2(5, 5), texCoord2(0, 5)));
        loidi_pos = point3(20.0, 0.0, 20.0);
    }

    void makeloidi1() {
        loidi1.clear();
        loidi1.setTextureFromBMP("data/nen.bmp");
        loidi1.addVertex(point3(-25, 3, 5));
        loidi1.addVertex(point3(5, 3, 5));
        loidi1.addVertex(point3(5, 3, -5));
        loidi1.addVertex(point3(-25, 3, -5));
        loidi1.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(5, 0), texCoord2(5, 5), texCoord2(0, 5)));
        loidi1_pos = point3(10.0, 0.0, 20.0);
    }

    void drawWall1() {
        Wallside.clear();
        Wallside.setTextureFromBMP("data/wall.bmp");

        Wallside.addVertex(point3(-15.0, 0.0, 15.0)); // 0: Dưới trái
        Wallside.addVertex(point3(15.0, 0.0, 15.0));
        Wallside.addVertex(point3(15.0, 10.0, 15.0));
        Wallside.addVertex(point3(-15.0, 10.0, 15.0));

        Wallside.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));

        wall1_pos = point3(0.0, 3.0, 0.0);
        wall2_pos = point3(0.0, 3.0, -30.0);
    }

    void drawWallside() {
        Wall.clear();
        Wall.setTextureFromBMP("data/wall.bmp");

        Wall.addVertex(point3(15.0, 0, 15.0)); // 0: Dưới trái
        Wall.addVertex(point3(15.0, 0, -15.0));
        Wall.addVertex(point3(15.0, 10.0, -15.0));
        Wall.addVertex(point3(15.0, 10.0, 15.0));

        Wall.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));

        wall3_pos = point3(0.0, 3.0, 0.0);
        wall4_pos = point3(-30.0, 3.0, 0.0);
    }

    void drawsannhath() {
        sannhath.clear();
        sannhath.setTextureFromBMP("data/Wood.bmp");

        sannhath.addVertex(point3(0, 0, 0)); // 0: Dưới trái
        sannhath.addVertex(point3(0, 0, 30.0));
        sannhath.addVertex(point3(30.0, 0, 30.0));
        sannhath.addVertex(point3(30.0, 0, 0));

        sannhath.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(5, 0), texCoord2(5, 5), texCoord2(0, 5)));

        sannhath_pos = point3(-15.0, 3.0, -15.0);
    }

    void resize(int width, int height) {
        if (height == 0) height = 1;
        const float ar = (float)width / (float)height;
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, ar, 0.1f, 1000.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }


    void drawCube() {
        Cube.clear();
        Cube.setTextureFromBMP("data/bricks.bmp");

        // Mặt trước (Z = 1)
        Cube.addVertex(point3(-0.5, -0.5, 0.5)); // 0: Dưới trái
        Cube.addVertex(point3(0.5, -0.5, 0.5)); // 1: Dưới phải
        Cube.addVertex(point3(0.5, 0.5, 0.5)); // 2: Trên phải
        Cube.addVertex(point3(-0.5, 0.5, 0.5)); // 3: Trên trái

        // Mặt sau (Z = -1)
        Cube.addVertex(point3(-0.5, -0.5, -0.5)); // 4: Dưới trái
        Cube.addVertex(point3(0.5, -0.5, -0.5)); // 5: Dưới phải
        Cube.addVertex(point3(0.5, 0.5, -0.5)); // 6: Trên phải
        Cube.addVertex(point3(-0.5, 0.5, -0.5)); // 7: Trên trái

        // --- 6 MẶT (Quads) ---
        Cube.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Trước
        Cube.addQuad(quadIndex(5, 4, 7, 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Sau
        Cube.addQuad(quadIndex(3, 2, 6, 7, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Trên
        Cube.addQuad(quadIndex(4, 5, 1, 0, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Dưới
        Cube.addQuad(quadIndex(1, 5, 6, 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Phải
        Cube.addQuad(quadIndex(4, 0, 3, 7, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // Trái

        cube_pos = point3(20.0, 0.0, 20.0);
    }

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
        draw(&loidi, loidi_pos);
        draw(&loidi1, loidi1_pos);
        draw(&Cube, cube_pos);
        draw(&skyTop, skyTop_pos);

        // --- THỰC HIỆN VẼ NỬA ĐƯỜNG TRÒN LÊN WALLSIDE ---
        // Màu sắc của nét vẽ nửa đường tròn (Ví dụ: Màu đỏ)
        glColor3f(1.0f, 0.0f, 0.0f);

        // Do wall1_pos tịnh tiến lên y = 3.0 và z = 0.0 nên tọa độ tuyệt đối mặt phẳng Wallside 1 là Z = 15.0
        // Ta vẽ tại tâm X=0.0, Y=3.0 (chính giữa chân bức tường), Bán kính R=5.0, Độ mịn=100 segments.
        // Tọa độ Z=15.01f để không bị "chìm" vào bề mặt texture của tường.
        drawArchDome3D(0.0, 13.0, 15.0, 15.0, 30.0, 100);

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
        drawWallside();
        drawsannhath();
        drawsannha();
        makeloidi();
        makeloidi1();
        makeSkyTop();
        drawCube();

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