namespace TestsGenerator.Core
{
    public class ParsedMethod
    {
        public string paramsStr;

        public string methodName;

        public string fullName => $"{methodName}_{paramsStr}";

    }
}
