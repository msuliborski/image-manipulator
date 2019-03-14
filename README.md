
# Image Manipulator

Application for simple image editing. Image Processing (2018) 

* Task 1 - Application for image processing and analysis, elementary operations, geometric operations and noise removal.  
* Task 2 - Filtration in spatial domain (histogram modifications, linear and non-linear operations, convolution).
* Task 3 - Morphological operations, segmentation.
* Task 4 - Filtration in frequency domain.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

In order to properly build application one might need following dependences.
```
$ apt install cimg-dev cimg-doc cimg-examples cmake gcc clang gdb build-essential libx11-dev libxext-dev
```

### Cloning

```
$ git clone https://github.com/msuliborski/image-manipulator
```

### Building

```
$ cd image-manipulator
$ cmake CMakeLists.txt 
$ make
$ out/./image-manipulator --help
```

### Usage

Using parameter `--help` one obtains list of avaliable commands. Here are examples of using them:
```
$ ./image-manipulator --brightness 40 ../img/color/lena.bmp output.bmp
$ ./image-manipulator --median 3 ../img/noise-color/lena-impulse3.bmp output.bmp
$ ./image-manipulator --slaplace 2 ../img/color/lena.bmp output.bmp
```

## Built with

* [CImg](http://www.http://cimg.eu/) - small and open-source C++ toolkit for image processing


## Authors

* **Michał Suliborski** - [msuliborski](https://github.com/msuliborski)
* **Arkadiusz Zasina** - [217868](https://github.com/217868)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details



