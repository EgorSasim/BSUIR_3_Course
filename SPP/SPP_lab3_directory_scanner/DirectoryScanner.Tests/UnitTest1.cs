using DirectoryScanner.Core;
using DirectoryScanner.Core.Struct;

namespace DirectoryScanner.Tests
{
    public class UnitTest1
    {
        [Fact]
        public void Test1()
        {
            var _token = new CancellationTokenSource();

            Scanner scanner = new Scanner(4, @"D:\Учеба\5 сем\НПО\lb1", _token.Token);
            scanner.StartProcess();

            Assert.True(scanner.Root.Childs.Count() == 5);
        }

        [Fact]
        public void Test2()
        {
            var _token = new CancellationTokenSource();

            Scanner scanner = new Scanner(10, @"D:\Учеба\5 сем", _token.Token);
            scanner.StartProcess();

            Assert.True(scanner.Root.Childs.Count() == 6 && scanner.Root.Childs.All(x => x is DirectoryNode));
        }


        [Fact]
        public void Test3()
        {
            var _token = new CancellationTokenSource();

            Scanner scanner = new Scanner(10, @"D:\Учеба\5 сем", _token.Token);
            scanner.StartProcess();

            Assert.True(((DirectoryNode)scanner.Root.Childs.Single(x => x.Name == "GBA")).Childs.All(x => x is FileNode));
        }
    }
}