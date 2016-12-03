using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SYKScenic
{
    public struct Vertex
    {

        public uint popularity { get; set; }
        public uint number;
        public string name;
        public string info;
        public bool restArea;
        public bool WC;
        public Vertex(string n, uint p, string i, bool r, bool w)
        {
            name = n;
            popularity = p;
            info = i;
            number = 0;
            restArea = r;
            WC = w;
        }

        public void reset(uint p, string i, bool r, bool w)
        {
            popularity = p;
            info = i;
            restArea = r;
            WC = w;
        }
    }

    public struct Edge
    {
        public uint distance { get; set; }
        public Vertex start;
        public Vertex end;

        public Edge(Vertex s, Vertex e, uint dis)
        {
            start = s;
            end = e;
            distance = dis;
        }
    }
}
