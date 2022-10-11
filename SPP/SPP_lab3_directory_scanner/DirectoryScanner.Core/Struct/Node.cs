using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;
using System.Runtime.CompilerServices;

namespace DirectoryScanner.Core.Struct
{
    public abstract class Node : INotifyPropertyChanged
    {
        public abstract long? Size { get; }

        public string FormatedSize => Size.HasValue ? $"Size {Size.Value}" : "Size -";

        public string Name => Path.GetFileName(Fullpath);

        public string Fullpath;

        public DirectoryNode? Parent;

        public event PropertyChangedEventHandler? PropertyChanged;
        public void OnPropertyChanged([CallerMemberName] string prop = "")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(prop));
        }

        public float? Percent => Parent != null && Parent.Size.HasValue ? Size / ((float)Parent.Size) : null;

        public string FormatedPercent => Percent.HasValue ? $"Percent {Percent.Value:0.00}%" : "Percent -";

        public Node(string path, DirectoryNode? directoryNode)
        {
            Fullpath = path;
            Parent = directoryNode;
            if(Parent != null)
            {
                PropertyChanged += (x,y) => Parent.OnPropertyChanged(y.PropertyName);
            }
           
        }
    }
}
