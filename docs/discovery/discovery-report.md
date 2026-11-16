Discovery report

Interview date: 16 November 2026. All sources checked on 16 November 2026.

Problem statement

An animation studio needs a renderer that it can extend and fix by itself, because it must deliver films on time without spending millions on licences, but the tools on the market are closed and its old in-house tool was impossible to understand.

Client interview summary

The interview lasted one hour, with the whole class asking questions. My notes don't say who asked each question, so I wrote "class" for all of them.

1. Reliability

Need: the same input must always give the same image, and when there is a problem in an image, the team must find the cause on the same day.

Q (class): What will show you that the software meets your needs?
A (client): A reliable image: same inputs, same output. And if there is a problem, we can understand why on the same day. Six months ago we had black dots in our images and nobody knew why. Rendering took twice as long and we delivered 3 weeks late.

2. Adding features

Need: the studio wants to add its own features, and partner studios must be able to contribute.

Q (class): What is the main thing you need?
A (client): Being able to add our own features. With Maya, the company says no, or it takes 6 months to a year. For now, we need spheres and planes.

3. Maintenance

Need: the code must still be understandable after the person who wrote it leaves, and technical choices must be written down with their reasons.

Q (class): Is there anything we have missed?
A (client): Last time, the person who wrote the software left. Nobody could explain the design choices, and the other 5 people in the team could not debug it.

Need: technical documentation for developers, and a user guide for artists.

Q (class): What kind of documentation do you need?
A (client): Our developers will take over the code, but we also want a user guide for the artists and the people who set up the scenes.

4. How it works

Need: a command-line tool that works like a "black box": a file describing the scene goes in, images come out. No interface.

Q (class): Do you want us to build an editing tool?
A (client): No, we just want to render. A scene description goes in, images come out.

5. Speed and hardware

Need: everything runs on the CPU (the studio has no graphics cards). Designers need a quick, smaller preview (about 10 previews per image), and the final render must be high quality.

Q (class): What kind of hardware do you have?
A (client): We don't have graphics cards, so everything is rendered on the CPU. Designers need a fast, smaller preview. The final image must be high quality.

Need: render a 90-minute film in 2 months at most, on up to 100 machines.

Q (class): How big is the render farm, and how long can the final render take?
A (client): Up to 100 machines, and no more than 2 months for the final render.

My conclusion: at 24 frames per second, a 90-minute film is about 130,000 frames. Spread over 100 machines for 60 days, that gives each machine about 1 hour per frame, at most. So the work will have to be split across many machines.

6. Cost and deadline

Need: spend much less on licences (over $2M last year), with a budget of 500,000 at most, and deliver by 5 January.

Q (class): How much did you spend on licences last year, and what is your budget?
A (client): Over $2 million, because we pay per machine and per artist. We want to spend no more than 500,000.

Q (class): What is your deadline?
A (client): The software must be ready by 5 January.

Open questions
Frame rate: is it 24 frames per second? My notes say "8 feet".
Is the 500,000 budget in euros or dollars?
What resolution: HD, 2K or 4K?
What file format is used to describe the scene?
Contradiction: the client said Maya is their renderer, but Maya is a 3D modelling tool. Its renderer is Arnold.
What does "fast" mean for a preview? How many seconds?
State of the art

Prices checked on 16 November 2026, in US dollars, per licence.

Solution	Maker	Licence	Pricing (checked 16/11/2026)	Capabilities	Sources
Arnold	Autodesk	Paid, subscription	Price not shown on the official page	Film rendering, on CPU or GPU, works inside Maya	autodesk.com
RenderMan	Pixar	Paid, free for non-commercial use	$595 per licence + $250 per year for updates	Used for Pixar films, comes with a render farm manager	renderman.pixar.com
V-Ray	Chaos	Paid, subscription	$540/year (Solo), $778.80/year (Premium), render machines cost extra	Visual effects, can split rendering across machines	chaos.com
Redshift	Maxon	Paid, subscription	$264/year	Made mainly for the GPU	help.maxon.net
Cycles	Blender Foundation	Open source (Apache 2.0)	Free	Realistic rendering, on CPU or GPU	code.blender.org
pbrt-v4	Pharr, Jakob, Humphreys	Open source (Apache 2.0)	Free	Reference renderer written in C++, explained in a free book	github.com/mmp/pbrt-v4

Conclusion: all these tools use the same idea: realistic ray tracing. The paid ones charge per person and per machine, which explains why the client spent over $2M. Their code is closed, so the client can't add features or find out why an image is wrong. Redshift is made for the GPU, and the client has none. The open-source tools are free, but their code is very big and was not made for this studio. None of them gives the client a small, well-documented code base that its own team and partners can grow.

What is ray tracing?

The input is a 3D scene: objects (like spheres and planes) with their materials, lights, and a camera. The output is an image. In between, for every pixel, the program sends a ray from the camera into the scene and finds the first object the ray hits. From that point, it sends a ray towards the light to check if the point is lit or in shadow. If the object is shiny, the ray bounces and the same steps happen again, up to a maximum number of bounces. All of this gives the colour of the pixel. Each pixel is computed on its own, so the work can be shared between several CPU cores or several machines.

Sources

Where I started: Ray Tracing in One Weekend (Shirley, Black, Hollasch)
Reference I would go back to: Physically Based Rendering, 4th edition, free online (Pharr, Jakob, Humphreys)
What is C++?
Programming paradigms

C++ is a compiled language: the code is turned into machine code before it runs, which makes it very fast. It is also statically typed, so types are checked before the program runs. You can write C++ in several styles:

procedural, with functions, like in C;
object-oriented, with classes, inheritance and polymorphism;
generic, with templates, to write code that works with different types.

Compared to JavaScript, C++ is much faster, but it is stricter and takes longer to compile.

What to watch out for

In C++, the developer has to handle many things that other languages do automatically:

Memory: there is no garbage collector, so you have to free memory yourself. If you forget, you get memory leaks or crashes. Smart pointers can free memory for you.
Undefined behaviour: reading outside an array or using a variable that was never set does not always cause an error. The program can do anything, without any warning.
Decimal numbers: small rounding errors can create black dots in the image. This is probably what happened to the client.
Building: compiling can be different on each computer, so everyone needs the same setup. This is why we use Docker and CMake.
Shaping the domain model

The code should use the client's own words for its concepts:

a Scene that holds Shapes (Sphere, Plane), Lights and a Camera;
an abstract Shape class with one method that answers "does this ray hit me?". Each shape answers it in its own way. To add a new shape, we only write a new class and don't touch the rest of the code. This is what the client needs to add features;
small, simple and fast objects for vectors, rays and colours, because the program creates millions of them.

