using System.Threading.Tasks.Dataflow;

namespace TestsGenerator.Core
{
    public class TestsGenerator1
    {
        private string _folder;

        private readonly int _parallelRead;
        private readonly int _parallelProcess;
        private readonly int _parallelWrite;

        private DataflowLinkOptions _dataflowLinkOptions = new() { PropagateCompletion = true };

        public TestsGenerator1(string folderPath, int parallelRead = 3, int parallelProcess = 3, int parallelWrite = 3)
        {
            _folder = folderPath;
            _parallelRead = parallelRead;
            _parallelProcess = parallelProcess;
            _parallelWrite = parallelWrite;
        }

        public async Task Generate(params string[] files)
        {
            var InputBuffer = new BufferBlock<string>();
            var ReadFiles = new TransformBlock<string, string>(ReadFile, new ExecutionDataflowBlockOptions() { MaxDegreeOfParallelism = _parallelRead });

            var ParseBlock = new TransformManyBlock<string, ParsedClass>(CodeGenerator.GetAllClassesFromFile, new ExecutionDataflowBlockOptions() { MaxDegreeOfParallelism = _parallelProcess });
            var Buffer = new BufferBlock<ParsedClass>();

            var GenerationBlock = new TransformBlock<ParsedClass, (string, string)>(CodeGenerator.BuildTextFile, new ExecutionDataflowBlockOptions() { MaxDegreeOfParallelism = _parallelProcess });

            var WriteBlock = new ActionBlock<(string path, string contents)>(WriteToFile, new ExecutionDataflowBlockOptions() { MaxDegreeOfParallelism = _parallelWrite });

            InputBuffer.LinkTo(ReadFiles, _dataflowLinkOptions);
            ReadFiles.LinkTo(ParseBlock, _dataflowLinkOptions);
            ParseBlock.LinkTo(Buffer, _dataflowLinkOptions);
            Buffer.LinkTo(GenerationBlock, _dataflowLinkOptions);
            GenerationBlock.LinkTo(WriteBlock, _dataflowLinkOptions);

            foreach (var file in files)
                InputBuffer.Post(file);

            InputBuffer.Complete();

            await WriteBlock.Completion;
        }


        public async Task<string> ReadFile(string path)
        {
            Console.WriteLine($"Reading {path}");
            return await File.ReadAllTextAsync(path);
        }
        public async Task WriteToFile((string path, string contents) file)
        {
            Console.WriteLine($"Writing to {file.path}");
            await File.WriteAllTextAsync($@"{_folder}\{file.path}.cs", file.contents);
        }
    }
}
