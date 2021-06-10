#!/bin/bash

function embed_shaders() {
  shader_file=$1
  shaders_path=$2

  rm "$shader_file" || :
  touch "$shader_file"

  printf "\n// Built file, do not edit manually\n\n" >>"$shader_file"

  for file in "$shaders_path"/*; do
    suffix=""
    filename=$(basename "$file" | cut -d. -f1)
    contents=$(cat "$file")

    case "$file" in
    *.frag)
      suffix="frag"
      ;;
    *.vert)
      suffix="vert"
      ;;
    *.geom)
      suffix="geom"
      ;;
    esac

    printf "static const char *%s = R\"\"\"\"(\\n%s\\n)\"\"\"\";" "${filename}_${suffix}" "$contents" >>"$shader_file"
    printf "\\n\\n" >>"$shader_file"
  done
}

embed_shaders "$1" "$2"
