// Copyright Epic Games, Inc. All Rights Reserved.

using System;
using System.IO;
using UnrealBuildTool;

public class MegaJam_2022_BoD : ModuleRules
{
    public MegaJam_2022_BoD(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        //Default Module Names
        PublicDependencyModuleNames.AddRange
            (
                new string[] 
                { 
                    "Core", 
                    "CoreUObject", 
                    "Engine", 
                    "InputCore",
                    "UMG",
                    "GameLiftServerSDK"
                }
            );

        //UMG Module Names
        PrivateDependencyModuleNames.AddRange
            (
                new string[] 
                { 
                    "Slate", 
                    "SlateCore"
                    //"OnlineSubsystem"
                }
            );

        //SET PATH
        var ProjectRootPath = System.IO.Path.GetFullPath(System.IO.Path.Combine(ModuleDirectory, "..\\..\\"));
        var GameLiftPath = System.IO.Path.GetFullPath(System.IO.Path.Combine(ProjectRootPath, "Plugins/GameLiftServerSDK/Source/GameLiftServerSDK/"));

        //Add include paths
        PublicIncludePaths.AddRange
            (
                new string[]
                {
                   Path.Combine(ModuleDirectory, "Public"),
                   Path.Combine(ModuleDirectory, "Public/Online"),
                   Path.Combine(ModuleDirectory, "Public/GameLift"),
                   Path.Combine(GameLiftPath, "Public")
                }
            );

        PrivateIncludePaths.AddRange
            (
                new string[] 
                {
                    Path.Combine(ModuleDirectory, "Private"),
                }
            );

        //SET UNICODE
        PublicDefinitions.Add("UNICODE");
        PublicDefinitions.Add("_UNICODE");

        // Build Platform Info
        System.Console.Write("---------- Target.Platform: ");
        if (Target.Platform == UnrealTargetPlatform.Win64 || Target.Platform == UnrealTargetPlatform.Win32)
        {
            Console.WriteLine("Windows");

        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            Console.WriteLine("Linux");
        }
        else
        {
            Console.WriteLine("Others");
        }
    }
}
