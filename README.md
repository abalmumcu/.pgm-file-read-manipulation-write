# .pgm File Read, Manipulation, and Write

**Project Description**: This repository includes processes for reading, manipulating, and writing .pgm files using C++.

## Project Overview

The ".pgm File Read, Manipulation, and Write" project focuses on performing various operations on .pgm files. It provides functionality to read input images in .pgm format, manipulate them using different algorithms, and write the manipulated images back to the disk.

## Project Structure

The project contains the following directories and files:

- **Original pgm file**: This directory stores the original input images in .pgm format.
- **output files**: This directory is used to save the generated output images.
- **README.md**: A Markdown file containing information about the project and its usage.
- **creating_new_pgm_file.cpp**: A C++ source file for creating a new .pgm file.
- **dft.cpp**: A C++ source file for performing Discrete Fourier Transform (DFT) on .pgm images.
- **histogram_equalization.cpp**: A C++ source file for performing histogram equalization on .pgm images.
- **laplacian_and_sobel_gradiant.cpp**: A C++ source file for applying Laplacian and Sobel gradient operators on .pgm images.
- **manipulation_with_filters.cpp**: A C++ source file for manipulating .pgm images using different filters.
- **pgm_read_write.cpp**: A C++ source file for reading and writing .pgm images.

## Usage

To use the ".pgm File Read, Manipulation, and Write" project, follow these steps:

1. Clone the repository:

   ```bash
   git clone https://github.com/abalmumcu/.pgm-file-read-manipulation-write.git
   ```

2. Ensure that all input images with the .pgm extension are placed in the same directory as the code files.

3. Compile the desired C++ source file using a C++ compiler:

   ```bash
   g++ -o executable_name source_file.cpp
   ```

   Replace `executable_name` with a suitable name for the generated executable.

4. Execute the compiled executable:

   ```bash
   ./executable_name
   ```

5. The program will perform the specified operations on the input .pgm images and save the output images to the "output files" directory.

## Important Notes

- All input images with the .pgm extension must be present in the directory where the code is located in order for the code to be compiled and run successfully.
- After compilation and execution, all output images generated will be automatically saved to the directory where the code is located.
- The content information (type, comment line, width, height, and maximum pixel value) of all input images will be displayed on the compilation screen after the compilation process.


## License

This project is licensed under the [MIT License](LICENSE).
```

Feel free to customize the README file with additional sections or specific instructions related to your project.
