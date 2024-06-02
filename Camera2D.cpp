#include "Camera2D.h"

class Camera2D {
public:
    Camera2D(float Viewport_Width, float Viewport_Height,
        float World_Width, float World_Height,
        float FocusX = 0, float FocusY = 0) :
        ViewportCenterX(Viewport_Width * 0.5f),
        ViewportCenterY(Viewport_Height * 0.5f),
        ViewportWidth(Viewport_Width),
        ViewportHeight(Viewport_Height),
        WorldBoundaryLeft(-World_Width * 0.5),
        WorldBoundaryTop(-World_Height * 0.5),
        WorldBoundaryRight(World_Width * 0.5),
        WorldBoundaryBottom(World_Height * 0.5),
        TargetX(0),
        TargetY(0),
        CameraFocusX(FocusX),
        CameraFocusY(FocusY),
        Zoom(1){}

    ~Camera2D() = default;

    void ScreenToWorld(float screenX, float screenY, float& worldX, float& worldY) const {
        worldX = CameraFocusX - (screenX - ViewportCenterX) / Zoom;
        worldY = CameraFocusY - (screenY - ViewportCenterY) / Zoom;
    }

    void WorldToScreen(float worldX, float worldY, float& screenX, float& screenY) const {
        screenX = ViewportCenterX + (CameraFocusX - worldX) * Zoom;
        screenY = ViewportCenterY + (CameraFocusY - worldY) * Zoom;
    }

    float GetScale() const { return Zoom; }

    void SetScale(float zoom = 1)
    {
        Zoom = zoom;
    }

    void Scale(float zoom = 1)
    {
        Zoom += zoom;
    }

    void SmoothMoveToPosition(float targetX, float targetY, float smoothing = 0.5f) {
        CameraFocusX += (targetX - CameraFocusX) * smoothing;
        CameraFocusY += (targetY - CameraFocusY) * smoothing;
    }

    void SetTarget(float targetX, float targetY) {
        TargetX = targetX;
        TargetY = targetY;
    }

    void SmoothMoveToTarget(float smoothing = 0.5f) {
        CameraFocusX += (TargetX - CameraFocusX) * smoothing;
        CameraFocusY += (TargetY - CameraFocusY) * smoothing;
    }

    void Shake(float intensityX = 5.5f, float intensityY = 5.5f) {
        std::uniform_real_distribution<float> disX(-intensityX, intensityX);
        std::uniform_real_distribution<float> disY(-intensityY, intensityY);
        CameraFocusX += disX(gen);
        CameraFocusY += disY(gen);
    }

    void ShakeCircle(float intensityX = 5.5f, float intensityY = 5.5f) {
        std::uniform_real_distribution<float> disX(-intensityX, intensityX);
        std::uniform_real_distribution<float> disY(-intensityY, intensityY);
        std::uniform_real_distribution<float> angle(-360.0f, 360.0f);
        float radian = angle(gen) / 360 * 3.1415926535 * 2;
        CameraFocusX += disX(gen) * std::cos(radian);
        CameraFocusY += disY(gen) * std::sin(radian);
    }

    void SetCameraCenter(short int Viewport_Width, short int Viewport_Height) {
        ViewportWidth = Viewport_Width;
        ViewportHeight = Viewport_Height;
        ViewportCenterX = ViewportWidth * 0.5f;
        ViewportCenterY = ViewportHeight * 0.5f;
    }

    void SetFocus(float FocusX, float FocusY) {
        CameraFocusX = FocusX;
        CameraFocusY = FocusY;
    }

    void Move(float deltaX, float deltaY) {
        CameraFocusX += deltaX;
        CameraFocusY += deltaY;
    }

    float GetFocusX() const { return CameraFocusX; }

    float GetFocusY() const { return CameraFocusY; }

    void SetWorldSize(float Width, float Height) {
        WorldBoundaryLeft = -Width * 0.5f;
        WorldBoundaryTop = -Height * 0.5f;
        WorldBoundaryRight = Width * 0.5f;
        WorldBoundaryBottom = Height * 0.5f;
    }

    bool SetWorldBoundaries(float left, float top, float right, float bottom) {
        if (left < right && top < bottom) {
            WorldBoundaryLeft = left;
            WorldBoundaryTop = top;
            WorldBoundaryRight = right;
            WorldBoundaryBottom = bottom;
            return true;
        }
        return false;
    }

    void ViewportCheckBoundaries() {
        float scaledOffsetX = ViewportCenterX / Zoom;
        float scaledOffsetY = ViewportCenterY / Zoom;
        CameraFocusX = std::max(WorldBoundaryLeft + scaledOffsetX, std::min(CameraFocusX, WorldBoundaryRight - scaledOffsetX));
        CameraFocusY = std::max(WorldBoundaryTop + scaledOffsetY, std::min(CameraFocusY, WorldBoundaryBottom - scaledOffsetY));

        if (ViewportWidth / Zoom > WorldBoundaryRight - WorldBoundaryLeft) {
            CameraFocusX = (WorldBoundaryLeft + WorldBoundaryRight) * 0.5f;
        }
        if (ViewportHeight / Zoom > WorldBoundaryBottom - WorldBoundaryTop) {
            CameraFocusY = (WorldBoundaryTop + WorldBoundaryBottom) * 0.5f;
        }
    }

    void GetFocusRect(float& left, float& top, float& right, float& bottom) {
         left = CameraFocusX - ViewportCenterX;
         top = CameraFocusY - ViewportCenterY;
         right = CameraFocusX + ViewportCenterX;
         bottom = CameraFocusY + ViewportCenterY;
    }

private:
    std::random_device rd;
    std::mt19937 gen(rd());
    float TargetX, TargetY;
    float CameraFocusX, CameraFocusY;
    float ViewportCenterX, ViewportCenterY, ViewportWidth, ViewportHeight;
    float Zoom, WorldBoundaryLeft, WorldBoundaryTop, WorldBoundaryRight, WorldBoundaryBottom;
};
