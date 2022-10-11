namespace DirectoryScanner.Core.Struct
{
    public sealed class DirectoryNode : Node
    {
        public bool IsComplited
        {
            get => _isComplited;
            set
            {
                _isComplited = value;
                OnPropertyChanged(nameof(FormatedSize));
                OnPropertyChanged(nameof(Childs));
                OnPropertyChanged(nameof(FormatedPercent));
            }
        }

        public IEnumerable<Node> Childs
        {
            get => _childs;
            set {
                _childs = value;
                OnPropertyChanged(nameof(Childs));
            }
        }

        private IEnumerable<Node> _childs;
        private bool _isComplited = false;

        public DirectoryNode(string path, DirectoryNode? directoryNode) : base(path, directoryNode)
        {
        }

        public override long? Size => IsComplited && Childs.All(x => x.Size.HasValue) ? Childs.Sum(x => x.Size) : null;
    }
}
