using Tracer.Core.Interfaces;
using System.Diagnostics;
using Tracer.Core.Structs;
using System.Reflection;

namespace Tracer.Core;

public class Tracer : ITracer
{
    private Stopwatch _stopwatch = new();
    private TraceResult _result = new();
    public TraceResult GetTraceResult() => _result;

    public void StartTrace()
    {
        _stopwatch.Start();
    }

  public void StopTrace()
        {
            _stopwatch.Stop();
            StackTrace st = new();
            StackFrame stackFrame = st.GetFrame(1);
            MethodBase mb = stackFrame.GetMethod();
            long innerTime = 0;
            for (int i = 0; i < _result.MethodNames.Count; i++)
            {
                if (_result.ParentMethodsNames[i].Equals(mb.Name))
                    innerTime += _result.ElapsedTime[i];
            }
            _result.AddResult(mb.Name, mb.DeclaringType.Name, st.GetFrame(2).GetMethod().Name, _stopwatch.ElapsedMilliseconds + innerTime, Thread.CurrentThread.ManagedThreadId);
            _stopwatch.Reset();
            _stopwatch.Start();
        }
}

