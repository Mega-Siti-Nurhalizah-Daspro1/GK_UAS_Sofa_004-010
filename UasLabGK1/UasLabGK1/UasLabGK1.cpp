#include <glut.h>

// Variabel transformasi global
// Digunakan untuk mengontrol rotasi, zoom, dan translasi pada tampilan objek 3D
float angleX = 0.0f, angleY = 0.0f; // Sudut rotasi pada sumbu X dan Y
float zoom = 1.0f;                  // Faktor zoom (besar-kecil tampilan)
float transX = 0.0f, transY = 0.0f; // Translasi pada sumbu X dan Y

// Fungsi untuk inisialisasi pengaturan OpenGL
void init() {
    glEnable(GL_DEPTH_TEST); // Mengaktifkan depth testing untuk memastikan objek dekat menutupi objek jauh
    glClearColor(0.8f, 0.7f, 0.9f, 1.0f); // Menentukan warna latar belakang (ungu pastel)

    // Menentukan perspektif tampilan
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 800.0 / 600.0, 1.0, 100.0); // Sudut pandang, rasio layar, jarak dekat, jarak jauh
    glMatrixMode(GL_MODELVIEW);
}

// Fungsi untuk menggambar kubus dengan skala, posisi, dan warna tertentu
void drawCube(float x, float y, float z, float r, float g, float b) {
    glColor3f(r, g, b); // Menentukan warna objek
    glPushMatrix(); // Menyimpan transformasi sebelumnya
    glScalef(x, y, z); // Mengubah skala kubus sesuai parameter
    glutSolidCube(1.0f); // Menggambar kubus dengan ukuran standar (1x1x1)
    glPopMatrix(); // Mengembalikan transformasi sebelumnya
}

// Fungsi untuk menggambar sofa 3D
void drawSofa() {
    // Bantalan sofa bawah
    glPushMatrix();
    glTranslatef(0.0f, 0.6f, 0.0f); // Mengatur posisi bantalan sofa
    drawCube(2.0f, 0.3f, 1.0f, 0.6f, 0.3f, 0.2f); // Menggambar bantalan sofa dengan warna coklat muda
    glPopMatrix();

    // Sandaran sofa
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, -0.5f); // Mengatur posisi sandaran sofa
    drawCube(2.0f, 0.7f, 0.2f, 0.5f, 0.25f, 0.15f); // Menggambar sandaran sofa dengan warna coklat lebih gelap
    glPopMatrix();

    // Pegangan sofa kiri
    glPushMatrix();
    glTranslatef(-1.1f, 0.85f, 0.0f); // Mengatur posisi pegangan sofa kiri
    drawCube(0.2f, 0.6f, 1.0f, 0.55f, 0.3f, 0.18f); // Menggambar pegangan sofa dengan warna coklat medium
    glPopMatrix();

    // Pegangan sofa kanan
    glPushMatrix();
    glTranslatef(1.1f, 0.85f, 0.0f); // Mengatur posisi pegangan sofa kanan
    drawCube(0.2f, 0.6f, 1.0f, 0.55f, 0.3f, 0.18f); // Menggambar pegangan sofa dengan warna coklat medium
    glPopMatrix();
}

// Fungsi utama untuk menggambar tampilan 3D
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Membersihkan layar dan buffer kedalaman
    glLoadIdentity();
    gluLookAt(5.0, 5.0, 5.0, // Posisi kamera
        0.0, 0.0, 0.0, // Titik yang dilihat
        0.0, 1.0, 0.0); // Arah atas kamera

    // Menerapkan transformasi global (translasi, zoom, rotasi)
    glTranslatef(transX, transY, 0.0f);
    glScalef(zoom, zoom, zoom);
    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    // Menggambar sofa utama
    drawSofa();

    glutSwapBuffers(); // Menampilkan buffer yang telah digambar ke layar
}

// Fungsi untuk menangani input keyboard
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w': angleX -= 5.0f; break; // Rotasi ke atas pada sumbu X
    case 's': angleX += 5.0f; break; // Rotasi ke bawah pada sumbu X
    case 'a': angleY -= 5.0f; break; // Rotasi ke kiri pada sumbu Y
    case 'd': angleY += 5.0f; break; // Rotasi ke kanan pada sumbu Y
    case '+': zoom += 0.1f; break; // Perbesar tampilan
    case '-': zoom -= 0.1f; break; // Perkecil tampilan
    case 27: exit(0); break; // Keluar dari program saat tombol ESC ditekan
    }
    glutPostRedisplay(); 
}

// Fungsi utama
int main(int argc, char** argv) {
    glutInit(&argc, argv); 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sofa 3D");
    init(); 
    glutDisplayFunc(display); 
    glutKeyboardFunc(keyboard); 
    glutMainLoop(); 
    return 0;
}