# Discovery report

Interview date: 16 November 2026 · Sources checked: 16 November 2026

## Problem statement

An animation studio needs a renderer that it can extend and troubleshoot itself, because it must deliver films on time without spending millions on licences, but market tools are closed and its old in-house tool was impossible to understand.

## Client interview summary

The interview was a one-hour session with the whole class. Questions are attributed to "class" because my notes do not record who asked each one.

### 1. Reliability

**Need:** the image must be reproducible (same input, same image), and the cause of a defect must be found within the same day.

> **Q (class):** What will show you that the software meets your needs?
> **A (client):** A reliable image: same inputs, same output. And if there is an anomaly, understanding within the same day why it happened. Six months ago there were black dots in the images and nobody knew why; rendering time doubled and delivery was 3 weeks late.

### 2. Adding features

**Need:** the studio wants to add its own features, and its partners must be able to contribute.

> **Q (class):** What is the main thing you need?
> **A (client):** The ability to add our own features. With Maya, the vendor either says no or takes 6 months to a year. For now, we need spheres and planes.

### 3. Maintainability

**Need:** the code must stay understandable when its author leaves, and technical choices must be explained in writing.

> **Q (class):** Is there anything we have missed?
> **A (client):** Last time, the person who wrote the software left. Nobody could explain the architecture choices, and the other 5 team members could not debug it.

**Need:** technical documentation for developers and a user guide for artists.

> **Q (class):** What kind of documentation do you need?
> **A (client):** A development team will take ownership of the code, but we expect a user guide for the artists and the people setting up scenes.

### 4. How it works

**Need:** a command-line "black box": a scene description file goes in, images come out, with no interface.

> **Q (class):** Do you want us to build an editing tool?
> **A (client):** No, we just want to render: a scene description goes in, images come out.

### 5. Performance and hardware

**Need:** render on the CPU only (no graphics cards), with a fast preview for designers (about 10 previews per image) and a high-quality final render.

> **Q (class):** What kind of hardware do you have?
> **A (client):** No graphics cards, so everything must be rendered by the CPU. Designers need a quick, smaller preview; the final image must be high quality.

**Need:** render a 90-minute film in 2 months maximum, on up to 100 machines.

> **Q (class):** How big is the farm, and how long can final rendering take?
> **A (client):** Up to 100 machines, and no more than 2 months of final rendering.

**My conclusion:** at 24 frames per second, that is about 130,000 frames, so roughly **1 hour maximum per frame per machine**. The work will need to be spread across several machines.

### 6. Cost and deadline

**Need:** spend far less on licences (over $2M last year), with a budget of 500,000 maximum, and deliver by **5 January**.

> **Q (class):** What did you spend on licences last year, and what is your budget?
> **A (client):** Over $2 million, paid per machine and per artist. We would like to spend no more than 500,000.

> **Q (class):** What is your deadline?
> **A (client):** The software must be delivered by 5 January.

### Open questions

1. Frame rate: 24 frames per second? My notes say "8 feet".
2. Is the 500,000 budget in euros or dollars?
3. Which resolution: HD, 2K or 4K?
4. Which file format describes the scene?
5. **Contradiction:** the client names Maya as its renderer, but Maya is a modelling tool whose renderer is Arnold.
6. What does "fast" mean for a preview: how many seconds?

## State of the art

Prices checked on 16 November 2026, in US dollars, per licence.

| Solution | Maker | Licence | Pricing (checked 16/11/2026) | Capabilities | Sources |
|---|---|---|---|---|---|
| Arnold | Autodesk | Proprietary, subscription | Not readable on the vendor page (shown dynamically) | Film rendering, CPU or GPU, integrated with Maya | [autodesk.com](https://www.autodesk.com/products/arnold/buy) |
| RenderMan | Pixar | Proprietary, free for non-commercial use | $595 per licence + $250/year maintenance | Renderer of Pixar films, render-farm manager included | [renderman.pixar.com](https://renderman.pixar.com/store/) |
| V-Ray | Chaos | Proprietary, subscription | $540/year (Solo), $778.80/year (Premium), render nodes extra | Visual effects, rendering spread over several machines | [chaos.com](https://www.chaos.com/vray/buy-online) |
| Redshift | Maxon | Proprietary, subscription | $264/year | Designed for the GPU first | [help.maxon.net](https://help.maxon.net/r3d/cinema/en-us/Content/html/Maintenance+Extension.html) |
| Cycles | Blender Foundation | Open source (Apache 2.0) | Free | Physically based rendering, CPU or GPU | [code.blender.org](https://code.blender.org/2013/08/cycles-render-engine-released-with-permissive-license/) |
| pbrt-v4 | Pharr, Jakob, Humphreys | Open source (Apache 2.0) | Free | Reference renderer in C++, explained in a free book | [github.com/mmp/pbrt-v4](https://github.com/mmp/pbrt-v4) |

**Conclusion:** all these solutions use the same technique, physically based ray tracing. Paid tools are billed per seat and per machine, which explains the client's $2M+ bill, and their code is closed, so the client can neither add features nor understand a defect. Redshift is designed for the GPU, which the client does not have. Open-source solutions are free, but their code is huge and not built for this studio. None of them gives the client a small, documented code base designed to be extended by its team and partners.

## What is ray tracing?

As **input**, the ray tracer receives a 3D scene: objects (spheres, planes) with their material, lights and a camera. As **output**, it produces an image. **In between**, for each pixel, it sends a ray from the camera and looks for the first object this ray hits. At that point, it sends a ray towards the light to know whether the point is lit or in shadow. If the object is reflective, the ray bounces and the process starts again, with a limited number of bounces. This gives the pixel's colour. Because each pixel is computed independently of the others, the work can be spread over several cores or several machines.

**Sources**
- Starting resource: [*Ray Tracing in One Weekend*](https://raytracing.github.io/books/RayTracingInOneWeekend.html) (Shirley, Black, Hollasch)
- Reference: [*Physically Based Rendering*, 4th edition, free online](https://pbr-book.org/) (Pharr, Jakob, Humphreys)

## What is C++?

### Programming paradigms

C++ is a **compiled** language: the code is translated into machine code before it runs, which makes it very fast. It is also **statically typed**: types are checked before execution. It supports several programming styles:
- **procedural**, with functions, as in C;
- **object-oriented**, with classes, inheritance and polymorphism;
- **generic**, with templates: code that works for several types.

Compared with JavaScript, it is much faster, but stricter and slower to compile.

### What to watch out for

C++ leaves the developer many things that other languages handle automatically:
- **Memory:** there is no garbage collector, so you must free memory yourself, otherwise you get leaks or crashes. Smart pointers free memory automatically.
- **Undefined behaviour:** going out of an array's bounds or reading an uninitialised variable does not necessarily raise an error; the program can then do anything, without warning.
- **Floating-point numbers:** small rounding errors can produce black dots in the image, probably the problem the client had.
- **Compilation:** it differs from one machine to another, so everyone needs an identical environment, hence Docker and CMake.

### Shaping the domain model

The client's concepts are represented in the code, using the client's own words:
- a **Scene** that contains **Shapes** (Sphere, Plane), **Lights** and a **Camera**;
- an abstract `Shape` class with a method "does this ray hit me?". Each shape implements it in its own way. To add a new shape, you create a new class without touching the rest, which meets the client's need for extensibility;
- small, simple and fast objects for vectors, rays and colours, because millions of them are created.

**Sources**
- Starting resource: [learncpp.com](https://www.learncpp.com/)
- Reference: [cppreference.com](https://en.cppreference.com/)
