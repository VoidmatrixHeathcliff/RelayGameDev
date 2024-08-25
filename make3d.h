#ifndef _make3D_h_
#define _make3D_h_
#include <graphics.h>
#include <conio.h>
#include <cmath>
#include <iostream>
#include <vector>

const double PI = 3.1415926535;
const int WIDTH = 800;
const int HEIGHT = 600;

struct Point3D {
    float x, y, z;

    Point3D operator-(const Point3D& other) const {
        return { x - other.x, y - other.y, z - other.z };
    }

    Point3D& operator+=(const Point3D& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Point3D operator+(const Point3D& other) const {
        return { x + other.x, y + other.y, z + other.z };
    }

    Point3D operator*(float scalar) const {
        return { x * scalar, y * scalar, z * scalar };
    }
};

struct Edge {
    Point3D start;
    Point3D end;
};

// 将角度转换为弧度
float degToRad(float angle) {
    return angle * PI / 180.0f;
}

// 矩阵旋转函数
Point3D rotatePoint(const Point3D& point, float angleX, float angleY, float angleZ) {
    float radX = degToRad(angleX);
    float radY = degToRad(angleY);
    float radZ = degToRad(angleZ);

    float cosX = cos(radX);
    float sinX = sin(radX);
    float cosY = cos(radY);
    float sinY = sin(radY);
    float cosZ = cos(radZ);
    float sinZ = sin(radZ);

    // 先绕 Z 轴旋转
    float x1 = point.x * cosZ - point.y * sinZ;
    float y1 = point.x * sinZ + point.y * cosZ;
    float z1 = point.z;

    // 再绕 Y 轴旋转
    float x2 = x1 * cosY + z1 * sinY;
    float z2 = -x1 * sinY + z1 * cosY;

    // 最后绕 X 轴旋转
    float y2 = y1 * cosX - z2 * sinX;
    float z3 = y1 * sinX + z2 * cosX;

    return { x2, y2, z3 };
}

class Cube {
public:
    Cube(Point3D base[4], float sideLength) {
        this->sideLength = sideLength;
        this->edges = generateCubeEdges(base, sideLength);
        this->initialEdges = edges;
        angleX = angleY = angleZ = 0.0f;
    }

    void rotate(float angleX, float angleY, float angleZ) {
        for (Edge& edge : edges) {
            edge.start = rotatePoint(edge.start, angleX, angleY, angleZ);
            edge.end = rotatePoint(edge.end, angleX, angleY, angleZ);
        }
    }

    void move(float dx, float dy, float dz) {
        moveCube(edges, dx, dy, dz);
    }

    void draw(float focalLength) const {
        drawCube(edges, focalLength);
    }

    void resetRotation() {
        edges = initialEdges;
        angleX = angleY = angleZ = 0.0f;
    }

    // 获取立方体左上角的坐标
    Point3D getPosition() const {
        // 假设立方体的左上角是第一条边的起点（通常是前面的一个顶点）
        return edges[0].start;
    }

    // 在Y轴方向上复制立方体
    std::vector<Cube> cubeCopyY(const Cube& original, int rows, int cols, float sideLength, float gap) {
        std::vector<Cube> cubes;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                Cube copy = original;
                copy.move(j * (sideLength + gap), i * (sideLength + gap), 0); // 在XY平面上偏移
                cubes.push_back(copy);
            }
        }
        return cubes;
    }

    // 在Z轴方向上复制立方体
    std::vector<Cube> cubeCopyZ(const Cube& original, int layers, int rows, int cols, float sideLength, float gap) {
        std::vector<Cube> cubes;
        std::vector<Cube> yCubes = cubeCopyY(original, rows, cols, sideLength, gap);
        for (int k = 0; k < layers; ++k) {
            for (const Cube& cube : yCubes) {
                Cube copy = cube;
                copy.move(0, 0, k * (sideLength + gap)); // 在Z方向上偏移
                cubes.push_back(copy);
            }
        }
        return cubes;
    }

private:
    float sideLength;
    float angleX, angleY, angleZ;
    std::vector<Edge> edges;
    std::vector<Edge> initialEdges;
    std::vector<Cube> cubes;

    std::vector<Edge> generateCubeEdges(Point3D base[4], float sideLength) {
        std::vector<Edge> cubeEdges;
        for (int i = 0; i < 4; ++i) {
            Point3D back = { base[i].x, base[i].y, base[i].z - sideLength };
            Point3D backNext = base[(i + 1) % 4] - Point3D{ 0, 0, sideLength };
            cubeEdges.push_back({ base[i], base[(i + 1) % 4] }); // 前面四条边
            cubeEdges.push_back({ back, backNext }); // 后面四条边
            cubeEdges.push_back({ base[i], back }); // 连接前后面的四条边
        }
        return cubeEdges;
    }

    void moveCube(std::vector<Edge>& edges, float dx, float dy, float dz) {
        for (Edge& edge : edges) {
            edge.start.x += dx;
            edge.start.y += dy;
            edge.start.z += dz;
            edge.end.x += dx;
            edge.end.y += dy;
            edge.end.z += dz;
        }
    }

    void drawCube(const std::vector<Edge>& edges, float focalLength) const {
        for (const Edge& edge : edges) {
            float z1 = edge.start.z + focalLength;
            float z2 = edge.end.z + focalLength;
            int x1 = (int)(edge.start.x * focalLength / z1 + WIDTH / 2);
            int y1 = (int)(edge.start.y * focalLength / z1 + HEIGHT / 2);
            int x2 = (int)(edge.end.x * focalLength / z2 + WIDTH / 2);
            int y2 = (int)(edge.end.y * focalLength / z2 + HEIGHT / 2);
            line(x1, y1, x2, y2);
        }
    }
};
// 以下为测试时运行调用
//int main() {
//    initgraph(WIDTH, HEIGHT);
//    BeginBatchDraw();
//
//    float sideLength = 20.0f;
//    Point3D base[4] = {
//        {-sideLength / 2, -sideLength / 2, 0},
//        {sideLength / 2, -sideLength / 2, 0},
//        {sideLength / 2, sideLength / 2, 0},
//        {-sideLength / 2, sideLength / 2, 0}
//    };
//    float gap = 0.f; // 偏移量设
//    Cube originalCube(base, sideLength);
//
//    std::vector<Cube> cubes = originalCube.cubeCopyZ(originalCube, 1, 1, 1, sideLength, gap); // 层、行、列
//
//    float angleX = 0.0f;
//    float angleY = 0.0f;
//    float angleZ = 0.0f;
//    float focalLength = 500.0f;
//
//    // 加载纹理图像
//    IMAGE texture;
//    loadimage(&texture, _T("img/background.png"), sideLength, sideLength);我想把材质固定到一个面一起旋转，但是失败了
//
//    while (true) {
//        cleardevice();
//
//        for (Cube& cube : cubes) {
//            cube.rotate(angleX, angleY, angleZ);
//            cube.draw(focalLength);
//
//            // 获取左上角点的坐标
//            Point3D position = cube.getPosition();
//
//            // 将3D坐标转换为屏幕2D坐标
//            int screenX = (int)(position.x * focalLength / (position.z + focalLength) + WIDTH / 2);
//            int screenY = (int)(position.y * focalLength / (position.z + focalLength) + HEIGHT / 2);
//
//            // 在计算出的屏幕位置上绘制纹理
//            putimage(screenX, screenY, &texture);
//        }
//
//        ExMessage msg;
//        while (peekmessage(&msg)) {
//            switch (msg.vkcode) {
//            case 0x57: angleX += 5.0f; break;
//            case 0x53: angleX -= 5.0f; break;
//            case 0x41: angleY -= 5.0f; break;
//            case 0x44: angleY += 5.0f; break;
//            case 0x51: angleZ -= 5.0f; break;
//            case 0x45: angleZ += 5.0f; break;
//            case VK_UP: // 向上移动
//                for (auto& cube : cubes) cube.move(0.0f, -10.0f, 0.0f);
//                break;
//            case VK_DOWN: // 向下移动
//                for (auto& cube : cubes) cube.move(0.0f, 10.0f, 0.0f);
//                break;
//            case VK_LEFT: // 向左移动
//                for (auto& cube : cubes) cube.move(-10.0f, 0.0f, 0.0f);
//                break;
//            case VK_RIGHT: // 向右移动
//                for (auto& cube : cubes) cube.move(10.0f, 0.0f, 0.0f);
//                break;
//            case 0x52: // 重置旋转
//                angleX = angleY = angleZ = 0.0f;
//                for (auto& cube : cubes) cube.resetRotation();
//                break;
//            case 0x1B: // 退出程序
//                closegraph();
//                return 0;
//            }
//        }
//
//        Sleep(50);
//        FlushBatchDraw();
//    }
//    EndBatchDraw();
//    return 0;
//}
//




#endif // !_make3d_h_

