using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Win32;

namespace Outhouse_FE
{
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            Load_Processes();
        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
        }

        private void Load_Processes()
        {
            Process[] processes = Process.GetProcesses();

            foreach (Process process in processes)
            {
                try
                {
                    ProcessListBox.Items.Add($"{process.Id} | {process.ProcessName}");
                }
                catch
                {
                    ProcessListBox.Items.Add($"Unknown Process");
                }
            }
        }

        private void BrowseButton_Click(object sender, RoutedEventArgs e)
        {
            var dialog = new OpenFolderDialog
            {
                Title = "Select output folder"
            };

            if (dialog.ShowDialog() == true)
            {
                OutputPathTextBox.Text = dialog.FolderName;
            }
        }

        private void DumpButton_Click(object sender, RoutedEventArgs e)
        {
            if (ProcessListBox.SelectedItem == null)
            {
                MessageBox.Show("Please select a process.", "No Process Selected", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            string selectedItem = ProcessListBox.SelectedItem.ToString();
            string[] parts = selectedItem.Split('|');
            if (parts.Length < 1 || !uint.TryParse(parts[0].Trim(), out uint pid))
            {
                MessageBox.Show("Invalid process selection.", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }

            string outputPath = OutputPathTextBox.Text;
            if (string.IsNullOrWhiteSpace(outputPath))
            {
                MessageBox.Show("Please select an output folder.", "No Output Folder", MessageBoxButton.OK, MessageBoxImage.Warning);
                return;
            }

            var options = new DumpOptions
            {
                handle_hijack = HandleHijackCheckBox.IsChecked == true
            };

            try
            {
                int result = DumpProcess(pid, outputPath, ref options);

                if (result == 0)
                {
                    MessageBox.Show("Process dump completed successfully!", "Success", MessageBoxButton.OK, MessageBoxImage.Information);
                }
                else
                {
                    MessageBox.Show($"Dump failed with error code: {result}", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show($"Failed to dump process: {ex.Message}", "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Unicode)]
        struct DumpOptions
        {
            [MarshalAs(UnmanagedType.I1)]
            public bool handle_hijack;
        }

        [DllImport("Outhouse.dll", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.StdCall)]
        static extern int DumpProcess(
            uint pid,
            string outputPath,
            ref DumpOptions options
        );
    }
}