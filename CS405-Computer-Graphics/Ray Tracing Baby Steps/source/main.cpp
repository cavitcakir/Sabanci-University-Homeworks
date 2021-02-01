#include "rtweekend.h"

#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "material.h"
#include "sphere.h"
#include "aarect.h"
#include "box.h"
#include "plane.h"

#include <iostream>

color ray_color(const ray &r, const color &background, const hittable &world, int depth)
{
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return color(0, 0, 0);

    // If the ray hits nothing, return the background color.
    if (!world.hit(r, 0.001, infinity, rec))
        return background;

    ray scattered;
    color attenuation;
    color emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);

    if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;

    return emitted + attenuation * ray_color(scattered, background, world, depth - 1);
}

hittable_list simple_light()
{
    hittable_list objects;

    auto difflightPurp = make_shared<diffuse_light>(color(2, 0, 6));
    auto difflightGreen = make_shared<diffuse_light>(color(0, 1, 0));
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_center_green = make_shared<lambertian>(color(0, 1, 0));
    auto material_ground = make_shared<lambertian>(color(0.8, 0.1, 0.1));
    auto material_left = make_shared<dielectric>(1.5);
    auto material_right = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);

    for (double x = -0; x > -2.5; x -= 0.6)
    {
        for (double y = 0.5; y < 3; y += 0.6)
        {
            for (double z = 0.5; z < 3; z+= 0.6)
            {
                objects.add(make_shared<sphere>(point3(x, y, z), 0.3, material_center_green));
            }
        }
    }
    


    // objects.add(make_shared<sphere>(point3(0, 0, 1), 0.5, material_center_green));
    // // objects.add(make_shared<sphere>(point3(0, 0, 1), 0.5, difflightGreen));
    // objects.add(make_shared<box>(point3(-0.25, 0, 0.1), point3(0.25, 0.5, 0.6), material_center_green)); // kup

    // objects.add(make_shared<sphere>(point3(1, 1.5, 2), 0.2, difflightPurp));
    // // objects.add(make_shared<plane>(point3(0.75, 1.25, 2), point3(1.25, 1.75, 2), difflightPurp)); // plane
    // objects.add(make_shared<sphere>(point3(1, 1, 1.5), 0.3, material_right));
    // objects.add(make_shared<sphere>(point3(1, 0.5, 2), 0.2, material_center));


    // objects.add(make_shared<sphere>(point3(-1, 1.5, 2), 0.2, difflightPurp));
    // objects.add(make_shared<sphere>(point3(-1, 1, 1.5), 0.3, material_right));
    // objects.add(make_shared<sphere>(point3(-1, 0.5, 2), 0.2, material_center));

    // objects.add(make_shared<plane>(point3(-0.5, 0.25, 2), point3(0.5, 1.25, 2), material_center_green)); // plane

    objects.add(make_shared<sphere>(point3(0, -100.5, 1), 100, material_ground));


    return objects;
}

int main()
{
    // Image Task_3_1_2

    // const auto aspect_ratio = 16.0 / 12.0;
    // const int image_width = 640;

    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 1920;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 40;

    // color background(0, 0, 0);
    color background(0, 0.2, 0.6);

    // World
    hittable_list world;



    world = simple_light();

    // Camera

    // camera cam(point3(0, 0.2, 1), point3(0, 0, -1), vec3(0, 1, 0), 75, aspect_ratio);
    // camera cam(point3(-2, 2, 1), point3(0, 0, -1), vec3(0, 1, 0), 65, aspect_ratio);

    // camera cam(point3(0, 0.6, -1), point3(0, 0, 1), vec3(0, 1, 0), 85, aspect_ratio); // kup
    // camera cam(point3(2, 2, -1), point3(0, 0, 1), vec3(0, 1, 0), 65, aspect_ratio); // kup icin

    camera cam(point3(-1, 5, -1), point3(-1, 0, 2), vec3(0, 1, 0), 85, aspect_ratio); // kup
    // camera cam(point3(4, 5, -3), point3(-3.2, 0, 4), vec3(0, 1, 0), 65, aspect_ratio); // kup icin

    // Render

    std::cout << "P3\n"<< image_width << ' ' << image_height << "\n255\n";

    int aa = 1; // 0 -> no aliasing, 1 -> random aliasing, 2 -> grid aliasing

    if (aa == 0 || aa == 1)
    {
        for (int j = image_height - 1; j >= 0; --j)
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i)
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    auto u = double(i) / (image_width - 1);
                    auto v = double(j) / (image_height - 1);
                    if (aa == 0)
                    {
                        u = double(i) / (image_width - 1);
                        v = double(j) / (image_height - 1);
                    }
                    else
                    {
                        u = (i + random_double()) / (image_width - 1);
                        v = (j + random_double()) / (image_height - 1);
                    }
                    ray r = cam.get_ray(u, v);
                    pixel_color += ray_color(r, background, world, max_depth);
                }
                write_color(std::cout, pixel_color, samples_per_pixel);
            }
        }
    }
    else
    {
        int grid = 3;

        for (int j = image_height - 1; j >= 0; --j) // y
        {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) // x
            {
                color pixel_color(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s)
                {
                    color temp_color(0, 0, 0);
                    for (int p = 0; p < grid; p++)
                    {
                        for (int q = 0; q < grid; q++)
                        {
                            auto u = ((double(i) + ((p * 1.0) / grid)) / (image_width - 1));
                            auto v = ((double(j) + ((q * 1.0) / grid)) / (image_height - 1));

                            ray r = cam.get_ray(u, v);
                            temp_color += ray_color(r, background, world, max_depth);
                        }
                    }

                    pixel_color += temp_color / (grid * grid);
                }
                write_color(std::cout, pixel_color, samples_per_pixel);
            }
        }
    }

    std::cerr << "\nDone.\n";
}