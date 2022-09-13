using Tracer.Serialization.Abstraction.Classes;
using Tracer.Core.Structs;
namespace Tracer.Core
{
    public class TraceResultsParser
    {
        public List<ThreadInfo> GetMethodsAndThreadsHierarchy(TraceResult traceResults)
        {
            List<ThreadInfo> result = new List<ThreadInfo>();
            var threadsIds = GetThreadsIds(traceResults);
            foreach (var th in threadsIds)
            {
                TraceResult threadTraceResults = GetTraceResultsForThread(th, traceResults);
                List<string> parentMethods = GetParentMethods(threadTraceResults);
                List<MethodInfo> methods = new List<MethodInfo>();
                foreach (var parentMethod in parentMethods)
                {
                    methods.AddRange(GetMethodsHierarchy(threadTraceResults, parentMethod));
                }
                result.Add(new ThreadInfo(th, CountTotalElapsedTime(methods), methods));
            }
            return result;
        }

        private long CountTotalElapsedTime(List<MethodInfo> methods)
        {
            long result = 0;
            foreach (var method in methods)
            {
                result += method.Time;
                result += CountTotalElapsedTime(method.Methods);
            }
            return result;
        }

        private List<MethodInfo> GetMethodsHierarchy(TraceResult traceResults, string parentMethod)
        {
            List<MethodInfo> results = new List<MethodInfo>();
            for (int i = 0; i < traceResults.ParentMethodsNames.Count; i++)
            {
                if (traceResults.ParentMethodsNames[i].Equals(parentMethod))
                    results.Add(new MethodInfo(traceResults.MethodNames[i], traceResults.ClassNames[i], traceResults.ElapsedTime[i], GetMethodsHierarchy(traceResults, traceResults.MethodNames[i])));
            }
            return results;
        }

        private List<string> GetParentMethods(TraceResult results)
        {
            List<string> result = new List<string>();
            foreach (var method in results.ParentMethodsNames)
            {
                if (!results.MethodNames.Contains(method) && !result.Contains(method))
                    result.Add(method);
            }
            return result;
        }

        private HashSet<int> GetThreadsIds(TraceResult traceResult)
        {
            var result = new HashSet<int>(traceResult.CurrentThreadsIds);
            return result;
        }

        private TraceResult GetTraceResultsForThread(int threadId, TraceResult traceResult)
        {
            var result = new TraceResult();
            for (int i = 0; i < traceResult.MethodNames.Count; i++)
            {
                if (traceResult.CurrentThreadsIds[i] == threadId)
                    result.AddResult(traceResult.MethodNames[i], traceResult.ClassNames[i], traceResult.ParentMethodsNames[i],
                        traceResult.ElapsedTime[i], threadId);
            }
            return result;
        }
    }
}