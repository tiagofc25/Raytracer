# 6. A shape has a material

## Context

Each object needs a way to compute its colour when light hits it (flat colour, Lambert shading, and more later). We will have several shapes (sphere, plane, and more later) and several materials.

Alternative: inheritance, where a shape *is* a material (for example `LambertSphere`, `FlatPlane`). Every new shape or material would need one class per combination: shapes × materials.

## Decision

Composition: a shape *has* a material. `Sphere` and `Plane` store a `Material`, and the hit they return (`HitInfo`) points to it. `Material` is an abstract class (Strategy pattern, like `ImageSaver`), with `FlatShader` and `LambertShader` as implementations. The camera asks the material of the hit object to shade the point.

## Status

Proposed

## Consequences

- We write shapes + materials classes, not shapes × materials. A new material needs no change in the shapes, and a new shape needs no change in the materials.
- Every shape repeats the same `_material` field and passes it on in its hit.
- Materials are held with `std::shared_ptr`, so several shapes can share one material. `HitInfo` holds a plain pointer to it, which is only valid while the shape exists.
