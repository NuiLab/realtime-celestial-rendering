![Cover Image][cover-img]

# Realtime Celestial Rendering

![Unreal Version][release-img] [![License][license-img]][license-url]

This paper proposes a technique to render a parametric celestial skybox with the ability to light environments similar to natural color corrected images from telescopes. We first precompute a ray map that coresponds to the view frustrum of the main camera to optimize updates to the cubemap environment, then render a physically accurate sky with a shader applied to that region of the cubemap. Our System integrates easily with **Unreal Engine 4** through a [plugin](unreal-project/Plugins/StarySkyGen) we provide.

## Setup

```bash
|- publication/
  |- dist/              # compiled .pdfs
  |- images/            # included images
  |- 3dui/
  |- jcgt/
  |- siggraph/
  |- citations.bib      # bibtex citations
  |- common.tex         # common plugins/settings
  |- abstract.tex
  |- related-work.tex
  |- code.tex
  |- conclusion.tex
  |- acknowledgements.tex
|- unreal-project/
  |- Plugins/
  |- celestialdemo.uproject
|- readme.md
```

### Research Paper

Download any Latex compiler such as [TeX Live](https://www.tug.org/texlive/) or [MiKTeX](https://miktex.org/) to compile the latex.

### Unreal Project

To run the Unreal example, install the latest version of [Unreal Engine 4](https://www.unrealengine.com/download), then right click on `./unreal-project/celestial-demo.uproject` and generate a solution for your operating system.

### StarySkyGen Plugin

Installing the plugin on your project is simply a matter of copying the folder `./unreal-project/Plugins/StarySkyGen` to your project's `Plugins` folder.

## Usage

After installing, create a blueprint class that inherits from the StarySkyGen class. This is an actor that you can place in your scene to render the sky. You can configure any of the defaults directly from the Blueprint class interface.

[cover-img]: images/asteroids.png
[release-img]: https://img.shields.io/badge/unreal-4.14.0-444444.svg?style=flat-square
[license-img]: http://img.shields.io/:license-mit-blue.svg?style=flat-square
[license-url]: https://opensource.org/licenses/MIT