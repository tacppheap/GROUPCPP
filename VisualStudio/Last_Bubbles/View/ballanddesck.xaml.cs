using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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
using Last_Bubbles.VM;
using System.ComponentModel;

namespace Last_Bubbles.View
{
    /// <summary>
    /// Interaction logic for ballanddesck.xaml
    /// </summary>
    public partial class ballanddesck : UserControl
    {
 
        public static DependencyProperty Desck_HeightProperty = DependencyProperty.Register("Desck_Height", typeof(int), typeof(ballanddesck), new FrameworkPropertyMetadata());
        public static DependencyProperty Desck_WidthProperty = DependencyProperty.Register("Desck_Width", typeof(int), typeof(ballanddesck), new FrameworkPropertyMetadata());

        public int Desck_Width
        {
            get { return (int)GetValue(Desck_WidthProperty); }
            set { SetValue(Desck_WidthProperty, value); }
        }
        public int Desck_Height
        {
            get { return (int)GetValue(Desck_HeightProperty); }
            set { SetValue(Desck_HeightProperty, value);  }
        }

        public ballanddesck()
        {
            InitializeComponent();
        }
        private void trystart()
        {
            if (canstart())
            {
                this.DataContext = new VM_BOARD(Desck_Height, Desck_Width);
                cmd_Start();

            }
        }
        private bool canstart()
        {

            if ((Desck_Height > 0) && (Desck_Width > 0))
                return true;
            else
                return false;
        }

        private void cmd_Start()
        {

            int board_width = (this.DataContext as VM_BOARD).NUM_COL;
            int board_height = (this.DataContext as VM_BOARD).NUM_ROW;

            for (int y = 0; y < board_height; y++)
            {
                for (int x = 0; x < board_width; x++)
                {
                    UCBALL ellipse = new UCBALL();
                    ellipse.DataContext = (this.DataContext as VM_BOARD).VM_Ball_List[board_width * y + x];
                    Binding bind = new Binding();
                    bind.Path = new PropertyPath("ball");
                    bind.Converter = new Last_Bubbles.VM.Style_Converter();
                    ellipse.SetBinding(UCBALL.Ball_StyleProperty, bind);
                    ellipse.Ball_Width = canvas.ActualWidth / board_width;
                    ellipse.Ball_Height = canvas.ActualHeight / board_height;
                    ellipse.MouseEnter += cmd_MouseOver;
                    ellipse.MouseLeave += cmd_MouseLeave;
                    ellipse.Del += cmd_del;
                    ellipse.MouseLeftButtonDown += cmd_MouseLeftButtonDown;
                    Canvas.SetLeft(ellipse, x * ellipse.Ball_Width);
                    Canvas.SetTop(ellipse, y * ellipse.Ball_Height);
                    canvas.Children.Add(ellipse);

                }
            }
        }

        private void cmd_MouseOver(object sender, RoutedEventArgs e)
        {

            UCBALL El_Source;
            El_Source = (UCBALL)sender;
            VM_BALL ball = (VM_BALL)El_Source.DataContext;
            ball.IsChecked = true;

        }

        private void cmd_MouseLeave(object sender, RoutedEventArgs e)
        {
            UCBALL El_Source;
            El_Source = (UCBALL)sender;
            VM_BALL ball = (VM_BALL)El_Source.DataContext;
            ball.IsChecked = false;
            (this.DataContext as VM_BOARD).int_score = 0;
        }

        private void cmd_MouseLeftButtonDown(object sender, RoutedEventArgs e)
        {

            UCBALL El_Source;
            El_Source = (UCBALL)sender;
            VM_BALL ball = (VM_BALL)El_Source.DataContext;
            if ((this.DataContext as VM_BOARD).board.Num_Checked_Balls.ob > 1)
                ball.IsKilled = true;
        }


        private void cmd_del(object sender, RoutedEventArgs e)
        {
            UCBALL El_Source;
            El_Source = (UCBALL)sender;
            canvas.Children.Remove(El_Source);

        }

        private void GP_Loaded(object sender, RoutedEventArgs e)
        {
            trystart();
        }
    }
}
