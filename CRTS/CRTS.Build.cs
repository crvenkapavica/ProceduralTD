// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using System.IO;
using System;
using UnrealBuildTool;

public class CRTS : ModuleRules
{
    private string ModulePath {
        get { return ModuleDirectory; }
    }
    private string ThirdPartyPath {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../../ThirdParty/")); }
    }
    public CRTS(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore",
        "HeadMountedDisplay", "UMG", "Slate", "SlateCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        LoadFBX(Target);
    }
    public bool LoadFBX(ReadOnlyTargetRules Target)
    {
        // Libraries Path      
        string LibrariesPath = Path.Combine(ThirdPartyPath, "fbx", "Libraries");
        PublicLibraryPaths.Add(LibrariesPath);
        PublicAdditionalLibraries.Add(Path.Combine(LibrariesPath, "libfbxsdk-md.lib"));

        // Include path
        string IncludePath = Path.Combine(ThirdPartyPath, "fbx", "Includes");
        PublicIncludePaths.Add(IncludePath);

        // Definitions
        Definitions.Add(string.Format("WITH_FBX_BINDING=1"));
        return true;
    }
}