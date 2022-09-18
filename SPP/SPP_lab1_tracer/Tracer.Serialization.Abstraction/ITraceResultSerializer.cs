using Tracer.Serialization.Abstraction.Classes;
namespace Tracer.Serialization.Abstractions
{
    public interface ITraceResultsSerializer
    {
        void Serialize(List<ThreadInfo> results, Stream to);
    }
}