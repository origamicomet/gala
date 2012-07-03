--[[
  This file is part of the Abstract Graphics Library.
  See readme.md and license.md for details.
]]--

Defines.agl =
{
    [{}] = { "AGL_BUILD" }
}

IncludePaths.agl =
{
    [{}] = { "include" },
    [{ "windows" }] = { 
        "../dependencies/Cg/include",
        "../dependencies/GLEW/include",
        "../dependencies/glext/include"
    }
}

LibraryPaths.agl =
{
    [{ "windows" }]                   = { "../dependencies/Cg/lib/"   .. _ACTION },
    [{ "windows", "opengl_debug" }]   = { "../dependencies/GLEW/lib/" .. _ACTION },
    [{ "windows", "opengl_release" }] = { "../dependencies/GLEW/lib/" .. _ACTION }
}

Dependencies.agl =
{
    [{ "windows" }]                   = { "cg" },
    [{ "windows", "opengl_debug" }]   = { "opengl32", "cgGL", "glew32" },
    [{ "windows", "opengl_release" }] = { "opengl32", "cgGL", "glew32" }
}

Flags.agl =
{
    [{ "opengl_debug" }]   = { "Symbols" },
    [{ "opengl_release" }] = { "Optimize", "EnableSSE", "EnableSSE2" }
}

TargetSuffix.agl =
{
    [{ "opengl_debug" }]   = "_gld",
    [{ "opengl_release" }] = "_gl"
}

solution "agl"
    location       ( "../build/" .. _ACTION .. "/agl" )
    configurations { "opengl_debug", "opengl_release" }

    project "agl"

        kind       ( "SharedLib" )
        language   ( "C" )
        uuid       ( "6c0bdcd2-8e93-4864-93dc-31340b298953" )

        objdir     ( "../build/" .. _ACTION .. "/agl/obj" )
        targetdir  ( "../lib/" .. _ACTION )
        targetname ( "agl" )

        configuration { "windows" }
            postbuildcommands {
                "move \"..\\..\\..\\lib\\" .. _ACTION .. "\\*.dll\" \"..\\..\\..\\bin\\" .. _ACTION .."\\\""
            }

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

        for k,v in pairs(Flags.agl) do
            configuration(k)
            flags(v)
        end

        configuration {}
            files {
                "include/**.h",
                "source/**.c"
            }