
using Flax.Build;
using Flax.Build.NativeCpp;
using System.IO;
using System.Linq;

public class SteamWorksFlax : GameModule
{
    /// <inheritdoc />
    public override void Init()
    {
        base.Init();

        // C#-only scripting
        BuildNativeCode = true;
    }

    /// <inheritdoc />
    public override void Setup(BuildOptions options)
    {
        base.Setup(options);

        options.ScriptingAPI.IgnoreMissingDocumentationWarnings = true;

        options.PublicDependencies.Add("OnlinePlatform");

        options.CompileEnv.IncludePaths.Add(Path.Combine(FolderPath, "include"));

        if (options.ScriptingAPI.Defines.Contains("PLATFORM_WINDOWS"))
            options.LinkEnv.InputLibraries.Add(Path.Combine(FolderPath, "lib", "steam_api64.dll"));
        if (options.ScriptingAPI.Defines.Contains("PLATFORM_LINUX"))
            options.LinkEnv.InputLibraries.Add(Path.Combine(FolderPath, "lib", "libsteam_api.so"));

        // Here you can modify the build options for your game module
        // To reference another module use: options.PublicDependencies.Add("Audio");
        // To add C++ define use: options.PublicDefinitions.Add("COMPILE_WITH_FLAX");
        // To learn more see scripting documentation.
    }
}
