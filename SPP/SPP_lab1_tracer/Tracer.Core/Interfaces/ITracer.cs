using Tracer.Core.Structs;

namespace Tracer.Core.Interfaces
{
    public interface ITracer
    {
        void StartTrace();
        void StopTrace();
        TraceResult GetTraceResult();
    }
}