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
