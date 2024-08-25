#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "../../include/vec2/Vec2.h"
#include <random>

// 2D������࣬���ڴ�����Ļ��������������֮���ת��
class Camera2D {
public:
    // ���캯��
    // Viewport_Width: �ӿڿ��
    // Viewport_Height: �ӿڸ߶�
    // World_Width: ������
    // World_Height: ����߶�
    // Focus: ��������㣨��ʼλ�ã�
    Camera2D(short int Viewport_Width, short int Viewport_Height,
        short int World_Width, short int World_Height,
        Vec2 Focus(0.0f, 0.0f));

    // ��������
    ~Camera2D() = default;

    // ����Ļ����ת��Ϊ��������
    void ScreenToWorld(Vec2 screen, Vec2& world) const;

    // ����������ת��Ϊ��Ļ����
    void WorldToScreen(Vec2 world, Vec2& screen) const;

    // ��ȡ��ǰ���ű���
    float GetScale() const;

    // �������ű���
    void SetScale(float zoom = 1.0f);

    // ���������
    void Scale(float zoom = 1.0f);

    // ƽ���ƶ���ָ��λ��
    void SmoothMoveToPosition(Vec2 target, float smoothing = 0.5f);

    // ����Ŀ��λ��
    void SetTarget(Vec2 target);

    // ƽ���ƶ���Ŀ��λ��
    void SmoothMoveToTarget(float smoothing = 0.5f);

    // �������Ч��
    void Shake(float intensityX = 5.5f, float intensityY = 5.5f);

    // �������Ч����Բ�Σ�
    void ShakeCircle(float intensityX = 5.5f, float intensityY = 5.5f);

    // �������������
    void SetCameraCenter(short int Viewport_Width, short int Viewport_Height);

    // ���ý���
    void SetFocus(Vec2 Focus);

    // �ƶ������
    void Move(Vec2 delta);

    // ��ȡ����λ��
    Vec2 GetFocus() const;

    // ���������С
    void SetWorldSize(short int Width, short int Height);

    // ����ӿڱ߽�
    void ViewportCheckBoundaries();

    // ��ȡ�������
    void GetFocusRect(float& left, float& top, float& right, float& bottom);

private:
    std::random_device rd;
    std::mt19937 gen(rd());
    Vec2 Target;          // Ŀ��λ��
    Vec2 CameraFocus;     // ���������
    Vec2 ViewportCenter;  // �ӿ�����
    short int ViewportWidth, ViewportHeight;  // �ӿڿ�Ⱥ͸߶�
    float Zoom;           // ���ű���
    float WorldBoundaryLeft, WorldBoundaryTop, WorldBoundaryRight, WorldBoundaryBottom;  // ����߽�
};

#endif // CAMERA2D_H