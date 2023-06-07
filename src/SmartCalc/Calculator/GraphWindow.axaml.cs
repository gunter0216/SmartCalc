using Avalonia.Controls;
using System.Text;
using OxyPlot;
using System.Collections.ObjectModel;

namespace Calculator;

public partial class GraphWindow : Window
{
    public GraphWindowViewModel ViewModel;
    public GraphWindow()
    {
        InitializeComponent();
        ViewModel = new GraphWindowViewModel(this);
        DataContext = ViewModel;
    }

    public class GraphWindowViewModel : ViewModelBase
    {
        private const double DefaultXRadius= 100;
        private const double DefaultYRadius = 100;
        private const double DefaultStep = 0.1;

        private string _formula = "";
        private GraphWindow _view;

        private string _xRadiusText = "";
        private string _yRadiusText = "";
        private string _stepText = "";

        private double _minimumBottomAxes = -DefaultXRadius;
        private double _maximumBottomAxes = DefaultXRadius;
        private double _minimumLeftAxes = -DefaultYRadius;
        private double _maximumLeftAxes = DefaultYRadius;

        public double MinimumBottomAxes
        {
            get => _minimumBottomAxes;
            set => this.RaiseAndSetIfChanged(ref _minimumBottomAxes, value);
        }

        public double MaximumBottomAxes
        {
            get => _maximumBottomAxes;
            set => this.RaiseAndSetIfChanged(ref _maximumBottomAxes, value);
        }

        public double MinimumLeftAxes
        {
            get => _minimumLeftAxes;
            set => this.RaiseAndSetIfChanged(ref _minimumLeftAxes, value);
        }

        public double MaximumLeftAxes
        {
            get => _maximumLeftAxes;
            set => this.RaiseAndSetIfChanged(ref _maximumLeftAxes, value);
        }

        public ObservableCollection<DataPoint> Points { get; private set; }

        public string XRadiusText
        {
            get => _xRadiusText;
            set => this.RaiseAndSetIfChanged(ref _xRadiusText, value);
        }

        public string YRadiusText
        {
            get => _yRadiusText;
            set => this.RaiseAndSetIfChanged(ref _yRadiusText, value);
        }

        public string StepText
        {
            get => _stepText;
            set => this.RaiseAndSetIfChanged(ref _stepText, value);
        }

        public GraphWindowViewModel(GraphWindow view)
        {
            _view = view;
            Points = new ObservableCollection<DataPoint>();
        }
        
        public void DrawGraph()
        {
            DrawGraph(_formula);
        }

        public void DrawGraph(string formula)
        {
            Points.Clear();

            _formula = formula;

            double XRadius;
            double YRadius;
            double Step;
            if (!double.TryParse(XRadiusText, out XRadius))
                XRadius = DefaultXRadius;
            if (!double.TryParse(YRadiusText, out YRadius))
                YRadius = DefaultYRadius;
            if (!double.TryParse(StepText, out Step))
                Step = DefaultStep;

            MinimumBottomAxes = -XRadius;
            MaximumBottomAxes = XRadius;
            MinimumLeftAxes = -YRadius;
            MaximumLeftAxes = YRadius;

            StringBuilder stringBuilder = new StringBuilder(formula);
            Model.Model.Calc(stringBuilder, 0);

            for (double curStep = -XRadius; curStep < XRadius; curStep += Step)
            {
                double result = Model.Model.LastCalc(curStep);
                if (result != 0 && !double.IsNormal(result) ||
                    result > YRadius || result < -YRadius)
                {
                    Points.Add(new DataPoint(double.NaN, double.NaN));
                } 
                else
                {
                    Points.Add(new DataPoint(curStep, result));
                }
            }
            _view.plot.InvalidatePlot(true);
        }
    }

    protected override bool HandleClosing()
    {
        this.Hide();
        return true;
    }
}