cmake_minimum_required(VERSION 3.10)
project(huffman_bowmanb1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(huffman_bowmanb1
        .gitignore
        README.md
        main.cpp
        LetterObject.cpp
        LetterObject.h
        List.cpp
        List.h
        Object.cpp
        Object.h
        TreeNode.cpp TreeNode.h HuffmanTree.cpp HuffmanTree.h)
