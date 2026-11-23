# Domain model

UML class diagram, without methods except for Vector. It uses the client's words: a scene holds shapes and a light, and a camera looks at it.

```mermaid
classDiagram
    Scene "1" *-- "*" Shape : holds
    Scene "1" *-- "1" Light : lit by
    Shape <|-- Sphere
    Shape <|-- Plane
    Shape "*" --> "1" Material : has
    Material <|-- FlatShader
    Material <|-- LambertShader
    Camera "1" --> "*" Ray : sends
    Camera --> Scene : renders
    Camera --> Image : fills
    Shape ..> HitInfo : returns
    HitInfo --> Material
    Image "1" *-- "*" Colour : pixels
    ImageSaver <|-- PngSaver
    ImageSaver ..> Image : saves

    class Vector {
        x: double
        y: double
        z: double
        +, -, * (scalar)
        dot(), length(), normalised()
    }
    class Ray {
        origin: Vector
        direction: Vector
    }
    class Shape {
        <<abstract>>
    }
    class Sphere {
        center: Vector
        radius: double
    }
    class Plane {
        point: Vector
        normal: Vector
    }
    class Material {
        <<abstract>>
    }
    class FlatShader {
        colour: Colour
    }
    class LambertShader {
        colour: Colour
    }
    class HitInfo {
        point: Vector
        normal: Vector
        t: double
    }
    class Light {
        position: Vector
        colour: Colour
    }
    class Camera {
        position: Vector
    }
    class Scene {
        background: Colour
    }
    class Image {
        width: unsigned int
        height: unsigned int
    }
    class Colour {
        r: double
        g: double
        b: double
    }
    class ImageSaver {
        <<abstract>>
    }
```

Notes:

- The camera always looks along the positive Z axis, at a screen placed at distance 1.
- The light is a point light. The sun is a point light placed very far away.
