-- premake5.lua
workspace "Ray-Tracing-II"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Ray-Tracing-II"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
include "Walnut/WalnutExternal.lua"

include "Ray-Tracing-II"