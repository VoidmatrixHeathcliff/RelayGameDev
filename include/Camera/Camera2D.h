#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "../../include/vec2/Vec2.h"
#include "../../include/time/Timer.h"
#include "../../include/singleton/Singleton.h"
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
        Vec2 Focus()) :CameraFocus(Focus()), ViewportWidth(Viewport_Width),
        ViewportHeight(Viewport_Height)
    {
        WorldBoundaryLeft = -200;
        WorldBoundaryRight = World_Width - 200;

        WorldBoundaryBottom = 100;
        WorldBoundaryTop = 100 - World_Height;
        
        Zoom = 1.0;

        gen();

        //ShakeTime.set()
    };

    // ��������
    ~Camera2D() = default;

public:

    // ����Ļ����ת��Ϊ��������
    Vec2 ScreenToWorld(Vec2& screen) const {
        Vec2 world = CameraFocus + screen;
        return world;
    };

    //����������ת��Ϊ��Ļ����
    Vec2 WorldToScreen(Vec2& world) const {
        Vec2 screen = world - CameraFocus;
        return screen;
    };

    // ��ȡ��ǰ���ű���
    float GetScale() const {
        return Zoom;
    };

    // �������ű���
    void SetScale(float zoom = 1.0f) {
        assert(zoom > 0);
        Zoom = zoom;
    };

    // ���������
    void Scale(float zoom = 1.0f) {
        assert(zoom > 0);
        ViewportWidth = zoom * ViewportWidth;
        ViewportHeight = zoom * ViewportHeight;
    };

    // ����Ŀ��λ��
    void SetTarget(Vec2 target) {
        assert(target.x >= WorldBoundaryLeft && target.x <= WorldBoundaryRight
            && target.y <= WorldBoundaryBottom && target.y >= WorldBoundaryTop);
        Target.x = target.x;
        Target.y = target.y;
    };

    // ƽ���ƶ���Ŀ��λ��, 10����ȫ��ƽ���� 0����ȫ�Ʋ��� ��smoothing��Ҫ����0
    //TODO
    void SmoothMoveToTarget(float smoothing = 0.5f) {
        assert(smoothing > 0);
        if (isShaking)return;
        CameraFocus = Target;

        while (CameraFocus != Target)
        {
            CameraFocus += (Target - CameraFocus) * 0.1 * smoothing;
        }
    };

    // ƽ���ƶ���ָ��λ��
    void SmoothMoveToPosition(Vec2 target, float smoothing = 0.5f) {
        assert(smoothing > 0);
        assert(target.x >= WorldBoundaryLeft && target.x <= WorldBoundaryRight
            && target.y >= WorldBoundaryTop && target.y <= WorldBoundaryBottom);
        if (isShaking)return;
        Target = target;

        while (CameraFocus != Target)
        {
            CameraFocus += (Target - CameraFocus) * 0.1 * smoothing;
        }
    };

    // �������Ч��
    //void Shake(float intensityX = 5.5f, float intensityY = 5.5f);

    // �������Ч����Բ�Σ� ��ؤ�棩��û����timer����ô�ã�
    void ShakeCircle(float strength) {
        isShaking = true;
        for (size_t i = 0; i < 10; i++)
        {
            CameraFocus.x = (-50 + gen() % 100) / 50.0f * strength;
            CameraFocus.y = (-50 + gen() % 100) / 50.0f * strength;
        }
        isShaking = false;
    };

    // �������������
    //void SetCameraCenter(short int Viewport_Width, short int Viewport_Height);

    // ���ý���
    void SetFocus(Vec2 Focus) {
        assert(Focus.x >= WorldBoundaryLeft && Focus.x <= WorldBoundaryRight
            && Focus.y >= WorldBoundaryTop && Focus.y <= WorldBoundaryBottom);
        CameraFocus = Focus;
    };

    // �ƶ������
    void Move(Vec2 delta) {
        if (isShaking)return;
        if (CameraFocus.x >= WorldBoundaryLeft && CameraFocus.x <= WorldBoundaryRight
            && CameraFocus.y >= WorldBoundaryTop && CameraFocus.y <= WorldBoundaryBottom) {
            return;
        };
        CameraFocus += delta;
    };

    // ��ȡ����λ��
    const Vec2& GetFocus() const {
        return CameraFocus;
    };

    // ���������С
    void SetWorldSize(short int Width, short int Height) {
        WorldBoundaryLeft = -200;
        WorldBoundaryRight = Width - 200;

        WorldBoundaryBottom = 100;
        WorldBoundaryTop = 100 - Height;
    };

    // ����ӿڱ߽�
    // ��֪��ɶ��˼������û��
    //void ViewportCheckBoundaries();

    // ��ȡ�������
    // Ҳ��֪��ɶ��˼
    //void GetFocusRect(float& left, float& top, float& right, float& bottom);

private:
    //std::random_device rd;
    bool isShaking = false;
   // Timer ShakeTime;
    float shakeStrength = 1.0;
    std::mt19937 gen;
    Vec2 Target;          // Ŀ��λ��
    Vec2 CameraFocus;     // ���������
    Vec2 ViewportCenter;  // �ӿ�����
    short int ViewportWidth, ViewportHeight;  // �ӿڿ�Ⱥ͸߶�
    float Zoom;           // ���ű���
    float WorldBoundaryLeft, WorldBoundaryTop, WorldBoundaryRight, WorldBoundaryBottom;  // ����߽�
};

#endif // CAMERA2D_H