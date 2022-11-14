using TestsGenerator.Core;

namespace TestsGenerator
{
    internal class Program
    {
        static void Main(string[] args)
        {
            TestsGenerator1 generator = new(@"D:\Учеба\5 сем\СПП\lab4\TestsGenerator\Generated");

            generator.Generate(
                @"D:\Учеба\5 сем\СПП\lab4\TestsGenerator\TestsGenerator.Tests\ClassForTests.cs",
                @"D:\Учеба\5 сем\СПП\lab4\TestsGenerator\TestsGenerator.Core\CodeGenerator.cs"
            ).GetAwaiter().GetResult();
        }
    }
}