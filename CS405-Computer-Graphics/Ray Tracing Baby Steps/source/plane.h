#ifndef PLANE_H
#define PLANE_H
//==============================================================================================
// Originally written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is
// distributed without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication
// along with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==============================================================================================

#include "rtweekend.h"

#include "aarect.h"
#include "hittable_list.h"

class plane : public hittable
{
public:
    plane() {}
    plane(const point3 &p0, const point3 &p1, shared_ptr<material> ptr);

    virtual bool hit(const ray &r, double t_min, double t_max, hit_record &rec) const override;

    virtual bool bounding_box(double time0, double time1, aabb &output_box) const override
    {
        output_box = aabb(plane_min, plane_max);
        return true;
    }

public:
    point3 plane_min;
    point3 plane_max;
    hittable_list sides;
};

plane::plane(const point3 &p0, const point3 &p1, shared_ptr<material> ptr)
{
    plane_min = p0;
    plane_max = p1;

    sides.add(make_shared<xy_rect>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));

}

bool plane::hit(const ray &r, double t_min, double t_max, hit_record &rec) const
{
    return sides.hit(r, t_min, t_max, rec);
}

#endif