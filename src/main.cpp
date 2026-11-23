#include <iostream>
#include <memory>
#include <string>

#include "colour/colour.h"
#include "geometry/sphere.h"
#include "image/image.h"
#include "io/png_saver.h"
#include "light/light.h"
#include "material/lambert_shader.h"
#include "math/vector.h"
#include "render/camera.h"

int main(int argc, char* argv[]) {
    std::string outputPath = argc > 1 ? argv[1] : "output.png";

    std::cout << "Hello, Raytracer!" << std::endl;

    Camera camera(Vector(0, 0, 0));
    Sphere sphere(Vector(0, 0, 5), 1.0, std::make_shared<LambertShader>(Colour(1, 0.2, 0.2)));
    Light light(Vector(-5, 5, 0), Colour(1, 1, 1));

    Image image(512, 256);
    camera.render(image, sphere, light, 2.0);

    PngSaver saver;
    saver.save(image, outputPath);

    std::cout << "Image saved to " << outputPath << std::endl;
    return 0;
}
