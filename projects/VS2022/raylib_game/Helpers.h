#pragma once
#include "raylib.h"

class Helpers {
public:
    static const Vector3 ComputeBoundingBoxCenter(const BoundingBox& box) {
        return Vector3{ (box.min.x + box.max.x) / 2.0f , 
                            (box.min.y + box.max.y) / 2.0f , 
                                (box.min.z + box.max.z) / 2.0f };
    }

    static const Vector3 ComputeBoundingBoxSize(const BoundingBox& box) {
        return Vector3{ box.max.x - box.min.x ,
                        box.max.y - box.min.y ,
                        box.max.z - box.min.z };
    }
};