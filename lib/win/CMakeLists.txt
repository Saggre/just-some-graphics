message("-- Linking SDL2_image")
add_library(SDL2_image SDL2_image.dll)
set_target_properties(SDL2_image PROPERTIES LINKER_LANGUAGE C)