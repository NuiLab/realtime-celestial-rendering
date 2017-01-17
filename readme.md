![Cover Image][cover-img]

# Realtime Celestial Rendering

[![License][license-img]][license-url]
![Unreal Version][release-img]
[![Featured in 3DUI 2017][3dui-img]][3dui-url]

This paper proposes a technique to render a parametric celestial skybox with the ability to light environments similar to natural color corrected images from telescopes. We first precompute a ray map that coresponds to the view frustrum of the main camera to optimize updates to the cubemap environment, then render a physically accurate sky with a shader applied to that region of the cubemap. Our System integrates easily with **Unreal Engine 4** through a [plugin](unreal-project/Plugins/StarySkybox) we provide.

## Setup

```bash
|- paper/                     # Paper and poster source files
|- unreal-project/            # Example Unreal Engine 4 Project
  |- Plugins/
    |- StarySkybox/           # Plugin Location
  |- celestialdemo.uproject
|- readme.md
```

### Research Paper

Download any Latex compiler such as [TeX Live](https://www.tug.org/texlive/) or [MiKTeX](https://miktex.org/) to compile the latex.

```bash
# Building a PDF
cd paper/
biblatex paper.bib
pdflatex paper.tex
pdflatex paper.tex
```

To compile the poster, you'll need to open `poster.indd` with [Adobe InDesign CC](http://www.adobe.com/products/indesign.html), and go to `File > Export`.

### Unreal Project

First install the latest version of [Unreal Engine 4](https://www.unrealengine.com/download), then right click on `./unreal-project/celestial-demo.uproject` and generate a solution for your operating system. 

From there run **Local Windows Debugger** to open Unreal's Level Editor.

#### Unreal Plugin

To install the plugin, copy the folder `./unreal-project/Plugins/StarySkybox` to your project's `Plugins` folder.

##### Usage

After installing, create a blueprint class that inherits from the StarySkybox class. This is an actor that you can place in your scene to render the sky. You can configure any of the defaults directly from the Blueprint class interface.

[cover-img]: images/asteroids.png
[release-img]: https://img.shields.io/badge/unreal-4.14.3-2a2a2a.svg?style=flat-square
[license-img]: http://img.shields.io/:license-mit-blue.svg?style=flat-square
[license-url]: https://opensource.org/licenses/MIT  
[3dui-img]: https://img.shields.io/badge/3dui-2017-1ab7ea.svg?style=flat-square
[3dui-url]: http://www.3dui.org/