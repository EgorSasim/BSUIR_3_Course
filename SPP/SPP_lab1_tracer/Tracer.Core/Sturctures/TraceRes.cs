namespace Tracer.Core.Structs
{
    public struct TraceResult
    {
        public List<string> MethodNames;
        public List<string> ClassNames;
        public List<string> ParentMethodsNames;
        public List<long> ElapsedTime;
        public List<int> CurrentThreadsIds;

        public TraceResult()
        {
            MethodNames = new List<string>();
            ClassNames = new List<string>();
            ParentMethodsNames = new List<string>();
            ElapsedTime = new List<long>();
            CurrentThreadsIds = new List<int>();
        }

        public void AddResult(string methodName, string className, string ancestorsMethodName, long elapsedMilliseconds, int currentThreadId)
        {
            MethodNames.Add(methodName);
            ClassNames.Add(className);
            ParentMethodsNames.Add(ancestorsMethodName);
            ElapsedTime.Add(elapsedMilliseconds);
            CurrentThreadsIds.Add(currentThreadId);
        }
    }
}