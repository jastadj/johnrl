#ifndef CLASS_CAMERA
#define CLASS_CAMERA

class Camera
{
private:
    int mAnchorX;
    int mAnchorY;

    int mWidth;
    int mHeight;

    //camera used map coordinate for top left corner
    int mMapX;
    int mMapY;

public:
    Camera(int ax, int ay, int nwidth, int nheight);

    void setCenter(int x, int y);

    bool isVisible(int x, int y);

    int getMapX() { return mMapX;}
    int getMapY() { return mMapY;}
    int getWidth() { return mWidth;}
    int getHeight() { return mHeight;}
    int getAnchorX() { return mAnchorX;}
    int getAnchorY() { return mAnchorY;}
};
#endif // CLASS_CAMERA
