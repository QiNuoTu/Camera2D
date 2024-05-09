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
        BoundaryLeft(-World_Width * 0.5),
        BoundaryTop(-World_Height * 0.5),
        BoundaryRight(World_Width * 0.5),
        BoundaryBottom(World_Height * 0.5),
        TargetPositionX(0),
        TargetPositionY(0),
        CameraFocusX(FocusX),
        CameraFocusY(FocusY),
        ZoomWidth(1), ZoomHeight(1) {}

    ~Camera2D() = default;

    float GetScaleX() const { return ZoomWidth; }
    
    float GetScaleY() const { return ZoomHeight; }

    void SetScale(float Zoom_Width = 1, float Zoom_Height = 1)
    {
        ZoomWidth = Zoom_Width;
        ZoomHeight = Zoom_Height;
    }

    void SmoothMoveToPosition(float targetX, float targetY, float smoothing = 0.5f) {
        CameraFocusX += (targetX - CameraFocusX) * smoothing;
        CameraFocusY += (targetY - CameraFocusY) * smoothing;
    }

    void SetTarget(float targetX, float targetY) {
        TargetPositionX = targetX;
        TargetPositionY = targetY;
    }

    void SmoothMoveToTarget(float smoothing = 0.5f) {
        CameraFocusX += (TargetPositionX - CameraFocusX) * smoothing;
        CameraFocusY += (TargetPositionY - CameraFocusY) * smoothing;
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
        float radian = angle(gen) / 2261.94671052f;
        CameraFocusX += disX(gen) * std::cos(radian);
        CameraFocusY += disY(gen) * std::sin(radian);
    }

    void SetCameraCenter(short int Viewport_Width, short int Viewport_Height) {
        ViewportWidth = Viewport_Width;
        ViewportHeight = Viewport_Height;
        ViewportCenterX = ViewportWidth * 0.5f;
        ViewportCenterY = ViewportHeight * 0.5f;
    }

    void ScreenToWorld(float screenX, float screenY, float& worldX, float& worldY) const {
         worldX = CameraFocusX - (screenX - ViewportCenterX) / ZoomWidth;
         worldY = CameraFocusY - (screenY - ViewportCenterY) / ZoomHeight;
    }

    void WorldToScreen(float worldX, float worldY, float& screenX, float& screenY) const {
        screenX = ViewportCenterX + (CameraFocusX - worldX) * ZoomWidth;
        screenY = ViewportCenterY + (CameraFocusY - worldY) * ZoomHeight;
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
        BoundaryLeft = -Width * 0.5f;
        BoundaryTop = -Height * 0.5f;
        BoundaryRight = Width * 0.5f;
        BoundaryBottom = Height * 0.5f;
    }

    bool SetWorldBoundaries(float left, float top, float right, float bottom) {
        if (left < right && top < bottom) {
            BoundaryLeft = left;
            BoundaryTop = top;
            BoundaryRight = right;
            BoundaryBottom = bottom;
            return true;
        }
        return false;
    }

    bool ViewportCheckBoundaries() {
        if (CameraFocusX - ViewportCenterX < BoundaryLeft)   { CameraFocusX = BoundaryLeft + ViewportWidth; }
        if (CameraFocusX + ViewportCenterX > BoundaryRight)  { CameraFocusX = BoundaryRight - ViewportWidth; }
        if (CameraFocusY - ViewportCenterY < BoundaryTop)    { CameraFocusY = BoundaryTop + ViewportHeight; }
        if (CameraFocusY + ViewportCenterY > BoundaryBottom) { CameraFocusY = BoundaryBottom - ViewportHeight; }
    }

    bool CheckBoundaries() {
        if (CameraFocusX < BoundaryLeft)   { CameraFocusX = BoundaryLeft; }
        if (CameraFocusX > BoundaryRight)  { CameraFocusX = BoundaryRight; }
        if (CameraFocusY < BoundaryTop)    { CameraFocusY = BoundaryTop; }
        if (CameraFocusY > BoundaryBottom) { CameraFocusY = BoundaryBottom; }
    }

    bool GetFocusRect(float& left, float& top, float& right, float& bottom) {
        left = CameraFocusX - ViewportCenterX;
        top = CameraFocusY - ViewportCenterY;
        right = ViewportWidth;
        bottom = ViewportHeight;
    }

private:
    std::random_device rd;
    std::mt19937 gen(rd());
    float TargetPositionX, TargetPositionY;
    float CameraFocusX, CameraFocusY;
    float ViewportCenterX, ViewportCenterY, ViewportWidth, ViewportHeight;
    float ZoomWidth, ZoomHeight;
    float BoundaryLeft, BoundaryTop, BoundaryRight, BoundaryBottom;
};
