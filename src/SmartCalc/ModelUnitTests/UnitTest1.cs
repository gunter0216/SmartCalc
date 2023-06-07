using Model;
using System.Text;

namespace ModelUnitTests
{
    public class UnitTest1
    {
        const double EPS = 1e-7;

        [Fact]
        public void Add()
        {
            CalcTest("1+ 2", 3);
            CalcTest("1 +4", 5);
            CalcTest("3 + 2", 5);
            CalcTest(" 1+9 ", 10);
            CalcTest(" 1+(-9) ", -8);
        }

        [Fact]
        public void Sub()
        {
            CalcTest("1- 2", -1);
            CalcTest("1 -4", -3);
            CalcTest("3 - 2", 1);
            CalcTest(" 1-9 ", -8);
            CalcTest(" 1-(-9) ", 10);
        }

        [Fact]
        public void Mul()
        {
            CalcTest("1* 2", 2);
            CalcTest("1 *4", 4);
            CalcTest("3 * 2", 6);
            CalcTest(" 1*9 ", 9);
            CalcTest(" 1*(9) ", 9);
        }

        [Fact]
        public void Div()
        {
            CalcTest("1/ 2", 0.5);
            CalcTest("1 /4", 0.25);
            CalcTest("3 / 2", 1.5);
            CalcTest(" 1/9 ", 0.1111111111111111);
            CalcTest(" 1/(9) ", 0.1111111111111111);
        }

        [Fact]
        public void Pow()
        {
            CalcTest("2^3", 8);
            CalcTest("2^4", 16);
            CalcTest("2^-2", 0.25);
            CalcTest("2^(-2)", 0.25);
            CalcTest("1.23^(1.23)", 1.2899809210012809);
            CalcTest("sin(45)^2", 0.5000000000006399);
            CalcTest("sin(90)^cos(90)", 1);
        }

        [Fact]
        public void UPlus()
        {
            CalcTest("+3", 3);
            CalcTest("+(+3)", 3);
            CalcTest("+(-3)", -3);
            CalcTest("4 * (+3)", 12);
        }

        [Fact]
        public void UMinus()
        {
            CalcTest("-3", -3);
            CalcTest("-(-3)", 3);
            CalcTest("-(+3)", -3);
            CalcTest("4 * (-3)", -12);
            CalcTest("4 - (-3)", 7);
            CalcTest("4 + (-3)", 1);
        }

        [Fact]
        public void Brackets()
        {
            CalcTest("3 + (4 * 2) / 8", 4);
        }

        [Fact]
        public void Number()
        {
            CalcTest("1e-6", 1e-6);
            CalcTest("1e+6", 1e+6);
            CalcTest("1.23e-7", 1.23e-7);
            CalcTest("-1.23e-7", -1.23e-7);
            CalcTest("-123.456", -123.456);
        }

        [Fact]
        public void Sin()
        {
            CalcTest("sin( 90    )", 1);
            CalcTest("sin( -90)", -1);
            CalcTest("sin( 1.23 )", 0.02146590093);
            CalcTest("sin(1000 )", -0.984807753012);
        }

        [Fact]
        public void ASin()
        {
            CalcTest("asin( 1)", 90);
            CalcTest("asin(-1 )", -90);
            CalcTest("asin( 0.02146590093 )", 1.229999999975);
        }

        [Fact]
        public void Cos()
        {
            CalcTest("cos( 1)", 0.999847695156);
            CalcTest("cos( 90)", 0);
        }

        [Fact]
        public void ACos()
        {
            CalcTest("acos( 1)", 0);
            CalcTest("acos(0.5 )", 60);
        }

        [Fact]
        public void Tan()
        {
            CalcTest("tan(1)", 0.017455064928);
            CalcTest("tan(333)", -0.509525449494);
        }

        [Fact]
        public void ATan()
        {
            CalcTest("atan(1)", 45);
            CalcTest("atan(333)", 89.827941119272);
        }

        [Fact]
        public void Sqrt()
        {
            CalcTest("sqrt(1)", 1);
            CalcTest("sqrt(9)", 3);
            CalcTest("sqrt(333)", 18.2482875908946591);
        }

        [Fact]
        public void Log()
        {
            CalcTest("log(1)", 0);
            CalcTest("log(10)", 1);
            CalcTest("log(333)", 2.5224442335063197);
        }

        [Fact]
        public void Ln()
        {
            CalcTest("ln(1)", 0);
            CalcTest("ln(10)", 2.3025850929940457);
            CalcTest("ln(333)", 5.8081424899804438);
        }

        [Fact]
        public void Mod()
        {
            CalcTest("4 mod 3", 1);
            CalcTest("2 mod 2", 0);
            CalcTest("333.333 mod 7", 4.333);
            CalcTest("-333.333 mod 7", -4.333);
        }

        [Fact]
        public void XTest()
        {
            CalcXTest("x + x", 2, 4);
            CalcXTest("x / x", 2, 1);
            CalcXTest("12 / x", 2, 6);
            CalcXTest("2 ^ x", 3, 8);
        }

        [Fact]
        public void IncorrectTest()
        {
            CalcIncorrectTest("sqrt(-1)");
            CalcIncorrectTest("asin(100)");
            CalcIncorrectTest("cos(qwe)");
            CalcIncorrectTest("etgntoih");
        }

        [Fact]
        public void PriorityTest()
        {
            CalcTest("(1 + 2) / 3 - sqrt(9) * cos(60)^sin(90) + 2 ^ tan(1)", 0.5121724171600924);
        }

        public void CalcTest(string str, double result)
        {
            Assert.Equal(Model.Model.Calc(new StringBuilder(str), 0), result, EPS);
        }

        public void CalcIncorrectTest(string str)
        {
            double result = Model.Model.Calc(new StringBuilder(str), 0);
            Assert.True(!double.IsNormal(result) || Model.Model.GetError());
        }

        public void CalcXTest(string str, double X, double result)
        {
            Assert.Equal(Model.Model.Calc(new StringBuilder(str), X), result, EPS);
        }
    }
}