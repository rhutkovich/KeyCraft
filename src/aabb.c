#include "aabb.h"

uint8_t aabbIntersectsPoint(AABB* box, vec3* point)
{
    return (point->x >= box->min.x && point->x <= box->max.x) &&
            (point->y >= box->min.y && point->y <= box->max.y) &&
            (point->z >= box->min.z && point->z <= box->max.z);
}

uint8_t aabbIntersectsAABB(AABB* box1, AABB* box2)
{
    return (box1->min.x <= box2->max.x && box1->max.x >= box2->min.x) &&
            (box1->min.y <= box2->max.y && box1->max.y >= box2->min.y) &&
            (box1->min.z <= box2->max.z && box1->max.z >= box2->min.z);
}

//Based on this: https://gdbooks.gitbooks.io/3dcollisions/content/Chapter3/raycast_aabb.html
uint8_t aabbIntersectsRay(AABB* box, vec3* origin, vec3* direction, float* hit)
{
    float tx1 = (box->min.x - origin->x) / direction->x;
    float tx2 = (box->max.x - origin->x) / direction->x;
    float ty1 = (box->min.y - origin->y) / direction->y;
    float ty2 = (box->max.y - origin->y) / direction->y;
    float tz1 = (box->min.z - origin->z) / direction->z;
    float tz2 = (box->max.z - origin->z) / direction->z;

    float tMin = fmax(fmax(fmin(tx1, tx2), fmin(ty1, ty2)), fmin(tz1, tz2));
    float tMax = fmin(fmin(fmax(tx1, tx2), fmax(ty1, ty2)), fmax(tz1, tz2));

    //Ray intersects AABB behind us || ray doesn't intersect
    if(tMax < 0 || tMin > tMax)
    {
        return 0;
    }

    if(tMin < 0)
    {
        *hit = tMax;
    }
    else
    {
        *hit = tMin;
    }
    return 1;
}