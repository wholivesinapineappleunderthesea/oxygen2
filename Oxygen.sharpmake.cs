using System.Collections.Generic;
using Sharpmake;

namespace Oxygen
{
	public abstract class BaseProject : Project
	{
		protected BaseProject()
		{
			RootPath = @"[project.SharpmakeCsPath]\projects\[project.Name]";
			SourceRootPath = @"[project.RootPath]\codebase";
		}
		[Configure]
		public virtual void ConfigureAll(Configuration conf, Target target)
		{
			conf.ProjectFileName = "[project.Name]_[target.Platform]";
			if (target.DevEnv != DevEnv.xcode)
				conf.ProjectFileName += "_[target.DevEnv]";
			conf.ProjectPath = @"[project.SharpmakeCsPath]\solution\projects\[project.Name]";
			conf.IntermediatePath = @"[project.SharpmakeCsPath]\solution\intermediate\[project.Name]_[target.Optimization]";
			conf.TargetPath = @"[project.SharpmakeCsPath]\solution\output\[project.Name]_[target.Optimization]";

			// Exceptions:
			conf.Options.Add(Options.Vc.Compiler.Exceptions.Disable);
			conf.Defines.Add("_HAS_EXCEPTIONS=0");

			// Compile time safeties:
			//conf.Options.Add(Options.Vc.General.TreatWarningsAsErrors.Enable);

			// C++ Library Mode:
			if (target.Optimization == Optimization.Debug)
				conf.Options.Add(Options.Vc.Compiler.RuntimeLibrary.MultiThreadedDebugDLL); // faster compile
			else
				conf.Options.Add(Options.Vc.Compiler.RuntimeLibrary.MultiThreaded);

			// C++ Standard:
			conf.Options.Add(Options.Vc.Compiler.CppLanguageStandard.Latest);
			conf.Options.Add(Options.Vc.Compiler.DefineCPlusPlus.Enable);

			conf.CustomProperties.Add("CustomOptimizationProperty", $"Custom-{target.Optimization}");

			// Include from source root
			conf.IncludePaths.Add(SourceRootPath);

			conf.Defines.Add("OXYWIN32");

			// Debug/Release defines
			if (target.Optimization == Optimization.Debug)
			{
				conf.Defines.Add("OXYDEBUG");
			}
			else
			{
				conf.Defines.Add("OXYRELEASE");
			}
		}

		public static ITarget[] GetDefaultTargets()
		{
			var targets = new List<ITarget>
			{
				new Target(
					Platform.win64,
					DevEnv.vs2022,
					Optimization.Release | Optimization.Debug
				),
			};

			return targets.ToArray();
		}
	}
	[Sharpmake.Generate]
	public class OxygenProject : BaseProject
	{
		public OxygenProject()
		{
			AddTargets(BaseProject.GetDefaultTargets());
			Name = "oxygen";
		}

		public override void ConfigureAll(Configuration conf, Target target)
		{
			base.ConfigureAll(conf, target);
			conf.Output = Configuration.OutputType.Exe;

			conf.SolutionFolder = "Engine";

			// Precompiled Headers:
			conf.PrecompHeader = "OxygenPCH.h";
			conf.PrecompSource = "OxygenPCH.cpp";

			conf.IncludePaths.Add(SourceRootPath + @"\engine");

			// OpenMP
			//conf.Options.Add(Options.Vc.Compiler.OpenMP.Enable);

			// Fastmath
			conf.Options.Add(Options.Vc.Compiler.FloatingPointModel.Fast);

			// Link dx11
			conf.LibraryFiles.Add("d3d11.lib");
			conf.LibraryFiles.Add("dxgi.lib");
			conf.LibraryFiles.Add("d3dcompiler.lib");

			// Resources
			// in [project.SharpmakeCsPath]\resources
			var fileInfo = Util.GetCurrentSharpmakeFileInfo();
			string rootDirectory = Util.SimplifyPath(fileInfo.DirectoryName);
			var resourcePath = System.IO.Path.Combine(rootDirectory, "resources");
			foreach (var file in System.IO.Directory.GetFiles(resourcePath, "*", System.IO.SearchOption.AllDirectories))
			{
				// folder path relative to resources/
				var relativePath = System.IO.Path.GetRelativePath(resourcePath, file);
				// remove file name
				var folderPath = System.IO.Path.GetDirectoryName(relativePath);
				// add to copy files
				conf.TargetCopyFilesToSubDirectory.Add(
					new KeyValuePair<string, string>(file, folderPath)
				);
			}

		}
	}
	[Sharpmake.Generate]
	public class OxygenSolution : Sharpmake.Solution
	{
		public OxygenSolution()
		{
			Name = "Oxygen";

			AddTargets(new Target(
					Platform.win64,
					DevEnv.vs2022,
					Optimization.Debug | Optimization.Release
			));
		}

		[Configure()]
		public void ConfigureAll(Configuration conf, Target target)
		{
			conf.SolutionFileName = "[solution.Name]_[target.DevEnv]_[target.Platform]";
			conf.SolutionPath = @"[solution.SharpmakeCsPath]\solution";
			conf.AddProject<OxygenProject>(target);
		}
	}
	public static class Main
	{
		[Sharpmake.Main]
		public static void SharpmakeMain(Sharpmake.Arguments arguments)
		{
			// Use the latest Windows 10 Kit
			KitsRootPaths.SetKitsRoot10ToHighestInstalledVersion(DevEnv.vs2022);
			arguments.Generate<OxygenSolution>();
		}
	}
}