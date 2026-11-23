#include <iostream>
#include <memory>
#include <string>

#include "colour/colour.h"
#include "geometry/plane.h"
#include "geometry/sphere.h"
#include "image/image.h"
#include "io/png_saver.h"
#include "light/light.h"
#include "material/lambert_shader.h"
#include "math/vector.h"
#include "render/camera.h"
#include "scene/scene.h"

// Milestone m1: a sphere lit by the sun on a ground plane.
int main(int argc, char* argv[]) {
    std::string path = argc > 1 ? argv[1] : "image.png";

    std::cout << "Hello, Raytracer!" << std::endl;

    // The sun: a point light very far away, high up on the left, behind the camera.
    Light sun(Vector(-500, 1000, -300), Colour(1, 1, 1));
    Colour sky(0.5, 0.7, 1.0);
    Scene scene(sun, sky);

    // Ground: the plane y = 0, facing up.
    scene.add(std::make_shared<Plane>(Vector(0, 0, 0), Vector(0, 1, 0),
                                      std::make_shared<LambertShader>(Colour(0.4, 0.7, 0.3))));
    // A red sphere resting on the ground.
    scene.add(std::make_shared<Sphere>(Vector(0, 1, 6), 1.0,
                                       std::make_shared<LambertShader>(Colour(1, 0.2, 0.2))));

    Camera camera(Vector(0, 1.5, 0));
    Image image(400, 300);
    camera.render(image, scene, 2.0);

    PngSaver saver;
    saver.save(image, path);

    std::cout << "Image saved to " << path << std::endl;
    return 0;
}
