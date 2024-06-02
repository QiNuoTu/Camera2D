# Camera2D
Camera2D is a 2D camera class, primarily designed to implement 2D perspective transformation and some basic camera control functionalities.
![GIF](https://github.com/QiNuoTu/Camera2D/assets/76236817/5400a7be-3681-4582-912e-d618a7dd74ba)


---

# Camera2D 类帮助文档

这个文档提供了`Camera2D`类的基本使用指南，包括如何创建对象、设置属性、执行操作和坐标转换。示例代码展示了如何在实际程序中使用这个类。

## 概述
`Camera2D`是一个用于处理2D摄像机视角转换和控制的类。它允许用户设置摄像机的视口大小、世界大小、焦点位置，并且提供了摄像机的缩放、平滑移动、抖动和边界检查等功能。

## 构造函数
```cpp
Camera2D(float Viewport_Width, float Viewport_Height,
        float World_Width, float World_Height,
        float FocusX = 0, float FocusY = 0);
```
- **参数**:
  - `Viewport_Width`: 视口的宽度。
  - `Viewport_Height`: 视口的高度。
  - `World_Width`: 世界（游戏地图或场景）的宽度。
  - `World_Height`: 世界的高度。
  - `FocusX`: 摄像机的焦点X坐标，默认为0。
  - `FocusY`: 摄像机的焦点Y坐标，默认为0。

## 成员函数

### 获取缩放比例
```cpp
float GetScale() const;
```
- **返回值**: 返回摄像机的缩放比例。

### 设置缩放比例
```cpp
void SetScale(float Zoom = 1);
```
- **参数**:
  - `Zoom`: 设置摄像机缩放比例，默认为1。

### 设置缩放比例
```cpp
void Scale(float Zoom = 1);
```
- **参数**:
  - `Zoom`: 缩放摄像机比例，默认为1。

### 平滑移动到指定位置
```cpp
void SmoothMoveToPosition(float targetX, float targetY, float smoothing = 0.5f);
```
- **参数**:
  - `targetX`: 目标的X坐标。
  - `targetY`: 目标的Y坐标。
  - `smoothing`: 平滑效果的系数，默认为0.5f。

### 设置目标点并平滑移动
```cpp
void SetTarget(float targetX, float targetY);
void SmoothMoveToTarget(float smoothing = 0.5f);
```
- **参数**: 同上。

### 摄像机抖动
```cpp
void Shake(float intensityX = 5.5f, float intensityY = 5.5f);
```
- **参数**:
  - `intensityX`: X轴抖动的强度，默认为5.5f。
  - `intensityY`: Y轴抖动的强度，默认为5.5f。

### 摄像机圆形区域抖动
```cpp
void ShakeCircle(float intensityX = 5.5f, float intensityY = 5.5f);
```
- **参数**: 同上。

### 设置视口大小
```cpp
void SetCameraCenter(short int Viewport_Width, short int Viewport_Height);
```
- **参数**: 设置新的视口宽度和高度。

### 坐标转换
```cpp
void ScreenToWorld(float screenX, float screenY, float& worldX, float& worldY) const;
void WorldToScreen(float worldX, float worldY, float& screenX, float& screenY) const;
```
- **参数**:
  - `screenX`, `screenY`: 窗口坐标。
  - `worldX`, `worldY`: 世界坐标。

### 设置焦点位置
```cpp
void SetFocus(float FocusX, float FocusY);
```
- **参数**:
  - `FocusX`: 新的焦点X坐标。
  - `FocusY`: 新的焦点Y坐标。

### 移动摄像机
```cpp
void Move(float deltaX, float deltaY);
```
- **参数**:
  - `deltaX`: 沿X轴的移动量。
  - `deltaY`: 沿Y轴的移动量。

### 获取焦点位置
```cpp
float GetFocusX() const;
float GetFocusY() const;
```
- **返回值**: 分别返回焦点的X和Y坐标。

### 设置世界大小和边界
```cpp
void SetWorldSize(float Width, float Height);
bool SetWorldBoundaries(float left, float top, float right, float bottom);
```
- **参数**: 设置世界的范围和边界。

### 边界检查
```cpp
bool ViewportCheckBoundaries();
bool CheckBoundaries();
```
- **返回值**: 返回一个布尔值，指示摄像机是否在边界内。

### 获取焦点矩形
```cpp
bool GetFocusRect(float& left, float& top, float& right, float& bottom);
```
- **参数**: 输出焦点区域的边界。

## 示例
```cpp
#include "Camera2D.h"

int main() {
    // 创建一个Camera2D对象
    Camera2D camera(800, 600, 2000, 1500); // 假设视口大小为800x600，世界大小为2000x1500

    // 设置摄像机的缩放比例为2倍
    camera.SetScale(2, 2);

    // 平滑移动摄像机到新的目标点
    camera.SmoothMoveToPosition(1000, 750, 0.1f);

    // 摄像机抖动效果
    camera.Shake(10.0f, 10.0f);

    // 检查并修正摄像机位置，确保不超出边界
    if (!camera.ViewportCheckBoundaries()) {
        // 处理边界检查失败的情况
    }

    return 0;
}
```
## 大示例
```cpp
//正确的把窗口坐标到世界坐标
void ScreenToWorld(Camera2D& camera, float screenX, float screenY) {
    float worldX, worldY;
    camera.ScreenToWorld(screenX, screenY, worldX, worldY);
}
//正确的绘制精灵到屏幕上
void DrawTextureAt(Camera2D& camera, Spirit& spirit, float x, float y, float scaleX, float scaleY) {
    float Screen_POINT_X, Screen_POINT_Y;
    camera.WorldToScreen(x, y, Screen_POINT_X, Screen_POINT_Y);
    scaleX *= camera.GetScaleX();
    scaleY *= camera.GetScaleY();
    Screen_POINT_X -= spirit.HalfWidth * scaleX;
    Screen_POINT_Y -= spirit.HalfHeight * scaleY;
    spirit.Draw(Screen_POINT_X, Screen_POINT_Y, scaleX, scaleY);
}
//实际案例千万注意，坐标系是已窗口中心为0且是正向的，
void Example() {
if (Q_Engine.GetKeyState(SPACE_KEY) == KEY_PRESSED) {
    if (Q_Engine.GetKeyState(A_KEY) == KEY_PRESSED) {
        Player2.X = Player2.X + 500 * Q_Engine.GetRenderRate() / 1000;
    }
    if (Q_Engine.GetKeyState(D_KEY) == KEY_PRESSED) {
        Player2.X = Player2.X - 500 * Q_Engine.GetRenderRate() / 1000;
    }
    if (Q_Engine.GetKeyState(W_KEY) == KEY_PRESSED) {
        Player2.Y = Player2.Y + 500 * Q_Engine.GetRenderRate() / 1000;
    }
    if (Q_Engine.GetKeyState(S_KEY) == KEY_PRESSED) {
        Player2.Y = Player2.Y - 500 * Q_Engine.GetRenderRate() / 1000;
    }
    Q_Camera.SmoothMoveToTarget(Player2, 0.1);
} else {
    if (Q_Engine.GetKeyState(A_KEY) == KEY_PRESSED) {
        Player.X = Player.X + 500 * Q_Engine.GetRenderRate() / 1000;
    }
    if (Q_Engine.GetKeyState(D_KEY) == KEY_PRESSED) {
        Player.X = Player.X - 500 * Q_Engine.GetRenderRate() / 1000;
    }
    if (Q_Engine.GetKeyState(W_KEY) == KEY_PRESSED) {
        Player.Y = Player.Y + 500 * Q_Engine.GetRenderRate() / 1000;
    }
    if (Q_Engine.GetKeyState(S_KEY) == KEY_PRESSED) {
        Player.Y = Player.Y - 500 * Q_Engine.GetRenderRate() / 1000;
    }
    Q_Camera.SmoothMoveToTarget(Player, 0.1);
}
if (Q_Engine.GetMouseClick(MOUSE_LEFT_BUTTON)) {
    Q_Camera.ScreenToWorld(Q_Engine.GetMousePosition(), POINT);
}
if (Q_Engine.GetMouseWheelState(VALUE)) {
    float zoom = Zoom + VALUE * 0.1f;
    Q_Camera.SetScale(zoom, zoom);
}
GLTexture1.StandardRender(0, 0);
Q_Camera.WorldToScreen(POINT.X, POINT.Y, _POINT.X, _POINT.Y);
Q_Engine.FillCircle(_POINT.X, _POINT.Y, 10);
GLTexture2.StandardRender(Player.X, Player.Y, 0.01f, 0.01f);
GLTexture3.StandardRender(Player2.X, Player2.Y, 0.05f, 0.05f);
GLSubtitle.RenderSubtitle(std::to_string(Q_FPS), BLUE_ARGB, 0, 0);
}
```
---
