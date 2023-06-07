using Avalonia.Controls;
using System.Text;
using System.Diagnostics;
using Avalonia.Controls.Selection;
using System.Collections.ObjectModel;
using System.IO;

namespace Calculator;

public partial class MainWindow : Window
{
    GraphWindow _graphWindow;
    public MainWindow()
    {
        InitializeComponent();
        _graphWindow = new GraphWindow();
        DataContext = new MainWindowViewModel(this, _graphWindow);
    }

    public class MainWindowViewModel : ViewModelBase
    {
        private readonly string HistoryLogPath = Path.Combine("log", "history.log");
        private readonly string DocumentationPath = Path.Combine("Documentation", "Documentation.html");
        private Window _window;
        private string _formulaText = "";
        private string _xText = "";
        GraphWindow _graphWindow;
        private bool _showHistory = false;
        public SelectionModel<string> Selection { get; }
        public ObservableCollection<string> HistoryList { get; set; } = new();

        public string XText
        {
            get => _xText;
            set => this.RaiseAndSetIfChanged(ref _xText, value);
        }

        public string FormulaText
        {
            get => _formulaText;
            set => this.RaiseAndSetIfChanged(ref _formulaText, value);
        }

        public MainWindowViewModel(Window window, GraphWindow graphWindow)
        {
            _window = window;
            _graphWindow = graphWindow;
            Selection = new();
            Selection.SelectionChanged += SelectionChanged;
            Selection.SingleSelect = true;
            LoadHistoryLog();
        }

        public void SaveHistoryLog()
        {
            using (StreamWriter writer = new StreamWriter(HistoryLogPath, false))
            {
                foreach (var line in HistoryList)
                {
                    writer.WriteLine(line);
                }
            }
        }

        private void LoadHistoryLog()
        {
            using (StreamReader reader = new StreamReader(HistoryLogPath))
            {
                string? line;
                while ((line = reader.ReadLine()) != null)
                {
                    HistoryList.Add(line);
                }
            }
        }

        public void ClearHistory()
        {
            HistoryList.Clear();
        }

        private void SelectionChanged(object? sender, SelectionModelSelectionChangedEventArgs e)
        {
            if (e.SelectedIndexes[0] >= 0 && e.SelectedIndexes[0] < HistoryList.Count)
            {
                FormulaText = HistoryList[e.SelectedIndexes[0]];
            }
        }

        public void AddTextInEntry(string parameter)
        {
            FormulaText = FormulaText + parameter;
        }

        public void RemoveLastSymbolInEntry()
        {
            if (FormulaText.Length > 0)
                FormulaText = FormulaText[..^1];
        }

        public void RemoveTextInEntry()
        {
            FormulaText = "";
        }

        public void ShowHistory()
        {
            if (!_showHistory)
            {
                _window.MaxHeight += 200;
                _window.MinHeight += 200;
                _window.Height += 200;
                _showHistory = true;
            } 
            else
            {
                _window.MaxHeight -= 200;
                _window.MinHeight -= 200;
                _window.Height -= 200;
                _showHistory = false;
            }
        }

        public void OpenDocumentation()
        {
            var p = new Process();
            p.StartInfo = new ProcessStartInfo(DocumentationPath)
            {
                UseShellExecute = true
            };
            p.Start();
        }

        public void CreateGraph()
        {
            _graphWindow.Show();
            _graphWindow.ViewModel.DrawGraph(FormulaText);
        }

        public void OnButtonEqualsClicked()
        {
            if (string.IsNullOrWhiteSpace(FormulaText))
            {
                FormulaText = "0";
                return;
            }
            double x = 0;
            double.TryParse(XText, out x);
            StringBuilder sb = new StringBuilder(FormulaText);
            double result = Model.Model.Calc(sb, x);
            if ((result == 0 || double.IsNormal(result)) && !Model.Model.GetError())
            {
                if ((HistoryList.Count > 0 &&
                     HistoryList[0] != FormulaText) ||
                     HistoryList.Count == 0)
                {
                    HistoryList.Insert(0, FormulaText);
                }
                FormulaText = result.ToString();
            }
            else
            {
                FormulaText = "Incorrect value";
            }
        }
    }

    protected override bool HandleClosing()
    {
        if (DataContext is MainWindowViewModel viewModel)
        {
            viewModel.SaveHistoryLog();
        }
        _graphWindow.Close();
        return base.HandleClosing();
    }
}