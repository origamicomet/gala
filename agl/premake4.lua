--[[
  This file is part of the Abstract Graphics Library.
  See readme.md and license.md for details.
]]--

Defines.agl =
{
    [{}] =
    {
        "AGL_BUILD"
    },

    [{ "opengl" }] =
    {
        "AGL_GL_VER=31"
    }
}

IncludePaths.agl =
{
    [{ "windows" }] =
    {
        "../dependencies/Cg/include",
        "../dependencies/GLEW/include",
        "../dependencies/glext/include"
    }
}

LibraryPaths.agl =
{
    [{ "windows" }] =
    {
        "../dependencies/Cg/lib/" .. _ACTION
    },

    [{ "windows", "opengl" }] =
    {
        "../dependencies/GLEW/lib/" .. _ACTION
    }
}

Dependencies.agl =
{
    [{ "windows" }] =
    {
        "cg"
    },

    [{ "windows", "opengl" }] =
    {
        "opengl32",
        "cgGL",
        "glew32"
    }
}

TargetSuffix.agl =
{
    [{ "" }]       = "",
    [{ "opengl" }] = "_opengl"
}

solution "agl"

    location ( "../build/" .. _ACTION )

    configurations
    {
        "debug", "release", "opengl"
    }

    platforms
    {
        "x32", "x64"
    }

    project "agl"

        kind       ( "SharedLib" )
        language   ( "C" )
        uuid       ( "6c0bdcd2-8e93-4864-93dc-31340b298953" )

        objdir     ( "../build/" .. _ACTION .. "/agl/obj" )
        targetdir  ( "../bin/" .. _ACTION )
        targetname ( "agl" )

        for k,v in pairs(Defines.agl) do
            configuration(k)
            defines(v)
        end

        for k,v in pairs(IncludePaths.agl) do
            configuration(k)
            includedirs(v)
        end

        for k,v in pairs(LibraryPaths.agl) do
            configuration(k)
            libdirs(v)
        end

        for k,v in pairs(Dependencies.agl) do
            configuration(k)
            links(v)
        end

        for k,v in pairs(TargetSuffix.agl) do
            configuration(k)
            targetsuffix(v)
        end

        configuration { "debug" }
            flags { "Symbols" }

        configuration { "release" }
            flags { "Optimize", "EnableSSE", "EnableSSE2" }

        configuration {}
            includedirs
            {
                "include"
            }

            files
            {
                "include/**.h",
                "source/**.c"
            }