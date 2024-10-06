# QyooGenerate-C

QyooGenerate is a generator for customizable graphical representations of a 2d qyoo barcode based on a binary number. It can create images in PNG or SVG format, with a range of options for colors, size, and patterns. This README provides instructions for compiling the C code, running the generator, and using the included test scripts.

## Project Overview

The Qyoo generator creates a visual output based on the provided binary ID, producing images with customizable foreground and dot colors. You can also specify the output size, format (PNG or SVG), and background color, with options for transparency.

### Key Options:

- **-id**: [REQUIRED] The numeric or binary ID that controls the visual pattern.
- **-o**: Specifies the output filename. The default is the ID-based name.
- **-w**: Sets the width of the image (default: 512).
- **-h**: Sets the height of the image (default: 512).
- **-fg**: Sets the foreground color (default: `#ffffff`).
- **-dot**: Sets the dot color (default: `#000000`).
- **-bg**: Sets the background color (default: `transparent`).
- **-svg**: Outputs the image in SVG format (default PNG).
- **-v**: Enables verbose mode for debugging (default no).
- **--help**: Displays this help message with available options.

## Compiling the Project

To compile the Qyoo generator, follow these steps:

1. Ensure you have **gcc** and **libgd** installed on your system. If not, you can install it using:
   ```
   brew install gd
   ```

2. Navigate to the project’s source (`src`) directory.

3. Run the `make` command to compile the source files:
   ```
   make
   ```

This will generate the executable `qyoo` in the `../bin` directory. Object files will be placed in the `../obj` directory, and the output files from the test scripts will be saved in the `../output` directory by default.

### Makefile Structure

The `Makefile` automates the compilation process:
- `SRCS`: The list of C source files.
- `OBJDIR`: The directory where object files (`.o`) are stored.
- `EXEDIR`: The directory where the final executable is stored.
- `OUTPUTDIR`: The directory where output images are stored.
- `make clean`: Cleans up compiled object files and the executable.

## Using the Qyoo Generator

Once compiled, you can generate images by running the `qyoo` executable with various options.

### Example Commands:

1. Basic usage with a decimal ID:
   ```
   ../bin/qyoo -id 12345 -o ../output/12345.png
   ```

2. Generate an image with custom foreground and dot colors:
   ```
   ../bin/qyoo -id 12345 -fg "#ff0000" -dot "#00ff00" -o ../output/12345_colored.png
   ```

3. Create an SVG with a binary ID:
   ```
   ../bin/qyoo -id 010101010101010101010101010101010101 -svg -o ../output/alternating.svg
   ```

4. Verbose mode for debugging:
   ```
   ../bin/qyoo -id 12345 -v
   ```

5. Generate a transparent PNG:
   ```
   ../bin/qyoo -id 67890 -bg transparent -o ../output/transparent.png
   ```

## Test Scripts

The project includes a series of test scripts for common use cases. These scripts automate the testing of the Qyoo generator for various scenarios.

### Available Test Scripts:

- **q_img_basic_1.sh**: Basic image with minimal parameters (default settings).
- **q_img_transparent_1.sh**: Image with a binary ID and transparent background.
- **q_img_random_dots_1.sh**: Image with a random dot pattern.
- **q_img_random_99.sh**: Generates 99 random images.
- **q_img_nonstandard_ratio.sh**: Generates images with non-standard aspect ratios.
- **q_img_nodots_1.sh**: All dots turned off in the image.
- **q_img_mixed_50.sh**: Generates 50 mixed-pattern images.
- **q_img_invalid_color.sh**: Test with invalid color codes to handle errors.
- **q_img_max_size.sh**: Generates the largest supported image size.
- **q_img_default_output.sh**: Uses default settings for output filename and format.
- **q_img_colors_10.sh**: Generates 10 images with random colors.
- **q_img_basic_colors_1.sh**: Basic test with specific colors.
- **q_img_alternating_2.sh**: Alternating dot patterns with binary IDs.
- **q_img_alldots_1.sh**: All dots turned on.

### Running the Test Scripts:

1. Ensure you have compiled the project and have the executable `../bin/qyoo` ready.
2. Go into the `scripts` directory and run the following command to make them executable:
	```
	chmod +x *
	```
2. Execute the desired test script. For example, to run the **q_img_basic_1.sh** test:
   ```
   ./q_img_basic_1.sh
   ```

Each script will generate one or more images in the `../output` directory based on the test case.

## Examples

### Example 1: Alternating Dot Pattern (Image)
This example generates a PNG image with an alternating dot pattern:
```
../bin/qyoo -id 010101010101010101010101010101010101 -o ../output/q_img_alternating_1.png
```

### Example 2: Random Dot Pattern
This generates a PNG image with a random binary ID:
```
RAND_ID=$((RANDOM + 68719476735))
../bin/qyoo -id $RAND_ID -fg "#ffffff" -dot "#000000" -bg transparent -o ../output/random.png
```

### Example 3: All Dots On (SVG)
This generates an SVG with all dots turned on:
```
../bin/qyoo -id 111111111111111111111111111111111111 -svg -o ../output/q_svg_alldots_1.svg
```

## Contributing

We welcome contributions to the QyooGenerator project. Please open an issue or submit a pull request if you'd like to contribute.

## License

This project is licensed under the BSD-3-Clause License. See the `LICENSE` file for details.