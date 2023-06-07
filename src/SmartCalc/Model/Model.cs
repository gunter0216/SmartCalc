using System.Runtime.InteropServices;
using System.Text;

namespace Model
{
    public static class Model
    {
        [DllImport("ModelDll\\build\\ModelDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public unsafe extern static double Calc(StringBuilder str, double x = 0);

        [DllImport("ModelDll\\build\\ModelDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public unsafe extern static bool GetError();

        [DllImport("ModelDll\\build\\ModelDll.dll", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.Cdecl)]
        public unsafe extern static double LastCalc(double x);
    }
}