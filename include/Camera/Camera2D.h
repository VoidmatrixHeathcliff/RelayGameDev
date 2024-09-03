#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "../../include/vec2/Vec2.h"
#include "../../include/time/Timer.h"
#include "../../include/singleton/Singleton.h"
#include <random>

// 2D摄像机类，用于处理屏幕坐标与世界坐标之间的转换
class Camera2D {
public:
    // 构造函数
    // Viewport_Width: 视口宽度
    // Viewport_Height: 视口高度
    // World_Width: 世界宽度
    // World_Height: 世界高度
    // Focus: 摄像机焦点（初始位置）
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

    // 析构函数
    ~Camera2D() = default;

public:

    // 将屏幕坐标转换为世界坐标
    Vec2 ScreenToWorld(Vec2& screen) const {
        Vec2 world = CameraFocus + screen;
        return world;
    };

    //将世界坐标转换为屏幕坐标
    Vec2 WorldToScreen(Vec2& world) const {
        Vec2 screen = world - CameraFocus;
        return screen;
    };

    // 获取当前缩放比例
    float GetScale() const {
        return Zoom;
    };

    // 设置缩放比例
    void SetScale(float zoom = 1.0f) {
        assert(zoom > 0);
        Zoom = zoom;
    };

    // 缩放摄像机
    void Scale(float zoom = 1.0f) {
        assert(zoom > 0);
        ViewportWidth = zoom * ViewportWidth;
        ViewportHeight = zoom * ViewportHeight;
    };

    // 设置目标位置
    void SetTarget(Vec2 target) {
        assert(target.x >= WorldBoundaryLeft && target.x <= WorldBoundaryRight
            && target.y <= WorldBoundaryBottom && target.y >= WorldBoundaryTop);
        Target.x = target.x;
        Target.y = target.y;
    };

    // 平滑移动到目标位置, 10是完全不平滑， 0是完全移不动 ，smoothing需要大于0
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

    // 平滑移动到指定位置
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

    // 摄像机震动效果
    //void Shake(float intensityX = 5.5f, float intensityY = 5.5f);

    // 摄像机震动效果（圆形） （丐版）（没看懂timer类怎么用）
    void ShakeCircle(float strength) {
        isShaking = true;
        for (size_t i = 0; i < 10; i++)
        {
            CameraFocus.x = (-50 + gen() % 100) / 50.0f * strength;
            CameraFocus.y = (-50 + gen() % 100) / 50.0f * strength;
        }
        isShaking = false;
    };

    // 设置摄像机中心
    //void SetCameraCenter(short int Viewport_Width, short int Viewport_Height);

    // 设置焦点
    void SetFocus(Vec2 Focus) {
        assert(Focus.x >= WorldBoundaryLeft && Focus.x <= WorldBoundaryRight
            && Focus.y >= WorldBoundaryTop && Focus.y <= WorldBoundaryBottom);
        CameraFocus = Focus;
    };

    // 移动摄像机
    void Move(Vec2 delta) {
        if (isShaking)return;
        if (CameraFocus.x >= WorldBoundaryLeft && CameraFocus.x <= WorldBoundaryRight
            && CameraFocus.y >= WorldBoundaryTop && CameraFocus.y <= WorldBoundaryBottom) {
            return;
        };
        CameraFocus += delta;
    };

    // 获取焦点位置
    const Vec2& GetFocus() const {
        return CameraFocus;
    };

    // 设置世界大小
    void SetWorldSize(short int Width, short int Height) {
        WorldBoundaryLeft = -200;
        WorldBoundaryRight = Width - 200;

        WorldBoundaryBottom = 100;
        WorldBoundaryTop = 100 - Height;
    };

    // 检查视口边界
    // 不知道啥意思，所以没做
    //void ViewportCheckBoundaries();

    // 获取焦点矩形
    // 也不知道啥意思
    //void GetFocusRect(float& left, float& top, float& right, float& bottom);

private:
    //std::random_device rd;
    bool isShaking = false;
   // Timer ShakeTime;
    float shakeStrength = 1.0;
    std::mt19937 gen;
    Vec2 Target;          // 目标位置
    Vec2 CameraFocus;     // 摄像机焦点
    Vec2 ViewportCenter;  // 视口中心
    short int ViewportWidth, ViewportHeight;  // 视口宽度和高度
    float Zoom;           // 缩放比例
    float WorldBoundaryLeft, WorldBoundaryTop, WorldBoundaryRight, WorldBoundaryBottom;  // 世界边界
};

#endif // CAMERA2D_H