using System.Runtime.InteropServices;
using System.Text;


namespace SYKScenic
{
    class ScenicDll
    {
        //链接自定义的C++ Dll库
        [DllImport("ScenicDll.dll", EntryPoint = "CreateNewVertex", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern uint CreateNewVertex(string name, uint popu, string info, bool r, bool w);

        [DllImport("ScenicDll.dll", EntryPoint = "CreateNewEdge", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern uint CreateNewEdge(string start, string end, uint dis);

        [DllImport("ScenicDll.dll", EntryPoint = "GetTourGuide", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern uint GetTourGuide(StringBuilder msg);

        [DllImport("ScenicDll.dll", EntryPoint = "GetLoopGraph", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern uint GetLoopGraph(StringBuilder msg);

        [DllImport("ScenicDll.dll", EntryPoint = "MiniDistance", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern uint MiniDistance(StringBuilder msg, string start, string end);

        [DllImport("ScenicDll.dll", EntryPoint = "MiniSpanTree", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern uint MiniSpanTree(StringBuilder msg);

        [DllImport("ScenicDll.dll", EntryPoint = "SortByPopularity", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern uint SortByPopularity(StringBuilder msg);

        [DllImport("ScenicDll.dll", EntryPoint = "KeySearch", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        public static extern uint KeySearch(StringBuilder msg);

    }
}
