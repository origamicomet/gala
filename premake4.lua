--[[
  This file is part of the Abstract Graphics Library.
  See readme.md and license.md for details.
]]--

Defines =
{
    ["Global"] =
    {
        [{ "" }] =
        {
        },

        [{ "windows", "release" }] =
        {
            "_HAS_ITERATOR_DEBUGGING=0",
            "_SECURE_SCL=0"
        },

        [{ "macosx" }] =
        {
        },

        [{ "linux" }] =
        {
        }
    }
}

IncludePaths =
{
    ["Global"] =
    {
    }
}

LibraryPaths =
{
    ["Global"] =
    {
    }
}

Dependencies =
{
    ["Global"] =
    {
    }
}

include "agl"
include "dependencies"
include "samples"