--[[
  This file is part of the Abstract Graphics Library.
  See readme.md and license.md for details.
]]--

Defines.samples.cube =
{
}

IncludePaths.samples.cube =
{
    [{ }] =
    {
        "../../agl/include",
        "../framework/include"
    }
}

LibraryPaths.samples.cube =
{
    [{ }] =
    {
        "../../lib/" .. _ACTION
    }
}

Dependencies.samples.cube =
{
    [{ "opengl" }] =
    {
        "agl_opengl",
        "framework_opengl"
    },

    [{ "opengl-debug" }] =
    {
        "agl_opengl_d",
        "framework_opengl_d"
    }
}

TargetSuffix.samples.cube =
{
    [{ "" }]             = "",
    [{ "opengl" }]       = "_opengl",
    [{ "opengl-debug" }] = "_opengl_d"
}

Flags.samples.cube =
{
    [{ "opengl" }] =
    {
        "Optimize", "EnableSSE", "EnableSSE2"
    },

    [{ "opengl-debug" }] =
    {
        "Symbols"
    }
}

project "cube"

    kind       ( "ConsoleApp" )
    language   ( "C" )
    uuid       ( "f4aabc84-8de6-45c6-924e-4b0762b455dc" )

    objdir     ( "../../build/" .. _ACTION .. "/samples/cube/obj" )
    targetdir  ( "../../bin/" .. _ACTION .. "/samples" )
    targetname ( "cube" )

    for k,v in pairs(Defines.samples.cube) do
        configuration(k)
        defines(v)
    end

    for k,v in pairs(IncludePaths.samples.cube) do
        configuration(k)
        includedirs(v)
    end

    for k,v in pairs(LibraryPaths.samples.cube) do
        configuration(k)
        libdirs(v)
    end

    for k,v in pairs(Dependencies.samples.cube) do
        configuration(k)
        links(v)
    end

    for k,v in pairs(TargetSuffix.samples.cube) do
        configuration(k)
        targetsuffix(v)
    end

    for k,v in pairs(Flags.samples.cube) do
        configuration(k)
        flags(v)
    end

    configuration {}
        files { "source/samples/cube.c" }