#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <cmath>
#include <random>
//Camera2D是一个，2D的摄像机类，主要功能是实现2D的视角转换，以及一些简单的摄像机控制功能。
class Camera2D {
public:
    //构造函数，设置视口大小，世界大小，以及焦点位置
    Camera2D(float Viewport_Width, float Viewport_Height,
        float World_Width, float World_Height,
        float FocusX = 0, float FocusY = 0);
 
    //析构函数
    ~Camera2D() = default;

    //取得摄像机的X缩放比例
    float GetScaleX() const;

    //取得摄像机的Y缩放比例
    float GetScaleY() const;

    //设置摄像机的缩放比例
    void SetScale(float Zoom_Width = 1, float Zoom_Height = 1);

    //焦点跟随某点移动，带有平滑效果
    void SmoothMoveToPosition(float targetX, float targetY, float smoothing = 0.5f);

    //设置目标点
    void SetTarget(float targetX, float targetY);

    //移动到目标点，带有平滑效果。
    void SmoothMoveToTarget(float smoothing = 0.5f);

    //摄像机抖动，带有随机效果
    void Shake(float intensityX = 5.5f, float intensityY = 5.5f);

    //摄像机已圆形区域抖动，带有随机效果
    void ShakeCircle(float intensityX = 5.5f, float intensityY = 5.5f);
    //设置视口大小
    void SetCameraCenter(short int Viewport_Width, short int Viewport_Height);

    //窗口坐标到世界坐标
    void ScreenToWorld(float screenX, float screenY, float& worldX, float& worldY) const;

    //世界坐标到窗口坐标
    void WorldToScreen(float worldX, float worldY, float& screenX, float& screenY) const;

    //设置焦点位置
    void SetFocus(float FocusX, float FocusY);

    //移动摄像机位置
    void Move(float deltaX, float deltaY);

    //取得焦点位置X
    float GetFocusX() const;

    //取得焦点位置Y
    float GetFocusY() const;

    //设置世界大小
    void SetWorldSize(float Width, float Height);

    //设置世界边界
    bool SetWorldBoundaries(float left, float top, float right, float bottom);

    //检查视口位置，防止摄像机超出边界
    bool ViewportCheckBoundaries();

    //检查焦点位置防止摄像机超出边界
    bool CheckBoundaries();

    //取得视口矩形
    bool GetFocusRect(float& left, float& top, float& right, float& bottom);

private:
    std::random_device rd;
    std::mt19937 gen(rd());
    float TargetPositionX, TargetPositionY;
    float CameraFocusX, CameraFocusY;
    float ViewportCenterX, ViewportCenterY, ViewportWidth, ViewportHeight;
    float ZoomWidth, ZoomHeight;
    float BoundaryLeft, BoundaryTop, BoundaryRight, BoundaryBottom;
};

#endif // CAMERA2D_H

// Camera2D implementation should be placed in a corresponding .cpp file