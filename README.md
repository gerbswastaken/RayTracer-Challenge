## The Raytracer Challenge: A Simple Raytracing Engine written in C++

<img src="https://user-images.githubusercontent.com/73233616/176517996-eb2b182e-c7f6-4133-85ac-f0dc9d59f2a0.png">
An example image generated by my Raytracing Engine.

# What is Raytracing?
<p>
Raytracing is a graphics rendering technique that is used to get realistic looking lighting, shadows, reflections, and refractions. The technique is 
very similar to the way that light works in real life; we assume light rays to be vectors and perform calculations to determine what objects they bounce, reflect, refract, get absorbed by. With this information, we can determine an ultimate color for each pixel on the screen, resulting in a 
very realistic looking image.

However, there are some downsides to this process. Most importantly, this process is extremely time consuming. This Raytracer took nearly an hour to render a simple 960x540 image. (This is not representative of Raytracers in general; this Raytracer is quite slow since I explicitly did not make any optmizations to the code because I wanted to understand exactly how Raytracers work. Further, this Raytracer is a software renderer; many performance improvements can be made by rewriting much of the linear algebra in graphics APIs like OpenGL or DirectX. The main point still stands though, the process of running thousands of calculations for each pixel can get very computationally expensive as the desired output resolution increases.)

Raytracing is quite an old technique. It was used to generate static backgrounds, notably in the point and click adventure game Myst, released in 1993.  
<img src="https://user-images.githubusercontent.com/73233616/176685649-33d33f54-41f4-4e12-a918-d505ca2b4aeb.png">

A screenshot from Myst (1993)

Raytracing is utilized extensively in 3D animations and animated movies to achieve realistic lighting and reflections; some frames of animation in Toy Story 3 took upto 39 hours to render on top of the line servers built to perform the specific task of rendering 3D environments.

Realtime Raytracing was something that seemed impossible for a long time. Simplifications of Raytracing, (notably Raycasting) were pivotal in the era where multimedia shifted from 2D to 3D, before computers were able to house enough computing power to render true 3D environments, but demand for 3D media was steadily increasing. Titles like Wolfenstein 3D (1992), Doom (1993), Duke Nukem 3D (1996), etc. used Raycasting to realize 
pseudo-3D worlds on hardware that was inadequate.
<img src="https://user-images.githubusercontent.com/73233616/176688550-3b910507-fd48-48fc-b357-4e10461e2154.png">

A screenshot from Doom (1993)

> To learn more about Raycasting, check out Orion, a Raycasting Engine written in C++:
> https://github.com/gerbswastaken/Orion
</p>

# Why did I start this Project?
<p>
I wanted to learn more about Raytracing, especially because of the recent advancements made in GPU technology.
(see Nvidia RTX: https://www.nvidia.com/en-in/design-visualization/technologies/rtx/)

I came across <i>The Ray Tracer Challenge</i> by Jamis Buck (http://raytracerchallenge.com/) and decided to try my hand at it, and wrote my own implementation using C++. Though the Raytracer is very basic, I was able to implement the fundamental process, and use it to generate some realistic images.

<img src="https://user-images.githubusercontent.com/73233616/176692969-3c11c9a7-0849-4dbe-b864-d3e1e04610a9.png">
<img src="https://user-images.githubusercontent.com/73233616/176692600-3a17f5f4-ad5b-4cce-b55a-eb0874d14cce.png">

# Features
<ul>
  <li>Multiple types of Geometry including cubes, planes, cylinders, spheres, cones, etc.</li>
  <li>Patterns for primitive object texturing.</li>
  <li>Outputs images in <code>.ppm</code> format.</li>
  <li>A movable camera to set up various shots and angles.</li>
  <li>Different types of light sources; customizable light colors.</li>
  <li>Reflection and Refraction of light rays.</li>
  <li>A modular Object-Oriented Approach to make adding further 3D models and textures fast and easy.</li>
  <li>A completely self-programmed Linear Algebra library for Matrix calculations.</li>
</ul>

# Future Improvements
<ul>
  <li>An option for the user to use faster (but less accurate) routines to speed up rendering times.</li>
  <li>A 3D interface using Rasterization (via OpenGL or DirectX) to allow the user to view the scene in realtime before rendering to make making adjustments easier</li>
  <li>An option to render the generated image in a window rather than outputting to a <code>.ppm</code> file.</li>
  <li>Provide the tools to render multiple frames of animation and stitch them together to form a video</li>
</ul>

