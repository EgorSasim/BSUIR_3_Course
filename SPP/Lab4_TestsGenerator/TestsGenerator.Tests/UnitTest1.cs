using TestsGenerator.Core;

namespace TestsGenerator.Tests
{
    public class UnitTest1 : IDisposable
    {
        const string Folder = $@"D:\Учеба\5 сем\СПП\lab4\TestsGenerator\Generated";
        readonly TestsGenerator1 _generator;

        public UnitTest1()
        {
            _generator = new(Folder);
        }

        [Fact]
        public async void SimpTest()
        {
            await _generator.Generate(@"D:\Учеба\5 сем\СПП\lab4\TestsGenerator\TestsGenerator.Tests\ClassForTests.cs");

            Assert.True(File.Exists(Folder + "\\" + typeof(ClassForTests).FullName + ".cs"));
        }

        [Fact]
        public async void OverloadTest()
        {
            await _generator.Generate(@"D:\Учеба\5 сем\СПП\lab4\TestsGenerator\TestsGenerator.Tests\ClassWithoverload.cs");

            var text = File.ReadAllText(Folder + "\\" + typeof(ClassWithoverload).FullName + ".cs");

            foreach (var method in typeof(ClassWithoverload).GetMethods())
            {
                text.Contains($"{method.Name}_{string.Join("_", method.GetParameters().Select(x => x.ParameterType.ToString()))}");
            }
        }

        [Fact]
        public async void TwoClassesTest()
        {
            await _generator.Generate(@"D:\Учеба\5 сем\СПП\lab4\TestsGenerator\TestsGenerator.Tests\FileWithTwoClasses.cs");

            Assert.True(File.Exists(Folder + "\\" + typeof(ClassOne).FullName + ".cs"));
            Assert.True(File.Exists(Folder + "\\" + typeof(ClassTwo).FullName + ".cs"));
        }

        [Fact]
        public async void ClassInsideClassTest()
        {
            await _generator.Generate(@"D:\Учеба\5 сем\СПП\lab4\TestsGenerator\TestsGenerator.Tests\ClassWithInnerClass.cs");

            Assert.True(File.Exists(Folder + "\\" + typeof(ClassWithInnerClass).FullName + ".cs"));
            Assert.True(File.Exists(Folder + "\\" + typeof(ClassWithInnerClass.InnerClass).FullName.Replace('+', '.') + ".cs"));
        }

        public void Dispose()
        {
            DirectoryInfo di = new(Folder);

            foreach (FileInfo file in di.GetFiles())
            {
                file.Delete();
            }
        }
    }
}