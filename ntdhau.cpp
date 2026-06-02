#include <glut.h>
#include "imageloader.h"
#include "texturemodel.h"
#include "linedmodel.h"
#include <math.h>

namespace ntdhau {

    TextureModel MoHinh_Tuong1, MoHinh_Tuong2, MoHinh_SanNha, MoHinh_SanGo, MoHinh_BauTroi, MoHinh_cot, MoHinh_CauThang, Kinh, Cua, MoHinh_thancay, MoHinh_lacay, Mai_nha, Lan_can;

    Vector3 vitri_tuong1, vitri_tuong2, vitri_tuong3, vitri_tuong4, vitri_san_nha, vitri_san_go, vitri_bau_troi, vitri_cot[9], vitri_cau_thang, vitri_mainha,
        vitri_kinh, vitri_kinh1, vitri_kinh2, vitri_kinh3, vitri_kinh4, vitri_kinh5, vitri_cua, vitri_cua1, vitri_thancay[13], vitri_lan_can;

    float camera_X = 5.0f, camera_Z = 55.0f;
    float vector_huong_X = 0.0f, vector_huong_Z = -1.0f;
    float goc_quay_ngang = -1.5f;
    float toc_do_di_chuyen = 0.5f;
    float goc_quay_doc = 0.0f;
    float do_cao_huong_nhin = -0.3f;

    void ve_mo_hinh(TextureModel* mo_hinh, Vector3 toa_do) {
        glPushMatrix();
        glTranslatef(toa_do.x, toa_do.y, toa_do.z);
        mo_hinh->draw();
        glPopMatrix();
    }

    void tao_bau_troi() {
        MoHinh_BauTroi.clear();
        MoHinh_BauTroi.setTextureFromBMP("data/sky.bmp");

        MoHinh_BauTroi.addVertex(point3(-100, 100, -100));//0
        MoHinh_BauTroi.addVertex(point3(100, 100, -100));//1
        MoHinh_BauTroi.addVertex(point3(100, 100, 100));//2
        MoHinh_BauTroi.addVertex(point3(-100, 100, 100));//3

        MoHinh_BauTroi.addVertex(point3(-100, -1, -100));//4
        MoHinh_BauTroi.addVertex(point3(100, -1, -100));
        MoHinh_BauTroi.addVertex(point3(100, -1, 100));
        MoHinh_BauTroi.addVertex(point3(-100, -1, 100));

        MoHinh_BauTroi.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        MoHinh_BauTroi.addQuad(quadIndex(4, 5, 1, 0, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        MoHinh_BauTroi.addQuad(quadIndex(4, 5, 6, 7, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        MoHinh_BauTroi.addQuad(quadIndex(5, 6, 2, 1, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        MoHinh_BauTroi.addQuad(quadIndex(4, 7, 3, 0, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        MoHinh_BauTroi.addQuad(quadIndex(6, 7, 3, 2, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));

        vitri_bau_troi = point3(0, 0, 0);
    }

    void tao_lancan() {
        Lan_can.clear();
        Lan_can.setTextureFromBMP("data/wood.bmp");
        Lan_can.addVertex(point3(-15.0f, 0.0f, 0.5f)); //0
        Lan_can.addVertex(point3(15.0f, 0.0f, 0.5f)); //1
        Lan_can.addVertex(point3(15.0f, 0.0f, -0.5f)); //2
		Lan_can.addVertex(point3(-12.5f, 0.0f, -0.5f)); //3

        Lan_can.addVertex(point3(-12.5f, 0.0f, -4.5f)); //4
        Lan_can.addVertex(point3(-15.0f, 0.0f, -4.5f));  //5
        
        Lan_can.addVertex(point3(-12.5f, -2.0f, -4.5f)); //6
        Lan_can.addVertex(point3(-15.0f, -2.0f, -4.5f));  //7

        Lan_can.addVertex(point3(-15.0f, -2.0f, 0.5f)); //8
        Lan_can.addVertex(point3(15.0f, -2.0f, 0.5f)); //9
        Lan_can.addVertex(point3(15.0f, -2.0f, -0.5f)); //10
        Lan_can.addVertex(point3(-12.5f, -2.0f, -0.5f)); //11

        Lan_can.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        Lan_can.addQuad(quadIndex(0, 3, 4, 5, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        Lan_can.addQuad(quadIndex(5, 0, 8, 7, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        Lan_can.addQuad(quadIndex(0, 8, 9, 1, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        Lan_can.addQuad(quadIndex(3, 0, 8, 11, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        vitri_lan_can = point3(0.0f, 5.0f, 19.5f);
    }

    void tao_mainha() {
        Mai_nha.clear();
        Mai_nha.setTextureFromBMP("data/roofpro.bmp");
        Mai_nha.addVertex(point3(-15.0f, 10.0f, 5.0f)); //0
        Mai_nha.addVertex(point3(-10.0f, 14.0f, 5.0f)); //1
        Mai_nha.addVertex(point3(-5.0f, 17.0f, 5.0f)); //2
        Mai_nha.addVertex(point3(5.0f, 17.0f, 5.0f)); //3
        Mai_nha.addVertex(point3(10.0f, 14.0f, 5.0f)); //4
        Mai_nha.addVertex(point3(15.0f, 10.0f, 5.0f)); //5

        Mai_nha.addVertex(point3(-15.0f, 10.0f, -30.0f)); // 6
        Mai_nha.addVertex(point3(-10.0f, 14.0f, -30.0f)); // 7
        Mai_nha.addVertex(point3(-5.0f, 17.0f, -30.0f));  // 8
        Mai_nha.addVertex(point3(5.0f, 17.0f, -30.0f));   // 9
        Mai_nha.addVertex(point3(10.0f, 14.0f, -30.0f));  // 10
        Mai_nha.addVertex(point3(15.0f, 10.0f, -30.0f));  //11

        Mai_nha.addQuad(quadIndex(0, 5, 4, 1, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        Mai_nha.addQuad(quadIndex(1, 4, 3, 2, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        Mai_nha.addQuad(quadIndex(6, 11, 10, 7, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        Mai_nha.addQuad(quadIndex(7, 10, 9, 8, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));

        Mai_nha.addQuad(quadIndex(6, 7, 1, 0, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        Mai_nha.addQuad(quadIndex(7, 8, 2, 1, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        Mai_nha.addQuad(quadIndex(8, 9, 3, 2, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        Mai_nha.addQuad(quadIndex(9, 10, 4, 3, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        Mai_nha.addQuad(quadIndex(10, 11, 5, 4, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        Mai_nha.addQuad(quadIndex(6, 11, 5, 0, texCoord2(0, 1), texCoord2(1, 1), texCoord2(1, 0), texCoord2(0, 0)));
        vitri_mainha = point3(0.0f, 3.0f, 15.0f);
    }

    void tao_kinh() {
        Kinh.clear();
        Kinh.setTextureFromBMP("data/glass1.bmp");
        Kinh.addVertex(point3(0.0f, 0.0f, 1.0f));
        Kinh.addVertex(point3(0.0f, 0.0f, -1.0f));
        Kinh.addVertex(point3(0.0f, 10.0f, -4.0f));
        Kinh.addVertex(point3(0.0f, 10.0f, 4.0f));
        Kinh.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        vitri_kinh = point3(15.1f, 3.0f, 11.0f);
        vitri_kinh1 = point3(15.1f, 3.0f, 0.0f);
        vitri_kinh2 = point3(15.1f, 3.0f, -11.0f);
        vitri_kinh3 = point3(-15.1f, 3.0f, 11.0f);
        vitri_kinh4 = point3(-15.1f, 3.0f, 0.0f);
        vitri_kinh5 = point3(-15.1f, 3.0f, -11.0f);
    }

    void tao_cua() {
        Cua.clear();
        Cua.setTextureFromBMP("data/door3.bmp");
        Cua.addVertex(point3(-2.5f, 0.0f, 0.0f));
        Cua.addVertex(point3(2.5f, 0.0f, 0.0f));
        Cua.addVertex(point3(2.5f, 5.0f, 0.0f));
        Cua.addVertex(point3(-2.5f, 5.0f, 0.0f));
        Cua.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        vitri_cua = point3(10.0f, 3.0f, 15.1f);
        vitri_cua1 = point3(-10.0f, 3.0f, 15.1f);
    }

    void tao_san_nha() {
        MoHinh_SanNha.clear();
        MoHinh_SanNha.setTextureFromBMP("data/nen.bmp");
        MoHinh_SanNha.addVertex(point3(100, 0, 100));
        MoHinh_SanNha.addVertex(point3(100, 0, -100));
        MoHinh_SanNha.addVertex(point3(-100, 0, -100));
        MoHinh_SanNha.addVertex(point3(-100, 0, 100));
        MoHinh_SanNha.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 100), texCoord2(100, 100), texCoord2(100, 0), texCoord2(0, 0)));
        vitri_san_nha = point3(0.0f, -0.01f, 0.0f);
    }

    void tao_tuong_2() {
        MoHinh_Tuong2.clear();
        MoHinh_Tuong2.setTextureFromBMP("data/wall.bmp");
        MoHinh_Tuong2.addVertex(point3(-15.0, 0.0, 0));
        MoHinh_Tuong2.addVertex(point3(15.0, 0.0, 0));
        MoHinh_Tuong2.addVertex(point3(15.0, 10.0, 0));
        MoHinh_Tuong2.addVertex(point3(-15.0, 10.0, 0));
        MoHinh_Tuong2.addVertex(point3(-15.0, 0, -30.0));
        MoHinh_Tuong2.addVertex(point3(-15.0, 10.0, -30.0));
        MoHinh_Tuong2.addVertex(point3(15.0, 10.0, -30.0));
        MoHinh_Tuong2.addVertex(point3(15.0, 0, -30.0));

        MoHinh_Tuong2.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_Tuong2.addQuad(quadIndex(0, 1, 7, 4, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_Tuong2.addQuad(quadIndex(0, 3, 5, 4, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_Tuong2.addQuad(quadIndex(5, 4, 7, 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_Tuong2.addQuad(quadIndex(7, 6, 2, 1, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));

        vitri_tuong1 = point3(0, 3.0, 15.0);
    }

    void tao_cot() {
        MoHinh_cot.clear();
        MoHinh_cot.setTextureFromBMP("data/wall.bmp");

        MoHinh_cot.addVertex(point3(1.0, 0, 1.0)); //0
        MoHinh_cot.addVertex(point3(1.0, 0, -1.0)); //1
        MoHinh_cot.addVertex(point3(-1.0, 0, -1.0)); //2
        MoHinh_cot.addVertex(point3(-1.0, 0, 1.0)); //3
        MoHinh_cot.addVertex(point3(1.0, 3, 1.0)); //4
        MoHinh_cot.addVertex(point3(1.0, 3, -1.0)); //5
        MoHinh_cot.addVertex(point3(-1.0, 3, -1.0)); //6
        MoHinh_cot.addVertex(point3(-1.0, 3, 1.0)); //7
        MoHinh_cot.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_cot.addQuad(quadIndex(0, 1, 5, 4, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_cot.addQuad(quadIndex(1, 2, 6, 5, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_cot.addQuad(quadIndex(2, 3, 7, 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_cot.addQuad(quadIndex(0, 3, 7, 4, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_cot.addQuad(quadIndex(4, 5, 6, 7, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));

        vitri_cot[0] = point3(0, 0, 0);
        vitri_cot[1] = point3(12, 0, 0);
        vitri_cot[2] = point3(-12, 0, 0);
        vitri_cot[3] = point3(0, 0, 12);
        vitri_cot[4] = point3(0, 0, -12);
        vitri_cot[5] = point3(12, 0, 12);
        vitri_cot[6] = point3(12, 0, -12);
        vitri_cot[7] = point3(-12, 0, 12);
        vitri_cot[8] = point3(-12, 0, -12);
    }

    void tao_cau_thang() {
        MoHinh_CauThang.clear();
        MoHinh_CauThang.setTextureFromBMP("data/nen.bmp");

        MoHinh_CauThang.addVertex(point3(-15.0, 3, 15.0)); //0
        MoHinh_CauThang.addVertex(point3(-15.0, 3, 20.0)); //1
        MoHinh_CauThang.addVertex(point3(15.0, 3, 20.0)); //2
        MoHinh_CauThang.addVertex(point3(15.0, 3, 15.0)); //3

        MoHinh_CauThang.addVertex(point3(15.0, 0, 15.0));
        MoHinh_CauThang.addVertex(point3(15.0, 0, 20));

        MoHinh_CauThang.addVertex(point3(19.0, 0, 15));
        MoHinh_CauThang.addVertex(point3(19.0, 0, 20));

        MoHinh_CauThang.addVertex(point3(-15.0, 2, 15.0)); //8
        MoHinh_CauThang.addVertex(point3(-15.0, 2, 20.0)); //9
        MoHinh_CauThang.addVertex(point3(15.0, 2, 20.0)); //10
        MoHinh_CauThang.addVertex(point3(15.0, 2, 15.0)); //11

        MoHinh_CauThang.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_CauThang.addQuad(quadIndex(2, 3, 4, 5, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_CauThang.addQuad(quadIndex(3, 4, 6, 6, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_CauThang.addQuad(quadIndex(2, 5, 7, 7, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_CauThang.addQuad(quadIndex(0, 1, 9, 8, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_CauThang.addQuad(quadIndex(3, 2, 10, 11, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_CauThang.addQuad(quadIndex(1, 2, 10, 9, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_CauThang.addQuad(quadIndex(0, 3, 11, 8, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));

        int vertex_index = 12;

        float zz = 20.0f;

        for (int l = 0; l < 6; l++) {
            float xx = 15.0f + (l * 0.5f);
            float yy = 3.0f - (l * 0.5f);

            MoHinh_CauThang.addVertex(point3(xx, yy - 0.5f, zz));
            MoHinh_CauThang.addVertex(point3(xx, yy - 0.5f, zz - 5.0f));

            MoHinh_CauThang.addVertex(point3(xx + 0.5f, yy - 0.5f, zz));
            MoHinh_CauThang.addVertex(point3(xx + 0.5f, yy - 0.5f, zz - 5.0f));

            MoHinh_CauThang.addVertex(point3(xx + 0.5f, yy - 1.0f, zz));
            MoHinh_CauThang.addVertex(point3(xx + 0.5f, yy - 1.0f, zz - 5.0f));

            MoHinh_CauThang.addQuad(quadIndex(
                vertex_index, vertex_index + 1, vertex_index + 3, vertex_index + 2,
                texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)
            ));
            MoHinh_CauThang.addQuad(quadIndex(
                vertex_index + 2, vertex_index + 3, vertex_index + 5, vertex_index + 4,
                texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)
            ));

            vertex_index += 6;
        }

        vitri_cau_thang = point3(0, 0, 0);
    }
    void tao_thancay() {
        MoHinh_thancay.clear();
        MoHinh_thancay.setTextureFromBMP("data/oak.bmp");

        MoHinh_thancay.addVertex(point3(-0.5f, 0.0f, -0.5f));
        MoHinh_thancay.addVertex(point3(0.5f, 0.0f, -0.5f));
        MoHinh_thancay.addVertex(point3(0.5f, 5.0f, -0.5f));
        MoHinh_thancay.addVertex(point3(-0.5f, 5.0f, -0.5f));
        MoHinh_thancay.addVertex(point3(-0.5f, 0.0f, 0.5f));
        MoHinh_thancay.addVertex(point3(0.5f, 0.0f, 0.5f));
        MoHinh_thancay.addVertex(point3(0.5f, 5.0f, 0.5f));
        MoHinh_thancay.addVertex(point3(-0.5f, 5.0f, 0.5f));
        MoHinh_thancay.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1))); // truoc , phai , trai , sau , day , tren
        MoHinh_thancay.addQuad(quadIndex(4, 5, 6, 7, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_thancay.addQuad(quadIndex(1, 5, 6, 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_thancay.addQuad(quadIndex(0, 3, 7, 4, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_thancay.addQuad(quadIndex(0, 4, 5, 1, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_thancay.addQuad(quadIndex(3, 2, 6, 7, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));


        vitri_thancay[0] = point3(-45, 0, 35);
        vitri_thancay[1] = point3(-30, 0, 45);
        vitri_thancay[2] = point3(-10, 0, 40);
        vitri_thancay[3] = point3(15, 0, 42);
        vitri_thancay[4] = point3(38, 0, 34);
        vitri_thancay[5] = point3(45, 0, 10);
        vitri_thancay[6] = point3(40, 0, -25);
        vitri_thancay[7] = point3(-35, 0, -30);
        vitri_thancay[8] = point3(-50, 0, 5);
        vitri_thancay[9] = point3(-15, 0, -45);
        vitri_thancay[10] = point3(5, 0, -48);
        vitri_thancay[11] = point3(25, 0, -42);
        vitri_thancay[12] = point3(55, 0, -5);



    }

    void tao_lacay() {
        MoHinh_lacay.clear();
        MoHinh_lacay.setTextureFromBMP("data/la.bmp");

        MoHinh_lacay.addVertex(point3(-2.5f, 4.0f, -2.5f));
        MoHinh_lacay.addVertex(point3(2.5f, 4.0f, -2.5f));
        MoHinh_lacay.addVertex(point3(2.5f, 7.0f, -2.5f));
        MoHinh_lacay.addVertex(point3(-2.5f, 7.0f, -2.5f));
        MoHinh_lacay.addVertex(point3(-2.5f, 4.0f, 2.5f));
        MoHinh_lacay.addVertex(point3(2.5f, 4.0f, 2.5f));
        MoHinh_lacay.addVertex(point3(2.5f, 7.0f, 2.5f));
        MoHinh_lacay.addVertex(point3(-2.5f, 7.0f, 2.5f));

        MoHinh_lacay.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_lacay.addQuad(quadIndex(4, 5, 6, 7, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_lacay.addQuad(quadIndex(1, 5, 6, 2, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_lacay.addQuad(quadIndex(0, 3, 7, 4, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_lacay.addQuad(quadIndex(0, 4, 5, 1, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
        MoHinh_lacay.addQuad(quadIndex(3, 2, 6, 7, texCoord2(0, 0), texCoord2(1, 0), texCoord2(1, 1), texCoord2(0, 1)));
    }



    void tao_san_go() {
        MoHinh_SanGo.clear();
        MoHinh_SanGo.setTextureFromBMP("data/Wood.bmp");
        MoHinh_SanGo.addVertex(point3(-15.0, 0, 15.0));
        MoHinh_SanGo.addVertex(point3(-15.0, 0, -15.0));
        MoHinh_SanGo.addVertex(point3(15.0, 0, -15.0));
        MoHinh_SanGo.addVertex(point3(15.0, 0, 15.0));
        MoHinh_SanGo.addQuad(quadIndex(0, 1, 2, 3, texCoord2(0, 10), texCoord2(10, 10), texCoord2(10, 0), texCoord2(0, 0)));
        vitri_san_go = point3(0.0f, 3.1f, 0.0f);
    }

    void thay_doi_kich_thuoc_cua_so(int chieu_rong, int chieu_cao) {
        if (chieu_cao == 0) chieu_cao = 1;
        const float ti_le_khung_hinh = (float)chieu_rong / (float)chieu_cao;
        glViewport(0, 0, chieu_rong, chieu_cao);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, ti_le_khung_hinh, 0.1f, 1000.0f);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void hien_thi_man_hinh()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        gluLookAt(
            camera_X, 2.0f, camera_Z,
            camera_X + vector_huong_X, 2.0f + do_cao_huong_nhin, camera_Z + vector_huong_Z,
            0.0f, 1.0f, 0.0f
        );

        glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);

        ve_mo_hinh(&MoHinh_Tuong2, vitri_tuong1);
        ve_mo_hinh(&MoHinh_SanNha, vitri_san_nha);
        ve_mo_hinh(&MoHinh_SanGo, vitri_san_go);
        ve_mo_hinh(&MoHinh_CauThang, vitri_cau_thang);
        ve_mo_hinh(&MoHinh_BauTroi, vitri_bau_troi);
        ve_mo_hinh(&Kinh, vitri_kinh);
        ve_mo_hinh(&Kinh, vitri_kinh1);
        ve_mo_hinh(&Kinh, vitri_kinh2);
        ve_mo_hinh(&Kinh, vitri_kinh3);
        ve_mo_hinh(&Kinh, vitri_kinh4);
        ve_mo_hinh(&Kinh, vitri_kinh5);
        ve_mo_hinh(&Cua, vitri_cua);
        ve_mo_hinh(&Cua, vitri_cua1);
        ve_mo_hinh(&Mai_nha, vitri_mainha);
		ve_mo_hinh(&Lan_can, vitri_lan_can);


        for (int h = 0; h < 9; h++) {
            ve_mo_hinh(&MoHinh_cot, vitri_cot[h]);
        }
        for (int i = 0; i < 13; i++) {
            ve_mo_hinh(&MoHinh_thancay, vitri_thancay[i]);
            ve_mo_hinh(&MoHinh_lacay, vitri_thancay[i]);
        }

        glPopMatrix();

        glutSolidSphere(5, 32, 32);

        glutSwapBuffers();
    }

    void xu_ly_phim_thuong(unsigned char phim_bam, int toa_do_chuot_X, int toa_do_chuot_Y) {
        switch (phim_bam) {
        case '>':
            toc_do_di_chuyen += 0.1f;
            break;
        case '<':
            toc_do_di_chuyen -= 0.1f;
            break;
        case 'w':
            if (goc_quay_doc < 1.5f) {
                goc_quay_doc += 0.05f;
                do_cao_huong_nhin = sin(goc_quay_doc);
            }
            break;
        case 's':
            if (goc_quay_doc > (-1.5f)) {
                goc_quay_doc -= 0.05f;
                do_cao_huong_nhin = sin(goc_quay_doc);
            }
            break;
        case 'a':
            goc_quay_ngang -= 0.05f;
            vector_huong_X = cos(goc_quay_ngang);
            vector_huong_Z = sin(goc_quay_ngang);
            break;
        case 'd':
            goc_quay_ngang += 0.05f;
            vector_huong_X = cos(goc_quay_ngang);
            vector_huong_Z = sin(goc_quay_ngang);
            break;
        }
        glutPostRedisplay();
    }

    void xu_ly_phim_dac_biet(int phim_bam, int toa_do_chuot_X, int toa_do_chuot_Y) {
        float he_so_di_chuyen = toc_do_di_chuyen;
        switch (phim_bam) {
        case GLUT_KEY_LEFT:
            camera_X += vector_huong_Z * he_so_di_chuyen;
            camera_Z -= vector_huong_X * he_so_di_chuyen;
            break;
        case GLUT_KEY_RIGHT:
            camera_X -= vector_huong_Z * he_so_di_chuyen;
            camera_Z += vector_huong_X * he_so_di_chuyen;
            break;
        case GLUT_KEY_UP:
            camera_X += vector_huong_X * he_so_di_chuyen;
            camera_Z += vector_huong_Z * he_so_di_chuyen;
            break;
        case GLUT_KEY_DOWN:
            camera_X -= vector_huong_X * he_so_di_chuyen;
            camera_Z -= vector_huong_Z * he_so_di_chuyen;
            break;
        }
        glutPostRedisplay();
    }

    void khoi_tao_ban_dau()
    {
        glClearColor(0, 0, 0, 1);
        glEnable(GL_DEPTH_TEST);

        glEnable(GL_TEXTURE_2D);

        tao_mainha();
        tao_tuong_2();
        // tao_tuong_1();
        tao_san_go();
        tao_san_nha();
		tao_lancan();
        tao_kinh();
        tao_cua();
        tao_bau_troi();
        tao_cot();
        tao_cau_thang();
        tao_thancay();
        tao_lacay();

        vector_huong_X = cos(goc_quay_ngang);
        vector_huong_Z = sin(goc_quay_ngang);
        do_cao_huong_nhin = sin(goc_quay_doc);
    }

    int main(int argc, char** argv)
    {
        glutInit(&argc, argv);

        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

        glutInitWindowPosition(50, 50);
        glutInitWindowSize(600, 600);
        glutCreateWindow("ntdhau");

        glutDisplayFunc(hien_thi_man_hinh);
        glutReshapeFunc(thay_doi_kich_thuoc_cua_so);
        glutKeyboardFunc(xu_ly_phim_thuong);
        glutSpecialFunc(xu_ly_phim_dac_biet);

        khoi_tao_ban_dau();

        glutMainLoop();

        return 0;
    }
};
