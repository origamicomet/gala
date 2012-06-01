--[[
  This file is part of the Abstract Graphics Library.
  See readme.md and license.md for details.
]]--

Defines.samples =
{
}

IncludePaths.samples =
{
}

LibraryPaths.samples =
{
}

Dependencies.samples =
{
}

TargetSuffix.samples =
{
}

Flags.samples =
{
}

solution "samples"

    location ( "../build/" .. _ACTION )

    configurations
    {
        "opengl", "opengl-debug"
    }

    platforms
    {
        "x32", "x64"
    }

    include "framework"
    include "cube"