using DirectoryScanner.Core.Struct;
using System.Collections.Concurrent;

namespace DirectoryScanner.Core
{
    public class Scanner
    {
        private uint _threadCount;
        private Semaphore _semaphore;
        private ConcurrentDictionary<Thread, int> _threads = new();

        public readonly DirectoryNode Root;

        private ConcurrentQueue<DirectoryNode> _queqe = new();
        private CancellationToken _token;

        public Scanner(uint threadCount, string path, CancellationToken token)
        {
            _threadCount = threadCount;
            _semaphore = new Semaphore((int)threadCount, (int)threadCount);
            Root = new DirectoryNode(path, null);
            _queqe.Enqueue(Root);
            _token = token;
        }

        public void StartProcess()
        {
            while (_queqe.Any() || _threads.Any() && !_token.IsCancellationRequested)
            {
                _semaphore.WaitOne();
                if (_queqe.TryDequeue(out DirectoryNode directory) && !_token.IsCancellationRequested)
                {
                    Thread thread = new(obj => ScanNode((DirectoryNode)obj));
                    _threads[thread] = thread.ManagedThreadId;
                    thread.Start(directory);
                }
                _semaphore.Release();
            }
        }

        private void ScanNode(DirectoryNode node)
        {
            _semaphore.WaitOne();
            var dir = new DirectoryInfo(node.Fullpath);

            var newNodes = new List<Node>();

            foreach (var subDir in dir.EnumerateDirectories())
            {
                if (_token.IsCancellationRequested) break;
                var subNode = new DirectoryNode(subDir.FullName, node);
                _queqe.Enqueue(subNode);

                newNodes.Add(subNode);
                //Thread.Sleep(500);
            }

            foreach (var file in dir.EnumerateFiles())
            {
                //Thread.Sleep(500);
                if (_token.IsCancellationRequested) break;
                newNodes.Add(new FileNode(file.FullName, file.Length, node));
            }

            node.Childs = newNodes;
            node.IsComplited = !_token.IsCancellationRequested;
            _threads.TryRemove(new (Thread.CurrentThread, Environment.CurrentManagedThreadId));
            _semaphore.Release();
        } 
    }
}