#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "../../include/vec2/Vec2.h"
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
        Vec2 Focus(0.0f, 0.0f));

    // 析构函数
    ~Camera2D() = default;

    // 将屏幕坐标转换为世界坐标
    void ScreenToWorld(Vec2 screen, Vec2& world) const;

    // 将世界坐标转换为屏幕坐标
    void WorldToScreen(Vec2 world, Vec2& screen) const;

    // 获取当前缩放比例
    float GetScale() const;

    // 设置缩放比例
    void SetScale(float zoom = 1.0f);

    // 缩放摄像机
    void Scale(float zoom = 1.0f);

    // 平滑移动到指定位置
    void SmoothMoveToPosition(Vec2 target, float smoothing = 0.5f);

    // 设置目标位置
    void SetTarget(Vec2 target);

    // 平滑移动到目标位置
    void SmoothMoveToTarget(float smoothing = 0.5f);

    // 摄像机震动效果
    void Shake(float intensityX = 5.5f, float intensityY = 5.5f);

    // 摄像机震动效果（圆形）
    void ShakeCircle(float intensityX = 5.5f, float intensityY = 5.5f);

    // 设置摄像机中心
    void SetCameraCenter(short int Viewport_Width, short int Viewport_Height);

    // 设置焦点
    void SetFocus(Vec2 Focus);

    // 移动摄像机
    void Move(Vec2 delta);

    // 获取焦点位置
    Vec2 GetFocus() const;

    // 设置世界大小
    void SetWorldSize(short int Width, short int Height);

    // 检查视口边界
    void ViewportCheckBoundaries();

    // 获取焦点矩形
    void GetFocusRect(float& left, float& top, float& right, float& bottom);

private:
    std::random_device rd;
    std::mt19937 gen(rd());
    Vec2 Target;          // 目标位置
    Vec2 CameraFocus;     // 摄像机焦点
    Vec2 ViewportCenter;  // 视口中心
    short int ViewportWidth, ViewportHeight;  // 视口宽度和高度
    float Zoom;           // 缩放比例
    float WorldBoundaryLeft, WorldBoundaryTop, WorldBoundaryRight, WorldBoundaryBottom;  // 世界边界
};

#endif // CAMERA2D_H