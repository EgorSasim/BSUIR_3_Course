using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TestsGenerator.Core
{
    internal class ParsedClass
    {
        public string Namespace;

        public string ClassName;

        public string FullName => !string.IsNullOrWhiteSpace(Namespace) ? $"{Namespace}.{ClassName}" : ClassName;

        public List<ParsedMethod> methods = new();
    }
}
