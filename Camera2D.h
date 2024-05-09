#ifndef CAMERA2D_H
#define CAMERA2D_H

#include <cmath>
#include <random>
//Camera2D��һ����2D��������࣬��Ҫ������ʵ��2D���ӽ�ת�����Լ�һЩ�򵥵���������ƹ��ܡ�
class Camera2D {
public:
    //���캯���������ӿڴ�С�������С���Լ�����λ��
    Camera2D(float Viewport_Width, float Viewport_Height,
        float World_Width, float World_Height,
        float FocusX = 0, float FocusY = 0);
 
    //��������
    ~Camera2D() = default;

    //ȡ���������X���ű���
    float GetScaleX() const;

    //ȡ���������Y���ű���
    float GetScaleY() const;

    //��������������ű���
    void SetScale(float Zoom_Width = 1, float Zoom_Height = 1);

    //�������ĳ���ƶ�������ƽ��Ч��
    void SmoothMoveToPosition(float targetX, float targetY, float smoothing = 0.5f);

    //����Ŀ���
    void SetTarget(float targetX, float targetY);

    //�ƶ���Ŀ��㣬����ƽ��Ч����
    void SmoothMoveToTarget(float smoothing = 0.5f);

    //������������������Ч��
    void Shake(float intensityX = 5.5f, float intensityY = 5.5f);

    //�������Բ�����򶶶����������Ч��
    void ShakeCircle(float intensityX = 5.5f, float intensityY = 5.5f);
    //�����ӿڴ�С
    void SetCameraCenter(short int Viewport_Width, short int Viewport_Height);

    //�������굽��������
    void ScreenToWorld(float screenX, float screenY, float& worldX, float& worldY) const;

    //�������굽��������
    void WorldToScreen(float worldX, float worldY, float& screenX, float& screenY) const;

    //���ý���λ��
    void SetFocus(float FocusX, float FocusY);

    //�ƶ������λ��
    void Move(float deltaX, float deltaY);

    //ȡ�ý���λ��X
    float GetFocusX() const;

    //ȡ�ý���λ��Y
    float GetFocusY() const;

    //���������С
    void SetWorldSize(float Width, float Height);

    //��������߽�
    bool SetWorldBoundaries(float left, float top, float right, float bottom);

    //����ӿ�λ�ã���ֹ����������߽�
    bool ViewportCheckBoundaries();

    //��齹��λ�÷�ֹ����������߽�
    bool CheckBoundaries();

    //ȡ���ӿھ���
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