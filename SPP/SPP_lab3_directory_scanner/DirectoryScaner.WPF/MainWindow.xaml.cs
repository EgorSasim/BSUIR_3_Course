using DirectoryScanner.Core;
using DirectoryScanner.Core.Struct;
using Microsoft.Win32;
using Ookii.Dialogs.Wpf;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace DirectoryScaner.WPF
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public ObservableCollection<DirectoryNode> testNodes = new();
        private CancellationTokenSource _token;

        public MainWindow()
        {
            InitializeComponent();
        }

        private void InputFile_Click(object sender, RoutedEventArgs e)
        {
            VistaFolderBrowserDialog dlg = new VistaFolderBrowserDialog();

            if (dlg.ShowDialog() == true)
            {
                ((Button)sender).Tag = dlg.SelectedPath;

                treeView1.ItemsSource = testNodes;

                _token = new CancellationTokenSource();

                testNodes.Clear();
                Scanner scanner = new Scanner(4, dlg.SelectedPath, _token.Token);
                testNodes.Add(scanner.Root);
                Thread thread = new(scanner.StartProcess);
                thread.Start();
            }
        }

        private void CancelBTN_Click(object sender, RoutedEventArgs e)
        {
            _token.Cancel();
        }
    }
}
