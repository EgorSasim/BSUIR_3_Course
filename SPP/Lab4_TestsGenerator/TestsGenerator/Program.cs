using TestsGenerator.Core;

namespace TestsGenerator
{
    internal class Program
    {
        static void Main(string[] args)
        {
            TestsGenerator1 generator = new(@"D:\BSUIR_3_Course\SPP\Lab4_TestsGenerator\TestsGenerator\Generated");

            generator.Generate(
                @"D:\BSUIR_3_Course\SPP\Lab4_TestsGenerator\TestsGenerator\TestsGenerator.Tests\ClassForTests.cs",
                @"D:\BSUIR_3_Course\SPP\Lab4_TestsGenerator\TestsGenerator\TestsGenerator.Core\CodeGenerator.cs"
            ).GetAwaiter().GetResult();
        }
    }
}