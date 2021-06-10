//
// Created by Sakri Koskimies on 4/10/21.
//

#ifndef JUST_SOME_GRAPHICS_SRC_CORE_IMAGE_HPP_
#define JUST_SOME_GRAPHICS_SRC_CORE_IMAGE_HPP_

class Image {
 public:
  static GLuint LoadBMP(const char *image_path) {
    // Data read from the header of the BMP file
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    uint dataPos;     // Position in the file where the actual data begins
    uint width, height;
    uint imageSize;   // = width*height*3
    // Actual RGB data
    unsigned char *data;

    // Open the file
    FILE *file = fopen(image_path, "rb");
    if (!file) {
      printf("Image could not be opened\n");
      return 0;
    }

    if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
      printf("Not a correct BMP file\n");
      return 0;
    }

    if (header[0] != 'B' || header[1] != 'M') {
      printf("Not a correct BMP file\n");
      return 0;
    }

    // Read ints from the byte array
    dataPos = *(int *) &(header[0x0A]);
    imageSize = *(int *) &(header[0x22]);
    width = *(int *) &(header[0x12]);
    height = *(int *) &(header[0x16]);

    // Some BMP files are malformatted, guess missing information
    if (imageSize == 0) {
      imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
    }

    if (dataPos == 0) {
      dataPos = 54; // The BMP header is done that way
    }

    data = new unsigned char[imageSize];

    // Read the actual data from the file into the buffer
    fread(data, 1, imageSize, file);

    // Everything is in memory now, the file can be closed
    fclose(file);

    // Texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    return textureID;
  }
};

#endif //JUST_SOME_GRAPHICS_SRC_CORE_IMAGE_HPP_
