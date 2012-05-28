--[[
  This file is part of the Abstract Graphics Library.
  See readme.md and license.md for details.
]]--

Defines.samples.framework =
{
}

IncludePaths.samples.framework =
{
    [{ }] =
    {
        "../../agl/include"
    }
}

LibraryPaths.samples.framework =
{
    [{ }] =
    {
        "../../lib/" .. _ACTION
    }
}

Dependencies.samples.framework =
{
    [{ "opengl" }] =
    {
        "agl_opengl"
    }
}

TargetSuffix.samples.framework =
{
    [{ "" }]       = "",
    [{ "opengl" }] = "_opengl"
}

project "framework"

    kind       ( "StaticLib" )
    language   ( "C" )
    uuid       ( "e883bdd2-8fb6-4589-8c55-5a748a7c675f" )

    objdir     ( "../../build/" .. _ACTION .. "/samples/framework/obj" )
    targetdir  ( "../../lib/" .. _ACTION )
    targetname ( "framework" )

    for k,v in pairs(Defines.samples.framework) do
        configuration(k)
        defines(v)
    end

    for k,v in pairs(IncludePaths.samples.framework) do
        configuration(k)
        includedirs(v)
    end

    for k,v in pairs(LibraryPaths.samples.framework) do
        configuration(k)
        libdirs(v)
    end

    for k,v in pairs(Dependencies.samples.framework) do
        configuration(k)
        links(v)
    end

    for k,v in pairs(TargetSuffix.samples.framework) do
        configuration(k)
        targetsuffix(v)
    end

    configuration { "debug" }
        flags { "Symbols" }

    configuration { "release" }
        flags { "Optimize", "EnableSSE", "EnableSSE2" }

    configuration {}
        includedirs { "include" }
        files       { "source/samples/framework.c" }