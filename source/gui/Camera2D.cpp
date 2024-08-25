#include "../../include/Camera/Camera2D.h"

class Camera2D {
public:
    Camera2D(short int Viewport_Width, short int Viewport_Height,
        short int World_Width, short int World_Height,
        Vec2 Focus(0.0f, 0.0f)):
        ViewportCenter(Viewport_Width * 0.5f, Viewport_Height * 0.5f),
        ViewportWidth(Viewport_Width),
        ViewportHeight(Viewport_Height),
        WorldBoundaryLeft(-World_Width * 0.5f),
        WorldBoundaryTop(-World_Height * 0.5f),
        WorldBoundaryRight(World_Width * 0.5f),
        WorldBoundaryBottom(World_Height * 0.5f),
        Target(0.0f, 0.0f),
        CameraFocus(Focus),
        Zoom(1.0f),
        rd(),
        gen(rd()){}

    ~Camera2D() = default;

    void ScreenToWorld(Vec2 screen, Vec2& world) const {
        world = CameraFocus - (screen - ViewportCenter) / Zoom;
    }

    void WorldToScreen(Vec2 world, Vec2& screen) const {
        screen = ViewportCenter + (CameraFocus - world) * Zoom;
    }

    float GetScale() const { return Zoom; }

    void SetScale(float zoom = 1.0f){
        Zoom = zoom;
    }

    void Scale(float zoom = 1.0f){
        Zoom += zoom;
    }

    void SmoothMoveToPosition(Vec2 target, float smoothing = 0.5f) {
        CameraFocus += (target - CameraFocus) * smoothing;
    }

    void SetTarget(Vec2 target) {
        Target = target;
    }

    void SmoothMoveToTarget(float smoothing = 0.5f) {
        CameraFocus += (Target - CameraFocus) * smoothing;
    }

    void Shake(float intensityX = 5.5f, float intensityY = 5.5f) {
        std::uniform_real_distribution<float> disX(-intensityX, intensityX);
        std::uniform_real_distribution<float> disY(-intensityY, intensityY);
        CameraFocus.x += disX(gen);
        CameraFocus.y += disY(gen);
    }

    void ShakeCircle(float intensityX = 5.5f, float intensityY = 5.5f) {
        std::uniform_real_distribution<float> disX(-intensityX, intensityX);
        std::uniform_real_distribution<float> disY(-intensityY, intensityY);
        std::uniform_real_distribution<float> angle(-360.0f, 360.0f);
        float radian = angle(gen) / 360 * 3.1415926535 * 2;
        CameraFocus.x += disX(gen) * std::cos(radian);
        CameraFocus.y += disY(gen) * std::sin(radian);
    }

    void SetCameraCenter(short int Viewport_Width, short int Viewport_Height) {
        ViewportWidth = Viewport_Width;
        ViewportHeight = Viewport_Height;
        ViewportCenter.x = Viewport_Width * 0.5f;
        ViewportCenter.y = Viewport_Height * 0.5f;
    }

    void SetFocus(Vec2 Focus) {
        CameraFocus = Focus;
    }

    void Move(Vec2 delta) {
        CameraFocus += delta;
    }

    Vec2 GetFocus() const { return CameraFocus; }

    void SetWorldSize(short int Width, short int Height) {
        WorldBoundaryLeft = -Width * 0.5f;
        WorldBoundaryTop = -Height * 0.5f;
        WorldBoundaryRight = Width * 0.5f;
        WorldBoundaryBottom = Height * 0.5f;
    }

    void ViewportCheckBoundaries() {
        float scaledOffsetX = ViewportCenter.x / Zoom;
        float scaledOffsetY = ViewportCenter.y / Zoom;
        CameraFocus.x = std::max(WorldBoundaryLeft + scaledOffsetX, std::min(CameraFocus.x, WorldBoundaryRight - scaledOffsetX));
        CameraFocus.y = std::max(WorldBoundaryTop + scaledOffsetY, std::min(CameraFocus.y, WorldBoundaryBottom - scaledOffsetY));

        if (ViewportWidth / Zoom > WorldBoundaryRight - WorldBoundaryLeft) {
            CameraFocus.x = (WorldBoundaryLeft + WorldBoundaryRight) * 0.5f;
        }
        if (ViewportHeight / Zoom > WorldBoundaryBottom - WorldBoundaryTop) {
            CameraFocus.y = (WorldBoundaryTop + WorldBoundaryBottom) * 0.5f;
        }
    }

    void GetFocusRect(float& left, float& top, float& right, float& bottom) {
        left = CameraFocus.x - ViewportCenter.x;
        top = CameraFocus.y - ViewportCenter.y;
        right = CameraFocus.x + ViewportCenter.x;
        bottom = CameraFocus.y + ViewportCenter.y;
    }
};
