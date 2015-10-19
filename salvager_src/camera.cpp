#include "camera.hpp"

Camera::Camera(int ax, int ay, int nwidth, int nheight)
{
    mAnchorX = ax;
    mAnchorY = ay;

    mWidth = nwidth;
    mHeight = nheight;

    mMapX = 0;
    mMapY = 0;
}

void Camera::setCenter(int x, int y)
{
    mMapX = x - (mWidth/2);
    mMapY = y - (mHeight/2);
}

bool Camera::isVisible(int x, int y)
{
    if( x >= mMapX && x < mMapX + mWidth && y >= mMapY && y < mMapY + mHeight) return true;

    return false;
}
