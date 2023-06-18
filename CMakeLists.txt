cmake_minimum_required(VERSION 3.5)
project(DIEditor VERSION 0.1 DESCRIPTION "Editor for engine module" LANGUAGES CXX)


file( GLOB SOURCES **.cpp )

SetFlags()
SetLibraries( DIGUI )
CreateLibrary( ${PROJECT_NAME} )